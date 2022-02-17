//
//  main.cpp
//  CS2-Homework4.2
//
//  Created by Shawn Davidson on 11/7/21.
//

#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

void removeOdds(list<int>& li);
void test1();

void removeOdds(vector<int>& v);
void test2();

void test3();

void test4();

int main()
{
    test1();
    cout << "Passed" << endl;
    
    test2();
    cout << "Passed" << endl;
    
    test3();
    cout << "Passed" << endl;
    
    test4();
    cout << "Passed" << endl;
}
