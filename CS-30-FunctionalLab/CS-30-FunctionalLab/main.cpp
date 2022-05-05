//
//  main.cpp
//  CS-30-FunctionalLab
//
//  Created by Shawn Davidson on 4/26/22.
//

#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <utility>

using namespace std;

void print_common_words(const std::string& text) {

    string newText;
    for (const char& c : text) {
        if (isalnum(c) || isdigit(c))
            newText += c;
        else
            newText += ' ';
    }

    unordered_map<string, int> um;
    istringstream iss(newText);
    for (string w; iss >> w; )
        um[w]++;
    vector<pair<string, int>> result(um.begin(), um.end());

    // sorts vector according to word count in descending order
    sort(begin(result), end(result),
            [] (pair<const string, int> p1, pair<const string, int> p2) {
        return p1.second > p2.second;
        });

    // prints the count then word
    for (const auto& r: result) {
        cout << r.second << " " << r.first << endl;
    }
}

// Functional version
void print_common_words_funct(const std::string& text) {

    vector<char> alphaNumericText(begin(text), end(text));
    
    std::erase_if(text, [](char ch) { return isalnum(ch) || isdigit(ch); });
    
//    string newText;
//    for (const char& c : text) {
//        if (isalnum(c) || isdigit(c))
//            newText += c;
//        else
//            newText += ' ';
//    }
//
//    unordered_map<string, int> um;
//    istringstream iss(newText);
//    for (string w; iss >> w; )
//        um[w]++;
//    vector<pair<string, int>> result(um.begin(), um.end());
//
//    // sorts vector according to word count in descending order
//    sort(begin(result), end(result),
//            [] (pair<const string, int> p1, pair<const string, int> p2) {
//        return p1.second > p2.second;
//        });
//
//    // prints the count then word
//    for (const auto& r: result) {
//        cout << r.second << " " << r.first << endl;
//    }
    
    return;
}

int main() {
    //print_common_words("The The The CS30 class is awesome!a.a.");
    print_common_words_funct("The The The CS30 class is awesome!a.a.");

}
