//
//  testmain.cpp
//  CS2-Project4
//
//  Created by Shawn Davidson on 10/24/21.
//

#include <iostream>
#include <fstream>
#include <istream>
using namespace std;

void printFile(istream &dictfile) { }

bool balanceFile(istream &dictfile) { return true; }

int main()
{
    ifstream infile;
    string filename;
    
    cout << "Please enter filename for C++ code: ";
    cin >> filename;
    infile.open(filename.c_str());

    if (!infile) {
        cout << "File not found!" << endl;
        return (1);
    }
    
    printFile(infile);
    
    if (balanceFile(infile))
        cout << "balance ok" << endl;
}
