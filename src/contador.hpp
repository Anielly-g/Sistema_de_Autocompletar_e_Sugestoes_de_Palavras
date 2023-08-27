#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream> 

using namespace std;

string cleanWord(string word);
vector<pair<string, int>> findTopKFrequent(vector<string>& words, size_t k);
void buildHeap(vector<pair<string, int>>& heap);
void heapify(vector<pair<string, int>>& heap, size_t size, size_t index);