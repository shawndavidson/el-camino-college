//
//  main.cpp
//  RecursiveLoop
//
//  Created by Shawn Davidson on 9/27/21.
//

#include <iostream>

using namespace std;

// Forward Declarations
void printPermutionsRecursively(string prefix, string rest);

    
void loop(int i, int max) {
    if (i == max)
        return;
    
    cout << i << endl;
    
    loop(i+1, max);
}


//     if (rest is empty) {
//         Display the prefix string.
//     }
//    else {
//         For each character in rest {
//             Add the character to the end of prefix.
//             Remove character from rest.
//             Use recursion to generate permutations with the updated values for prefix and rest.
//         }
//     }
void printPermutions(string prefix, string rest) {

    if (rest.length() == 0) {
        cout << prefix << endl;
    }else {
        for (int i = 0; i < rest.length();i++) {
            string nextPrefix = prefix + rest[i];
            string nextRest   = rest.substr(0, i) + rest.substr(i+1);
            
            printPermutions(nextPrefix, nextRest);
        }
    }
}

void loopPermutations(int i, int max, string prefix, string rest) {
    if (i == max)
        return;
    
    string nextPrefix = prefix + rest[i];
    string nextRest   = rest.substr(0, i) + rest.substr(i+1);

    printPermutionsRecursively(nextPrefix, nextRest);

    loopPermutations(i+1, max, prefix, rest);
}

void printPermutionsRecursively(string prefix, string rest) {

    if (rest.length() == 0) {
        cout << prefix << endl;
    }else {
        loopPermutations(0, (int)rest.length(), prefix, rest);
    }
}


int main(int argc, const char * argv[]) {
    //loop(0, 10);
    
    printPermutions("", "look");
    
    return 0;
}
