#ifndef _BINARY_BUFFER_H
#define _BINARY_BUFFER_H

#include <vector>
#include <fstream>

class BinaryBuffer
{
private:
    std::vector<unsigned char> buffer; //Буфер за запазване на битове
    int index = 0; //Брой битове заети в последния char

    void shiftLeft();
    void shiftRight();
public:
    BinaryBuffer &operator <<=(const size_t amount);
    BinaryBuffer &operator >>=(const size_t amount);
    BinaryBuffer & operator ++();
    int numBits();
    void operator +=(const BinaryBuffer &);
    void writeByte(const char &);
    void writeTo(std::ostream &);
    void print() const;
};

#endif