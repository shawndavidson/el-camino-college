//
//  main.cpp
//  CSInterview
//
//  Created by Shawn Davidson on 7/5/22.
//

#include <iostream>

using namespace std;

struct Node {
    // Data
    int     value;
    
    // Pointer to the next Node in our list
    Node*   next;
};

class LinkedList {
public:
    // Default Constructor
    LinkedList() : head(nullptr), size(0) {
    }
    
    // Destructor
    ~LinkedList() {
        // Iterate through the list
        while (head != nullptr) {
            // Preserve the current node so we can delete it
            Node* prev = head;

            // Advance to the next node
            head = head->next;
            
            // Release the memory allocated to the node
            delete prev;
        }
    }
    
    // Get the number of items in the list
    size_t getSize() const {
        return size;
    }
    
    // Get the value at the specified index
    // Returns true, if the index is valid. Otherwise, false.
    bool get(int index, int& value) const {
        if (index < 0 || index >= getSize())
            return false;
        
        Node* node = head;
        
        for (int i = 0; i < index; i++) {
            node = node->next;
        }
        
        value = node->next->value;
        
        return true;
    }
    
    // Insert a value into the front of the list
    // Returns true, if successful. Otherwise, false.
    bool insertFront(int value) {
        // Create a new node with our value
        Node* node = new Node;
        
        if (node == nullptr) {
            cout << "Unable to allocate memory" << endl;
            return false;
        }
        
        node->value = value;
        node->next  = head;
     
        // Point the head to the new beginning of the list
        head = node;
        
        // Track how many items are in the list
        size++;
        
        return true;
    }
    
    // Insert a value after a specific node the list
    // Returns true, if successful. Otherwise, false.
    bool insertAfter(int beforeValue, int value) {
        Node* before = search(beforeValue);
        
        if (before == nullptr)
            return false;
        
        // Create a new node with our value
        Node* node = new Node;
        
        if (node == nullptr) {
            cout << "Unable to allocate memory" << endl;
            return false;
        }
        
        // Set our value
        node->value = value;
        
        // Point to the next node
        node->next  = before->next;
     
        // Make the previous node point to us
        before->next = node;
        
        // Track how many items are in the list
        size++;
        
        return true;
    }
    
    bool insertBefore(int afterValue, int value) {
        // Create a new node with our value
        Node* newNode = new Node;
        
        if (newNode == nullptr) {
            cout << "Unable to allocate memory" << endl;
            return false;
        }
        
        // Set our value
        newNode->value = value;
        
        // Is the head the value we're looking for?
        if (head && head->value == afterValue) {
            // Point to the current head since we come before it
            newNode->next = head;
            
            // Now, we're the head
            head = newNode;
            
            // Track the updated size
            size++;
            
            return true;
        }
        
        Node* node = head;
        
        // Iterate through the list to find the node BEFORE the one containing
        // afterValue
        while (node->next != nullptr) {
            // Does the next node contain afterValue?
            if (node->next->value == afterValue) {
                // Insert ourselves
                newNode->next   = node->next;
                node->next      = newNode;
                
                // Track updated size
                size++;
                return true;
            }
            // Advance to the next node
            node = node->next;
        }
        
        // Release memory since afterValue wasn't found
        delete newNode;
        
        return false;
    }
    
    // Remove the first occurance of a node with the given value
    // Returns true, if successful. Otherwise, false.
    bool remove(int value) {
        Node* node = head;
        Node* prev = nullptr;
        
        // Iterate through the list
        while (node != nullptr) {
            // Is this the value we're looking for?
            if (node->value == value) {
                // Was there a node before this one?
                if (prev != nullptr) {
                    prev->next = node->next;
                }
                
                // Is this node the head, i.e. first in the list?
                if (head == node) {
                    head = node->next;
                }
                
                // Dellocate the memory
                delete node;
                
                // Track how many items are in the list
                size--;
                
                return true;
            }
            
            // Preserve the previous node so we can skip over the deleted
            // node when we find it
            prev = node;
            
            // Advance to the next node
            node = node->next;
        }
        
        // Indicate that the value wasn't found
        return false;
    }
    
    // Reverse the list
    void reverse() {
        // Preserve the head because this will point to the last node AFTER
        // we reverse the list
        Node* tail = head;
        
        // Delegate to our recursive helper method (override)
        reverse(head);
        
        // Mark the new end of the list
        tail->next = nullptr;
    }
    
    // Print all of the items in the list
    void print() const {
        // Iterate through the list
        for(Node* node = head; node != nullptr; node = node->next) {
            // Print each value
            cout << node->value << " ";
        }
        cout << endl;
    }
    
private:
    // Search for the first occurance of a value
    // Returns the node if it's found. Otherwise, nullptr
    Node* search(int value) const {
        Node* node = head;
        
        // Iterate through the list
        while (node != nullptr) {
            // Is this the value we're looking for?
            if (node->value == value) {
                return node;
            }
            
            // Advance to the next node
            node = node->next;
        }
        
        // Indicate that the value wasn't found
        return nullptr;
    }
    
    // Reverse the list (recursive helper method)
    Node* reverse(Node* node) {
        // Have we reached the end of the list?
        if (node->next == nullptr) {
            // Mark our new head, i.e. pointer to first node
            head = node;
        }else {
            Node* next = reverse(node->next);
            
            // Reverse the direction of our link; make the next node point
            // back at us
            next->next = node;
        }
        
        return node;
    }
    
private:
    // Pointer to the first Node in our list
    Node*   head;
    
    // Track the size seperately so we don't have to count every item
    // to check the size
    size_t  size;
};


int main(int argc, const char * argv[]) {
    // Instantiate an object from class LinkedList
    LinkedList myList;
    
    // Insert integers 0...9
    for (int i = 0; i < 10; i++) {
        myList.insertFront(i);
    }
    
    // Search for the node containing the value 4
    int value;
    
    myList.get(4, value);
    
    // Verify that it actually has the value 4
    assert(myList.get(4, value) == true);
    assert(value == 4);
    assert(myList.getSize() == 10);
    
    // Print the full show (no changes yet)
    cout << "Inserted 0-9 in that order:" << endl;
    myList.print();
    
    // Print the list (without the 0 we deleted)
    cout << endl;
    cout << "Removed 0 leaving 1-9:" << endl;
    myList.remove(0);
    assert(myList.getSize() == 9);
    myList.print();
    
    cout << endl;
    cout << "Reversed List:" << endl;
    myList.reverse();
    myList.print();
    
    cout << endl;
    cout << "Insert 44 after the 4" << endl;
    myList.insertAfter(4, 44);
    myList.print();
    
    cout << endl;
    cout << "Insert 99 before the 9" << endl;
    myList.insertBefore(9, 99);
    myList.print();
    
    cout << endl;
    cout << "Insert 0 before the 1" << endl;
    myList.insertBefore(1, 0);
    myList.print();

    cout << endl;
    
    return 0;
}
