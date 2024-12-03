#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip> 

using namespace std;

// Record " word : number of this word " by map container
std::map <std::string, int> countWordFrequency( const std::vector<string> &words){
    std::map <std::string, int> wordCount;
    for(const auto &word : words){
        ++wordCount[word]; // key is word and value is the number of the word
    }
    return wordCount;
}

// Sort pairs in descending order of frequency occurrence
bool sortByValue(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b){
    return a.second > b.second;
}

int main(){

    // Read the file and insert every single word into the vector(editorVector)
    std::fstream readFile{"input.txt"};
    std::vector <string> v{};

    std::string word {};

    while(readFile >> word){
        v.push_back(word);
    }

    auto result = countWordFrequency(v);

    // Copy all elements in map to a vector since we cannot sort anything in a map
    // Get a vector containing all the map elements, each of which is a pair, preserving the original key-value relationships
    std::vector < std::pair<std::string, int> > frequencyOrdered (result.begin(), result.end());

    // Sort by the value in each element(pair) of the vector
    std::sort(frequencyOrdered.begin(), frequencyOrdered.end(), sortByValue);

    // Print all elements and keep the key (pair.first) right aligned
    for (auto &pair : frequencyOrdered){
       int width = 12;
       std::cout << std::setw(width) << std::right << pair.first << " " << pair.second << std::endl;
    }







    return 0;
}