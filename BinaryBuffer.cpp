#include "BinaryBuffer.h"
#include <iostream>

void BinaryBuffer::shiftLeft()
{
    if(buffer.empty()) buffer.push_back(0);

    if(index >= 7) 
    {
        index = 0;
        buffer.push_back(0);
    }
    else
    {
        index++;
        buffer.back() <<= 1;
    }
}

void BinaryBuffer::shiftRight()
{
    if(buffer.empty()) buffer.push_back(0);

    if(index <= 0) 
    {
        buffer.pop_back();
        
        if(buffer.empty()) index = 0;
        else index = 7;
    }
    else
    {
        index--;
        buffer.back() >>= 1;
    }
}

BinaryBuffer &BinaryBuffer::operator <<=(size_t amount)
{
    for(int i=0; i < amount; i++) shiftLeft();
    return *this;
}

BinaryBuffer &BinaryBuffer::operator >>=(size_t amount)
{
    for(int i=0; i < amount; i++) shiftRight();
    return *this;
}


BinaryBuffer &BinaryBuffer::operator ++()
{
    if(buffer.size() == 0) buffer.push_back(0);
    buffer.back()++;
    return *this;
}

void BinaryBuffer::operator +=(const BinaryBuffer &other)
{
    if(other.buffer.size() == 0) return;

    for(int i=0; i < other.buffer.size() - 1; i++)
    {
        writeByte(other.buffer[i]);
    }

    unsigned char c = 1 << other.index;
    for(int j=0; j < other.index; j++)
    {
        if((other.buffer.back() & c) / c == 1)
        {
            operator ++();
        }
        shiftLeft();
        c >>= 1;
    }
}

void BinaryBuffer::writeByte(const char &byte)
{
    if(buffer.size() == 0) buffer.push_back(0);

    unsigned char c = 128;
    for(int j=0; j < 8; j++)
    {
        if((byte & c) / c == 1)
        {
            operator ++();
        }
        shiftLeft();
        c >>= 1;
    }
}

void BinaryBuffer::writeTo(std::ofstream &stream)
{
    if(buffer.empty()) return;

    for(int i=0; i < buffer.size() - 1;i++)
    {
        stream.write((char *)&buffer[i], sizeof(char));
    }
    char lastByte = buffer.back() << (7 - index);
    stream.write((char *)&lastByte, sizeof(char));

}

void BinaryBuffer::print() const
{
    if(buffer.size() == 0) return;

    for(int i=0; i < buffer.size() - 1; i++)
    {
        unsigned char c = 128;
        for(int j=0; j < 8 ;j++)
        {
            std::cout << (buffer[i] & c) / c;
            c >>= 1;
        }
        std::cout << " ";
    }

    unsigned char c = 1 << index;
    for(int j=0; j < index; j++)
    {
        std::cout << (buffer.back() & c) / c;
        c >>= 1;
    }
}

int BinaryBuffer::numBits()
{
    return (buffer.size() - 1) * 8 + index;
}