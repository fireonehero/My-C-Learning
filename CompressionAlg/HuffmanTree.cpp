#include "HuffmanTree.hpp"
#include <fstream>
#include <map>
#include <iostream>
#include <vector>


std::map<char, int> getFrequencies(const std::string& filename){
    std::ifstream fileOpen(filename);
    if(!fileOpen){
        std::cerr << ("Error: File did not open correctly or does not exist. Exiting.");
        return {};
    }

    std::map<char, int> charFrequencies;
    char ch;

    while(fileOpen.get(ch)){
        charFrequencies[ch]++;
    }

    fileOpen.close();
    return charFrequencies;
}

Node* buildHuffmanTree(const std::map<char, int>& frequencies){
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> pq;

    for(auto const& x : frequencies){

        Node* leafPointerNode = new Node(x.first, x.second);

        pq.push(leafPointerNode);
    }

    while(pq.size() > 1){
        Node* topNodePointer = pq.top();
        pq.pop();
        Node* secondTopNodePointer = pq.top();
        pq.pop();

        Node* parentNode = new Node(topNodePointer, secondTopNodePointer);
        pq.push(parentNode);
    }
    return pq.top();
}

void generateCodes(Node* root, std::string currentCode, std::map<char, std::string>& huffmanCodes){
    if(root->left == nullptr && root->right == nullptr){
        huffmanCodes[root->character_value, root->frequency_value];
        return;
    } else {
        while(root->left != nullptr){
            
        }
    }
}