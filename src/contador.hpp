#ifndef CONTADOR_HPP
#define CONTADOR_HPP

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

#include <set> // Incluímos a biblioteca para a árvore AVL
#include <sstream> 

using namespace std;

string cleanWord(string word);
vector<pair<string, int>> findTopKFrequent(vector<string>& words, size_t k, const string& palavraChave);
void buildHeap(vector<pair<string, int>>& heap);
void heapify(vector<pair<string, int>>& heap, size_t size, size_t index);

#endif

