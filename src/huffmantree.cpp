#include "huffmantree.hpp"
#include <queue>

using namespace std;


HuffmanNode* buildHuffmanTree(const vector<pair<string, int>>& topKFrequent) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> pq;

    // Inicializa a fila de prioridade com nós individuais para cada palavra-chave e sua frequência
    for (const auto& entry : topKFrequent) {
       pq.push(new HuffmanNode(entry.first, entry.second));
    }

    

    // Constrói a árvore de Huffman combinando os nós de menor frequência
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* parent = new HuffmanNode("", left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }

    return pq.top();
}
    

 

void printHuffmanTreeStructure(HuffmanNode* root, ofstream& outputFile) {
    if (root != nullptr) {
        if (!root->word.empty()) { // Verifica se a palavra não está vazia
            outputFile << root->word << " - " << root->frequency << endl;
        }
        printHuffmanTreeStructure(root->left, outputFile);
        printHuffmanTreeStructure(root->right, outputFile);
    }
}
  

    

