
#include <iostream>
#include <cstring>
#include <fstream>
#include "Huffman.h"


int main(int argc, char** argv)
{
    enum Mode {Comression, Decompression, Adaptive, Debug};
    short mode = Mode::Comression;
    std::string fileName, outputName;
    for(int i=0; i < argc; i++)
    {
        if(strcmp(argv[i], "-c") == 0)
        {
            mode = Mode::Comression;
        } else if(strcmp(argv[i], "-d") == 0)
        {
            mode = Mode::Decompression;
        } else if(strcmp(argv[i], "-debug") == 0)
        {
            mode = Mode::Debug;
        } else if(strcmp(argv[i], "-i") == 0)
        {
            
            fileName = argv[++i];
        } else if(strcmp(argv[i], "-o") == 0)
        {
            outputName = argv[++i];
        }
    }

    std::cout << fileName << " " << outputName << std::endl;
    
    Huffman table;

    switch (mode)
    {
    case Mode::Comression:
    {
        std::ifstream iFile(fileName);
        std::ofstream oFile(outputName, std::ios::binary | std::ios::out);
        table.addSymbol(iFile);
        table.createTree();
        // table.printTree();
        table.exportAt(iFile, oFile);
        iFile.close();
        oFile.close();

        std::cout << '\n';
        std::ifstream iFile2(outputName, std::ios::binary | std::ios::in);
        char c;
        while (iFile2.get(c))
        {
            for (int i = 7; i >= 0; i--)
                std::cout << ((c >> i) & 1);
            std::cout << " ";
        }
        break;
    }
    case Mode::Decompression:
    {
        BinaryBuffer buf;
        std::cout << "DECOMPRESSING" << std::endl;
        for(int i = 0; i < 10; i++)
        {
            ++buf;
            buf <<= 3;
        }

        buf.print();
        break;
    }
    case Mode::Debug:
        
        break;
    case Mode::Adaptive:
        
        break;
    default:
        break;
    }

    // table.addSymbol("a", 5);
    // table.addSymbol("b", 2);
    // table.addSymbol("c");
    // table.addSymbol("d");
    // table.addSymbol("r", 2);
    // table.createTree();
    // table.printTree();

    // table.print();
    return 0;
}