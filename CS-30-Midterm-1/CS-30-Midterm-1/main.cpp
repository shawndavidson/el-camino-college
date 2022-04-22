//
//  main.cpp
//  CS-30-Midterm-1
//
//  Created by Shawn Davidson on 4/7/22.
//

#include <iostream>
#include <iostream>
#include <memory>
using namespace std;
 
struct cs30 {
    string section;
    int numstudents;
};
 
int main( ) {
    
     
//    shared_ptr<cs30> sp1(make_shared<cs30>());  // a
    auto sp1(make_shared<cs30>());  // a

  
//    shared_ptr<cs30> sp2(sp1);  // b
    auto sp2(sp1);  // b

    cout << "Enter the section : ";
 
    cin >> sp1->section; // c
     cout << "Enter the number of students: ";
 
    cin >> sp2->numstudents; // d
     
     {
         shared_ptr<cs30> sp3;  // e
 
         sp3 = sp1;  // f
        cout << "reference count " << sp1.use_count(); // g
     }
     
    weak_ptr<cs30> w1 = sp1;
      
    cout << "Section " << w1.lock()->section << endl; // i
      
    cout << "Num Students " << sp1->numstudents << endl; // j
     
//    unique_ptr<cs30> up1(make_unique<cs30>());  // k
    auto up1(make_unique<cs30>());  // k

    unique_ptr<cs30> up2;  // l
     
    up2 = std::move(up1);  // m
 
     cout << "reference count " << sp1.use_count();  // n
}



/*
 #include <vector>
#include <string>
#include <utility>
#include <map>
using namespace std;
 


 void printContacts(
 map<string, vector<pair<string, string>>>& contacts) {
 
  // YOUR CODE GOES HERE
    for (auto numbers : contacts) {
        cout << numbers.first << endl;
        
        for (auto pairs : numbers.second) {
            cout << "      " << pairs.first << ": " << pairs.second << endl;
        }
    }
}

void printContacts2(
 map<string, vector<pair<string, string>>>& contacts) {
 
  // YOUR CODE GOES HERE
    for (auto numbers = begin(contacts);
         numbers != end(contacts);
         numbers++) {
        cout << numbers->first << endl;
        
        for (auto pairs = begin(numbers->second);
             pairs != end(numbers->second);
             pairs++) {
            cout << "      " << pairs->first << ": " << pairs->second << endl;
        }
    }
}
 
int main() {
     
    map<string, vector<pair<string, string>>> contacts;
     
   // emplace just pushes the two strings as a pair to the
   // back of the vector. It's similar to push_back.
    contacts["Jerry"].emplace_back("home:", "3104444444");
    contacts["Jerry"].emplace_back("cell:", "2135555555");
    contacts["Sarah"].emplace_back("email:", "s@elco.edu");
    contacts["Sarah"].emplace_back("cell:", "8186666666");
     
    printContacts(contacts);
    
    printContacts2(contacts);
}
*/
