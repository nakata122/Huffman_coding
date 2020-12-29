#ifndef _FREQUENCY_TABLE_H
#define _FREQUENCY_TABLE_H

#include <unordered_map> 
#include <string>
#include <vector>

class FrequencyTable
{
private:

    struct Node
    {
        unsigned int index, priority;
        std::string data;
    };


    std::vector <Node *> minHeap;

    template <class T>
    void swap (T &first, T & second);
public:
    FrequencyTable(const int n);
    FrequencyTable(FrequencyTable &);
    ~FrequencyTable();
    FrequencyTable &operator =(FrequencyTable &);

    void addSymbol(const std::string &key);
    Node *insert(const std::string &data, unsigned int priority);
    Node *pop();
    void balance(int index);

    void print();
};

#endif