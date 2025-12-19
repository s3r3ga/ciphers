#include "modAlphaCipher.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cctype>
using namespace std;

modAlphaCipher::modAlphaCipher(const wstring& key_value)
{
    // Проверка наличия ключа
    if (key_value.empty()) {
        throw invalid_argument("Пустой ключ недопустим");
    }
    
    // Проверка на пробелы в ключе
    if (key_value.find(L' ') != wstring::npos) {
        throw invalid_argument("Ключ не должен содержать пробелы");
    }
    
    // Проверка на знаки препинания и цифры в ключе
    wstring invalid_chars = L",.!?;:'\"-()0123456789";
    for (wchar_t c : key_value) {
        if (invalid_chars.find(c) != wstring::npos) {
            throw invalid_argument("Ключ не должен содержать цифры или знаки препинания");
        }
    }
    
    // Проверка на однородность ключа (вырожденный ключ)
    bool all_same = true;
    if (key_value.length() > 1) {
        wchar_t first_char = toupper(key_value[0], locale("ru_RU.UTF-8"));
        for (size_t i = 1; i < key_value.length(); ++i) {
            if (toupper(key_value[i], locale("ru_RU.UTF-8")) != first_char) {
                all_same = false;
                break;
            }
        }
        if (all_same) {
            throw invalid_argument("Вырожденный ключ (все символы одинаковые)");
        }
    }
    
    // Инициализация ассоциативного массива alphaNum
    for (size_t index = 0; index < numAlpha.size(); index++) {
        alphaNum[numAlpha[index]] = index;
    }
    
    // Преобразование ключа к верхнему регистру и валидация
    wstring upper_key = to_upper(key_value);
    if (!isValid(upper_key)) {
        throw invalid_argument("Ключ содержит недопустимые символы");
    }
    
    try {
        key = convert(upper_key);
    } catch (const exception& e) {
        throw invalid_argument("Некорректный ключ: " + string(e.what()));
    }
}

wstring modAlphaCipher::encrypt(const wstring& plain_text)
{
    // Проверка входного текста
    if (plain_text.empty()) {
        throw invalid_argument("Пустой текст не может быть зашифрован");
    }
    
    // Проверка, содержит ли текст хотя бы одну букву
    bool has_alpha = false;
    wstring russian_letters = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    for (wchar_t c : plain_text) {
        if (russian_letters.find(c) != wstring::npos) {
            has_alpha = true;
            break;
        }
    }
    
    if (!has_alpha) {
        throw invalid_argument("Текст не содержит букв");
    }
    
    // Преобразование текста: удаляем всё кроме букв, строчные -> прописные
    wstring text = to_upper(plain_text);
    
    // После преобразования проверяем что остались буквы
    if (text.empty()) {
        throw invalid_argument("После удаления не-букв текст стал пустым");
    }
    
    try {
        vector<int> processed = convert(text);
        for (size_t pos = 0; pos < processed.size(); pos++) {
            processed[pos] = (processed[pos] + key[pos % key.size()]) % numAlpha.size();
        }
        return convert(processed);
    } catch (const exception& e) {
        throw runtime_error("Сбой при шифровании: " + string(e.what()));
    }
}

wstring modAlphaCipher::decrypt(const wstring& encrypted_text)
{
    // Проверка входного текста
    if (encrypted_text.empty()) {
        throw invalid_argument("Пустой текст не может быть дешифрован");
    }
    
    // Для шифротекста проверяем строго - только прописные русские буквы
    if (!isValid(encrypted_text)) {
        throw invalid_argument("Шифротекст содержит недопустимые символы");
    }
    
    try {
        vector<int> processed = convert(encrypted_text);
        for (size_t pos = 0; pos < processed.size(); pos++) {
            processed[pos] = (processed[pos] + numAlpha.size() - key[pos % key.size()]) % numAlpha.size();
        }
        return convert(processed);
    } catch (const exception& e) {
        throw runtime_error("Сбой при дешифровке: " + string(e.what()));
    }
}

vector<int> modAlphaCipher::convert(const wstring& input_str)
{
    vector<int> output;
    for (auto ch : input_str) {
        if (alphaNum.find(ch) == alphaNum.end()) {
            // Преобразуем символ в строку для сообщения об ошибке
            char buf[MB_CUR_MAX];
            wctomb(buf, ch);
            throw invalid_argument("Найден некорректный символ: '" + string(buf) + "'");
        }
        output.push_back(alphaNum[ch]);
    }
    return output;
}

wstring modAlphaCipher::convert(const vector<int>& input_vec)
{
    wstring output;
    for (auto val : input_vec) {
        if (val < 0 || val >= static_cast<int>(numAlpha.size())) {
            throw out_of_range("Неверный индекс символа: " + to_string(val));
        }
        output.push_back(numAlpha[val]);
    }
    return output;
}

wstring modAlphaCipher::to_upper(const wstring& s)
{
    wstring result;
    wstring lower = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    wstring upper = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    
    for (wchar_t c : s) {
        // Преобразуем строчные в прописные
        size_t pos = lower.find(c);
        if (pos != wstring::npos) {
            result += upper[pos];
        }
        // Прописные оставляем как есть
        else if (upper.find(c) != wstring::npos) {
            result += c;
        }
        // Пробелы, знаки препинания, цифры - пропускаем (удаляем)
        // Если это русская буква в любом регистре, она уже обработана выше
        // Все остальные символы игнорируем
    }
    
    return result;
}

bool modAlphaCipher::isValid(const wstring& s)
{
    // Проверяем что все символы - прописные русские буквы
    for (wchar_t c : s) {
        bool is_russian_upper = false;
        for (wchar_t ru : numAlpha) {
            if (c == ru) {
                is_russian_upper = true;
                break;
            }
        }
        if (!is_russian_upper) {
            return false;
        }
    }
    return true;
}

// Дополнительный метод для проверки открытого текста (можно добавить в .h если нужно)
bool modAlphaCipher::isValidText(const wstring& s)
{
    wstring valid_chars = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ ,.!?;:'\"-()0123456789";
    
    for (wchar_t c : s) {
        if (valid_chars.find(c) == wstring::npos) {
            return false;
        }
    }
    return true;
}
