#include "lab05.h"
#include <iostream>
#include <fstream>

// TODO: Complementary work: Crashes if given an empty text file. (core dumped) -- CHECK
//
// TODO: Complementary work: Initialize variables with {}, not =. -- CHECK


int main(int argc, char* argv[]) { // argv[0]=main.exe argv[1]=any.txt argv[2]=parameter
	if (argc < 2) {
		std::cout << "file name is needed" << std::endl;
		return 0;
	}
	else if (argc < 3) {
		std::cout << "parameters should be input" << std::endl;
	}

	std::string fileName{ argv[1] };

	std::ifstream inputFile(fileName);

	if (!inputFile.is_open()) {
		std::cerr << "Error: Unable to open file " << fileName << std::endl;
		return 1;
	}

	if (inputFile.peek() == std::ifstream::traits_type::eof()) {
		std::cout << "The file " << fileName << " is empty." << std::endl;
		inputFile.close();
		return 0;
	}

	std::vector<std::string> parameters(argv + 2, argv + argc);//parameters are saved in vector<std::string>

	checkParameters(fileName, parameters);

	return 0;
}