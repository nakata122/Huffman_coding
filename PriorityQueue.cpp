#ifndef _PRIORITY_QUEUE_CPP
#define _PRIORITY_QUEUE_CPP

#include "PriorityQueue.h"
#include <iostream>
#include <stdexcept>

template<class T, class Comp>
PriorityQueue<T, Comp>::PriorityQueue(PriorityQueue &other)
{
    root = copyHelper(other.root);
}

template<class T, class Comp>
PriorityQueue<T,Comp> &PriorityQueue<T, Comp>::operator =(PriorityQueue &other)
{
    if(&other != this)
    {
        clearHelper(root);
        root = copyHelper(other.root);
    }
    return *this;
}

template <class T, class Comp>
void PriorityQueue<T,Comp>::push(T &data)
{
    numElements++;
    if(root == nullptr)
    {
        root = new Node {data, true, nullptr, nullptr};
        return;
    }
    else
        insert(data, root);
}

template <class T, class Comp>
void PriorityQueue<T,Comp>::insert(T &data, Node *&at)
{
    Node **curr = &at;
    Comp compare;
    //Търсим елемент, който чупи условието compare
    while(*curr != nullptr && compare(data, (*curr)->data))
    {
        if((*curr)->side)
        {
            (*curr)->side = false;
            curr = &(*curr)->left;
        }
        else
        {
            (*curr)->side = true;
            curr = &(*curr)->right;
        }
    }

    //Намерили сме и този елемент е листо. Можем да го запишем там
    if((*curr) == nullptr)
    {
        *curr = new Node {data, true, nullptr, nullptr};
    }
    else //Трябва да се разместват елементи. Спрямо това дали завиваме наляво или надясно се пуска рекурсивно надолу разместването
    {
        T temp = (*curr)->data;
        (*curr)->data = data;

        if((*curr)->side)
        {
            (*curr)->side = false;
            insert(temp, (*curr)->left);
        }
        else
        {
            (*curr)->side = true;
            insert(temp, (*curr)->right);
        }
        
    }
}

template <class T, class Comp>
T &PriorityQueue<T,Comp>::top()
{
    if(root == nullptr)  throw std::runtime_error("Cannot get top on empty queue");

    return root->data;
}

template <class T, class Comp>
void PriorityQueue<T,Comp>::pop()
{
    if(root == nullptr) throw std::runtime_error("Cannot pop empty queue");
    numElements--;

    popHelper(root);
}

template <class T, class Comp>
void PriorityQueue<T,Comp>::popHelper(Node *&curr)
{
    Comp compare;
    if(curr->left == nullptr && curr->right == nullptr) //Листо
    {
        delete curr;
        curr = nullptr;
    }
    else if(curr->left == nullptr) //Лявото поддърво е празно. Можем да заменим с дясното
    {
        Node *temp = curr->right;
        delete curr;
        curr = temp;
    }
    else if(curr->right == nullptr) //Дясното поддърво е празно. Можем да заменим с лявото
    {
        Node *temp = curr->left;
        delete curr;
        curr = temp;
    }
    else //И двете дървета имат нещо. Трябва да проверим по кой път да тръгнем
    {
        if(compare(curr->right->data, curr->left->data))
        {
            curr->data = curr->left->data;
            popHelper(curr->left);
        }
        else
        {
            curr->data = curr->right->data;
            popHelper(curr->right);
        }
        
    }
    
}

template <class T, class Comp>
void PriorityQueue<T,Comp>::print()
{
    //BFS print with sentinels
    std::queue<Node *> q;

    q.push(root);
    q.push(nullptr);

    while(!q.empty())
    {
        Node *curr = q.front();
        q.pop();
        
        if(curr == nullptr)
        {
            std::cout << std::endl;
            if(!q.empty()) q.push(nullptr);
            
        }
        else
        {
            std::cout << curr->data << " ";
            if(curr->left != nullptr)
                q.push(curr->left);
            if(curr->right != nullptr)
                q.push(curr->right);
        }
        
        
    }
}

template <class T, class Comp>
size_t PriorityQueue<T,Comp>::size()
{
    return numElements;
}

template <class T, class Comp>
void PriorityQueue<T,Comp>::clearHelper(PriorityQueue<T,Comp>::Node *curr)
{
    if(curr != nullptr)
    {
        clearHelper(curr->left);
        clearHelper(curr->right);
        delete curr;
    }
}

template <class T, class Comp>
typename PriorityQueue<T,Comp>::Node *PriorityQueue<T,Comp>::copyHelper(PriorityQueue<T,Comp>::Node *other)
{
    if(other == nullptr) return nullptr;

    Node *left = copyHelper(other->left);
    Node *right = copyHelper(other->right);

    return new Node {other->priority, other->data, left, right};
}

template <class T, class Comp>
PriorityQueue<T,Comp>::~PriorityQueue()
{
    clearHelper(root);
}

#endif