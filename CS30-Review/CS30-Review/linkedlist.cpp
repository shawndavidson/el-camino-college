//
//  linkedlist.cpp
//  CS30-Review
//
//  Created by Shawn Davidson on 2/15/22.
//

#include "linkedlist.hpp"

// copy constructor
LinkedList::LinkedList(const LinkedList& rhs) : head(nullptr) {
    // If we're trying to copy ourself do nothing
    if (&rhs == this || rhs.head == nullptr)
        return;
    
    Node* node = new Node;
    this->head = node;
    
    for (const Node* other = rhs.head; other != nullptr; other = other->next) {
        node->value = other->value;
    }
}

// Destructor
LinkedList::~LinkedList() {
    while (head != nullptr) {
        Node* n = head;
        head = head->next;
        delete n;
    }
}

// assignment operator
const LinkedList& LinkedList::operator=(const LinkedList& rhs) {
    // If we're trying to assign ourself to ourself do nothing
    if (&rhs == this)
        return *this;
    
    // Use the copy swap idiom trick
    LinkedList temp;
    temp.swap(*this);
    
    return *this;
}

// Inserts val at the front of the list
void LinkedList::insertToFront(const ItemType &val) {
    // Create the new node
    Node* node = new Node;
    
    node->value = val;
    node->next  = head;
    
    head = node;
}

// Prints the LinkedList
void LinkedList::printList() const {
    Node* node = head;
    
    while (node != nullptr) {
        cout << node->value << " ";
        
        node = node->next;
    }
    
    cout << endl;
}

// Sets item to the value at position i in this
// LinkedList and return true, returns false if
// there is no element i
bool LinkedList::get(int i, ItemType& item) const {
    Node* node = head;
    
    for (int index = 0; index < i && node != nullptr; index++) {
        node = node->next;
    }
    
    // Invariant: node either points to the ith node OR it's null
    if (node == nullptr)
        return false;
    
    item = node->value;
    
    return true;
}

// Reverses the LinkedList
void LinkedList::reverseList() {
    // Handle an empty list, there's nothing to do
    if (head == nullptr)
        return;
    
    reverseListRecur(head, nullptr);
}

// Prints the LinkedList in reverse order
void LinkedList::printReverse() const {
    // Handle an empty list, there's nothing to do
    if (head == nullptr)
        return;
    
    printReverseRecur(head);
    
    cout << endl;
}

void LinkedList::printReverseRecur(const Node* node) const {
    if (node->next)
        printReverseRecur(node->next);
        
    cout << node->value << " ";
}

// Helps reverse the LinkedList using recursion
void LinkedList::reverseListRecur(Node* current, Node* last) {
    // Is there another node in the list?
    if (current->next)
        reverseListRecur(current->next, current);
     else {
        // We've reached the last element
        head = current;
    }
    
    current->next = last;
}

// Appends the values of other onto the end of this
// LinkedList.
void LinkedList::append(const LinkedList &other) {
    // If the other list is empty, there's nothing to do
    if (other.head == nullptr)
        return;
    
    // Find the end of the list we're copying TO (this)
    Node* last = head;
    
    while(last != nullptr && last->next != nullptr)
        last = last->next;
    
    const int otherLength = other.size();
    
    Node* node = other.head;
    
    // Iterate through the nodes of the list we're copying FROM. Be careful
    // not to exceed the original length of the other list. Otherwise, if the client attempts
    // append ourself it will cause an infinite loop.
    for(int i = 0; i < otherLength && node != nullptr; i++) {
        // Copy this node
        Node* copy  = new Node;
        copy->value = node->value;
        copy->next  = nullptr;
        
        // Attach the copy to the end of our list
        if (last) {
            last->next = copy;
            
            // Track the end of our list
            last = last->next;
        }
        else {
            head = copy;
            last = head;
        }
        
        // Move to the next node in the list we're copying
        node = node->next;
    }
}

// Exchange the contents of this LinkedList with the other one.
void LinkedList::swap(LinkedList &other) {
    Node* temp = head;
    
    head = other.head;
    other.head = temp;
}

// Returns the number of items in the Linked List.
int LinkedList::size() const {
    int count = 0;
    
    Node* node = head;
    
    while(node != nullptr) {
        count++;
        node = node->next;
    }
    
    return count;
}
