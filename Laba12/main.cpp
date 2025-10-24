#include <iostream>
#include <string>
#include <locale>
#include "modAlphaCipher.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    try {
        modAlphaCipher cipher(3);
        cout << "Создан шифратор с ключом: " << cipher.getKey() << endl;
        
        string test_text = "КОДИРОВКА";
        cout << "Исходный текст: " << test_text << endl;
        
        string encrypted = cipher.encrypt(test_text);
        cout << "Зашифрованный текст: " << encrypted << endl;
        
        string decrypted = cipher.decrypt(encrypted);
        cout << "Расшифрованный текст: " << decrypted << endl;
        
        if (test_text == decrypted) {
            cout << "ТЕСТ ПРОЙДЕН: Исходный и расшифрованный текст совпадают!" << endl;
        } else {
            cout << "ТЕСТ НЕ ПРОЙДЕН: Тексты не совпадают!" << endl;
            return 1;
        }
        
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}