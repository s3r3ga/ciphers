#include "modAlphaCipher.h"
#include <stdexcept>
#include <iostream>

modAlphaCipher::modAlphaCipher(const std::wstring& skey)
{
    // Инициализируем алфавит и создаем карту символов
    for (size_t i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    
    std::wstring upper_key = to_upper(skey);
    if (!isValid(upper_key)) {
        throw std::invalid_argument("Ключ содержит недопустимые символы");
    }
    
    key = convert(upper_key);
}

std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    std::wstring text = to_upper(open_text);
    if (!isValid(text)) {
        throw std::invalid_argument("Текст содержит недопустимые символы");
    }
    
    std::vector<int> work = convert(text);
    for (size_t i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % numAlpha.size();
    }
    return convert(work);
}

std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    std::wstring text = to_upper(cipher_text);
    if (!isValid(text)) {
        throw std::invalid_argument("Текст содержит недопустимые символы");
    }
    
    std::vector<int> work = convert(text);
    for (size_t i = 0; i < work.size(); i++) {
        work[i] = (work[i] + numAlpha.size() - key[i % key.size()]) % numAlpha.size();
    }
    return convert(work);
}

std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for (wchar_t c : s) {
        if (alphaNum.find(c) == alphaNum.end()) {
            throw std::invalid_argument("Недопустимый символ в тексте");
        }
        result.push_back(alphaNum[c]);
    }
    return result;
}

std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for (int i : v) {
        if (i < 0 || i >= static_cast<int>(numAlpha.size())) {
            throw std::out_of_range("Индекс выходит за границы алфавита");
        }
        result += numAlpha[i];
    }
    return result;
}

std::wstring modAlphaCipher::to_upper(const std::wstring& s)
{
    std::wstring result = s;
    std::wstring lower = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    std::wstring upper = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    
    for (size_t i = 0; i < result.size(); i++) {
        size_t pos = lower.find(result[i]);
        if (pos != std::wstring::npos) {
            result[i] = upper[pos];
        }
    }
    return result;
}

bool modAlphaCipher::isValid(const std::wstring& s)
{
    for (wchar_t c : s) {
        if (alphaNum.find(c) == alphaNum.end()) {
            return false;
        }
    }
    return true;
}