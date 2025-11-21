#include "modAlphaCipher.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>
using namespace std;
modAlphaCipher::modAlphaCipher(const wstring& key_value)
{
    // Проверка наличия ключа
    if (key_value.empty()) {
        throw invalid_argument("Пустой ключ недопустим");
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
    // Преобразование текста к верхнему регистру и валидация
    wstring text = to_upper(plain_text);
    if (!isValid(text)) {
        throw invalid_argument("Текст содержит недопустимые символы");
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
    // Преобразование текста к верхнему регистру и валидация
    wstring text = to_upper(encrypted_text);
    if (!isValid(text)) {
        throw invalid_argument("Текст содержит недопустимые символы");
    }
    try {
        vector<int> processed = convert(text);
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
            throw invalid_argument("Найден некорректный символ: '" + string(1, static_cast<char>(ch)) + "'");
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
    wstring result = s;
    wstring lower = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    wstring upper = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    for (size_t i = 0; i < result.size(); i++) {
        size_t pos = lower.find(result[i]);
        if (pos != wstring::npos) {
            result[i] = upper[pos];
        }
    }
    // Удаляем пробелы из результата
    result.erase(remove(result.begin(), result.end(), L' '), result.end());
    return result;
}
bool modAlphaCipher::isValid(const wstring& s)
{
    for (wchar_t c : s) {
        if (alphaNum.find(c) == alphaNum.end()) {
            return false;
        }
    }
    return true;
}