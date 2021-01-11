#ifndef _BINARY_BUFFER_H
#define _BINARY_BUFFER_H

#include <vector>
#include <fstream>

class BinaryBuffer
{
private:
    std::vector<unsigned char> buffer; //Буфер за запазване на битове
    char index = 0; //Брой битове заети в последния char

    void shiftLeft(); //Помощна функция за shift left 1
    void shiftRight(); // Помощна функция за shift right 1
public:
    BinaryBuffer &operator <<=(const size_t amount); 
    BinaryBuffer &operator >>=(const size_t amount);
    BinaryBuffer &operator ++(); //Събира последният бит на буфера с 1
    int numBits(); //Броя на заетите до сега битове
    void operator +=(const BinaryBuffer &); //Слепване на два битови буфера
    void writeByte(const char &); //Записване на цял байт
    void writeTo(std::ostream &); //Сериализация
    void print() const; //Извеждане на конзолата в debug режим
};

#endif