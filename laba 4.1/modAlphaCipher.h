/**
 * @file modAlphaCipher.h
 * @brief Заголовочный файл для класса modAlphaCipher
 * @details Реализация шифра Гронсвельда для русскоязычных сообщений
 * @version 1.0
 * @date 2025
 * @author Ходжаев С.А.
 */

#pragma once
#include <vector>
#include <string>
#include <map>
#include <locale>
#include <codecvt>

/**
 * @class modAlphaCipher
 * @brief Класс для шифрования и дешифрования текста методом Гронсвельда
 * 
 * Класс реализует алгоритм шифрования Гронсвельда с поддержкой русского алфавита.
 * Шифрование осуществляется путем сдвига букв на величину, определяемую ключом.
 */
class modAlphaCipher
{
private:
    std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; ///< Русский алфавит
    std::map<wchar_t, int> alphaNum; ///< Карта для преобразования символов в числа
    std::vector<int> key; ///< Ключ шифрования в числовом представлении
    
    /**
     * @brief Преобразует строку в вектор числовых значений
     * @param s Входная строка для преобразования
     * @return Вектор целых чисел, соответствующих символам строки
     * @throw std::invalid_argument если строка содержит недопустимые символы
     */
    std::vector<int> convert(const std::wstring& s);
    
    /**
     * @brief Преобразует вектор числовых значений в строку
     * @param v Вектор целых чисел для преобразования
     * @return Строка, соответствующая вектору чисел
     * @throw std::out_of_range если индекс выходит за границы алфавита
     */
    std::wstring convert(const std::vector<int>& v);
    
    /**
     * @brief Преобразует строку к верхнему регистру и удаляет пробелы
     * @param s Входная строка для преобразования
     * @return Строка в верхнем регистре без пробелов
     */
    std::wstring to_upper(const std::wstring& s);
    
    /**
     * @brief Проверяет валидность строки
     * @param s Строка для проверки
     * @return true если строка содержит только русские буквы, false в противном случае
     */
    bool isValid(const std::wstring& s);
    
public:
    /**
     * @brief Удаленный конструктор по умолчанию
     * Класс не может быть создан без ключа
     */
    modAlphaCipher() = delete;
    
    /**
     * @brief Конструктор класса modAlphaCipher
     * @param skey Ключ шифрования в виде строки
     * @throw std::invalid_argument если ключ содержит недопустимые символы
     */
    modAlphaCipher(const std::wstring& skey);
    
    /**
     * @brief Шифрует открытый текст
     * @param open_text Текст для шифрования
     * @return Зашифрованная строка
     * @throw std::invalid_argument если текст содержит недопустимые символы
     */
    std::wstring encrypt(const std::wstring& open_text);
    
    /**
     * @brief Дешифрует зашифрованный текст
     * @param cipher_text Текст для дешифрования
     * @return Расшифрованная строка
     * @throw std::invalid_argument если текст содержит недопустимые символы
     */
    std::wstring decrypt(const std::wstring& cipher_text);
};
