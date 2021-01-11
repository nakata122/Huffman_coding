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
    Node *root;
    bool debug;

    std::unordered_map<std::string, int> alphabet;
    std::unordered_map<std::string, BinaryBuffer> lookup;

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
    void addSymbol(const std::string &);
    void addSymbol(const std::string &, const int);
    bool serialize(std::istream &, std::ostream &);
    bool deserialize(std::istream &, std::ostream &);
    void printTree();
    void setDebug(bool);
};

#endif