#include "modAlphaCipher.h"
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

modAlphaCipher::modAlphaCipher(int k)
{
    if (!isValidKey(k)) {
        throw invalid_argument("Неверный ключ. Ключ должен быть положительным числом.");
    }
    key = k;
}

string modAlphaCipher::encrypt(const string& plain_text)
{
    // Текст уже без пробелов, проверяем только на пустоту
    if (plain_text.empty()) {
        return "";
    }
    
    // Проверяем и преобразуем в верхний регистр
    string upper_text;
    for (char c : plain_text) {
        if (isalpha(c)) {
            // Проверяем, что символ английский
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                upper_text += toupper(c);
            } else {
                throw invalid_argument("Текст содержит неанглийские символы. Разрешены только буквы английского алфавита.");
            }
        } else {
            throw invalid_argument("Текст содержит небуквенные символы. Разрешены только буквы английского алфавита.");
        }
    }
    
    string text = upper_text;
    
    // Определяем количество строк
    size_t text_len = text.length();
    size_t rows = (text_len + key - 1) / key;
    
    // Создаем таблицу
    vector<vector<char>> table(rows, vector<char>(key, ' '));
    
    // ЗАПИСЬ: по горизонтали слева направо, сверху вниз
    size_t pos = 0;
    for (size_t i = 0; i < rows; i++) {
        for (int j = 0; j < key; j++) {
            if (pos < text_len) {
                table[i][j] = text[pos++];
            }
        }
    }
    
    // ЧТЕНИЕ: сверху вниз, справа налево
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

string modAlphaCipher::decrypt(const string& cipher_text)
{
    // Текст уже без пробелов, проверяем только на пустоту
    if (cipher_text.empty()) {
        return "";
    }
    
    // Проверяем и преобразуем в верхний регистр
    string upper_text;
    for (char c : cipher_text) {
        if (isalpha(c)) {
            // Проверяем, что символ английский
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                upper_text += toupper(c);
            } else {
                throw invalid_argument("Текст содержит неанглийские символы. Разрешены только буквы английского алфавита.");
            }
        } else {
            throw invalid_argument("Текст содержит небуквенные символы. Разрешены только буквы английского алфавита.");
        }
    }
    
    string text = upper_text;
    
    // Определяем количество строк
    size_t text_len = text.length();
    size_t rows = (text_len + key - 1) / key;
    
    // Создаем таблицу для зашифрованного текста
    vector<vector<char>> table(rows, vector<char>(key, ' '));
    
    // Запись зашифрованного текста: сверху вниз, справа налево
    size_t pos = 0;
    for (int j = key - 1; j >= 0; j--) {
        for (size_t i = 0; i < rows; i++) {
            if (pos < text_len) {
                table[i][j] = text[pos++];
            }
        }
    }
    
    // Считывание исходного текста: по горизонтали слева направо, сверху вниз
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

bool modAlphaCipher::isValidKey(int key)
{
    return key > 0;
}

void modAlphaCipher::setKey(int k)
{
    if (!isValidKey(k)) {
        throw invalid_argument("Неверный ключ. Ключ должен быть положительным числом.");
    }
    key = k;
}

int modAlphaCipher::getKey() const
{
    return key;
}
