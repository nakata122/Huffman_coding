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
        char data;
        Node *left, *right;
    };

private:
    Node *root;
    bool debug;

    std::unordered_map<char, int> alphabet;
    std::unordered_map<char, BinaryBuffer> lookup;

    Node *copyHelper(Node *);
    void printHelper(Node *, std::string trace);
    void lookupHelper(Node *, BinaryBuffer trace);
    Node *decerializeHelper(std::istream &);
    void clearHelper(Node *);
public:
    Huffman() : root(nullptr), debug(false) {};
    Huffman(const Huffman &);
    Huffman &operator =(const Huffman &);
    ~Huffman();

    void createTree();
    void addSymbol(std::istream &);
    void addSymbol(const char &);
    void addSymbol(const char &, const int);
    bool serialize(std::istream &, std::ostream &);
    bool deserialize(std::istream &, std::ostream &);
    void printTree();
    void setDebug(bool);
};

#endif