#ifndef HUFFMAN_TREE_HPP
#define HUFFMAN_TREE_HPP

#include <queue>
#include <map>
#include <string>

struct Node {
    char character_value;
    int frequency_value;
    Node* left;
    Node* right;

    Node(char character, int frequency) {
        character_value = character;
        frequency_value = frequency;
        left = nullptr;
        right = nullptr;
    }

    Node(Node* left_child, Node* right_child){
        left = left_child;
        right = right_child;
        character_value = '\0';
        frequency_value = left_child->frequency_value + right_child->frequency_value;
    }

};

struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return a->frequency_value > b->frequency_value;
    }
};

std::map<char, int> getFrequencies(const std::string& filename);

Node* buildHuffmanTree(const std::map<char, int>& freqencies);

void generateCodes(Node* root, std::string currentCode, std::map<char, std::string>& huffmanCodes);

void deleteTree(Node* root);

#endif