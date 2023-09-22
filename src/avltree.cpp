 #include "avltree.hpp"
 #include <iostream> 
#include <algorithm>
#include <cctype>
#include <sstream>

void AVLTree::clearTree(AVLNode* node) {
    if (node != nullptr) {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}

// Construtor da classe AVLTree
AVLTree::AVLTree() : root(nullptr) {}

// Destrutor da classe AVLTree
AVLTree::~AVLTree() {
    clearTree(root);
}

// Função auxiliar para calcular a altura de um nó
int AVLTree::getHeight(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

// Função auxiliar para calcular o fator de balanceamento de um nó
int AVLTree::getBalanceFactor(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// Rotação à direita em torno de y
AVLNode* AVLTree::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Rotação à esquerda em torno de x
AVLNode* AVLTree::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Função para inserir um nó na árvore AVL, limitando o tamanho da árvore para manter apenas o top k
AVLNode* AVLTree::insert(AVLNode* node, const string& word, int frequency, size_t k) {
    if (node == nullptr) {
        AVLNode* newNode = new AVLNode;
        newNode->word = word;
        newNode->frequency = frequency;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->height = 1;
        return newNode;
    }

    if (word < node->word) {
        node->left = insert(node->left, word, frequency, k);
    } else if (word > node->word) {
        node->right = insert(node->right, word, frequency, k);
    } else {
        node->frequency = frequency;
        return node;
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalanceFactor(node);

    // Casos de balanceamento
    if (balance > 1 && word < node->left->word) {
        return rotateRight(node);
    }

    if (balance < -1 && word > node->right->word) {
        return rotateLeft(node);
    }

    if (balance > 1 && word > node->left->word) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && word < node->right->word) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Função para construir a árvore AVL com base nas palavras-chave mais frequentes (top k)
void AVLTree::buildFromTopKFrequent(const vector<pair<string, int>>& topKFrequent) {
    for (const auto& entry : topKFrequent) {
        root = insert(root, entry.first, entry.second, topKFrequent.size());
    }
}

// Função auxiliar para imprimir a árvore em ordem
void AVLTree::printInOrder(ostream& os, AVLNode* node) const {
    if (node != nullptr) {
        printInOrder(os, node->left);
        os << node->word << " - " << node->frequency << endl;
        printInOrder(os, node->right);
    }
}

// Função pública para imprimir a árvore em ordem
void AVLTree::printInOrder(ostream& os) const {
    printInOrder(os, root);
}

// Função para limpar a memória da árvore
void AVLTree::clear() {
    clearTree(root);
    root = nullptr;
}