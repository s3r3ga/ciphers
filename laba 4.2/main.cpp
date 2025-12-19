/**
 * @file main.cpp
 * @brief Главный файл программы шифрования методом маршрутной перестановки
 * @details Содержит пользовательский интерфейс для работы с шифром
 * @version 1.0
 * @date 2025
 * @author Ходжаев С.А.
 */

#include <iostream>
#include <string>
#include <locale>
#include <limits>
#include <algorithm>
#include "modAlphaCipher.h"

using namespace std;

/**
 * @brief Удаляет пробелы из строки
 * @param str Входная строка
 * @return Строка без пробелов
 * 
 * Функция использует алгоритм remove-erase для удаления всех пробелов из строки.
 */
string removeSpaces(const string& str) {
    string result = str;
    result.erase(remove(result.begin(), result.end(), ' '), result.end());
    return result;
}

/**
 * @brief Главная функция программы
 * @return Код завершения (0 - успешно, 1 - ошибка)
 * 
 * Программа предоставляет интерактивный интерфейс для:
 * 1. Ввода ключа (положительного числа)
 * 2. Выбора операции (шифрование/дешифрование/выход)
 * 3. Ввода текста для обработки
 * 4. Вывода результатов
 * 
 * @note Программа работает только с английским алфавитом
 * @warning Ключ должен быть положительным числом
 */
int main() {

    int key;           ///< Ключ шифрования (количество столбцов)
    string text;       ///< Текст для обработки
    int operation;     ///< Выбранная операция
    
    cout << "Шифратор готов к работе!" << endl;
    
    // Ввод ключа
    while (true) {
        cout << "Введите ключ (положительное число): ";
        cin >> key;
        
        if (cin.fail()) {
            // Если ввод не удался (буква вместо числа)
            cin.clear(); // Сбрасываем флаг ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем буфер
            cout << "Ошибка: Ключ должен быть числом!" << endl;
        } else if (key <= 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем буфер
            cout << "Ошибка: Ключ должен быть положительным числом!" << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем буфер
            break;
        }
    }
    
    try {
        // Создаем объект шифратора
        modAlphaCipher cipher(key);
        cout << "Создан шифратор с ключом: " << cipher.getKey() << endl;
        
        // Главный цикл программы
        do {
            cout << "\nВыберите операцию:" << endl;
            cout << "1 - Зашифровать текст" << endl;
            cout << "2 - Расшифровать текст" << endl;
            cout << "0 - Выход" << endl;
            cout << "Ваш выбор: ";
            cin >> operation;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                operation = -1; // Устанавливаем неверную операцию
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            
            if (operation == 1 || operation == 2) {
                cout << "Введите текст(только на английском): ";
                getline(cin, text);
                
                // Удаляем пробелы из введенного текста
                string textWithoutSpaces = removeSpaces(text);
                cout << "Текст без пробелов: " << textWithoutSpaces << endl;
                
                try {
                    if (operation == 1) {
                        // Шифрование
                        string encrypted = cipher.encrypt(textWithoutSpaces);
                        cout << "Зашифрованный текст: " << encrypted << endl;
                    } else {
                        // Дешифрование
                        string decrypted = cipher.decrypt(textWithoutSpaces);
                        cout << "Расшифрованный текст: " << decrypted << endl;
                    }
                } catch (const exception& e) {
                    cout << "Ошибка при обработке: " << e.what() << endl;
                }
            } else if (operation != 0) {
                cout << "Неверная операция! Попробуйте снова." << endl;
            }
            
        } while (operation != 0);
        
        cout << "Выход из программы." << endl;
        
    } catch (const exception& e) {
        cout << "Ошибка инициализации: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
