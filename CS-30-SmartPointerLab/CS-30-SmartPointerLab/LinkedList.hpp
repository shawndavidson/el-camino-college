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
#include "FootBallRoster.hpp"

using namespace std;

typedef FootBallPlayer ItemType;

struct Node {
    ItemType value;
    //Node *next;
    shared_ptr<Node> next;
};

// Stream operator for outputting a LinkedList 
ostream& operator<<(ostream& os, const LinkedList& list);

// Stream operator for outputting a FootBallPlayer
ostream& operator<<(ostream& os, const FootBallPlayer& player);

class LinkedList {

private:
//    Node *head=nullptr;
    shared_ptr<Node> head;
    
public:
    // default constructor
    LinkedList() noexcept = default;
    
    void insertToFront(ItemType val);

    // copy constructor
    LinkedList(const LinkedList& rhs);
    
    // assignment operator
    const LinkedList& operator=(const LinkedList& rhs);
    
    void printList(ostream& os) const;
    
    ~LinkedList();
    
    // Not used
//    Node * findLast() {
//
//        // return nullptr if list is empty
//        return nullptr;
//    }
    
    // Not used
//    Node * findSecondLast() {
//
//        // return nullptr if there is no second last
//        return nullptr;
//
//    }
    
    void deleteItem(ItemType v);
    
    //bool findItem(ItemType& item, bool (*predicate)(const ItemType&));
    bool findItem(ItemType& item, std::function<bool(const ItemType&)> predicate);
    
//    void insertToRear(ItemType val);
    
    void swap(LinkedList& other) noexcept;
    
    bool operator==(const LinkedList& rhs) const noexcept;
};

#endif /* LinkedList_hpp */
