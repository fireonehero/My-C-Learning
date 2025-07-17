#include "HuffmanTree.hpp"
#include <fstream>
#include <map>
#include <iostream>


std::map<char, int> getFrequencies(const std::string& filename){
    std::ifstream fileOpen(filename);
    if(!fileOpen){
        std::cerr << ("Error: File did not open correctly or does not exist. Exiting.");
    }

    std::map<char int> charFrequencies;

}