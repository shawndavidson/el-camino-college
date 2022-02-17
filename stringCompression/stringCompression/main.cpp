//
//  main.cpp
//  stringCompression
//
//  Created by Shawn Davidson on 1/4/22.
//
// Cracking the Coding Interview
// Problem 1.5
// Lessons Learned:
// - C++ strings are mutable unlike Java so string concatenation is efficient. Java string concatenation ends up being O(n^2)

#include <iostream>

using namespace std;

// Compress a string by replacing redundant characters with one instance
// of that character following by the number of instances
string compress(string text) {
    string result;
    int textLen = text.length();
    
    for (int i = 0; i < textLen; i++) {
        int freq = 1;
        
        while (i < textLen && text[i] == text[i-1]) {
            i++;
            freq++;
        }
        
        if (i > 0) {
            result += to_string(freq);
        }
        
        result += text[i];
    }
    
    return result.length() < text.length() ? result : text;
    
}

int main(int argc, const char * argv[]) {
    string input = "aabcccccaaa";
    
    cout << "Input: " << input << endl;
    string output = compress(input);
    
    cout << "Output: " << output << endl;
    
    return 0;
}
