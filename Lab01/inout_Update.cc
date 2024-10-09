#include <iostream>
#include <string>
#include <iomanip>

// Comment: You can initialize without { 0 } and { "" } but what you have is fine --- CHECK

int main() {
	int theInt{};
	char theChar{};
	double theDouble{};
	std::string theString{};

	std::cout << "Enter one integer: ";
	std::cin >> theInt;
	std::cout << "You entered the number: " << theInt << std::endl;
	std::cin.ignore(1000, '\n');
	

	std::cout << "Enter four integers: ";
	std::cin >> theInt;
	std::cout << "You entered the number: " << theInt << " ";
	std::cin >> theInt;
	std::cout << theInt <<" ";
	std::cin >> theInt;
	std::cout << theInt << " ";
	std::cin >> theInt;
	std::cout << theInt << std::endl;

	std::cout << "Enter one integer and one real number: ";
	std::cin >> theInt >> theDouble;
	std::getline(std::cin, theString);
	std::cout << std::setfill(' ');
	std::cout << "The real is: " << std::fixed << std::setprecision(3) << std::setw(12) << theDouble << std::endl;
	std::cout << "The integer is: " << std::setw(9) << theInt << std::endl;
	std::cin.ignore(1000, '\n');

	std::cout << "Enter one real and one integer number: ";
	std::cout << std::setfill('.');
	std::cin  >> theDouble >> theInt;
	std::cout << "The real is: " << std::setw(11) << theDouble << std::endl;
	std::cout << "The integer is: " << std::setw(8) << theInt << std::endl;
	std::cin.ignore(1000, '\n');

	std::cout << "Enter a character: ";
	std::cin >> theChar;
	std::cout << "You entered: " << theChar << std::endl;
	std::cin.ignore(1000, '\n');

	std::cout << "Enter a word: ";
	std::cin >> theString;
	std::cout << "The word '" << theString << "' has " << theString.size() << " character(s)." << std::endl;

	std::cout << "Enter an integer and a word: ";
	std::cin >> theInt >> theString;
	std::cout << "You entered '" << theInt << "' and '" << theString << "'." <<std::endl;
	std::cin.ignore(1000, '\n');

	std::cout << "Enter an character and a word: ";
	std::cin >> theChar >> theString;
	std::cout << "You entered the string \"" << theString << "\" and the character '" << theChar << "'." << std::endl;
	std::cin.ignore(1000, '\n');

	std::cout << "Enter a word and real number: ";
	std::cin >> theString >> theDouble;
	std::cout << "You entered \"" << theString << "\" and \"" << theDouble << std::endl;
	std::cin.ignore(1000, '\n');

	std::cout << "Enter a text-line: ";
	std::getline(std::cin, theString);
	std::cout << "You entered: \"" << theString << "\"" << std::endl;
	std::cin.ignore(1000, '\n');

	std::cout << "Enter a second line of text: ";
	std::getline(std::cin, theString);
	std::cout << "You entered: \"" << theString << ".\"" << std::endl; 
	std::cin.ignore(1000, '\n');

	std::cout << "Enter three words: ";
	std::cin >> theString;
	std::cout << "You entered: '" << theString << " ";
	std::cin >> theString;
	std::cout << theString << " ";
	std::cin >> theString;
	std::cout << theString << "'" << std::endl;

	return 0;
}
