
#include "binarytree.hpp"
#include <iostream>

using namespace std;

// Construtor da classe BinaryTree
BinaryTree::BinaryTree() : root(nullptr) {}

// Destrutor da classe BinaryTree
BinaryTree::~BinaryTree() {
    clear();
}

// Função para inserir um nó na árvore binária
TreeNode* BinaryTree::insert(TreeNode* node, const string& word, int frequency) {
    if (node == nullptr) {
        return new TreeNode(word, frequency);
    }

    if (word < node->word) {
        node->left = insert(node->left, word, frequency);
    } else if (word > node->word) {
        node->right = insert(node->right, word, frequency);
    } else {
        node->frequency = frequency;
    }

    return node;
}

// Função pública para inserir um nó na árvore binária
void BinaryTree::insert(const string& word, int frequency) {
    root = insert(root, word, frequency);
}

// Função auxiliar para construir a árvore binária com base nas palavras-chave mais frequentes (top k)
void BinaryTree::buildFromTopKFrequent(TreeNode*& node, const vector<pair<string, int>>& topKFrequent, size_t k) {
    if (topKFrequent.empty() || k == 0) {
        return;
    }

    node = insert(node, topKFrequent.front().first, topKFrequent.front().second);
    buildFromTopKFrequent(node->left, vector<pair<string, int>>(topKFrequent.begin() + 1, topKFrequent.end()), k - 1);
}

// Função pública para construir a árvore binária com base nas palavras-chave mais frequentes (top k)
void BinaryTree::buildFromTopKFrequent(const vector<pair<string, int>>& topKFrequent) {
    buildFromTopKFrequent(root, topKFrequent, topKFrequent.size());
}

// Função auxiliar para imprimir a árvore binária em ordem
void BinaryTree::printInOrder(ostream& os, TreeNode* node) const {
    if (node != nullptr) {
        printInOrder(os, node->left);
        os << node->word << " - " << node->frequency << endl;
        printInOrder(os, node->right);
    }
}

// Função pública para imprimir a árvore binária em ordem
void BinaryTree::printInOrder(ostream& os) const {
    printInOrder(os, root);
}

// Função para limpar a memória da árvore binária
void BinaryTree::clear() {
    clearTree(root);
    root = nullptr;
}

// Função auxiliar para liberar a memória da árvore binária
void BinaryTree::clearTree(TreeNode* node) {
    if (node != nullptr) {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}
