// test_cipher.cpp - модульные тесты для шифра
#include "modAlphaCipher.h"
#include <iostream>
#include <locale>
#include <exception>
#include <string>

// Простой тестовый фреймворк
void run_test(const std::string& name, bool (*test_func)()) {
    std::cout << "Тест: " << name << " ... ";
    try {
        if (test_func()) {
            std::cout << "\033[32mOK\033[0m\n";
        } else {
            std::cout << "\033[31mFAIL\033[0m\n";
        }
    } catch (const std::exception& e) {
        std::cout << "\033[31mFAIL (исключение: " << e.what() << ")\033[0m\n";
    } catch (...) {
        std::cout << "\033[31mFAIL (неизвестное исключение)\033[0m\n";
    }
}

// ========== ТЕСТЫ ИЗ ТАБЛИЦЫ 1 (Конструктор) ==========

bool test_1_1_valid_key() {
    modAlphaCipher cipher(L"БВГ");
    return true;
}

bool test_1_2_long_key() {
    modAlphaCipher cipher(L"БВГДЕЁЖЗИЙ");
    return true;
}

bool test_1_3_lowercase_key() {
    modAlphaCipher cipher(L"бвг");
    return true;
}

bool test_1_4_key_with_digits() {
    try {
        modAlphaCipher cipher(L"Б1");
        return false;
    } catch (const std::invalid_argument&) {
        return true;
    }
}

bool test_1_5_key_with_punctuation() {
    try {
        modAlphaCipher cipher(L"Б,В");
        return false;
    } catch (const std::invalid_argument&) {
        return true;
    }
}

bool test_1_6_key_with_spaces() {
    try {
        modAlphaCipher cipher(L"Б В");
        return false;
    } catch (const std::invalid_argument&) {
        return true;
    }
}

bool test_1_7_empty_key() {
    try {
        modAlphaCipher cipher(L"");
        return false;
    } catch (const std::invalid_argument&) {
        return true;
    }
}

bool test_1_8_degenerate_key() {
    try {
        modAlphaCipher cipher(L"ААА");
        return false;
    } catch (const std::invalid_argument&) {
        return true;
    }
}

// ========== ТЕСТЫ ИЗ ТАБЛИЦЫ 2 (Метод encrypt) ==========

bool test_2_1_uppercase_string() {
    modAlphaCipher cipher(L"Б");
    return cipher.encrypt(L"ПРИВЕТМИР") == L"РСЙГЁУНЙС";
}

bool test_2_2_lowercase_string() {
    modAlphaCipher cipher(L"Б");
    return cipher.encrypt(L"приветмир") == L"РСЙГЁУНЙС";
}

bool test_2_3_string_with_spaces_and_punctuation() {
    modAlphaCipher cipher(L"Б");
    return cipher.encrypt(L"Привет, Мир!!!") == L"РСЙГЁУНЙС";
}

bool test_2_4_string_with_numbers() {
    modAlphaCipher cipher(L"Б");
    std::wstring result = cipher.encrypt(L"С Новым 2025 Годом");
    // Проверяем что цифры удалены
    return result.find(L'2') == std::wstring::npos &&
           result.find(L'0') == std::wstring::npos &&
           result.find(L'5') == std::wstring::npos;
}

bool test_2_5_empty_text() {
    modAlphaCipher cipher(L"Б");
    try {
        cipher.encrypt(L"");
        return false;
    } catch (const std::invalid_argument&) {
        return true;
    }
}

bool test_2_6_no_alpha_string() {
    modAlphaCipher cipher(L"Б");
    try {
        cipher.encrypt(L"1234+8765=9999");
        return false;
    } catch (const std::invalid_argument&) {
        return true;
    }
}

bool test_2_7_max_shift_key() {
    try {
        modAlphaCipher cipher(L"Я");
        std::wstring result = cipher.encrypt(L"АБВГД");
        
        // Правильный результат для ключа "Я" (сдвиг на 32 позиции назад)
        // А(0) + Я(32) = 32 % 33 = 32 -> Я
        // Б(1) + Я(32) = 33 % 33 = 0 -> А
        // В(2) + Я(32) = 34 % 33 = 1 -> Б
        // Г(3) + Я(32) = 35 % 33 = 2 -> В
        // Д(4) + Я(32) = 36 % 33 = 3 -> Г
        // Ожидаемый результат: ЯАБВГ
        
        std::wstring expected = L"ЯАБВГ";
        
        if (result != expected) {
            // Выводим отладочную информацию
            std::wcout << L"Отладка test_2_7:" << std::endl;
            std::wcout << L"  Вход: АБВГД" << std::endl;
            std::wcout << L"  Ключ: Я" << std::endl;
            std::wcout << L"  Получено: " << result << std::endl;
            std::wcout << L"  Ожидалось: " << expected << std::endl;
            
            // Выводим коды символов
            std::wcout << L"  Коды полученных символов: ";
            for (wchar_t c : result) {
                std::wcout << (int)c << L" ";
            }
            std::wcout << std::endl;
            
            std::wcout << L"  Коды ожидаемых символов: ";
            for (wchar_t c : expected) {
                std::wcout << (int)c << L" ";
            }
            std::wcout << std::endl;
        }
        
        return result == expected;
    } catch (const std::exception& e) {
        std::cout << "Исключение в test_2_7: " << e.what() << std::endl;
        return false;
    }
}

// ========== ТЕСТЫ ИЗ ТАБЛИЦЫ 3 (Метод decrypt) ==========

bool test_3_1_uppercase_string() {
    modAlphaCipher cipher(L"Б");
    return cipher.decrypt(L"РСЙГЁУНЙС") == L"ПРИВЕТМИР";
}

bool test_3_2_lowercase_in_ciphertext() {
    modAlphaCipher cipher(L"Б");
    try {
        cipher.decrypt(L"рсйгёунйс");
        return false;
    } catch (const std::invalid_argument&) {
        return true;
    }
}

bool test_3_3_spaces_in_ciphertext() {
    modAlphaCipher cipher(L"Б");
    try {
        cipher.decrypt(L"РСЙ ГЁУ НЙС");
        return false;
    } catch (const std::invalid_argument&) {
        return true;
    }
}

bool test_3_4_digits_in_ciphertext() {
    modAlphaCipher cipher(L"Б");
    try {
        cipher.decrypt(L"РС2025ЙГЁУ");
        return false;
    } catch (const std::invalid_argument&) {
        return true;
    }
}

bool test_3_5_punctuation_in_ciphertext() {
    modAlphaCipher cipher(L"Б");
    try {
        cipher.decrypt(L"РСЙГЁ,УНЙС");
        return false;
    } catch (const std::invalid_argument&) {
        return true;
    }
}

bool test_3_6_empty_ciphertext() {
    modAlphaCipher cipher(L"Б");
    try {
        cipher.decrypt(L"");
        return false;
    } catch (const std::invalid_argument&) {
        return true;
    }
}

bool test_3_7_max_shift_key() {
    try {
        modAlphaCipher cipher(L"Я");
        std::wstring result = cipher.decrypt(L"ЯАБВГ");
        
        // Ожидаемый результат: АБВГД
        std::wstring expected = L"АБВГД";
        
        if (result != expected) {
            // Выводим отладочную информацию
            std::wcout << L"Отладка test_3_7:" << std::endl;
            std::wcout << L"  Вход: ЯАБВГ" << std::endl;
            std::wcout << L"  Ключ: Я" << std::endl;
            std::wcout << L"  Получено: " << result << std::endl;
            std::wcout << L"  Ожидалось: " << expected << std::endl;
            
            // Выводим коды символов
            std::wcout << L"  Коды полученных символов: ";
            for (wchar_t c : result) {
                std::wcout << (int)c << L" ";
            }
            std::wcout << std::endl;
            
            std::wcout << L"  Коды ожидаемых символов: ";
            for (wchar_t c : expected) {
                std::wcout << (int)c << L" ";
            }
            std::wcout << std::endl;
        }
        
        return result == expected;
    } catch (const std::exception& e) {
        std::cout << "Исключение в test_3_7: " << e.what() << std::endl;
        return false;
    }
}
int main() {
    // Установка локали
    std::locale::global(std::locale("ru_RU.UTF-8"));
    
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "ЛАБОРАТОРНАЯ РАБОТА: МОДУЛЬНОЕ ТЕСТИРОВАНИЕ\n";
    std::cout << std::string(50, '=') << "\n\n";
    
    // ТЕСТЫ КОНСТРУКТОРА
    std::cout << "=== ТЕСТЫ КОНСТРУКТОРА (Таблица 1) ===\n";
    run_test("1.1 - Валидный ключ", test_1_1_valid_key);
    run_test("1.2 - Длинный ключ", test_1_2_long_key);
    run_test("1.3 - Ключ со строчными", test_1_3_lowercase_key);
    run_test("1.4 - Ключ с цифрами", test_1_4_key_with_digits);
    run_test("1.5 - Ключ со знаками", test_1_5_key_with_punctuation);
    run_test("1.6 - Ключ с пробелами", test_1_6_key_with_spaces);
    run_test("1.7 - Пустой ключ", test_1_7_empty_key);
    run_test("1.8 - Вырожденный ключ", test_1_8_degenerate_key);
    
    // ТЕСТЫ ШИФРОВАНИЯ
    std::cout << "\n=== ТЕСТЫ ШИФРОВАНИЯ (Таблица 2) ===\n";
    run_test("2.1 - Шифрование прописных", test_2_1_uppercase_string);
    run_test("2.2 - Шифрование строчных", test_2_2_lowercase_string);
    run_test("2.3 - Шифрование с пробелами и знаками", test_2_3_string_with_spaces_and_punctuation);
    run_test("2.4 - Шифрование с цифрами", test_2_4_string_with_numbers);
    run_test("2.5 - Шифрование пустого текста", test_2_5_empty_text);
    run_test("2.6 - Шифрование без букв", test_2_6_no_alpha_string);
    run_test("2.7 - Шифрование с максимальным сдвигом", test_2_7_max_shift_key);
    
    // ТЕСТЫ ДЕШИФРОВАНИЯ
    std::cout << "\n=== ТЕСТЫ ДЕШИФРОВАНИЯ (Таблица 3) ===\n";
    run_test("3.1 - Дешифрование прописных", test_3_1_uppercase_string);
    run_test("3.2 - Дешифрование со строчными", test_3_2_lowercase_in_ciphertext);
    run_test("3.3 - Дешифрование с пробелами", test_3_3_spaces_in_ciphertext);
    run_test("3.4 - Дешифрование с цифрами", test_3_4_digits_in_ciphertext);
    run_test("3.5 - Дешифрование со знаками", test_3_5_punctuation_in_ciphertext);
    run_test("3.6 - Дешифрование пустого текста", test_3_6_empty_ciphertext);
    run_test("3.7 - Дешифрование с максимальным сдвигом", test_3_7_max_shift_key);
    
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "ТЕСТИРОВАНИЕ ЗАВЕРШЕНО\n";
    std::cout << std::string(50, '=') << "\n";
    
    return 0;
}
