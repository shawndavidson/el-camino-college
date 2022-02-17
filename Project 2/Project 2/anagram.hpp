//
//  anagram.hpp
//  Project 2
//
//  Created by Shawn Davidson on 9/27/21.
//

#ifndef anagram_hpp
#define anagram_hpp

#include <stdio.h>
#include <string>

using namespace std;

int     loadDictionary(istream &dictfile, string dict[]);
int     permuteRecur(string word, const string dict[], int size, string results[]);
void    printRecur(const string results[], int size);


#endif /* anagram_hpp */
