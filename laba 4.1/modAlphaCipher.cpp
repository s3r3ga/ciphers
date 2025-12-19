/**
 * @file modAlphaCipher.cpp
 * @brief Реализация класса modAlphaCipher
 * @details Содержит реализацию методов шифрования Гронсвельда
 */

#include "modAlphaCipher.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>

/**
 * @brief Конструктор класса modAlphaCipher
 * @param skey Ключ шифрования в виде строки
 * @throw std::invalid_argument если ключ содержит недопустимые символы
 * 
 * Конструктор инициализирует алфавит, создает карту символов,
 * проверяет и преобразует ключ, затем сохраняет его в числовом виде.
 */
modAlphaCipher::modAlphaCipher(const std::wstring& skey)
{
    // Инициализируем алфавит и создаем карту символов
    for (size_t i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    
    std::wstring upper_key = to_upper(skey);
    if (!isValid(upper_key)) {
        throw std::invalid_argument("Ключ содержит недопустимые символы");
    }
    
    key = convert(upper_key);
}

/**
 * @brief Шифрует открытый текст
 * @param open_text Текст для шифрования
 * @return Зашифрованная строка
 * @throw std::invalid_argument если текст содержит недопустимые символы
 * 
 * Алгоритм шифрования:
 * 1. Преобразование текста в верхний регистр
 * 2. Проверка валидности символов
 * 3. Преобразование текста в числовой вид
 * 4. Применение шифра Гронсвельда (сдвиг на величину ключа)
 * 5. Преобразование результата обратно в строку
 */
std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    std::wstring text = to_upper(open_text);
    if (!isValid(text)) {
        throw std::invalid_argument("Текст содержит недопустимые символы");
    }
    
    std::vector<int> work = convert(text);
    for (size_t i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % numAlpha.size();
    }
    return convert(work);
}

/**
 * @brief Дешифрует зашифрованный текст
 * @param cipher_text Текст для дешифрования
 * @return Расшифрованная строка
 * @throw std::invalid_argument если текст содержит недопустимые символы
 * 
 * Алгоритм дешифрования является обратным к алгоритму шифрования:
 * 1. Преобразование текста в верхний регистр
 * 2. Проверка валидности символов
 * 3. Преобразование текста в числовой вид
 * 4. Обратный сдвиг на величину ключа
 * 5. Преобразование результата обратно в строку
 */
std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    std::wstring text = to_upper(cipher_text);
    if (!isValid(text)) {
        throw std::invalid_argument("Текст содержит недопустимые символы");
    }
    
    std::vector<int> work = convert(text);
    for (size_t i = 0; i < work.size(); i++) {
        work[i] = (work[i] + numAlpha.size() - key[i % key.size()]) % numAlpha.size();
    }
    return convert(work);
}

/**
 * @brief Преобразует строку в вектор числовых значений
 * @param s Входная строка для преобразования
 * @return Вектор целых чисел, соответствующих символам строки
 * @throw std::invalid_argument если строка содержит недопустимые символы
 */
std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for (wchar_t c : s) {
        if (alphaNum.find(c) == alphaNum.end()) {
            throw std::invalid_argument("Недопустимый символ в тексте");
        }
        result.push_back(alphaNum[c]);
    }
    return result;
}

/**
 * @brief Преобразует вектор числовых значений в строку
 * @param v Вектор целых чисел для преобразования
 * @return Строка, соответствующая вектору чисел
 * @throw std::out_of_range если индекс выходит за границы алфавита
 */
std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for (int i : v) {
        if (i < 0 || i >= static_cast<int>(numAlpha.size())) {
            throw std::out_of_range("Индекс выходит за границы алфавита");
        }
        result += numAlpha[i];
    }
    return result;
}

/**
 * @brief Преобразует строку к верхнему регистру и удаляет пробелы
 * @param s Входная строка для преобразования
 * @return Строка в верхнем регистре без пробелов
 */
std::wstring modAlphaCipher::to_upper(const std::wstring& s)
{
    std::wstring result = s;
    std::wstring lower = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    std::wstring upper = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    
    for (size_t i = 0; i < result.size(); i++) {
        size_t pos = lower.find(result[i]);
        if (pos != std::wstring::npos) {
            result[i] = upper[pos];
        }
    }
    
    // Удаляем пробелы из результата
    result.erase(std::remove(result.begin(), result.end(), L' '), result.end());
    
    return result;
}

/**
 * @brief Проверяет валидность строки
 * @param s Строка для проверки
 * @return true если строка содержит только русские буквы, false в противном случае
 */
bool modAlphaCipher::isValid(const std::wstring& s)
{
    for (wchar_t c : s) {
        if (alphaNum.find(c) == alphaNum.end()) {
            return false;
        }
    }
    return true;
}
