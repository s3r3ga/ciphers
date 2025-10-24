#pragma once
#include <string>
#include <vector>
#include <stdexcept>

class modAlphaCipher
{
private:
    int key; // количество столбцов
    
    std::string removeSpaces(const std::string& text);
    bool isValidKey(int key);
    
public:
    modAlphaCipher() = delete;
    modAlphaCipher(int k);
    
    std::string encrypt(const std::string& plain_text);
    std::string decrypt(const std::string& cipher_text);
    
    void setKey(int k);
    int getKey() const;
};