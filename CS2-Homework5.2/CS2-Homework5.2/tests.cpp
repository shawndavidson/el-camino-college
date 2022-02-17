//
//  tests.cpp
//  Project 2
//
//  Created by Shawn Davidson on 9/27/21.
//

#include "tests.hpp"
#include <algorithm>
#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int     loadDictionary(istream &dictfile, vector<string>& dict);
int     permute(string word, vector<string>& dict, vector<string>& results);
void    print(const vector<string>& results);

void doBasicTests()
{
    {
        vector<string> dictionary;
        // TODO: hack - revert absolute path 
        ifstream dictfile("/Users/sdavidson/XCodeProjects/Project 2/Project 2/smallwords.txt");
        if (!dictfile) {
           cout << "smallwords.txt file not found!" << endl;
           exit (1);
        }
        int numResults = loadDictionary(dictfile, dictionary);
        std::sort(dictionary.begin(), dictionary.end());
        assert(numResults == 5 && dictionary[0] == "act" && dictionary[numResults-1] == "tac");
    }
    {
       vector<string> results;
       vector<string> example{ "act", "cat", "camino", "rat", "tac" };
       int numResults = permute("tca", example, results);
       std::sort(results.begin(), results.end());
       assert(numResults == 3 && results[0] == "act" && results[1] == "cat" && results[2] == "tac");
    }
    {
       vector<string> results;
       vector<string> example{ "kool", "moe", "dee" };
       int numResults;
       numResults = permute("look", example, results);
       assert(numResults == 1 && results[0] == "kool");
    }
    cout << "Passed all basic tests" << endl;
}
