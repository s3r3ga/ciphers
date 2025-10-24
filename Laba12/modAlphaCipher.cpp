#include "modAlphaCipher.h"
#include <vector>
#include <algorithm>
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
    string text = removeSpaces(plain_text);
    
    if (text.empty()) {
        return "";
    }
    
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
    
    // сверху вниз, справа налево
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
    string text = removeSpaces(cipher_text);
    
    if (text.empty()) {
        return "";
    }
    
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

string modAlphaCipher::removeSpaces(const string& text)
{
    string result;
    for (char c : text) {
        if (c != ' ') {
            result += c;
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