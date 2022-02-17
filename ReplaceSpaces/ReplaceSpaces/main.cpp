//
//  main.cpp
//  ReplaceSpaces
//
//  Created by Shawn Davidson on 1/1/22.
//
// Cracking the Coding Interview
// Problem 1.4

#include <iostream>

using namespace std;

//void replace(char* p, const char* text) {
//    while (*text != '\x0') {
//        *(p++) = *(text++);
//    }
//}

void replaceSpaces(char* str, int size) {
    if (size < 4)
        return;
    
    // Go to the last character BEFORE the null terminator
    char* p = str + size - 2;
    
    // Skip trailing whitespace
    while(p >= str && *p == ' ')
        p--;
    
    // Go to the last character BEFORE the null terminator
    char* s = str + size - 2;
    
    while (p >= str) {
        if (*p != ' ') {
            *s = *p;
            s--;
            p--;
        }else {
            p--;
            s -= 3;
            s[1] = '%';
            s[2] = '2';
            s[3] = '0';
//            s-= 2;
//            replace(s, "%20");
//            s--;
        }
    }
}

int main(int argc, const char * argv[]) {
    char s[] = "Mr John Smith    ";
    
    cout << s << endl;
    replaceSpaces(s, sizeof(s) / sizeof(s[0]));
    cout << s << endl;
    
    return 0;
}
