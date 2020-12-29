#include "Huffman.h"
#include <stack>
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

bool Huffman::serialize(std::ifstream &from, std::ofstream &to)
{
    //DFS header
    std::stack<Node *> q;
    q.push(root);

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

    return true;
}

bool Huffman::deserialize(std::ifstream &from, std::ofstream &to)
{
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
        std::cout << " ";
    }

    return true;
}

Huffman::Node *Huffman::decerializeHelper(std::ifstream &stream)
{
    std::string temp;
    char c;
    stream >> c;
    if(c == '~') 
    {
        return new Node {0, "~", decerializeHelper(stream), decerializeHelper(stream)};
    }
    else
    {
        temp = c;
        return new Node {0, temp, nullptr, nullptr};
    }
}

Huffman::~Huffman()
{

}