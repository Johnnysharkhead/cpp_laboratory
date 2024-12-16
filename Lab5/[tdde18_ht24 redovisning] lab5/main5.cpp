#include "lab05.h"
#include <iostream>


// TODO: Complementary work: Crashes if given an empty text file. (core dumped)
//
// TODO: Complementary work: Initialize variables with {}, not =.
//
//
int main(int argc, char* argv[]) { // argv[0]=main.exe argv[1]=any.txt argv[2]=parameter
	if (argc < 2) {
		std::cout << "file name is needed" << std::endl;
		return 0;
	}
	else if (argc < 3) {
		std::cout << "parameters should be input" << std::endl;
	}

	std::string fileName = argv[1];
	std::vector<std::string> parameters(argv + 2, argv + argc);//parameters are saved in vector<std::string>

	chectParameters(fileName, parameters);

	return 0;
}
