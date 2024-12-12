#ifndef OPERATION_H
#define OPERATION_H

#include <string>
#include <vector>
#include <algorithm>
#include <map>

std::string toLowerCase(const std::string& str);
std::map <std::string, int> countWordFrequency(const std::vector<std::string>& words);
int calculateColumnWidth(const std::vector<std::string>& text);

void chectParameters(std::string fileName, std::vector<std::string> parameters);

void printFunction(const std::vector<std::string>& text);
void frequencyFunction(const std::vector<std::string>& text);
void tableFunction(const std::vector<std::string>& text);
void substituteFunction(std::vector<std::string>& text, const std::string& oldWord, const std::string& newWord);
void removeFunction(std::vector<std::string>& text, const std::string& wordToRemove);

#endif