#include "Huffman.h"
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include "PriorityQueue.h"

class Compare { 
public: 
    bool operator()(Huffman::Node* a, 
                    Huffman::Node* b) 
    { 
        return a->priority >= b->priority; 
    } 
}; 

Huffman::Huffman(const Huffman &other)
{
    root = copyHelper(other.root);
}

Huffman& Huffman::operator =(const Huffman &other)
{
    if(&other != this)
    {
        clearHelper(root);
        root = copyHelper(other.root);
    }
    return *this;
}

Huffman::Node *Huffman::copyHelper(Huffman::Node *other)
{
    if(other == nullptr) return nullptr;

    Node *left = copyHelper(other->left);
    Node *right = copyHelper(other->right);

    return new Node {other->priority, other->data, left, right};
}

void Huffman::addSymbol(std::istream &stream)
{
    char c;
    std::string temp;
    while (stream.get(c))
    {
        temp = c;
        alphabet[temp]++;
    }
    
    stream.clear();
    stream.seekg(0);
}

void Huffman::addSymbol(const std::string &key)
{
    alphabet[key]++;
}

void Huffman::addSymbol(const std::string &key, const int amount)
{
    alphabet[key] += amount;
}

void Huffman::createTree()
{
    std::priority_queue<Node *, std::vector<Node *>, Compare> q;
    // PriorityQueue<Node *, Compare> q;

    for(auto &item : alphabet)
    {
        Node *temp = new Node({item.second, item.first, nullptr, nullptr});
        q.push(temp);
    }
    std::cout<<'\n';

    while(q.size() > 1)
    {
        Node *left = q.top();
        q.pop();
        Node *right = q.top();
        q.pop();
        Node *curr = new Node {left->priority + right->priority, "~", left, right};
        q.push(curr);
    }

    root = q.top();
    lookupHelper(root, BinaryBuffer());
}


void Huffman::lookupHelper(Node *current, BinaryBuffer trace)
{
    if(current == nullptr) return;
    lookup[current->data] = trace;

    lookupHelper(current->left, trace <<= 1);
    trace >>= 1;
    lookupHelper(current->right, (++trace) <<= 1);
}

void Huffman::printTree()
{
    printHelper(root, "");
}

void Huffman::printHelper(Node *current, std::string trace)
{
    if(current == nullptr) return;
    std::cout << current->data << " " << trace << std::endl;

    printHelper(current->left, trace+'0');
    printHelper(current->right, trace+'1');
}

bool Huffman::serialize(std::istream &from, std::ostream &to)
{
    //DFS header
    std::stack<Node *> q;
    q.push(root);

    //Записване на дървото
    while(!q.empty())
    {
        Node *curr = q.top();
        q.pop();

        if(curr != nullptr)
        {
            q.push(curr->right);
            q.push(curr->left);
            to.write(curr->data.c_str(), curr->data.size());
        }
    }
    
    char c;
    std::string temp;
    int count = 0;
    char num;
    BinaryBuffer buf;

    //Записване на битовете последователно в буфера
    while (from.get(c))
    {
        temp = c;
        buf += lookup[temp];
    }

    if(debug)
    {
        std::cout << "\n";
        buf.print();
    }
    
    buf.writeTo(to);

    return true;
}

bool Huffman::deserialize(std::istream &from, std::ostream &to)
{

    //Четене на дървото
    root = decerializeHelper(from);

    char c;
    Node *current = root;
    while (from.get(c))
    {
        for (int i = 7; i >= 0; i--)
        {
            if(((c >> i) & 1) == 0)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }

            if(current->left == nullptr && current->right == nullptr)
            {
                to << current->data;
                current = root;
            }
        }
    }

    return true;
}

Huffman::Node *Huffman::decerializeHelper(std::istream &stream)
{
    std::string temp;
    char c;
    stream.get(c);
    if(c == '~') //Специален символ, означаващ Node
    {
        return new Node {0, "~", decerializeHelper(stream), decerializeHelper(stream)};
    }
    else //Иначе е листо
    {
        temp = c;
        return new Node {0, temp, nullptr, nullptr}; 
    }
}

void Huffman::setDebug(bool val)
{
    debug = val;
}

void Huffman::clearHelper(Huffman::Node *curr)
{
    if(curr != nullptr)
    {
        clearHelper(curr->left);
        clearHelper(curr->right);
        delete curr;
    }
}

Huffman::~Huffman()
{
    clearHelper(root); //Изчистване на паметта рекурсивно
}