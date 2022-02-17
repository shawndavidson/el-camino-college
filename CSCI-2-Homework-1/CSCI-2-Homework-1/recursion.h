//
//  recursion.h
//  CSCI-2-Homework-1
//
//  Created by Shawn Davidson on 9/22/21.
//

#ifndef recursion_h
#define recursion_h

#include <string>


int     multi(unsigned int m, unsigned int n);
int     countDigit(int num, int digit);
std::string  pairMinus(std::string n);
std::string  findParen(std::string str);
bool    pathPresent(std::string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
bool    combinationSum(const int a[], int size, int target);

#endif /* recursion_h */
