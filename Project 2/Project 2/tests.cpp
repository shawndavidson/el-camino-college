//
//  tests.cpp
//  Project 2
//
//  Created by Shawn Davidson on 9/27/21.
//

#include "tests.hpp"
#include "anagram.hpp"
#include <algorithm>
#include <cassert>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void doBasicTests()
{
    const int TESTINGMAX = 10;
    {
        string dictionary[TESTINGMAX];
        // TODO: hack - revert absolute path 
        ifstream dictfile("/Users/sdavidson/XCodeProjects/Project 2/Project 2/smallwords.txt");
        if (!dictfile) {
           cout << "smallwords.txt file not found!" << endl;
           exit (1);
        }
        int numResults = loadDictionary(dictfile, dictionary);
        std::sort(dictionary, dictionary + numResults);
        assert(numResults == 5 && dictionary[0] == "act" && dictionary[numResults-1] == "tac");
    }
    {
       string results[TESTINGMAX];
       string example[ ] = { "act", "cat", "camino", "rat", "tac" };
       int numResults = permuteRecur("tca", example, 5, results);
       std::sort(results, results + numResults);
       assert(numResults == 3 && results[0] == "act" && results[1] == "cat" && results[2] == "tac");
    }
    {
       string results[TESTINGMAX];
       string example[ ] = { "kool", "moe", "dee" };
       int numResults ;
       numResults = permuteRecur("look", example, 1, results);
       assert(numResults == 1 && results[0] == "kool");
    }
    cout << "Passed all basic tests" << endl;
}
