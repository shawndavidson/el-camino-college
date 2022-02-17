//
//  LinkedList.cpp
//  CS2-Homework3
//
//  Created by Shawn Davidson on 10/22/21.
//

#include <iostream>
#include <string>
#include "LinkedList.hpp"

using namespace std;

// Copy Constructor
LinkedList::LinkedList(const LinkedList& rhs) : head(nullptr) {
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
LinkedList::~LinkedList() {
    // Walk the list and delete each node behind us
    while (head != nullptr) {
        Node *prev = head;
        
        head = head->next;
        delete prev;
    }
}

// Assignment Operator
const LinkedList& LinkedList::operator=(const LinkedList& rhs)
{
    if (this == &rhs)
        return *this;
    
    // Copy swap idiom
    LinkedList temp(rhs);
    this->swap(temp);
    
    return *this;
}


// Inserts val at the front of the list
void LinkedList::insertToFront(const ItemType &val) {
    // Create the new node with val
    Node* node  = new Node;
    node->value = val;
    node->next  = head;
    
    // Set the head to the new node
    head        = node;
}

// Prints the LinkedList
void LinkedList::printList() const {
    // Walk the list and print each value
    for (Node* node = head; node != nullptr; node = node->next) {
        cout << node->value << " ";
    }
    cout << endl;
}

// Sets item to the value at position i in this
// LinkedList and return true, returns false if
// there is no element i
bool LinkedList::get(int i, ItemType& item) const {
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
void LinkedList::reverseList() {
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
void LinkedList::reverseListRecurse(Node* prev, Node* next) {
    // If there is another element in the list then recurse. Otherwise, mark the new head.
    if (next->next != nullptr)
        reverseListRecurse(next, next->next);
    else
        head = next;
    
    // Reverse the direction of our links
    next->next = prev;
}

// Prints the LinkedList in reverse order
void LinkedList::printReverse() const {
    printReverseRecurse(head);
    cout << endl;
}

void LinkedList::printReverseRecurse(const Node* node) const {
    if (node == nullptr)
        return;
        
    if (node->next)
        printReverseRecurse(node->next);
    
    cout << node->value << " ";
}

// Appends the values of other onto the end of this
// LinkedList.
void LinkedList::append(const LinkedList &other)
{
    const int maxSize = other.size();
        
    // If the other list is empty, there's nothing to do
    if (other.head == nullptr)
        return;
    
    // If our list is empty just copy the other list
    if (head == nullptr) {
        // Leverage the copy constructor to create a new instance (like the copy idiom technique)
        LinkedList temp(other);
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
void LinkedList::swap(LinkedList &other) {
    Node* temp = other.head;
    other.head = this->head;
    this->head = temp;
}

// Returns the number of items in the Linked List.
int LinkedList::size() const {
    int count = 0;
    
    for (Node* node = head;node != nullptr; node = node->next) {
        count++;
    }
    
    return count;
}


//////////////////////////////////////////////////////////////////////
// Main
//////////////////////////////////////////////////////////////////////

int main(int argc, const char * argv[]) {
    {
        cout << endl;
        cout << "Testing ::get()" << endl;
        
        LinkedList ls;
        ls.insertToFront("Jack");
        ls.insertToFront("Germaine");
        ls.insertToFront("Agatha");
        ls.insertToFront("Agnes");

        for (int k = 0; k < ls.size(); k++)
        {
            string x;
            ls.get(k, x);
            cout << x << endl;
        }
        //    must write
        //
        //        Agnes
        //        Agatha
        //        Germaine
        //        Jack
    }
    {
        cout << endl;
        cout << "Testing ::get()" << endl;
        
        LinkedList ls;
        ls.insertToFront("George");
        ls.insertToFront("Louise");
        ls.insertToFront("Lionel");
        ls.insertToFront("Helen");

        ls.printList();
        ls.printReverse();
        
        //must write
        //
        //    Helen Lionel Louise George
        //    George Louise Lionel Helen
    }
    {
        cout << endl;
        cout << "Testing ::append()" << endl;
        
        LinkedList e1;
            e1.insertToFront("bell");
            e1.insertToFront("biv");
            e1.insertToFront("devoe");
            LinkedList e2;
            e2.insertToFront("Andre");
            e2.insertToFront("Big Boi");
            e1.append(e2);  // adds contents of e2 to the end of e1
            string s;
            assert(e1.size() == 5  &&  e1.get(3, s)  &&  s == "Big Boi");
            assert(e2.size() == 2  &&  e2.get(1, s)  &&  s == "Andre");
            LinkedList e3;
            e3.insertToFront("Rare Essence");
            e3.insertToFront("JunkYard");
            e3.insertToFront("Chuck Brown");
            e3.append(e3);
            assert(e3.size() == 6  &&  e3.get(3, s)  &&  s == "Chuck Brown");
    }
    {
        cout << endl;
        cout << "Testing ::reverseList()" << endl;
        
        LinkedList e1;
           e1.insertToFront("Sam");
           e1.insertToFront("Carla");
           e1.insertToFront("Cliff");
           e1.insertToFront("Norm");

           e1.reverseList();  // reverses the contents of e1
           string s;
           assert(e1.size() == 4  &&  e1.get(0, s)  &&  s == "Sam");
    }
    {
        cout << endl;
        cout << "Testing ::swap()" << endl;
        
        LinkedList e1;
        e1.insertToFront("A");
        e1.insertToFront("B");
        e1.insertToFront("C");
        e1.insertToFront("D");
        LinkedList e2;
        e2.insertToFront("X");
        e2.insertToFront("Y");
        e2.insertToFront("Z");
        e1.swap(e2);  // exchange contents of e1 and e2
        string s;
        assert(e1.size() == 3  &&  e1.get(0, s)  &&  s == "Z");
        assert(e2.size() == 4  &&  e2.get(2, s)  &&  s == "B");
    }
    
    return 0;
}

