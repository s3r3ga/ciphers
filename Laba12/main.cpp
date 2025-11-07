#include <iostream>
#include <string>
#include <locale>
#include <limits>
#include <algorithm>
#include "modAlphaCipher.h"

using namespace std;

// Функция для удаления пробелов из строки
string removeSpaces(const string& str) {
    string result = str;
    result.erase(remove(result.begin(), result.end(), ' '), result.end());
    return result;
}

int main() {

    int key;
    string text;
    int operation;
    
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
        modAlphaCipher cipher(key);
        cout << "Создан шифратор с ключом: " << cipher.getKey() << endl;
        
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
                        string encrypted = cipher.encrypt(textWithoutSpaces);
                        cout << "Зашифрованный текст: " << encrypted << endl;
                    } else {
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
