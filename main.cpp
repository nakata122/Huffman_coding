
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include "Huffman.h"

int main(int argc, char** argv)
{

    enum Mode {Comression, Decompression, Adaptive, Debug}; //Различни режими за работа с програмата
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
        std::cout << "COMPRESSING" << std::endl;
        std::ifstream iFile(fileName);
        std::ofstream oFile(outputName, std::ios::binary | std::ios::out);
        table.addSymbol(iFile);
        table.createTree();
        table.serialize(iFile, oFile);
        iFile.close();
        oFile.close();
        break;
    }
    case Mode::Decompression:
    {
        std::cout << "DECOMPRESSING" << std::endl;

        std::ifstream iFile(fileName, std::ios::binary | std::ios::in);
        std::ofstream oFile(outputName);

        table.deserialize(iFile, oFile);
        break;
    }
    case Mode::Debug:
    {
        std::ifstream iFile(fileName);
        table.addSymbol(iFile);
        table.createTree();
        table.printTree();
        table.setDebug(true);
        std::stringstream temp;
        table.serialize(iFile, temp);
        iFile.close();
        
        break;
    }
    case Mode::Adaptive:
        
        break;
    default:
        break;
    }
    return 0;
}