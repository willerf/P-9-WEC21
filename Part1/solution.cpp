#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>

using namespace std;

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

int main() {
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

    vector<string> words;

    ifstream indata;
    string input;
    indata.open("Test1.txt");
    if(!indata) {
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }

    indata >> input;
    words.push_back(input);
    while (!indata.eof()) {
        indata >> input;
        words.push_back(input);
    }
    indata.close();

    vector<int> times;
    int minimumTime = 1000000;
    for(int i = 0; i < words.size(); i++) {
        int currentTime = wordTime(words[i], buttonCharacters, characterButtons);
        times.push_back(currentTime);
        if(currentTime < minimumTime) {
            minimumTime = currentTime;
        }
    }

    for(int i = 0; i < words.size(); i++) {
        if(times[i] == minimumTime) {
            cout << words[i] << " = " << minimumTime / 4.0 << "s\n";
        }
    }

    return 0;
}
