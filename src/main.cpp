#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <unordered_set>
#include "contador.hpp"
#include <chrono>

using namespace std;

int main() {
    auto inicio=chrono::high_resolution_clock::now();
    unordered_set<string> stopwords;
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
    string inputFile = "dataset/input" + to_string(fileNumber) + ".data";
    ifstream inputFileStream(inputFile);

    vector<string> words; 
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
        fileNumber++;
        inputFile = "dataset/input" + to_string(fileNumber) + ".data";
        inputFileStream.open(inputFile);
    }

    size_t k = 20;
    vector<pair<string, int>> topKFrequent = findTopKFrequent(words, k); 

      sort(topKFrequent.begin(), topKFrequent.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second < b.second;
    }); 

    cout << "Top " << k << " frequent elements:" << endl;
    for (size_t i = 0; i < topKFrequent.size(); ++i) {
        cout << i + 1 << ". " << topKFrequent[i].first << " - " << topKFrequent[i].second << " times" << endl;
    }

    auto fim=chrono::high_resolution_clock::now();
    auto total=chrono::duration_cast<chrono::microseconds>(fim-inicio);

    cout<<"Runtime: "<< total.count();
    cout<<" microseconds."<<endl;

    return 0;
}
