#ifndef OPERATION_H
#define OPERATION_H

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <map>
#include <iomanip> 

// Get the longest word in a vector, using its length in setting the width of first column regarding the output 
int firstcolumnWidth(const std::vector<std::string> vec) {
	std::string longestWord {};
	for(auto const &word : vec){
	if (word.length() > longestWord.length()) {
		longestWord = word;
		}
	}
	std::cout << "The longest word in the text is: " << longestWord << ", with the length of " << longestWord.length() << std::endl;
	std::cout << "So we set the width of the first column: " << longestWord.length() << std::endl; 
	return longestWord.length();
}
	

// Record " word : number of this word " by map container
std::map <std::string, int> countWordFrequency( const std::vector<std::string> &words){  //the parameter is vector with all words stored
    
	std::map <std::string, int> wordCount; // Initialize a map named wordCount
	// std::map < std::string, int, std::greater<std::string> > wordCount;
    
	for(const auto &word : words){
        ++wordCount[word]; // key is word(the way to access a element in a map) and value is the number of the word
    }
    return wordCount; // By default, this map is sorted by **key** in ascending order.
}

// Sort pairs in descending order of frequency occurrence
bool sortByValue(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b){
    return a.second > b.second; // .second = [the value of each pair], namely the occurance frequency for each word
	//return a.second < b.second;
}


//enter a single word, returns the word with all lower case letters
std::string toLowerCase(const std::string& str) {
	std::string result = str;
	std::transform(result.begin(), result.end(), result.begin(), ::tolower);
	return result;
}

void substitudeText(std::vector<std::string>& text,const std::string& oldWord, const std::string& newWord) {
	for (auto& it : text) {
		if (toLowerCase(it) == toLowerCase(oldWord)) {
			it = newWord;
			break;
		}
	}
	std:: cout << "The word you input is not in text, please input the word that you want to replace again." << std::endl;
}

void removeText(std::vector<std::string>& text, const std::string& word) {
	auto it = text.begin();
	bool flag;
	while (it != text.end()) {
		if (toLowerCase(*it) == toLowerCase(word)) {
			it = text.erase(it);
			flag = false;
		}
		else it++;
	}
	if(flag){
		std:: cout << "The word you input is not in text, please input the word that you want to delete again." << std::endl;
	}
	
}








#endif