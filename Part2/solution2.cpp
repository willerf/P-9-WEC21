#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>

using namespace std;

// Declares maps for initial state of phone without any broken buttons
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

// Same function as part 1 that calculates the time to type a word given the button maps
int wordTime(string word, map<int, string> buttonCharacters, map<char, int> characterButtons) {
    string lowercaseWord = "";
    for(int i = 0; i < word.size(); i++) {
        if(word[i] - 'A' < 26) {
            lowercaseWord += word[i] + 32;
        } else {
            lowercaseWord += word[i];
        }
    }

    int time = 0;
    for(int i = 0; i < word.size(); i++) {
        if(word[i] - 'A' < 26) {
            time += 8;
        } 
        
        if(i != 0 && characterButtons[lowercaseWord[i]] == characterButtons[lowercaseWord[i - 1]]) {
            time++;
        }

        int letterPosition = buttonCharacters[characterButtons[lowercaseWord[i]]].find(lowercaseWord[i]);
        time += letterPosition + 1;
    }

    return time - 1;
}

// Function to change the button maps given a broken button
void changeMaps(int brokenButton) {
    // Iterate through the buttons and add the correct number of characters or add none if it is the broken button
    int buttonCount = 1;
    char currentLetter = 'a';
    for(int button = 2; button <= 9; button++) {
        // If the button is broken
        if(button == brokenButton) {
            buttonCharacters[button] = "";
            continue;
        }

        // Assign either 4 or 3 letters depending on which button
        if(buttonCount == 6 || buttonCount == 7) {
            buttonCharacters[button] = "";
            buttonCharacters[button] += (char)(currentLetter);
            buttonCharacters[button] += (char)(currentLetter + 1);
            buttonCharacters[button] += (char)(currentLetter + 2);
            currentLetter += 3;
        } else {
            buttonCharacters[button] = "";
            buttonCharacters[button] += (char)(currentLetter);
            buttonCharacters[button] += (char)(currentLetter + 1);
            buttonCharacters[button] += (char)(currentLetter + 2);
            buttonCharacters[button] += (char)(currentLetter + 3);
            currentLetter += 4;
        }

        buttonCount++;
    }
    
    // Map each character to their button given the new button to characters map
    for(int i = 2; i <= 9; i++) {
        for(int j = 0; j < buttonCharacters[i].size(); j++) {
            characterButtons[buttonCharacters[i][j]] = i;
        }
    }
}

int main() {
    // Stores list of words
    vector<string> words;

    // Open file
    ifstream indata;
    indata.open("Part2.txt");
    if(!indata) {
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }

    // Input the broken button
    int brokenButton;
    indata >> brokenButton;

    // Update the maps given the broken button
    changeMaps(brokenButton);

    // Input the list of words
    string input;
    indata >> input;
    words.push_back(input);
    while (!indata.eof()) {
        indata >> input;
        words.push_back(input);
    }
    indata.close();

    // Create the list of times
    vector<int> times;
    int minimumTime = 1000000;
    for(int i = 0; i < words.size(); i++) {
        int currentTime = wordTime(words[i], buttonCharacters, characterButtons);
        times.push_back(currentTime);
        // Update the minimum
        if(currentTime < minimumTime) {
            minimumTime = currentTime;
        }
    }

    // Output the minimum words
    for(int i = 0; i < words.size(); i++) {
        if(times[i] == minimumTime) {
            cout << words[i] << " = " << minimumTime / 4.0 << "s\n";
        }
    }

    return 0;
}
