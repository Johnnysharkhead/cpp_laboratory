#include "lab05.h"
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {//argv[0]=main.exe argv[1]=any.txt argv[2]=parameter
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