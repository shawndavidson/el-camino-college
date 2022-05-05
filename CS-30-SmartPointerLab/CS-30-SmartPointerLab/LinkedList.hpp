//
//  LinkedList.hpp
//  CS-30-SmartPointerLab
//
//  Created by Shawn Davidson on 4/21/22.
//

#ifndef LinkedList_hpp
#define LinkedList_hpp

#include <iostream>
#include <memory>
#include <functional> // needed for std::function

#include "FootBallRoster.hpp"

using namespace std;

typedef FootBallPlayer ItemType;

struct Node {
    ItemType            value;
    shared_ptr<Node>    next;
};

// Stream operator for outputting a LinkedList 
ostream& operator<<(ostream& os, const LinkedList& list);

// Stream operator for outputting a FootBallPlayer
ostream& operator<<(ostream& os, const FootBallPlayer& player);

class LinkedList {

private:
    shared_ptr<Node> head;
    
public:
    // default constructor
    LinkedList() noexcept = default;
    
    // copy constructor
    LinkedList(const LinkedList& rhs);
    
    // Destructor
    ~LinkedList() = default;

    void insertToFront(ItemType val);
    
    void printList(ostream& os) const;
        
    void deleteItem(ItemType v);
    
    // Find the first item in the list that satisfies a given predicate function (returns true).
    // If an item is found, the return value of this function is true and the item is passed back by reference as an argument. Otherwise, it returns
    // false and argument item is not changed.
    bool findItem(ItemType& item, std::function<bool(const ItemType&)> predicate);
            
    // assignment operator
    const LinkedList& operator=(const LinkedList& rhs);
    
    // Equality Operator
    bool operator==(const LinkedList& rhs) const noexcept;
    
private:
    // Swap our internal state with another instance (supports the copy-swap idiom).
    void swap(LinkedList& other) noexcept;
};

#endif /* LinkedList_hpp */
