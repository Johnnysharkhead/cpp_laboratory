
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream file("input.txt");

    string words{};
    string shortestWord{};
    string longestWord{};
    
    int wordCount{};
    int totalLength{};
    
    // Set a variable to store the first word in the file before the loop. 
    // Assign the value of this variable to both shortestWord and longestWord.
    file >> words;
    shortestWord = longestWord = words;

    do
    {   
        wordCount++; //Given that we've already read a word in the file, we change the value of wordCount to 1 before the loop starts 

          for (int i = 0; i < words.length(); i++){
            if (words[i] < 'A' || words[i] > 'z' || (words[i] > 'Z' && words[i] < 'a') ) {
				words.erase(i);
            }
        }
        
        int wordLength = words.length();
        totalLength += wordLength;

        if (wordLength < shortestWord.length()) {
            shortestWord = words;
        }
        if (wordLength > longestWord.length()) {
            longestWord = words;
        }   

    } while (file >> words);
    

    if (wordCount == 0) {
        cout << "Warning: The file is empty!" <<  endl;
    } 
    else {
        double averageLength = totalLength / wordCount;

         cout << "There are " <<  wordCount << " words in the file." << endl;
         cout << "The shortest word: " << shortestWord << " with " <<  shortestWord.length() << " character(s)" <<  endl;
         cout << "The longest word: " << longestWord <<  " with " <<  longestWord.length() << " character(s)" <<  endl;
         cout << "The average length was " << averageLength << " character(s). " << endl;
    }

    return 0;

    }
