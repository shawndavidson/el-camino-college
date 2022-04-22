//
//  LinkedList.cpp
//  CS-30-SmartPointerLab
//
//  Created by Shawn Davidson on 4/21/22.
//

#include "LinkedList.hpp"

// Stream operator to output a LinkedList
ostream& operator<<(ostream& os, const LinkedList& list)
{
    list.printList(os);
    return os;
}

// Stream operator to output a FootBallPlayer
ostream& operator<<(ostream& os, const FootBallPlayer& player)
{
    os << player.name << " #" << player.num << endl;
    return os;
}

// Exception safety: Strong Guarantee
void LinkedList::insertToFront(ItemType val) {
    auto p = make_shared<Node>();
    p->value = val;
    p->next = head;
    
    head = p;
}

// copy constructor
// Exception Safety: Strong Guarantee
LinkedList::LinkedList(const LinkedList& rhs) {
    // If rhs is just an alias for this, do nothing
    if (this == &rhs)
        return;
    
    // If the other list is empty, just nullify our head
    if (rhs.head == nullptr) {
        head.reset();
        return;
    }
    
    // Create a new head that's a copy of the rhs
    shared_ptr<Node> newHead = make_shared<Node>();

    newHead->value = rhs.head->value;
    
    shared_ptr<Node> copy   = newHead;

    shared_ptr<Node> other         = rhs.head->next;
    
    while (other != nullptr) {
        // Create a copy of the next node from the rhs
        copy->next  = make_shared<Node>();
        copy->next->value = other->value;
        
        // Advanced to the next node on the rhs
        other   = other->next;
        copy    = copy->next;
    }
    
    // Lastly, switch to the new head to maintain a strong guarantee with
    // respect to exception safety
    head = newHead;
}

void LinkedList::printList(ostream& os = cout) const {
    for (auto p = head; p != nullptr; p = p->next)
        os << p->value;
    os << endl;
}

void LinkedList::deleteItem(ItemType v) {
    
    // This function points a pointer one before the node
    // that should be deleted. It first checks if the list is
    // empty or the item to be deleted if the first node.
    
    if (head == nullptr)
        return;
    if (head->value == v)
    {
        head = head->next;
        return;
    }

    shared_ptr<Node> p = head;
    while (p != nullptr) {
        if (p->next != nullptr && v == p->next->value)
            break;
        p = p->next;
    }
    if (p == nullptr) // not found
        return;

    p->next = p->next->next;
}

bool LinkedList::findItem(ItemType& item, std::function<bool(const ItemType&)> predicate){
    // return true or false if v is in List
    auto p = head;
    
    while (p != nullptr) {
        if (predicate(p->value)) {
            item = p->value;
            return true;
        }
        p = p->next;
    }

    return false;
}

// assignment operator
// Exception safety: Strong
const LinkedList& LinkedList::operator=(const LinkedList& rhs) {
    // code goes here
    if (this == &rhs)
        return *this;
    
    // Use copy-swap idom to facilitate a strong guarantee (exception safety)
    LinkedList temp(rhs);
    temp.swap(*this);
    
    return *this;
}

// equality operator
bool LinkedList::operator==(const LinkedList& rhs) const noexcept {
    if (this == &rhs)
        return true;
    
    shared_ptr<Node> p      = head;
    shared_ptr<Node> other  = rhs.head;
    
    while (p != nullptr) {
        if (other == nullptr || p->value != other->value)
            return false;
        
        p       = p->next;
        other   = other->next;
    }
    
    return p == nullptr && other == nullptr;
}

void LinkedList::swap(LinkedList& other) noexcept {
    shared_ptr<Node> _head = head;
    head = other.head;
    other.head = _head;
}
