#ifndef OPERATION_H
#define OPERATION_H

#include <string>
#include <vector>
#include <algorithm>

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
		}
	}
}

void removeText(std::vector<std::string>& text, const std::string& word) {
	auto it = text.begin();
	while (it != text.end()) {
		if (toLowerCase(*it) == toLowerCase(word)) {
			it = text.erase(it);
		}
		else it++;
	}
}

#endif