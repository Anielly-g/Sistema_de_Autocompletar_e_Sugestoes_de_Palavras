#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include "contador.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <set> 
#include <sstream> 


struct AVLNode {
    string word;
    int frequency;
    AVLNode* left;
    AVLNode* right;
    int height;
};

class AVLTree {
public:
    AVLTree();
    ~AVLTree();
    void buildFromTopKFrequent(const vector<pair<string, int>>& topKFrequent);
    void printInOrder(ostream& os) const;
    void clear();

private:
    AVLNode* root;

    int getHeight(AVLNode* node);
    int getBalanceFactor(AVLNode* node);
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
    AVLNode* insert(AVLNode* node, const string& word, int frequency, size_t k);
    void printInOrder(ostream& os, AVLNode* node) const;
    void clearTree(AVLNode* node);
};

#endif