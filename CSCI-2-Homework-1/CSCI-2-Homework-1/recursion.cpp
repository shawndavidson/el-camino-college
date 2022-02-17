//
//  recursion.cpp
//  CSCI-2-Homework-1
//
//  Created by Shawn Davidson on 9/22/21.
//

#include <string>

using namespace std;

// Homework #1
// Returns the product of two positive integers, m and n,
// using only repeated addition.
int multi(unsigned int m, unsigned int n)
{
    if (m == 0 || n == 0)
        return 0;

    return m + multi(m, n - 1);
}


// Returns the number of occurrences of digit in the decimal
// representation of num. digit is an int between 0 and 9
// inclusive.
//
// Pseudocode Example:
//    countDigit(18838, 8) => 3
//    countDigit(55555, 3) => 0
//    countDigit(0, 0)     => 0 or 1 (either is fine)
//
int countDigit(int num, int digit)
{
    if (num == 0)
        return 0;

    int whatsLeft = num / 10;
    int remainder = num % 10;

    if (remainder == digit)
        return countDigit(whatsLeft, digit) + 1;
    else
        return countDigit(whatsLeft, digit);
}


// Returns a string where the same characters next each other in
// string n are separated by "--". You can use substr in this problem
//
// Pseudocode Example:
//    pairMinus("goodbye") => "go--odbye"
//    pairMinus("yyuu")    => "y--yu--u"
//    pairMinus("aaaa")    => "a--a--a--a"
//
string pairMinus(string n)
{
    if (n.length() < 2)
        return n;

    if (n[0] == n[1])
    {
        string ch;

        ch += n[0];

        return ch + "--" + pairMinus(n.substr(1));
    }

    return n[0] + pairMinus(n.substr(1));
}

// str contains a single pair of parenthesis, return a new string
// made of only the parenthesis and whatever those parensthesis
// contain. You can use substr in this problem.
//
//  Pseudocode Example:
//     findParen("abc(ghj)789") => "(ghj)"
//     findParen("(x)7")        => "(x)"
//     findParen("4agh(y)")     => "(y)"
//
string findParen(string str)
{
    if (str.length() < 2)
        return "";

    if (str[0] == '(' && str[str.length()-1] == ')')
        return str;

    size_t pos = str[0] == '(' ? 0 : 1;
    size_t len = str[str.length() - 1] == ')' ? str.length() : (str.length() - 1);
    len -= pos;

    return findParen(str.substr(pos, len));
}

bool combinationSum(const int a[], int size, int target)
{
    if (size == 0)
        return target == 0;
    
    if (size == 1)
        return a[0] == target;
    
    if (a[size-1] == target || combinationSum(a, size-1, target))
        return true;
    
    return combinationSum(a, size-1, target - a[size-1]);
}

// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
bool pathPresent(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    const char visited  = 'V';
    const char wall     = 'X';
    const char pit      = '@';
    
    enum directions {
        north, east, south, west, alwaysLastDirection
    };
    
    // If the start location is equal to the ending location, then we've
    // solved the maze, so return true.
    if (sr == er && sc == ec)
        return true;
 
    // Mark the start location as visited.
    maze[sr][sc] = visited;
    
    //    For each of the four directions,
    for (int direction = north; direction < alwaysLastDirection; direction++)
    {
        int nextRow = sr;
        int nextCol = sc;
        
        switch(direction) {
            case north:
                nextRow--;
                break;
            case east:
                nextCol++;
                break;
            case south:
                nextRow++;
                break;
            case west:
                nextCol--;
                break;
        }
        // Check if it's outside the bounds of the array
        if ((nextRow < 0 || nextRow >= nRows) ||
            (nextCol < 0 || nextCol >= nCols))
            continue;
        
        // If the location one step in that direction (from the start
        // location) is unvisited,
        // then call pathPresent starting from that location (and
        // ending at the same ending location as in the
        // current call).
        // If that returned true,
        // then return true.
        // Note: Also check if it's a wall or a pit
        if (maze[nextRow][nextCol] == visited ||
            maze[nextRow][nextCol] == wall ||
            maze[nextRow][nextCol] == pit)
            continue;

        if (pathPresent(maze, nRows, nCols, nextRow, nextCol, er, ec))
            return true;
    }
    
    // Return false.
    return false;
}


