#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP
#pragma once


#include "contador.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct TreeNode {
    string word;
    int frequency;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const string& w, int f) : word(w), frequency(f), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    BinaryTree();
    ~BinaryTree();
    void insert(const string& word, int frequency);
    void buildFromTopKFrequent(const vector<pair<string, int>>& topKFrequent);
    void printInOrder(ostream& os) const;
    void clear();

private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, const string& word, int frequency);
    void buildFromTopKFrequent(TreeNode*& node, const vector<pair<string, int>>& topKFrequent, size_t k);
    void printInOrder(ostream& os, TreeNode* node) const;
    void clearTree(TreeNode* node);
};

#endif