#ifndef _PRIORITY_QUEUE_H
#define _PRIORITY_QUEUE_H

#include <queue>

template<class T, class Comp>
class PriorityQueue
{
private:
    struct Node
    {
        T data;
        bool side;
        Node *left;
        Node *right;
    };

    Node *root;
    size_t numElements;

    void insert(T &, Node *&);
    void popHelper(Node *&);
    void clearHelper(Node *);
    Node *copyHelper(Node *);
public:
    PriorityQueue(): root(nullptr), numElements(0) {};
    PriorityQueue(PriorityQueue &);
    PriorityQueue &operator =(PriorityQueue &);
    ~PriorityQueue();

    void push(T&);
    T &top();
    void pop();
    void print();
    size_t size();
};

#include "PriorityQueue.cpp"

#endif