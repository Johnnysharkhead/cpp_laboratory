#ifndef OPERATION_H
#define OPERATION_H

#include <string>
#include <vector>
#include <algorithm>
#include <map>

// TODO: Complementary work: Use reference (to constant) for input
// parameters of class type. -- CHECK

std::string toLowerCase(const std::string& str);
std::map <std::string, int> countWordFrequency(const std::vector<std::string>& words);
int calculateCollumWidth(const std::vector<std::string>& text);

void checkParameters(const std::string& fileName, const std::vector<std::string>& parameters);

void printFunction(const std::vector<std::string>& text);
void frequencyFunction(const std::vector<std::string>& text);
void tableFunction(const std::vector<std::string>& text);
void substituteFunction(std::vector<std::string>& text, const std::string& oldWord, const std::string& newWord);
void removeFunction(std::vector<std::string>& text, const std::string& wordToRemove);


#endif