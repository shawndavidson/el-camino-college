//
//  main.cpp
//  Midterm-Prep
//
//  Created by Shawn Davidson on 10/11/21.
//

#include <iostream>

#include "BankAccount.hpp"
#include "CS1Line.hpp"
#include "Circle.hpp"

using namespace std;

// Recursion practice problems v1
// Return the minimum value in an array of integers
int Min(int A[], int n) {
    if (n == 1)
        return A[0];
    
    if (A[n-1] < Min(A, n-1))
        return A[n-1];
    else
        return Min(A, n-1);
}

// Recursion practice problems v1
// Return the index of the minimum value in an array of integers
int findIndexOfMin(int A[], int n) {
    if (n == 1)
        return 0;
    
    if (A[n-1] < Min(A, n-1))
        return n-1;
    else
        return findIndexOfMin(A, n-1);
}

int countDigits(int digit, int numb) {
    if (numb == 0)
        return 0;
    
    int last_digit = numb % 10;
    int next_numb  = numb / 10;
    
    if (last_digit == digit)
        return 1 + countDigits(digit, next_numb);
    else
        return countDigits(digit, next_numb);
}

void testFindIndexOfMin() {
    int A[] = { 3, 5, 1, 7, 9, -3, 10};
    
    std::cout << "Index of min value: " << findIndexOfMin(A, sizeof(A) / sizeof(A[0]));
}

string pairPlus(string n) {
    if (n.length() <= 1)
        return n;
    
    if (n[0] == n[1]) {
        return string() + n[0] + "++" + pairPlus(n.substr(1));
    }else
        return string() + n[0] + pairPlus(n.substr(1));
}

void testPairPlus() {
    string s = "bb";
    
    cout << "pairPlus(" << s << ") => " << pairPlus(s) << endl;
}

int fibonacci(int n) {
    if (n == 0)
        return 0;
    if (n == 1 || n == 2)
        return 1;
    
    return fibonacci(n-1) + fibonacci(n-2);
}

void testFibonacci() {
    for (int i = 0; i < 10; i++) {
        cout << fibonacci(i) << endl;
    }
}

int count_42s(const int array[], const int n) {
    if (n == 0)
        return 0;
    
    if (array[0] == 42)
        return 1 + count_42s(array + 1, n - 1);

    return count_42s(array + 1, n - 1);
}

void printArray(const int a[], const int n) {
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    
    cout << endl;
}

void test_count_42() {
    const int a[] = { 2, 3, 0, 1, 424, 5, 1, 9, 4, -1, 42 };
    const int n = sizeof(a) / sizeof(a[0]);
    
    cout << "Array a = " << endl;
    printArray(a, n);
    
    cout << "count_42s(a) => " << count_42s(a, n) << endl;
}

int count_42s_v2(const int array[], const int low, const int high) {
    if (low > high)
        return 0;
    
    if (low == high)
        return array[low] == 42 ? 1 : 0;
    
    int mid = ((high + low) / 2);
    
    return count_42s_v2(array, low, mid) + count_42s_v2(array, mid+1, high);
}

void test_count_42_v2() {
    const int a[] = { 42, 3, 5, 4, 2, 42, 42 };
    const int n = sizeof(a) / sizeof(a[0]);
    
    cout << "Array a = " << endl;
    printArray(a, n);
    
    cout << "count_42s(a) => " << count_42s_v2(a, 0, n-1) << endl;
}

void deleteB(char* msg) {
    for (char *p = msg; *p != 0; p++) {
        if (*p == 'b' || *p == 'B') {
            char* m = p + 1;
            
            while (*m != 0) {
                *(m-1) = *m;
                m++;
            }
            *(m-1) = 0;
        }
    }
}

void test_deleteB() {
    // https://stackoverflow.com/questions/3036289/best-way-to-create-a-c-string
    //char*s = "Tebo Nebo"; // access violation! Attempts to modify string table
    //string s = "Tebo Nebo";
    char s[] = "Tebo Neb0";

    cout << "s = " << s << endl;
    deleteB(s);
    //deleteB((char*) s.c_str()); // if s is a std::string
    cout << "output = " << s << endl;
}

void testBankAccount() {
    BankAccount ba(500, 1234); // initial amount: $500, password: 1234
    cout << "$" << ba.balance(1234) << endl; // prints $500.00
    cout << "$" << ba.balance(2345) << endl; // prints $-1
    ba.deposit(25, 1234); // deposit $25
    cout << "$" << ba.balance(1234) << endl; // prints $525.00
    ba.withdraw(500, 2345); // should return false
    ba.withdraw(1000, 1234); // should return false
    ba.withdraw(100, 1234); // make the withdraw
    cout << "$" << ba.balance(1234) << endl; // prints $425.00
    ba.setPassword(1234, 2345); // change the password
    ba.withdraw(300, 2345); // make the withdraw
}


void testCS1Line() {
    CS1Line line1(5, 4, -17);
    double slope1 = line1.getSlope();
    // slope1 is assigned -1.25
    bool onLine1 = line1.isOnLine(5, -2);
    // true because 5(5) + 4(-2) + (-17) = 0
    CS1Line line2(-25, 40, 30);
    double slope2 = line2.getSlope();
    // slope2 is assigned 0.625
    bool onLine2 = line2.isOnLine(5, -2);
    // false because -25(5) + 40(-2) + 30 ≠ 0
    
    return;
}

void testCircle() {
    Circle myCircle(2.34);
    double circ = myCircle.getCircumference();
    double area = myCircle.getArea();
    
    cout << "The area of the circle is" << area << " and the circumference is " << circ << endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    testCircle();

    return 0;
}
