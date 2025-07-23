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

    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " -c <input_file> <output_file> OR "
                  << argv[0] << " -d <compressed_file> <decompressed_file>" << std::endl;
        return 1;
    }

    if (std::string(argv[1]) == "-c") {
        inputFileName = argv[2];
        outputFileName = argv[3];

        std::string initialCode = "";
        std::map<char, std::string> huffmanCodesMap;
        Node* root = nullptr;

        std::map<char, int> frequencies = getFrequencies(inputFileName);
        if (frequencies.empty()) {
            std::cerr << "Error: No frequencies found or input file could not be read. Compression aborted." << std::endl;
            return 1;
        }

        root = buildHuffmanTree(frequencies);
        generateCodes(root, initialCode, huffmanCodesMap);

        std::ofstream outFile;
        outFile.open(outputFileName, std::ios::binary);
        if (!outFile) {
            std::cerr << "Error: Output file '" << outputFileName << "' did not open correctly. Aborting compression." << std::endl;
            if (root) deleteTree(root);
            return 1;
        }

        long long originalCharCount = 0;
        for (auto const& pair : frequencies) {
            originalCharCount += pair.second;
        }

        int uniqueCharCount = frequencies.size();
        outFile.write(reinterpret_cast<const char*>(&uniqueCharCount), sizeof(int));
        outFile.write(reinterpret_cast<const char*>(&originalCharCount), sizeof(long long));

        for (auto const& pair : frequencies) {
            char char_value = pair.first;
            int freq_value = pair.second;
            outFile.put(char_value);
            outFile.write(reinterpret_cast<const char*>(&freq_value), sizeof(int));
        }

        BitWriter bitWriter(&outFile);

        std::ifstream inFileOriginal;
        inFileOriginal.open(inputFileName);

        if (!inFileOriginal) {
            std::cerr << "Error: Could not re-open input file '" << inputFileName << "' for compression pass. Aborting compression." << std::endl;
            outFile.close();
            if (root) deleteTree(root);
            return 1;
        }

        char ch;
        while (inFileOriginal.get(ch)) {
            std::string huffmanCodeForChar = huffmanCodesMap[ch];
            for (char bitChar : huffmanCodeForChar) {
                bitWriter.writeBit(bitChar);
            }
        }
        bitWriter.flush();

        outFile.close(); 
        inFileOriginal.close();
        if (root) deleteTree(root);

        std::cout << "File compressed successfully!" << std::endl;
        return 0;

    } else if (std::string(argv[1]) == "-d") {
        inputFileName = argv[2];
        outputFileName = argv[3];

        std::ifstream inFileCompressed;
        inFileCompressed.open(inputFileName, std::ios::binary);
        if (!inFileCompressed) {
            std::cerr << "Error: Compressed input file '" << inputFileName << "' did not open correctly. Aborting decompression." << std::endl;
            return 1;
        }

        std::map<char, int> frequenciesDecomp;
        Node* rootDecomp = nullptr;

        int uniqueCharCountDecomp;
        inFileCompressed.read(reinterpret_cast<char*>(&uniqueCharCountDecomp), sizeof(int));
        if (!inFileCompressed.good()) {
            std::cerr << "Error: Failed to read header unique character count from '" << inputFileName << "'. Aborting decompression." << std::endl;
            inFileCompressed.close();
            return 1;
        }
        
        long long originalCharCountDecomp = 0;
        inFileCompressed.read(reinterpret_cast<char*>(&originalCharCountDecomp), sizeof(long long));
        if (!inFileCompressed.good()) {
            std::cerr << "Error: Failed to read original character count from header in '" << inputFileName << "'. Aborting decompression." << std::endl;
            inFileCompressed.close();
            return 1;
        }


        for (int i = 0; i < uniqueCharCountDecomp; ++i) {
            char charValue;
            int freqValue;

            inFileCompressed.get(charValue);
            inFileCompressed.read(reinterpret_cast<char*>(&freqValue), sizeof(int));
            
            if (!inFileCompressed.good()) {
                std::cerr << "Error: Incomplete header in '" << inputFileName << "'. Aborting decompression." << std::endl;
                inFileCompressed.close();
                if (rootDecomp) deleteTree(rootDecomp); 
                return 1;
            }

            frequenciesDecomp[charValue] = freqValue;
        }

        rootDecomp = buildHuffmanTree(frequenciesDecomp);
        BitReader bitReader(&inFileCompressed);

        std::ofstream outFileDecompressed;
        outFileDecompressed.open(outputFileName);

        if (!outFileDecompressed) {
            std::cerr << "Error: Decompressed output file '" << outputFileName << "' did not open correctly. Aborting decompression." << std::endl;
            inFileCompressed.close();
            if (rootDecomp) deleteTree(rootDecomp);
            return 1;
        }

        Node* currentNode = rootDecomp;
        int bit;
        long long decodedCharCount = 0;

        while((bit = bitReader.readBit()) != EOF && decodedCharCount < originalCharCountDecomp){
            if(bit == 0) {
                currentNode = currentNode->left;
            } else {
                currentNode = currentNode->right;
            }

            if(currentNode->left == nullptr && currentNode->right == nullptr){
                outFileDecompressed.put(currentNode->character_value);
                decodedCharCount++;
                currentNode = rootDecomp;
            }
        }

        outFileDecompressed.close();
        inFileCompressed.close();
        if(rootDecomp){
            deleteTree(rootDecomp);
        }

        std::cout << "File decompressed successfully!" << std::endl;
        return 0;

    } else {
        std::cerr << "Error: Invalid option. Use -c for compress or -d for decompress." << std::endl;
        std::cerr << "Usage: " << argv[0] << " -c <input_file> <output_file> OR "
                  << argv[0] << " -d <compressed_file> <decompressed_file>" << std::endl;
        return 1;
    }

    return 0;
}