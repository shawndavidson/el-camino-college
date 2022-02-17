//
//  anagram.cpp
//  Project 2
//
//  Created by Shawn Davidson on 9/27/21.
//

#include "anagram.hpp"
#include "tests.hpp"

#include <iostream>
#include <fstream>
#include <istream>
#include <string>

using namespace std;

const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in

// Forward Declaration(s)
void printPermutionsRecursively(string prefix, string rest, string results[],
                                int& nResults, const string dict[], const int size);

int main()
{
    doBasicTests();
    
    cout << endl << endl;
    
    string results[MAXRESULTS];
    string dict[MAXDICTWORDS];
        
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;
    
    // TODO: must remove absolute path - copy words.txt to target location
    dictfile.open("/Users/sdavidson/XCodeProjects/Project 2/Project 2/words.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }
     
    nwords = loadDictionary(dictfile, dict);
    
    cout << "Please enter a string for an anagram: ";
    cin >> word;
    
    int numMatches = permuteRecur(word, dict, nwords, results);
    if (!numMatches)
        cout << "No matches found" << endl;
    else
        printRecur(results, numMatches);
}

// Recursively load dictionary words from an input stream into dict
int loopDictionaryWords(int i, int max, istream& dictfile, string dict[]) {
    // If we've reached the end of the simulated loop then bail
    if (i == max)
        return 0;
    
    // Create an inner scope before the recursive call to conserve stack space
    {
        string word;
        
        // Read in new words (one per line) but skip over empty lines
        do {
            if (dictfile.eof())
                return 0;
            
            std::getline(dictfile, word);
        }while (word == "");
        
        // Save our word to the front of the dictionary
        dict[0] = word;
    }
    
    // Recursively load the next word in the rest of the dictionary - simulate iteration
    return 1 + loopDictionaryWords(i+1, max, dictfile, dict + 1);
}

int loadDictionary(istream &dictfile, string dict[]) {
    // Call our recursive helper that simulates iteration to read a word at a time
    // up to MAXDICTWORDS
    return loopDictionaryWords(0, MAXDICTWORDS, dictfile, dict);
}

// Check if a word is within an array of words
// Returns true if the word is present.
bool hasWord(string word, const string words[], const int size) {
    // If there's nothing left to check report that it wasn't found
    if (size == 0)
        return false;
    
    // Check the first element
    if (words[0] == word)
        return true;
    
    // Recursively check the rest of the array [1...N]
    return hasWord(word, words + 1, size - 1);
}

// Recursively iterate through each character in a word and
void loopPermutations(int i, int max, string prefix, string rest, string results[],
                      int& nResults, const string dict[], const int size) {
    // If we've reached the end of the loop or we max'ed out on results
    if (i == max || nResults == MAXRESULTS)
        return;
    
    // For the next recursive call move character rest[i] out of rest and to the end of the prefix. However,
    // take care not to change prefix and rest because we have to handle each character
    // at this level in addition to drilling down recursively
    string nextPrefix = prefix + rest[i];
    string nextRest   = rest.substr(0, i) + rest.substr(i+1);

    // Drill down recursively to the NEXT level of permutations
    printPermutionsRecursively(nextPrefix, nextRest, results, nResults, dict, size);

    // Move to the next letter of rest at the CURRENT level in our tree of permutations
    loopPermutations(i+1, max, prefix, rest, results, nResults, dict, size);
}

// Print the permutations of a word (using ONLY recursion)
void printPermutionsRecursively(string prefix, string rest, string results[],
                                int& nResults, const string dict[], const int size) {
    // If results is full then bail
    if (nResults == MAXRESULTS)
        return;
    
    // If rest is empty then we have a permutation in prefix?
    if (rest.length() == 0) {
        // If it's NOT already in the array AND it's in the dictionary save to results
        if (!hasWord(prefix, results, nResults) && hasWord(prefix, dict, size)) {
            results[nResults++] = prefix;
        }
    }else {
        // Simulate iteration using recursion
        loopPermutations(0, (int)rest.length(), prefix, rest, results, nResults, dict, size);
    }
}

// Recursively search for the permutations of a word in a dictionary
// Returns the results in parameter results by reference
int permuteRecur(string word, const string dict[], int size, string results[])
{
    int nResults = 0;

    printPermutionsRecursively("", word, results, nResults, dict, size);
    
    return nResults;
}

// Print the results array
void printRecur(const string results[], int size)
{
    if (size == 0)
        return;
    
    cout << "Matching word " << results[0] << endl;
    
    printRecur(results + 1, size - 1);
}

