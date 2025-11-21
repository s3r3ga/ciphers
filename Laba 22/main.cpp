#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <algorithm>
#include "modAlphaCipher.h"

// Функция для удаления пробелов из строки
std::wstring remove_spaces(const std::wstring& str) {
    std::wstring result = str;
    result.erase(std::remove(result.begin(), result.end(), L' '), result.end());
    return result;
}
int main()
{
    // Устанавливаем локаль
    try {
        std::locale::global(std::locale("ru_RU.UTF-8"));
    } catch (const std::exception& e) {
        std::cout << "Не удалось установить локаль: " << e.what() << std::endl;
        std::cout << "Продолжаем без локали..." << std::endl;
    }
    std::wcout.imbue(std::locale());
    std::wcin.imbue(std::locale());
    std::wstring key;
    std::wstring text;
    int op;
    std::wcout << L"Шифратор готов. Введите ключ (только русские буквы): ";
    std::getline(std::wcin, key);
    // Удаляем пробелы из ключа
    key = remove_spaces(key);
    try {
        modAlphaCipher cipher(key);
        std::wcout << L"Ключ загружен успешно." << std::endl;
        do {
            std::wcout << L"\nВыберите операцию (0-выход, 1-зашифровать, 2-расшифровать): ";
            std::wcin >> op;
            std::wcin.ignore(); // Очищаем буфер
            if (op > 2) {
                std::wcout << L"Неверная операция!" << std::endl;
            } else if (op > 0) {
                std::wcout << L"Введите текст (только русские буквы): ";
                std::getline(std::wcin, text);
                // Удаляем пробелы из текста
                text = remove_spaces(text);
                try {
                    if (op == 1) {
                        std::wstring encrypted = cipher.encrypt(text);
                        std::wcout << L"Зашифрованный текст: " << encrypted << std::endl;
                    } else {
                        std::wstring decrypted = cipher.decrypt(text);
                        std::wcout << L"Расшифрованный текст: " << decrypted << std::endl;
                    }
                } catch (const std::exception& e) {
                    std::wcout << L"Ошибка при обработке: " << e.what() << std::endl;
                }
            }
        } while (op != 0);
    } catch (const std::exception& e) {
        std::wcout << L"Ошибка инициализации: " << e.what() << std::endl;
        std::wcout << L"Пожалуйста, используйте только русские буквы." << std::endl;
        return 1;
    }
    std::wcout << L"Выход из программы." << std::endl;
    return 0;
}