#include "lab05.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include <iomanip> 


// Record " word : number of this word " by map container
std::map <std::string, int> countWordFrequency( const std::vector<std::string> &words){
    std::map <std::string, int> wordCount; // Intitialize a map
    for(const auto &word : words){
        ++wordCount[word]; // key is word and value is the number of the word
    }
    return wordCount; 
}

// Sort pairs in descending order of frequency occurrence
bool sortByValue(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b){
    return a.second > b.second;
}

int main(int argc, char* argv[]) { // argv[0]=main.exe argv[1]=any.txt argv[2]=parameter
	if (argc < 2) {
		std::cout << "file name is needed" << std::endl;
		return 0;
	}
	else if (argc < 3) {
		std::cout << "parameters should be input" << std::endl;
	}

	std::string fileName = argv[1];
	std::fstream file(fileName.c_str());
	if (!file) {
		std::cout << "cannot open the file" << std::endl;
		return 1;
	}
	
	std::string word;
	
	std::vector<std::string> text;//text is saved in vector<std::string>
	
	while (file >> word) {
		text.push_back(word);
	}

	std::vector<std::string> parameters(argv + 2, argv + argc);//parameters are saved in vector<std::string>
	for (auto it : parameters) {
		if (it.find("--print") != std::string::npos) {

		}
		
		else if (it.find("--frequency") != std::string::npos) {
			auto result = countWordFrequency(text);

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
		}

		else if (it.find("--table") != std::string::npos) {

		}
		else if (it.find("--substitute=") != std::string::npos) {
			auto equalSign = it.find('=');
			auto plusSign = it.find('+');
			std::string oldWord = it.substr(equalSign + 1, plusSign - equalSign - 1);
			std::string newWord = it.substr(plusSign + 1);
			substitudeText(text, oldWord, newWord);
		}
		else if(it.find("--remove=") != std::string::npos) {
			auto equalSign = it.find('=');
			std::string newWord = it.substr(equalSign + 1);
			removeText(text, newWord);
		}
	}

	for (auto it : text) {
		std::cout << it << " ";
	}


	//we may not need to write it back to the file yet?
	return 0;
}