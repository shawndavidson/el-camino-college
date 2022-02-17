//
//  main.cpp
//  C++ReviewWeek1
//
//  Created by Shawn Davidson on 9/1/21.
//

#include <iostream>

using namespace std;

/* Problem 1a
int main()
{
    int arr[3] = { 5, 10, 15 };
    int* ptr = arr;

    *ptr = 10;          // set arr[0] to 10
    *(ptr + 1) = 20;      // set arr[1] to 20
    ptr += 2;
    ptr[0] = 30;        // set arr[2] to 30

    while (ptr >= arr)
    {
        //ptr--;
        cout << ' ' << *ptr;    // print values
        ptr--;
    }
    cout << endl;
}
 */

/* Problem 1b
 */
//void findDisorder(int arr[], int n, int** p)
//{
//    for (int k = 1; k < n; k++)
//    {
//        if (arr[k] < arr[k-1])
//        {
//             *p = arr + k;
//             return;
//        }
//    }
//    *p = nullptr;
//}
//
//int main()
//{
//    int nums[6] = { 10, 20, 20, 40, 30, 50 };
//    int* ptr;
//
//    findDisorder(nums, 6, &ptr);
//    if (ptr == nullptr)
//        cout << "The array is ordered" << endl;
//    else
//    {
//            cout << "The disorder is at address " << ptr << endl;
//            cout << "It's at index " << ptr - nums << endl;
//            cout << "The item's value is " << *ptr << endl;
//    }
//}

/* Problem 1c */
//#include <iostream>
//#include <cmath>
//using namespace std;
//
//void hypotenuse(double leg1, double leg2, double* resultPtr)
//{
//    *resultPtr = sqrt(leg1*leg1 + leg2*leg2);
//}
//
//int main()
//{
//    double value;
//    double* p = &value;
//    hypotenuse(1.5, 2.0, p);
//    cout << "The hypotenuse is " << *p << endl;
//}

/* Problem 1d */
// return true if two C strings are equal
//bool match(char *str1, char *str2)
//{
//  while (*str1 != 0  &&  *str2 != 0)  // zero bytes at ends
//  {
//      if (*str1 != *str2)  // compare corresponding characters
//          return false;
//      str1++;            // advance to the next character
//      str2++;
//  }
//  return *str1 == *str2;   // both ended at same time?
//}
//
//int main()
//{
//  char a[10] = "pointy";
//  char b[10] = "pointless";
//
//  if (match(a,b))
//      cout << "They're the same!\n";
//}

/* Problem 1e */
//#include <iostream>
//using namespace std;
//
//int* computeSquares(int& n)
//{
//    static int arr[10];
//    n = 10;
//    for (int k = 0; k < n; k++)
//        arr[k] = (k+1) * (k+1);
//    return arr;
//}
//
//void f()
//{
//    int junk[100];
//    for (int k = 0; k < 100; k++)
//        junk[k] = 123400000 + k;
//}
//
//int main()
//{
//    int m;
//    int* ptr = computeSquares(m);
//    f();
//    for (int i = 0; i < m; i++)
//        cout << ptr[i] << ' ';
//}


/* Problem 3a
 */
//#include <iostream>
//
//using namespace std;
//
//double computeAverage(const double* scores, int nScores)
// {
//     double tot = 0;
//     for (int i = 0; i < nScores; i++)
//     {
//         tot += scores[i];
//     }
//     return tot/nScores;
// }
//
//
//int main()
//{
//    double arr[5] = {1,1,10,10};
//
//    double average = computeAverage(arr, 4);
//
//    cout << "Average is: " << average << endl;
//}

/* Problem 3b
 */

// This function searches through str for the character chr.
 // If the chr is found, it returns a pointer into str where
 // the character was first found, otherwise nullptr (not found).

// const char* findTheChar(char* str, char chr)
// {
//     for (;*str != 0; str++)
//         if (*str == chr)
//             return str;
//
//     return nullptr;
// }

/* problem 3c */
//const char* findTheChar(const char* str, char chr)
//{
//    for (int k = 0; *(str+k) != 0; k++)
//        if (*(str+k) == chr)
//            return str + k;
//
//    return nullptr;
//}
//
//int main() {
//    char arr[] = "alldogsgotoheaven";
//    char ch = 'g';
//
//    const char* p = findTheChar(arr, ch);
//
//    if (p == nullptr)
//        cout << "Character not found!";
//    else
//        cout << "Character was found in string at: " << p;
//
//    cout << endl;
//}

/* Problem 4 */
//#include <iostream>
//
//    using namespace std;
//
//    int* minimart(int* a, int* b)
//    {
//        if (*a < *b)
//            return a;
//        else
//            return b;
//    }
//
//    void swap1(int* a, int *b)
//    {
//        int* temp = a;
//        a = b;
//        b = temp;
//    }
//
//    void swap2(int* a, int *b)
//    {
//        int temp = *a;
//        *a = *b;
//        *b = temp;
//    }
//
//    int main()
//    {
//        int array[6] = { 5, 3, 4, 17, 22, 19 };
//
//        int* ptr = minimart(array, &array[2]);
//        ptr[1] = 9;
//        ptr += 2;
//        *ptr = -1;
//        *(array+1) = 79;
//
//        cout << "diff=" << &array[5] - ptr << endl;
//
//        swap1(&array[0], &array[1]);
//        swap2(array, &array[2]);
//
//        for (int i = 0; i < 6; i++)
//            cout << array[i] << endl;
//    }

/* Problem 5 */
//#include <iostream>
//
//using namespace std;
//
//void deleteG(char *str)
//{
//    while(*str != 0)
//    {
//        if (*str == 'g' || *str == 'G')
//        {
//            char* p = str + 1;
//
//            do {
//                *(p-1) = *p;
//            }while (*(p++) != 0);
//        }
//        str++;
//    }
//}
//
//int main()
//{
//    char msg[100] = "I recall the glass gate next to Gus in Lagos, near the gold bridge.";
//    deleteG(msg);
//    cout << msg;  // prints   I recall the lass ate next to us in Laos, near the old bride.
//}

// Recursive Problem #1
//int countNegative(const int a[], int count)
//{
//    if (count == 0) return 0;
//
//    return (a[count-1] < 0 ? 1 : 0) + countNegative(a, count - 1);
//}
//
//int main()
//{
//    int a[] = { -1, 2, 3, -1, 0, -1, 4};
//
//    cout << "The array has " << countNegative(a, 7) << " negative numbers" << endl;
//}

//// Recursive Problem #2
//bool anyNegatives(const int a[], int count)
//{
//    if (count == 0)
//        return false;
//
//    return a[count-1] < 0 || anyNegatives(a, count-1);
//}
//
//int main()
//{
//    int a[] = { -1, 2, 3, -1, 0, -1, 4};
//
//    if (anyNegatives(a, 7))
//        cout << "The array contains negative numbers" << endl;
//    else
//        cout << "The array does NOT contain negative numbers" << endl;
//
//}

// Recursive Problem #3
//int firstNegative(const int a[], int count)
//{
//    if (count == 0)
//        return -1;
//
//    if (a[0] < 0)
//        return 0;
//
//    int num = firstNegative(a + 1, count - 1);
//
//    if (num == -1)
//        return -1;
//    else
//        return num + 1;
//}
//
//int main()
//{
//    int a[] = { 1, 2, 3, -1, 0, -1, 4};
//
//    cout << "The first negative was found at index: " << firstNegative(a, 7) << endl;
//}

// Homework #1
// Returns the product of two positive integers, m and n,
// using only repeated addition.
//int multi(unsigned int m, unsigned int n)
//{
//    if (m == 0 || n == 0)
//        return 0;
//
//    return m + multi(m, n - 1);
//}
//
//int main()
//{
//    unsigned int a = 1, b = 9;
//
//    cout << "The product of " << a << " and " << b << " is " << multi(a, b) << endl;
//}

// Returns the number of occurrences of digit in the decimal
// representation of num. digit is an int between 0 and 9
// inclusive.
//
// Pseudocode Example:
//    countDigit(18838, 8) => 3
//    countDigit(55555, 3) => 0
//    countDigit(0, 0)     => 0 or 1 (either is fine)
//
//int countDigit(int num, int digit)
//{
//    if (num == 0)
//        return 0;
//
//    int whatsLeft = num / 10;
//    int remainder = num % 10;
//
//    if (remainder == digit)
//        return countDigit(whatsLeft, digit) + 1;
//    else
//        return countDigit(whatsLeft, digit);
//}
//
//int main()
//{
//    cout << "countDigits returned " << countDigit(18838, 8);
//}

// Returns a string where the same characters next each other in
// string n are separated by "--". You can use substr in this problem
//
// Pseudocode Example:
//    pairMinus("goodbye") => "go--odbye"
//    pairMinus("yyuu")    => "y--yu--u"
//    pairMinus("aaaa")    => "a--a--a--a"
//
//string pairMinus(string n)
//{
//    if (n.length() < 2)
//        return n;
//
//    if (n[0] == n[1])
//    {
//        string ch;
//
//        ch += n[0];
//
//        return ch + "--" + pairMinus(n.substr(1));
//    }
//
//    return n[0] + pairMinus(n.substr(1));
//}
//
//int main()
//{
//    string s = "goodbye";
//
//    cout << "pairMinus(\"" << s << "\") returned " << pairMinus(s) << endl;
//}

// Homework #1
// str contains a single pair of parenthesis, return a new string
// made of only the parenthesis and whatever those parensthesis
// contain. You can use substr in this problem.
//
//  Pseudocode Example:
//     findParen("abc(ghj)789") => "(ghj)"
//     findParen("(x)7")        => "(x)"
//     findParen("4agh(y)")     => "(y)"
//
//string findParen(string str)
//{
//    if (str.length() < 2)
//        return "";
//
//    if (str[0] == '(' && str[str.length()-1] == ')')
//        return str;
//
//    size_t pos = str[0] == '(' ? 0 : 1;
//    size_t len = str[str.length() - 1] == ')' ? str.length() : (str.length() - 1);
//    len -= pos;
//
//    return findParen(str.substr(pos, len));
//}
//
//int main()
//{
//    string s = "abc(ghj)789"; // (x)7"; // 4agh(y)"; //"abc(ghj)789";
//
//    cout << "findParen(\"" << s << "\")" << " => " << findParen(s) << endl;
//}

// Homework #1
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

int main()
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
