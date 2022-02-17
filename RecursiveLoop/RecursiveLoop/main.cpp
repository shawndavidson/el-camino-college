//
//  main.cpp
//  RecursiveLoop
//
//  Created by Shawn Davidson on 9/27/21.
//

#include <iostream>

using namespace std;

// Forward Declarations
void printPermutionsRecursively(string prefix, string rest,
                                string results[], int& nResults, int maxResults);

    
void loop(int i, int max) {
    if (i == max)
        return;
    
    cout << i << endl;
    
    loop(i+1, max);
}


// Print the permutations of a word (using iteration AND recursion)
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

void loopPermutations(int i, int max, string prefix, string rest, string results[],
                      int& nResults, int maxResults) {
    if (i == max)
        return;
    
    string nextPrefix = prefix + rest[i];
    string nextRest   = rest.substr(0, i) + rest.substr(i+1);

    printPermutionsRecursively(nextPrefix, nextRest, results, nResults, maxResults);

    loopPermutations(i+1, max, prefix, rest, results, nResults, maxResults);
}

// Print the permutations of a word (using ONLY recursion)
void printPermutionsRecursively(string prefix, string rest, string results[],
                                int& nResults, int maxResults) {

    if (rest.length() == 0) {
        cout << prefix << endl;
        // Save permutation to results
        results[nResults++] = prefix;
    }else {
        loopPermutations(0, (int)rest.length(), prefix, rest, results, nResults, maxResults);
    }
}


int main(int argc, const char * argv[]) {
    //loop(0, 10);
    
    const int   MAXRESULTS = 1000;
    string      results[MAXRESULTS];
    int         nResults = 0;
    
    printPermutionsRecursively("", "good", results, nResults, MAXRESULTS);
    
    return 0;
}
