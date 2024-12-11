#include "lab05.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include <iomanip> 

		

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
	std::vector<std::string> text; //text is saved in vector<std::string>
	while (file >> word) {
		text.push_back(word);
	}

	std::vector<std::string> parameters(argv + 2, argv + argc);//parameters are saved in vector<std::string>
	
	for (auto it : parameters) {
		if (it.find("--print") != std::string::npos) {
			
			// When iterating through the vector, it passes each std::string element as an argument to the lambda function
			std::for_each(
				text.begin(), text.end(),[](const std::string &word) {std::cout << word << " ";}
			);
			std::cout << std::endl;

			// Alternative way (using iterator) to implment print
			// for(auto it = text.begin(); it != text.end(); ++it){
			// 	std::cout << *it << " ";
			// }
			// std::cout << std::endl;
		
		}
		

		else if (it.find("--frequency") != std::string::npos) {
			auto result = countWordFrequency(text);

			// Copy all elements in map to a vector since we cannot sort anything in a map
			// Get a vector(frequencyOrdered) containing all the map elements, each of which is a pair, preserving the original key-value relationships
			std::vector < std::pair<std::string, int> > frequencyOrdered (result.begin(), result.end());

			// Sort by the value in each element(pair) of the vector
			std::sort(frequencyOrdered.begin(), frequencyOrdered.end(), sortByValue);
			
			// Print all elements and keep the key (pair.first) right aligned
			int columnWidth = firstcolumnWidth(text);
			for (auto &pair : frequencyOrdered){
				std::cout << std::setw(columnWidth) << std::right << pair.first << " " << pair.second << std::endl;
			}
		}


		else if (it.find("--table") != std::string::npos) {
			auto result = countWordFrequency(text); // By default, map in C++ is sorted by **key** in ascending order.
			
			int columnWidth = firstcolumnWidth(text);
			
			std::for_each(
				result.begin(), result.end(),[&columnWidth](const std::pair<std::string,int> &temp){
					std::cout << std::setw(columnWidth) << std::left << temp.first << " " << temp.second << std::endl;
				}
			);
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

	//we may not need to write it back to the file yet?
	return 0;
}