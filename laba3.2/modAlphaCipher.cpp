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
    if (cipher_text.empty()) {
        return "";
    }
    
    // Проверяем и преобразуем в верхний регистр
    string text;
    for (char c : cipher_text) {
        if (isalpha(c)) {
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                text += toupper(c);
            } else {
                throw invalid_argument("Текст содержит неанглийские символы.");
            }
        } else {
            throw invalid_argument("Текст содержит небуквенные символы.");
        }
    }
    
    size_t len = text.length();
    size_t rows = (len + key - 1) / key;
    
    // Создаем пустую таблицу
    vector<vector<char>> table(rows, vector<char>(key, ' '));
    
    // Заполняем таблицу маркерными символами для отслеживания заполненных ячеек
    size_t total_cells = rows * key;
    size_t empty_cells = total_cells - len;
    
    // Помечаем пустые ячейки в конце таблицы (последние строки последних столбцов)
    for (size_t i = 0; i < empty_cells; i++) {
        size_t col = key - 1 - i;
        table[rows - 1][col] = '\0'; // Маркер пустой ячейки
    }
    
    // Записываем шифротекст в таблицу справа налево сверху вниз,
    // пропуская маркерные ячейки
    size_t pos = 0;
    for (int col = key - 1; col >= 0; col--) {
        for (size_t row = 0; row < rows; row++) {
            if (table[row][col] != '\0') { // Если ячейка не маркерная
                if (pos < len) {
                    table[row][col] = text[pos++];
                }
            }
        }
    }
    
    // Читаем исходный текст слева направо сверху вниз
    string result;
    for (size_t row = 0; row < rows; row++) {
        for (int col = 0; col < key; col++) {
            if (table[row][col] != '\0' && table[row][col] != ' ') {
                result += table[row][col];
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
