#ifndef _BINARY_BUFFER_H
#define _BINARY_BUFFER_H

#include <vector>
#include <fstream>

class BinaryBuffer
{
private:
    std::vector<unsigned char> buffer;
    int index = 0;

    void shiftLeft();
    void shiftRight();
public:
    BinaryBuffer &operator <<=(const size_t amount);
    BinaryBuffer &operator >>=(const size_t amount);
    BinaryBuffer & operator ++();
    void operator +=(const BinaryBuffer &);
    void writeTo(std::ofstream &);
    void print() const;
};

#endif