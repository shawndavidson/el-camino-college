//
//  anagram.cpp
//  Project 2
//
//  Created by Shawn Davidson on 9/27/21.
//

//#include "tests.hpp"

#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

// Places each string in dictfile into the vector dict. Returns the number of words loaded into dict.
int loadDictionary(istream &dictfile, vector<string>& dict)
{
    int linesRead = 0;
    string word;
    
    while (!dictfile.eof()) {
        // Read in new words (one per line)
        std::getline(dictfile, word);
        
        // Skip empty lines
        if (word == "")
            continue;
        
        dict.push_back(word);
        linesRead++;
    }
    
    return linesRead;
}

int permute(string word, vector<string>& dict, vector<string>& results)
{
    int numFound = 0;
    
    unordered_set<string> uniqueResults;
    
    vector<char> letters(word.begin(), word.end());
    
    // Must sort letters for next_permutation to work correctly!
    sort(letters.begin(), letters.end());
    
    // Iterate through all the permutations of word
    do {
        string permutation(letters.begin(), letters.end());
        
        if (find(dict.begin(), dict.end(), permutation) != dict.end()) {
            // Insert matches into an unordered_set to ensure matches are unique
            uniqueResults.insert(permutation);
            numFound++;
        }
    }while (next_permutation(letters.begin(), letters.end()));
           
    // Append our unique matches to results
    for (auto iter = uniqueResults.begin(); iter != uniqueResults.end(); iter++)
        results.push_back(*iter);
    
    return numFound;
}


void print(const vector<string>& results) {
    for (auto iter = results.begin(); iter != results.end(); iter++)
        cout << "Matching word " << *iter << endl;
}

int main()
{
    //doBasicTests();
    
    cout << endl << endl;
    
    vector<string> results;
    vector<string> dict;
        
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;
    
    dictfile.open("words.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }
     
    nwords = loadDictionary(dictfile, dict);
    
    cout << "Please enter a string for an anagram: ";
    cin >> word;
    
    int numMatches = permute(word, dict, results);
    if (!numMatches)
        cout << "No matches found" << endl;
    else
        print(results);
}


