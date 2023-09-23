#ifndef HUFFMAN_TREE_HPP
#define HUFFMAN_TREE_HPP

#include "contador.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

// Estrutura para representar um nó da árvore de Huffman
struct HuffmanNode {
    std::string word;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(const std::string& w, int freq) : word(w), frequency(freq), left(nullptr), right(nullptr) {}
};

// Comparador para ordenar os nós da fila de prioridade
struct CompareNodes {
    bool operator()(HuffmanNode* lhs, HuffmanNode* rhs) const {
        return lhs->frequency > rhs->frequency;
    }
};

// Função para construir a árvore de Huffman com base nas palavras mais frequentes
HuffmanNode* buildHuffmanTree(const vector<pair<string, int>>& topKFrequent);

// Função para imprimir a árvore de Huffman em pré-ordem
void printHuffmanTreeStructure(HuffmanNode* root, ofstream& outputFile);

#endif 
