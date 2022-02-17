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


template <typename T>
class LinkedList {
    
private:
    struct Node {
        T       value;
        Node    *next;
    };
    
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
    void insertToFront(const T &val);
    
      // Prints the LinkedList
    void printList() const;
    
      // Sets item to the value at position i in this
      // LinkedList and return true, returns false if
      // there is no element i
    bool get(int i, T& item) const;
    
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

// Copy Constructor
template <typename T>
LinkedList<T>::LinkedList(const LinkedList& rhs) : head(nullptr) {
    if (this == &rhs || rhs.head == nullptr)
        return;
    
    // Invariant: rhs has at least one element
    
    head    = new Node;
    
    Node* h = head;
    
    // Deep copy all of the elements from the rhs
    Node* r = rhs.head;
        
    while (r != nullptr) {
        // Copy the value and create another node if the rhs has more elements
        h->value = r->value;
        h->next  = r->next ? new Node : nullptr;
        
        r = r->next;
    }
}


// Destructor
template <typename T>
LinkedList<T>::~LinkedList() {
    // Walk the list and delete each node behind us
    while (head != nullptr) {
        Node *prev = head;
        
        head = head->next;
        delete prev;
    }
}

// Assignment Operator
template <typename T>
const LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
{
    if (this == &rhs)
        return *this;
    
    // Copy swap idiom
    LinkedList<T> temp(rhs);
    this->swap(temp);
    
    return *this;
}


// Inserts val at the front of the list
template <typename T>
void LinkedList<T>::insertToFront(const T &val) {
    // Create the new node with val
    Node* node  = new Node;
    
    node->value = val;
    node->next  = head;
    
    // Set the head to the new node
    head        = node;
}

// Prints the LinkedList
template <typename T>
void LinkedList<T>::printList() const {
    // Walk the list and print each value
    for (Node* node = head; node != nullptr; node = node->next) {
        cout << node->value << " ";
    }
    cout << endl;
}

// Sets item to the value at position i in this
// LinkedList and return true, returns false if
// there is no element i
template <typename T>
bool LinkedList<T>::get(int i, T& item) const {
    Node* node = head;
    
    for (int j = 0; node != nullptr; j++, node = node->next) {
        if (j == i) {
            item = node->value;
            return true;
        }
    }
    
    return false;
}

// Reverses the LinkedList
template <typename T>
void LinkedList<T>::reverseList() {
    if (head == nullptr || head->next == nullptr)
        return;
    
    // Preserve the next element before we mark the new end of the list
    // so we can recursely walk the remainder of the list
    Node* next = head->next ? head->next : nullptr;
    
    // The head becomes the tail so terminate the list.
    if (head)
        head->next = nullptr;
    
    reverseListRecurse(head, next);
}

// Reverses the LinkedList
template <typename T>
void LinkedList<T>::reverseListRecurse(Node* prev, Node* next) {
    // If there is another element in the list then recurse. Otherwise, mark the new head.
    if (next->next != nullptr)
        reverseListRecurse(next, next->next);
    else
        head = next;
    
    // Reverse the direction of our links
    next->next = prev;
}

// Prints the LinkedList in reverse order
template <typename T>
void LinkedList<T>::printReverse() const {
    printReverseRecurse(head);
    cout << endl;
}

template <typename T>
void LinkedList<T>::printReverseRecurse(const Node* node) const {
    if (node == nullptr)
        return;
        
    if (node->next)
        printReverseRecurse(node->next);
    
    cout << node->value << " ";
}

// Appends the values of other onto the end of this
// LinkedList.
template <typename T>
void LinkedList<T>::append(const LinkedList<T> &other)
{
    const int maxSize = other.size();
        
    // If the other list is empty, there's nothing to do
    if (other.head == nullptr)
        return;
    
    // If our list is empty just copy the other list
    if (head == nullptr) {
        // Leverage the copy constructor to create a new instance (like the copy idiom technique)
        LinkedList<T> temp(other);
        this->swap(temp);
        
        return;
    }
    
    // Find the tail of this list
    Node* node = head;
    
    while (node->next != nullptr)
        node = node->next;
        
    // Create a new node to append the first element of the other list
    node->next = new Node;
    
    node = node->next;
    
    // Invariant:
    // node points to the last element
    
    // Walk the other list. Be sure to handle the case where append() is called
    // with the same list by checking maxSize, i.e. myList.append(myList). We check maxSize to avoid
    // an infinite loop.
    Node const* o = other.head;
    
    for(int i = 0; o != nullptr && i < maxSize; i++) {
        // Copy the value and create the next node
        node->value = o->value;
        node->next  = (o->next && i < maxSize-1) ? new Node : nullptr;

        node = node->next;
        
        o = o->next;
    }
}

// Exchange the contents of this LinkedList with the other one.
template <typename T>
void LinkedList<T>::swap(LinkedList<T> &other) {
    Node* temp = other.head;
    other.head = this->head;
    this->head = temp;
}

// Returns the number of items in the Linked List.
template <typename T>
int LinkedList<T>::size() const {
    int count = 0;
    
    for (Node* node = head;node != nullptr; node = node->next) {
        count++;
    }
    
    return count;
}


#endif /* LinkedList_hpp */
