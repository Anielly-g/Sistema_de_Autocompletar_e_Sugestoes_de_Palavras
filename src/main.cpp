#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <unordered_set>
#include "avltree.hpp"
#include "huffmantree.hpp"
#include "binarytree.hpp"
#include "contador.hpp"
#include <chrono>

using namespace std;

int main() {
    auto inicio = chrono::high_resolution_clock::now();
    unordered_set<string> stopwords;
    // Leitura das stopwords
    ifstream stopwordsFile("dataset/stopwords.data");
    if (!stopwordsFile.is_open()) {
        cout << "Failed to open stopwords file." << endl;
        return 1;
    }

    string stopword;
    while (stopwordsFile >> stopword) {
        transform(stopword.begin(), stopword.end(), stopword.begin(), ::tolower);
        stopwords.insert(stopword);
    }
    stopwordsFile.close();

    int fileNumber = 0;
    string inputFile = "dataset/texto" + to_string(fileNumber) + ".data";


    ofstream outputFile("dataset/output.data");

    if (!outputFile.is_open()) {
        // Se o arquivo de saída não existir, cria
        outputFile.open("dataset/output.data");
        if (!outputFile.is_open()) {
            cout << "Failed to create or open output file." << endl;
            return 1;
        }
    }

    // Leitura das palavras-chave de um arquivo
    vector<string> palavrasChave;
    ifstream palavrasChaveFile("dataset/input.data");
    if (!palavrasChaveFile.is_open()) {
        cout << "Failed to open input file." << endl;
        return 1;
    }

    string palavraChave;
    while (palavrasChaveFile >> palavraChave) {
        transform(palavraChave.begin(), palavraChave.end(), palavraChave.begin(), ::tolower);
        palavrasChave.push_back(palavraChave);
    }
    palavrasChaveFile.close();

    while (true) {
        ifstream inputFileStream(inputFile);
        if (!inputFileStream.is_open()) {
            break; // Sai do loop se não for possível abrir o arquivo
        }

        vector<string> words;

        // Processamento do arquivo de entrada, exclusão de stopwords e cálculo das palavras mais frequentes para este arquivo
        while (inputFileStream.is_open()) {
            string line;
            while (getline(inputFileStream, line)) {
                transform(line.begin(), line.end(), line.begin(), ::tolower);
                istringstream wordStream(line);
                string word;
                while (wordStream >> word) {
                    transform(word.begin(), word.end(), word.begin(), ::tolower);

                    word = cleanWord(word);

                    if (stopwords.find(word) == stopwords.end()) {
                        words.push_back(word);
                    }
                }
            }

            inputFileStream.close();
        }

        size_t k = 20;

        // Indica qual arquivo está sendo analisado
        outputFile << "Analisando o arquivo: " << inputFile << endl;
        outputFile << endl;

         // Verifica se cada palavra-chave está presente no arquivo
        for (const string &palavraChave : palavrasChave) {
            bool palavraChavePresente = find(words.begin(), words.end(), palavraChave) != words.end();

          
            outputFile << "Palavra-chave: " << palavraChave << endl ;
            outputFile << endl; 
            outputFile << "--------------------------------------------------------"<< endl; 
            if (palavraChavePresente) {
                vector<pair<string, int>> topKFrequent = findTopKFrequent(words, k , palavraChave);

               
                //constrói a árvore AVL com base nas palavras mais frequentes 
                AVLTree avlTree;
                avlTree.buildFromTopKFrequent(topKFrequent);

                // Imprime a árvore AVL para esta palavra-chave
                outputFile << "AVL Tree para a palavra: " << palavraChave << endl;
                avlTree.printInOrder(outputFile);
                outputFile << "--------------------------------------------------------"<< endl; 

                //constrói a árvore binária com base nas palavras mf
                BinaryTree binaryTree;
                binaryTree.buildFromTopKFrequent(topKFrequent);

                // Imprime a árvore Binária para esta palavra-chave
                outputFile << "BINARY Tree para a palavra: " << palavraChave << endl;
                binaryTree.printInOrder(outputFile);
                outputFile << "--------------------------------------------------------"<< endl; 
                
                //constrói a árvore binária com base nas palavras mf
                HuffmanNode* huffmanTree = buildHuffmanTree(topKFrequent);
                //imprime a árvore Huffman para esta palavra-chave
                outputFile << "HUFFMAN Tree para a palavra: " << palavraChave << endl;
                printHuffmanTreeStructure(huffmanTree, outputFile);
               


            } else {
                outputFile << "Não encontrada no texto." << endl;
                outputFile << "--------------------------------------------------------"<< endl; 
            }

            outputFile << endl;
        }


        outputFile << "--------------------------------------------------------"<< endl; 

        fileNumber++;
        inputFile = "dataset/texto" + to_string(fileNumber) + ".data";
    }

    

    auto fim = chrono::high_resolution_clock::now();
    auto total = chrono::duration_cast<chrono::microseconds>(fim - inicio);

    outputFile << "Runtime: " << total.count() << " microseconds." << endl;
     
    outputFile.close();

    return 0;
}
