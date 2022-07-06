//
//  main.cpp
//  CS-30-Functional-Lab
//
//  Created by Shawn Davidson on 5/5/22.
//

#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <ctype.h>

using namespace std;

// Print each pair displaying the frequency then the word
void print_pairs(vector <pair<int, string>> v) {
    for (auto pair : v) {
        cout << pair.first << " " << pair.second << endl;
    }
}

// Sort by frequency in descending order
vector <pair<int, string>> sort_by_frequency(vector <pair<int, string>> v) {
    sort(begin(v), end(v),
         [](auto i, auto j){ return i.first > j.first; });
    
    return v;
}

// Reverse first and second element of each pair in map
vector <pair<int, string>> reverse_pairs(unordered_map<string, int> pairs) {
    vector <pair<int, string>> result;
    
    // Reverse the .first and .second for each pair so our association will
    // go from a frequency to a word
    transform(begin(pairs), end(pairs),
              back_inserter(result),
              [](auto pair) -> std::pair<int, string> {
                    return { pair.second, pair.first };
              });
    
    return result;
}

// Count the frequency of each word
unordered_map<string, int> count_occurences(vector<string> names) {
    unordered_map<string, int> result;
    for (auto name : names) {
        result[name]++;
    }
    
    return result;
}

// Use transform and a for-loop
vector<string> words(string text) {
    // Replace non-alphanumeric characters with a single space
    replace_if(
       begin(text), end(text),
       [](char ch) { return !isalnum(ch); },
       ' '
    );
    
    stringstream    iss(text);
    vector<string>  sv;

    // Split text into words seperated by whitespace
    for (string w; iss >> w; ) {
        sv.push_back(w);
    }
    
    return sv;
}


void print_common_words(string text) {

    vector<string> w = words(text);
    unordered_map<string, int> m = count_occurences(w);
    vector<pair<int, string>> r = reverse_pairs(m);
    vector<pair<int, string>> s = sort_by_frequency(r);
    print_pairs(s);
}

int main() {
    print_common_words("the.the.the,a,\nword\nword\n,a,b,a");
    
    //print_common_words("The The The CS30 class is awesome!a.a.");

}
