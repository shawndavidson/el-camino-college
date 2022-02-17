//
//  main.cpp
//  CSCI-2-Homework-1
//
//  Created by Shawn Davidson on 9/22/21.
//

#include <iostream>
#include <string>
#include "recursion.h"

using namespace std;

void testMulti()
{
    unsigned int a = 1, b = 9;

    cout << "The product of " << a << " and " << b << " is " << multi(a, b) << endl;
}

void testCountDigits()
{
    cout << "countDigits returned " << countDigit(18838, 8);
}

void testPairMinus()
{
    string s = "goodbye";

    cout << "pairMinus(\"" << s << "\") returned " << pairMinus(s) << endl;
}

void testFindParen()
{
    string s = "abc(ghj)789"; // (x)7"; // 4agh(y)"; //"abc(ghj)789";

    cout << "findParen(\"" << s << "\")" << " => " << findParen(s) << endl;
}

void testPathPresent()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X.......@X",
        "XX@X@@.XXX",
        "X..X.X...X",
        "X..X...@.X",
        "X....XXX.X",
        "X@X....XXX",
        "X..XX.XX.X",
        "X...X....X",
        "XXXXXXXXXX"
    };

    if (pathPresent(maze, 10,10, 6,4, 1,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}

void testCombinationSum()
{
    const int a[] = {2, 4, 8};
    
    cout << "combinationSum(a, 3, 10) = " << combinationSum(a, 3, 10) << endl;
    cout << "combinationSum(a, 3, 12) = " << combinationSum(a, 3, 12) << endl;
    
    int b[] = { 2, 4, 8, 6 };
    cout << "combinationSum(b, 4, 11) = " << combinationSum(b, 4, 11) << endl;

    int c[] = {};
    cout << "combinationSum(c, 0, 0) = " << combinationSum(c, 0, 0) << endl;

}


int main(int argc, const char * argv[]) {
    // insert code here...
    
    testMulti();
    testPairMinus();
    testCountDigits();
    testPathPresent();
    testFindParen();
    testCombinationSum();
    
    return 0;
}

