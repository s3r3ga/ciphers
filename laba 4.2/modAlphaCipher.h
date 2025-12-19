/**
 * @file modAlphaCipher.h
 * @brief Заголовочный файл для класса шифра маршрутной перестановки
 * @details Реализация шифра маршрутной перестановки для английского алфавита
 * @version 1.0
 * @date 2025
 */

#pragma once
#include <string>
#include <vector>
#include <stdexcept>

/**
 * @class modAlphaCipher
 * @brief Класс для шифрования и дешифрования методом маршрутной перестановки
 * 
 * Класс реализует алгоритм маршрутной перестановки:
 * 1. Текст записывается в таблицу по строкам
 * 2. Чтение осуществляется по столбцам справа налево
 * 3. Дешифрование - обратный процесс
 */
class modAlphaCipher
{
private:
    int key; ///< Количество столбцов в таблице перестановки
    
    /**
     * @brief Проверяет валидность ключа
     * @param key Ключ для проверки
     * @return true если ключ положительный, false в противном случае
     */
    bool isValidKey(int key);
    
public:
    /**
     * @brief Удаленный конструктор по умолчанию
     */
    modAlphaCipher() = delete;
    
    /**
     * @brief Конструктор с параметром
     * @param k Ключ шифрования (количество столбцов)
     * @throw std::invalid_argument если ключ невалидный
     */
    modAlphaCipher(int k);
    
    /**
     * @brief Шифрует текст методом маршрутной перестановки
     * @param plain_text Текст для шифрования
     * @return Зашифрованная строка
     * @throw std::invalid_argument если текст содержит недопустимые символы
     */
    std::string encrypt(const std::string& plain_text);
    
    /**
     * @brief Дешифрует текст методом маршрутной перестановки
     * @param cipher_text Текст для дешифрования
     * @return Расшифрованная строка
     * @throw std::invalid_argument если текст содержит недопустимые символы
     */
    std::string decrypt(const std::string& cipher_text);
    
    /**
     * @brief Устанавливает новый ключ шифрования
     * @param k Новый ключ
     * @throw std::invalid_argument если ключ невалидный
     */
    void setKey(int k);
    
    /**
     * @brief Возвращает текущий ключ шифрования
     * @return Текущий ключ
     */
    int getKey() const;
};
