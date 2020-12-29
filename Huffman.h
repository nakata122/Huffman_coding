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
    int numNodes = 0;
    std::unordered_map<std::string, int> alphabet;
    std::unordered_map<std::string, BinaryBuffer> lookup;

    void printHelper(Node *, std::string trace);
    void lookupHelper(Node *, BinaryBuffer trace, bool first);
    Node *decerializeHelper(std::ifstream &);
public:
    Huffman() : root(nullptr) {};
    Huffman(const Huffman &);
    Huffman &operator =(const Huffman &);
    ~Huffman();

    void createTree();
    void addSymbol(std::ifstream &);
    void addSymbol(const std::string &);
    void addSymbol(const std::string &, const int);
    bool serialize(std::ifstream &, std::ofstream &);
    bool deserialize(std::ifstream &, std::ofstream &);
    void printTree();
};

#endif