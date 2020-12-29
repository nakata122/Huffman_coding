#include "FrequencyTable.h"
#include <iostream>
#include <cmath>

FrequencyTable::FrequencyTable(const int n)
{

}

void FrequencyTable::addSymbol(const std::string &key)
{
    // alphabet[key]++;
}

FrequencyTable::Node *FrequencyTable::insert(const std::string &data, unsigned int priority)
{

    Node *newNode = new Node{minHeap.size(), priority, data};
    minHeap.push_back(newNode);

    balance(ceil(newNode->index / 2.0) - 1); //Send parent
    std::cout << "\n";

    return newNode;
}

FrequencyTable::Node *FrequencyTable::pop()
{
    Node *result = minHeap[0];
    minHeap[0] = minHeap[minHeap.size() - 1];
    minHeap.pop_back();

    balance(0);

    return result;
}

void FrequencyTable::balance(int index)
{
    std::cout << index << " " << minHeap.size() << " ";
    if(index >= minHeap.size()) return;

    if(index * 2 < minHeap.size() && minHeap[index] > minHeap[index * 2])
    {
        swap(minHeap[index * 2], minHeap[index]);
        swap(minHeap[index * 2]->index, minHeap[index]->index);
        balance(ceil(index / 2.0) - 1);
    }
    if(index * 2 + 1 < minHeap.size() && minHeap[index] > minHeap[index * 2 + 1])
    {
        swap(minHeap[index * 2 + 1], minHeap[index]);
        swap(minHeap[index * 2 + 1]->index, minHeap[index]->index);
        balance(ceil(index / 2.0) - 1);
    }
}

void FrequencyTable::print()
{
    for(Node *item : minHeap)
    {
        std::cout << item->data << " ";
    }
}


template <class T>
void FrequencyTable::swap (T &first, T &second)
{
    T temp = first;

    first = second;
    second = temp;
}



FrequencyTable::~FrequencyTable()
{
    
}

