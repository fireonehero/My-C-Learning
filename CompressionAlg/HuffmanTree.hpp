
#ifndef HUFFMAN_TREE_HPP
#define HUFFMAN_TREE_HPP

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

};

#endif