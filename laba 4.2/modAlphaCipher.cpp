/**
 * @file modAlphaCipher.cpp
 * @brief Реализация класса шифра маршрутной перестановки
 */

#include "modAlphaCipher.h"
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

/**
 * @brief Конструктор класса
 * @param k Ключ шифрования
 * @throw std::invalid_argument если ключ невалидный
 */
modAlphaCipher::modAlphaCipher(int k)
{
    if (!isValidKey(k)) {
        throw invalid_argument("Неверный ключ. Ключ должен быть положительным числом.");
    }
    key = k;
}

/**
 * @brief Шифрует текст методом маршрутной перестановки
 * @param plain_text Текст для шифрования
 * @return Зашифрованная строка
 * @details Алгоритм:
 * 1. Проверка и преобразование текста
 * 2. Запись текста в таблицу по строкам
 * 3. Чтение таблицы по столбцам справа налево
 */
string modAlphaCipher::encrypt(const string& plain_text)
{
    if (plain_text.empty()) {
        return "";
    }
    
    // Проверяем и преобразуем в верхний регистр
    string upper_text;
    for (char c : plain_text) {
        if (isalpha(c)) {
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                upper_text += toupper(c);
            } else {
                throw invalid_argument("Текст содержит неанглийские символы.");
            }
        } else {
            throw invalid_argument("Текст содержит небуквенные символы.");
        }
    }
    
    string text = upper_text;
    size_t text_len = text.length();
    size_t rows = (text_len + key - 1) / key;
    
    // Создаем таблицу
    vector<vector<char>> table(rows, vector<char>(key, ' '));
    
    // Запись по строкам
    size_t pos = 0;
    for (size_t i = 0; i < rows; i++) {
        for (int j = 0; j < key; j++) {
            if (pos < text_len) {
                table[i][j] = text[pos++];
            }
        }
    }
    
    // Чтение по столбцам справа налево
    string result;
    for (int j = key - 1; j >= 0; j--) {
        for (size_t i = 0; i < rows; i++) {
            if (table[i][j] != ' ') {
                result += table[i][j];
            }
        }
    }
    
    return result;
}

/**
 * @brief Дешифрует текст методом маршрутной перестановки
 * @param cipher_text Текст для дешифрования
 * @return Расшифрованная строка
 * @details Алгоритм обратен шифрованию:
 * 1. Проверка и преобразование текста
 * 2. Запись текста в таблицу по столбцам справа налево
 * 3. Чтение таблицы по строкам
 */
string modAlphaCipher::decrypt(const string& cipher_text)
{
    if (cipher_text.empty()) {
        return "";
    }
    
    // Проверяем и преобразуем в верхний регистр
    string upper_text;
    for (char c : cipher_text) {
        if (isalpha(c)) {
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                upper_text += toupper(c);
            } else {
                throw invalid_argument("Текст содержит неанглийские символы.");
            }
        } else {
            throw invalid_argument("Текст содержит небуквенные символы.");
        }
    }
    
    string text = upper_text;
    size_t text_len = text.length();
    size_t rows = (text_len + key - 1) / key;
    
    // Создаем таблицу
    vector<vector<char>> table(rows, vector<char>(key, ' '));
    
    // Запись по столбцам справа налево
    size_t pos = 0;
    for (int j = key - 1; j >= 0; j--) {
        for (size_t i = 0; i < rows; i++) {
            if (pos < text_len) {
                table[i][j] = text[pos++];
            }
        }
    }
    
    // Чтение по строкам
    string result;
    for (size_t i = 0; i < rows; i++) {
        for (int j = 0; j < key; j++) {
            if (table[i][j] != ' ') {
                result += table[i][j];
            }
        }
    }
    
    return result;
}

/**
 * @brief Проверяет валидность ключа
 * @param key Ключ для проверки
 * @return true если ключ положительный
 */
bool modAlphaCipher::isValidKey(int key)
{
    return key > 0;
}

/**
 * @brief Устанавливает новый ключ
 * @param k Новый ключ
 * @throw std::invalid_argument если ключ невалидный
 */
void modAlphaCipher::setKey(int k)
{
    if (!isValidKey(k)) {
        throw invalid_argument("Неверный ключ. Ключ должен быть положительным числом.");
    }
    key = k;
}

/**
 * @brief Возвращает текущий ключ
 * @return Текущий ключ
 */
int modAlphaCipher::getKey() const
{
    return key;
}
