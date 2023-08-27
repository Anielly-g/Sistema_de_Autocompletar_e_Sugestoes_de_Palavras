 #include "contador.hpp"
 #include <iostream> 
#include <algorithm>
#include <cctype>
#include <sstream>

using namespace std;

string cleanWord(string word) {
    string cleanedWord;


    size_t pos = 0;
    while ((pos = word.find("—", pos)) != std::string::npos) {
        cleanedWord += word.substr(0, pos);  
        cleanedWord += " "; 
        pos += 3;  
        word = word.substr(pos);  
        pos = 0;  
    }
    
    for (size_t i = 0; i < word.length(); i++) {
        char c = word[i];

        if (((c == '.' || c == ',' || c == '!' || c == '?' || c == ':' || c == ';') && isalnum(word[i + 1])) || ((i == word.length() - 1) && word[i] == '-')) {
            word[i] = ' ';
        }
        
       
        if (word[i] == '-' && word[i + 1] == '-') {
            word[i] = ' ';
            word[i + 1] = ' ';
        }
       
        c = word[i];
        if (!ispunct(c) || c == '-' || c == '/' || c == '_') {
            cleanedWord += c;
        }
        
    }


    return cleanedWord;
}



void heapify(vector<pair<string, int>>& heap, size_t size, size_t index) {
    size_t smallest = index;
    size_t left_child = 2 * index + 1;
    size_t right_child = 2 * index + 2;

    if (left_child < size && heap[left_child].second < heap[smallest].second) {
        smallest = left_child;
    }

    if (right_child < size && heap[right_child].second < heap[smallest].second) {
        smallest = right_child;
    }

    if (smallest != index) {
        swap(heap[index], heap[smallest]);
        heapify(heap, size, smallest);
    }
}

void buildHeap(vector<pair<string, int>>& heap) {
    for (int i = heap.size() / 2 - 1; i >= 0; --i) {
        heapify(heap, heap.size(), i);
    }
}

vector<pair<string, int>> findTopKFrequent(vector<string>& words, size_t k) {
    unordered_map<string, int> freqMap;
    for (string& word : words) {
        transform(word.begin(), word.end(), word.begin(), ::tolower); // Convert to lowercase
        word = cleanWord(word);
        istringstream wordStream(word);
        string individualWord;
        while (wordStream >> individualWord) {
            if (!individualWord.empty()) {
                freqMap[individualWord]++;
            }
        }
    }

     vector<pair<string, int>> heap;
    for (const auto& entry : freqMap) {
        if (heap.size() < k) {
            heap.push_back(entry);
        } else if (entry.second > heap[0].second) {
            heap[0] = entry;
            heapify(heap, k, 0); 
        }
    }

    buildHeap(heap);
    return heap;
}

 
