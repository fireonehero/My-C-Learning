#include "HuffmanTree.hpp"
#include "BitStream.hpp"

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>



int main(int argc, char* argv[]) {
    std::string inputFileName;
    std::string outputFileName;
    std::string initalCode = "";
    std::map<char, std::string> huffmanCodesMap;

    if(argc > 4){
        std::cerr << "Error: Too many arguments were passed, please try again with the correct arguments. Exiting." << std::endl;
        return 1;
    }

    if(argv[1] == "-c"){
        inputFileName = argv[2];
        outputFileName = argv[3];
        std::map<char, int> frequencies = getFrequencies(inputFileName);
        Node* root = buildHuffmanTree(frequencies);
        generateCodes(root, initalCode, huffmanCodesMap);

        std::ofstream outFile;
        outFile.open(outputFileName, std::ios::binary);
        if(!outFile){
            std::cerr << ("Error: File did not open correctly or does not exist. Exiting.");
            return 1;
        }

        int uniqueCharCount = frequencies.size();
        outFile.write(reinterpret_cast<const char*>(&uniqueCharCount), sizeof(int));

    }

    return 0;
}
