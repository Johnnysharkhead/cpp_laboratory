#include "lab05.h"
#include <iostream>
#include <fstream>
#include <iomanip> 

// TODO: Complentary work: Not everything need a comment, read the
// "Readability" section. Don't leave dead code as comments either. -- CHECK
//
// TODO: Complementary work: Don't use for_each to print, try copying to
// the outputstream -- CHECK
//
// TODO: Complementary work: You do not have to check if the word exists before
// trying to replace it or remove it. -- CHECK
//
// TODO: Complementary work: Do not repeat similar code, especially in frequency
// and table where you only change the sticky manipulator -- CHECK


//enter a single word, returns the word with all lower case letters
std::string toLowerCase(const std::string& str) {
	std::string result = str;
	std::transform(result.begin(), result.end(), result.begin(), ::tolower);
	return result;
}

// Transfer the vector with all words stored to a map 
// Record " word : number of this word " by map container, which is used in "--frequency" and "--table"
std::map <std::string, int> countWordFrequency(const std::vector<std::string>& words) {

	std::map <std::string, int> wordCount; // Initialize a map named wordCount
	
	for (const auto& word : words) {
		++wordCount[word]; 
	}
	return wordCount; 
}

int calculateCollumWidth(const std::vector<std::string>& text) {
	// Get the longest word in a vector, using its length in setting the width of first column regarding the output 
	auto it = std::max_element(text.begin(), text.end(), [](std::string a, std::string b) {
		return a.length() < b.length();
		});
	return (*it).length();
}


void printWord(const std::vector<std::string>& text, bool sortByFrequency) {
    auto wordCount = countWordFrequency(text);
    int columnWidth = calculateCollumWidth(text);
	std::vector<std::pair<std::string, int>> words(wordCount.begin(), wordCount.end()); // Constructor

    if (sortByFrequency) { // Used for --frequency
        std::sort(words.begin(), words.end(),[](const auto& a, const auto& b) { return a.second > b.second; });
    }

    for (const auto& pair : words) {
        std::cout << std::setw(columnWidth) << (sortByFrequency ? std::right : std::left) << pair.first << " " << pair.second << std::endl;
    }
}


void chectParameters(std::string fileName, const std::vector<std::string> &parameters) {
	std::fstream file(fileName.c_str());
	if (!file) {
		std::cout << "cannot open the file, please check if the file is exist" << std::endl;
		return;
	}

	std::string word;
	std::vector<std::string> text;
	while (file >> word) {
		text.push_back(word);
	}

	for (auto it : parameters) {
		if (it.find("--print") != std::string::npos) {
			printFunction(text);
		}

		else if (it.find("--frequency") != std::string::npos) {
			frequencyFunction(text);
		}

		else if (it.find("--table") != std::string::npos) {
			tableFunction(text);
		}

		else if (it.find("--substitute=") != std::string::npos) {
			auto equalSign = it.find('=');
			auto plusSign = it.find('+');
			std::string oldWord = it.substr(equalSign + 1, plusSign - equalSign - 1);
			std::string newWord = it.substr(plusSign + 1);
			substituteFunction(text, oldWord, newWord);
		}

		else if (it.find("--remove=") != std::string::npos) {
			auto equalSign = it.find('=');
			std::string wordToRemove = it.substr(equalSign + 1);

			removeFunction(text, wordToRemove);
		}
		else {
			std::cout << "wrong argument(s) exist, please check format" << std::endl;
		}

	}
}

void printFunction(const std::vector<std::string>& text) {
	std::copy(text.begin(), text.end(), std::ostream_iterator<std::string>(std::cout, " "));
	std::cout << std::endl;
}

void frequencyFunction(const std::vector<std::string>& text) {
 	printWord(text, true);
}

void tableFunction(const std::vector<std::string>& text) {
	printWord(text, false);
}

void substituteFunction(std::vector<std::string>& text, const std::string& oldWord, const std::string& newWord) {
	std::replace(text.begin(), text.end(), oldWord, newWord);
}

// TODO: Comment: Could have used the normal std::remove() instead. -- CHECK
void removeFunction(std::vector<std::string>& text, const std::string& wordToRemove) {
	auto newEnd = std::remove(text.begin(), text.end(), wordToRemove); 
	text.erase(newEnd, text.end());
}
