#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include <unordered_map> 
#include <string>
#include <fstream>
#include "BinaryBuffer.h"

class Huffman
{
public:
    struct Node
    {
        int priority;
        std::string data;
        Node *left, *right;
    };

private:
    Node *root = nullptr;
    bool debug = false;

    std::unordered_map<std::string, int> alphabet;
    std::unordered_map<std::string, BinaryBuffer> lookup;

    void printHelper(Node *, std::string trace);
    void lookupHelper(Node *, BinaryBuffer trace, bool first);
    Node *decerializeHelper(std::istream &);
public:
    Huffman() : root(nullptr) {};
    Huffman(const Huffman &);
    Huffman &operator =(const Huffman &);
    ~Huffman();

    void createTree();
    void addSymbol(std::istream &);
    void addSymbol(const std::string &);
    void addSymbol(const std::string &, const int);
    bool serialize(std::istream &, std::ostream &);
    bool deserialize(std::istream &, std::ostream &);
    void printTree();
    void setDebug(bool);
};

#endif