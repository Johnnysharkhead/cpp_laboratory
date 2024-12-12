#include "lab05.h"
#include <iostream>
#include <fstream>
#include <iomanip> 

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
	// std::map < std::string, int, std::greater<std::string> > wordCount;
	for (const auto& word : words) {
		++wordCount[word]; // key is word(the way to access a element in a map) and value is the number of the word
	}
	return wordCount; // By default, this map is sorted by **key** in ascending order.

}

int calculateColumnWidth(const std::vector<std::string>& text) {
	// Get the longest word in a vector, using its length in setting the width of first column regarding the output 
	auto it = std::max_element(text.begin(), text.end(), [](std::string a, std::string b) {
		return a.length() < b.length();
		});
	return (*it).length();
	// std::cout << "The longest word in the text is: " << *it << ", with the length of " << columnWidth << std::endl;
	// std::cout << "So we set the width of the first column: " << columnWidth << std::endl; 
}

void chectParameters(std::string fileName, std::vector<std::string> parameters) {
	std::fstream file(fileName.c_str());
	if (!file) {
		std::cout << "cannot open the file, please check if the file is exist" << std::endl;
		return;
	}

	std::string word;
	std::vector<std::string> text; //text is saved in vector<std::string>
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
	std::for_each(
		text.begin(), text.end(), [](const std::string& word) {std::cout << word << " "; }
	);
	std::cout << std::endl;
}

void frequencyFunction(const std::vector<std::string>& text) {
	auto result = countWordFrequency(text);

	// Copy all elements in map to a vector since we cannot sort anything in a map
	// Get a vector(frequencyOrdered) containing all the map elements, each of which is a pair, preserving the original key-value relationships
	std::vector < std::pair<std::string, int> > frequencyOrdered(result.begin(), result.end());

	// Sort by the value of pairs in a vector in descending/ascending order of frequency occurrence
	std::sort(frequencyOrdered.begin(), frequencyOrdered.end(),
		[](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
			return a.second > b.second;
			//return a.sencond < b.second;
		});

	// Print all elements and keep the key (pair.first) right aligned
	int columnWidth = calculateColumnWidth(text);
	for (auto& pair : frequencyOrdered) {
		std::cout << std::setw(columnWidth) << std::right << pair.first << " " << pair.second << std::endl;
	}
}

void tableFunction(const std::vector<std::string>& text) {
	int columnWidth = calculateColumnWidth(text);
	auto result = countWordFrequency(text); // By default, map in C++ is sorted by **key** in ascending order.

	std::for_each( // The elements in the vector(result) are type "pair<string, int>".
		result.begin(), result.end(), [&columnWidth](const std::pair<std::string, int>& temp) { // Capture the width of column in lambda function
			std::cout << std::setw(columnWidth) << std::left << temp.first << " " << temp.second << std::endl;
		}
	);
}
void substituteFunction(std::vector<std::string>& text, const std::string& oldWord, const std::string& newWord) {

	auto findIT = std::find(text.begin(), text.end(), oldWord); // a iterator will move to the word that you want to replace 
	if (findIT != text.end()) {
		std::replace(text.begin(), text.end(), oldWord, newWord);
	}
	else {
		std::cout << "The word you input is not in text, please input the word that you want to replace again." << std::endl;
	}
}
void removeFunction(std::vector<std::string>& text, const std::string& wordToRemove) {
	auto findIT = std::find(text.begin(), text.end(), wordToRemove);
	if (findIT != text.end()) {
		text.erase(std::remove_if(text.begin(), text.end(), [&wordToRemove](std::string x) { return x == wordToRemove; }), text.end());
	}
	else {
		std::cout << "The word you input is not in text, please input the word that you want to delete again." << std::endl;
	}
}