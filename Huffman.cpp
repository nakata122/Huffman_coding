#include "Huffman.h"
#include <queue>
#include <vector>
#include <iostream>

class Compare { 
public: 
    bool operator()(Huffman::Node* a, 
                    Huffman::Node* b) 
    { 
        return a->priority >= b->priority; 
    } 
}; 

void Huffman::addSymbol(std::ifstream &stream)
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

    for(auto &item : alphabet)
    {
        q.push(new Node({item.second, item.first, nullptr, nullptr}));
    }
    std::cout<<'\n';

    numNodes = q.size();
    while(q.size() > 1)
    {
        numNodes++;
        Node *left = q.top();
        q.pop();
        Node *right = q.top();
        q.pop();
        Node *curr = new Node {left->priority + right->priority, "~", left, right};
        q.push(curr);
    }

    root = q.top();
    lookupHelper(root, BinaryBuffer(), true);

    for(auto &item : lookup)
    {
        std::cout << item.first << " ";
        item.second.print();
        std::cout << '\n';
    }
}


void Huffman::lookupHelper(Node *current, BinaryBuffer trace, bool first)
{
    if(current == nullptr) return;
    lookup[current->data] = trace;

    lookupHelper(current->left, trace <<= 1, false);
    trace >>= 1;
    lookupHelper(current->right, (++trace) <<= 1, false);
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

bool Huffman::exportAt(std::ifstream &from, std::ofstream &to)
{
    //BFS header
    // to.write((char *)&numNodes, 4);

    // std::queue<Node *> q;
    // q.push(root);

    // while(!q.empty())
    // {
    //     Node *curr = q.front();
    //     q.pop();

    //     if(curr != nullptr)
    //     {
    //         q.push(curr->left);
    //         q.push(curr->right);

    //         to.write(curr->data.c_str(), 1);
    //     }
    // }
    // to << '\n';
    char c;
    std::string temp;
    int count = 0;
    char num;
    BinaryBuffer buf;

    while (from.get(c))
    {
        temp = c;
        lookup[temp].print();
        std::cout << " ";
        buf += lookup[temp];
    }
    std::cout << "\n";
    buf.print();
    buf.writeTo(to);
    // to.write((char *)&num, sizeof(num));

    return true;
}

Huffman::~Huffman()
{

}