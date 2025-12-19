#include "modAlphaCipher.h"
#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>
#include <locale>

// Простой тестовый фреймворк
class TestRunner {
private:
    int total = 0;
    int passed = 0;
    int failed = 0;
    
public:
    void runTest(const std::string& name, bool (*test)()) {
        total++;
        std::cout << "[" << total << "] " << name << " ... ";
        
        try {
            if (test()) {
                std::cout << "\033[32mПРОЙДЕН\033[0m\n";
                passed++;
            } else {
                std::cout << "\033[31mПРОВАЛЕН\033[0m\n";
                failed++;
            }
        } catch (const std::exception& e) {
            std::cout << "\033[31mПРОВАЛЕН (исключение: " << e.what() << ")\033[0m\n";
            failed++;
        } catch (...) {
            std::cout << "\033[31mПРОВАЛЕН (неизвестное исключение)\033[0m\n";
            failed++;
        }
    }
    
    void printSummary() {
        std::cout << "\n" << std::string(40, '=') << "\n";
        std::cout << "ИТОГИ ТЕСТИРОВАНИЯ:\n";
        std::cout << "Всего тестов: " << total << "\n";
        std::cout << "Пройдено: " << passed << "\n";
        std::cout << "Провалено: " << failed << "\n";
        
        if (failed == 0) {
            std::cout << "\033[42m\033[37m ВСЕ ТЕСТЫ ПРОЙДЕНЫ \033[0m\n";
        } else {
            std::cout << "\033[41m\033[37m ЕСТЬ ПРОВАЛЕННЫЕ ТЕСТЫ \033[0m\n";
        }
        std::cout << std::string(40, '=') << "\n";
    }
    
    int getExitCode() const {
        return failed == 0 ? 0 : 1;
    }
};

// ========== ТЕСТЫ ДЛЯ КОНСТРУКТОРА ==========

bool test_1_1_valid_key() {
    modAlphaCipher cipher(5);
    return cipher.getKey() == 5;
}

bool test_1_2_min_key() {
    modAlphaCipher cipher(1);
    return cipher.getKey() == 1;
}

bool test_1_3_large_key() {
    modAlphaCipher cipher(100);
    return cipher.getKey() == 100;
}

bool test_1_4_zero_key() {
    try {
        modAlphaCipher cipher(0);
        return false; // Не должно дойти сюда
    } catch (const std::invalid_argument&) {
        return true;
    }
}

bool test_1_5_negative_key() {
    try {
        modAlphaCipher cipher(-5);
        return false;
    } catch (const std::invalid_argument&) {
        return true;
    }
}

// ========== ТЕСТЫ ДЛЯ ШИФРОВАНИЯ ==========

bool test_2_1_encrypt_short() {
    modAlphaCipher cipher(3);
    std::string result = cipher.encrypt("ABC");
    return !result.empty() && result.length() == 3;
}

bool test_2_2_encrypt_equal_to_key() {
    modAlphaCipher cipher(4);
    std::string result = cipher.encrypt("ABCD");
    return result.length() == 4;
}

bool test_2_3_encrypt_longer_than_key() {
    modAlphaCipher cipher(3);
    std::string result = cipher.encrypt("ABCDEF");
    return result.length() == 6;
}

bool test_2_4_encrypt_empty() {
    modAlphaCipher cipher(5);
    std::string result = cipher.encrypt("");
    return result.empty();
}

bool test_2_5_encrypt_lowercase() {
    modAlphaCipher cipher(4);
    std::string result = cipher.encrypt("abcdEFGH");
    // Проверяем что все символы в верхнем регистре
    for (char c : result) {
        if (!(c >= 'A' && c <= 'Z')) return false;
    }
    return result.length() == 8;
}

bool test_2_6_encrypt_english_only() {
    modAlphaCipher cipher(3);
    std::string result = cipher.encrypt("HELLO");
    return result.length() == 5;
}

bool test_2_7_encrypt_russian() {
    modAlphaCipher cipher(4);
    try {
        cipher.encrypt("Привет");
        return false;
    } catch (const std::invalid_argument&) {
        return true;
    }
}

bool test_2_8_encrypt_with_digits() {
    modAlphaCipher cipher(3);
    try {
        cipher.encrypt("ABC123");
        return false;
    } catch (const std::invalid_argument&) {
        return true;
    }
}

bool test_2_9_encrypt_with_punctuation() {
    modAlphaCipher cipher(3);
    try {
        cipher.encrypt("A,B.C!");
        return false;
    } catch (const std::invalid_argument&) {
        return true;
    }
}

bool test_2_10_encrypt_with_spaces() {
    modAlphaCipher cipher(3);
    try {
        cipher.encrypt("A B C");
        return false;
    } catch (const std::invalid_argument&) {
        return true;
    }
}

// ========== ТЕСТЫ ДЛЯ ДЕШИФРОВАНИЯ ==========

bool test_3_1_decrypt_short() {
    modAlphaCipher cipher(3);
    std::string encrypted = cipher.encrypt("ABC");
    std::string decrypted = cipher.decrypt(encrypted);
    return decrypted == "ABC";
}

bool test_3_2_decrypt_equal_to_key() {
    modAlphaCipher cipher(4);
    std::string encrypted = cipher.encrypt("ABCD");
    std::string decrypted = cipher.decrypt(encrypted);
    return decrypted == "ABCD";
}

bool test_3_3_decrypt_longer_than_key() {
    modAlphaCipher cipher(3);
    std::string encrypted = cipher.encrypt("ABCDEF");
    std::string decrypted = cipher.decrypt(encrypted);
    return decrypted == "ABCDEF";
}

bool test_3_4_decrypt_empty() {
    modAlphaCipher cipher(5);
    std::string result = cipher.decrypt("");
    return result.empty();
}

bool test_3_5_decrypt_lowercase() {
    modAlphaCipher cipher(4);
    
    // Сначала зашифровываем текст
    std::string original = "ABCDEFGH";
    std::string encrypted = cipher.encrypt(original);
    
    // Теперь пробуем дешифровать строчными буквами
    // Преобразуем зашифрованный текст в строчные
    std::string lowercase_encrypted;
    for (char c : encrypted) {
        lowercase_encrypted += tolower(c);
    }
    
    // Должно работать, так как decrypt преобразует в верхний регистр
    std::string decrypted = cipher.decrypt(lowercase_encrypted);
    
    // Должны получить исходный текст
    return decrypted == original;
}

bool test_3_6_encrypt_decrypt_cycle() {
    modAlphaCipher cipher(5);
    std::string original = "TESTMESSAGE";
    std::string encrypted = cipher.encrypt(original);
    std::string decrypted = cipher.decrypt(encrypted);
    
    if (decrypted != original) {
        std::cout << "\n  Отладка test_3_6:\n";
        std::cout << "  Оригинал: " << original << "\n";
        std::cout << "  Зашифровано: " << encrypted << "\n";
        std::cout << "  Расшифровано: " << decrypted << "\n";
    }
    
    return decrypted == original;
}

bool test_3_7_decrypt_russian() {
    modAlphaCipher cipher(4);
    try {
        cipher.decrypt("Привет");
        return false;
    } catch (const std::invalid_argument&) {
        return true;
    }
}

bool test_3_8_decrypt_with_digits() {
    modAlphaCipher cipher(3);
    try {
        cipher.decrypt("ABC123");
        return false;
    } catch (const std::invalid_argument&) {
        return true;
    }
}
    
int main() {
    // Установка локали для русских сообщений
    std::locale::global(std::locale("ru_RU.UTF-8"));
    
    TestRunner runner;
    
    std::cout << "МОДУЛЬНОЕ ТЕСТИРОВАНИЕ: ШИФР МАРШРУТНОЙ ПЕРЕСТАНОВКИ\n";
    std::cout << "==================================================\n\n";
    
    // Конструктор и ключи
    std::cout << "=== ТЕСТЫ КОНСТРУКТОРА ===\n";
    runner.runTest("1.1 Валидный ключ", test_1_1_valid_key);
    runner.runTest("1.2 Минимальный ключ", test_1_2_min_key);
    runner.runTest("1.3 Большой ключ", test_1_3_large_key);
    runner.runTest("1.4 Нулевой ключ", test_1_4_zero_key);
    runner.runTest("1.5 Отрицательный ключ", test_1_5_negative_key);
    
    // Шифрование
    std::cout << "\n=== ТЕСТЫ ШИФРОВАНИЯ ===\n";
    runner.runTest("2.1 Короткий текст", test_2_1_encrypt_short);
    runner.runTest("2.2 Текст равен ключу", test_2_2_encrypt_equal_to_key);
    runner.runTest("2.3 Текст длиннее ключа", test_2_3_encrypt_longer_than_key);
    runner.runTest("2.4 Пустой текст", test_2_4_encrypt_empty);
    runner.runTest("2.5 Текст в строчных", test_2_5_encrypt_lowercase);
    runner.runTest("2.6 Только английские буквы", test_2_6_encrypt_english_only);
    runner.runTest("2.7 Русские буквы", test_2_7_encrypt_russian);
    runner.runTest("2.8 Цифры в тексте", test_2_8_encrypt_with_digits);
    runner.runTest("2.9 Знаки препинания", test_2_9_encrypt_with_punctuation);
    runner.runTest("2.10 Пробелы в тексте", test_2_10_encrypt_with_spaces);
    
    // Дешифрование
    std::cout << "\n=== ТЕСТЫ ДЕШИФРОВАНИЯ ===\n";
    runner.runTest("3.1 Короткий шифротекст", test_3_1_decrypt_short);
    runner.runTest("3.2 Шифротекст равен ключу", test_3_2_decrypt_equal_to_key);
    runner.runTest("3.3 Шифротекст длиннее ключа", test_3_3_decrypt_longer_than_key);
    runner.runTest("3.4 Пустой шифротекст", test_3_4_decrypt_empty);
    runner.runTest("3.5 Шифротекст в строчных", test_3_5_decrypt_lowercase);
    runner.runTest("3.6 Цикл шифрование-дешифрование", test_3_6_encrypt_decrypt_cycle);
    runner.runTest("3.7 Русские буквы в шифротексте", test_3_7_decrypt_russian);
    runner.runTest("3.8 Цифры в шифротексте", test_3_8_decrypt_with_digits);

    runner.printSummary();
    
    return runner.getExitCode();
}
