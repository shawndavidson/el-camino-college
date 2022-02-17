//
//  LinkedList.hpp
//  CS2-Homework3
//
//  Created by Shawn Davidson on 10/22/21.
//

#ifndef LinkedList_hpp
#define LinkedList_hpp

#include <iostream>
#include <string>
using namespace std;

using ItemType = string;

struct Node {
    ItemType value;
    Node *next;
};

class LinkedList {
    
private:
    Node *head;
    
public:
    
      // default constructor
    LinkedList() : head(nullptr) { }
    
      // copy constructor
    LinkedList(const LinkedList& rhs);
    
      // Destroys all the dynamically allocated memory
      // in the list.
    ~LinkedList();
    
      // assignment operator
    const LinkedList& operator=(const LinkedList& rhs);
    
      // Inserts val at the front of the list
    void insertToFront(const ItemType &val);
    
      // Prints the LinkedList
    void printList() const;
    
      // Sets item to the value at position i in this
      // LinkedList and return true, returns false if
      // there is no element i
    bool get(int i, ItemType& item) const;
    
      // Reverses the LinkedList
    void reverseList();
    
      // Prints the LinkedList in reverse order
    void printReverse() const;
    
      // Appends the values of other onto the end of this
      // LinkedList.
    void append(const LinkedList &other);
    
      // Exchange the contents of this LinkedList with the other one.
    void swap(LinkedList &other);
    
      // Returns the number of items in the Linked List.
    int size() const;
    
private:
    // Helper method that prints the LinkedList in reverse order using indirect recursion
    void printReverseRecurse(const Node* node) const;
    
    // Helper method that reverses the LinkedList using indirect recursion
    void reverseListRecurse(Node* prev, Node* next);
};
#endif /* LinkedList_hpp */
