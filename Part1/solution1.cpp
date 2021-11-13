#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>

using namespace std;

int wordTime(string word, map<int, string> buttonCharacters, map<char, int> characterButtons) {
    // Creates a string that is the lowercase version of the word string
    string lowercaseWord = "";
    for(int i = 0; i < word.size(); i++) {
        if(word[i] - 'A' < 26) {
            lowercaseWord += word[i] + 32;
        } else {
            lowercaseWord += word[i];
        }
    }

    // Calculates the time to type the word represented as number of quarter seconds
    int time = 0;
    for(int i = 0; i < word.size(); i++) {
        // If the word is a capital
        if(word[i] - 'A' < 26) {
            time += 8;
        } 
        
        // Check if the current button is same as last
        if(i != 0 && characterButtons[lowercaseWord[i]] == characterButtons[lowercaseWord[i - 1]]) {
            time++;
        }

        // Find the number of clicks on the button needed
        int letterPosition = buttonCharacters[characterButtons[lowercaseWord[i]]].find(lowercaseWord[i]);
        time += letterPosition + 1;
    }

    // Return the time minus 1 since the last character does not require a quarter second pause
    return time - 1;
}

int main() {
    // Map to map buttons to their ordered characters
    map<int, string> buttonCharacters = {
        {2, "abc"},
        {3, "def"},
        {4, "ghi"},
        {5, "jkl"},
        {6, "mno"},
        {7, "pqrs"},
        {8, "tuv"},
        {9, "wxyz"}
    };

    // Map to map characters to their button
    map<char, int> characterButtons = {
        {'a', 2}, {'b', 2}, {'c', 2},
        {'d', 3}, {'e', 3}, {'f', 3},
        {'g', 4}, {'h', 4}, {'i', 4},
        {'j', 5}, {'k', 5}, {'l', 5},
        {'m', 6}, {'n', 6}, {'o', 6},
        {'p', 7}, {'q', 7}, {'r', 7}, {'s', 7},
        {'t', 8}, {'u', 8}, {'v', 8},
        {'w', 9}, {'x', 9}, {'y', 9}, {'z', 9}
    };

    // List of the words in the input
    vector<string> words;

    // Open the file
    ifstream indata;
    string input;
    indata.open("Test1.txt");
    if(!indata) {
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }

    // Take in the input and add them to the list
    indata >> input;
    words.push_back(input);
    while (!indata.eof()) {
        indata >> input;
        words.push_back(input);
    }
    indata.close();

    // Add the times for each word to a list
    vector<int> times;
    // Stores the minimum of the times
    int minimumTime = 1000000;
    for(int i = 0; i < words.size(); i++) {
        int currentTime = wordTime(words[i], buttonCharacters, characterButtons);
        times.push_back(currentTime);
        // Updates the minimum time
        if(currentTime < minimumTime) {
            minimumTime = currentTime;
        }
    }

    // Outputs all of the words with the minimum time
    for(int i = 0; i < words.size(); i++) {
        if(times[i] == minimumTime) {
            cout << words[i] << " = " << minimumTime / 4.0 << "s\n";
        }
    }

    return 0;
}
