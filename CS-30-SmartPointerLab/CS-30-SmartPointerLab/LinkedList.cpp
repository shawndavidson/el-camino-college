//
//  LinkedList.cpp
//  CS-30-SmartPointerLab
//
//  Created by Shawn Davidson on 4/21/22.
//

#include "LinkedList.hpp"

ostream& operator<<(ostream& os, const LinkedList& list)
{
    list.printList(os);
    return os;
}

ostream& operator<<(ostream& os, const FootBallPlayer& player)
{
    os << player.name << " #" << player.num << endl;
    return os;
}

// Exception safety: Strong Guarantee
void LinkedList::insertToFront(ItemType val) {
//        Node *p = new Node;
    auto p = make_shared<Node>();
    p->value = val;
    p->next = head;
    
    head = p;
}

// copy constructor
// Exception Safety: Strong Guarantee
LinkedList::LinkedList(const LinkedList& rhs) {
    // code goes here
    
    // If rhs is just an alias for this, do nothing
    if (this == &rhs)
        return;
    
    // If the other list is empty, just nullify our head
    if (rhs.head.get() == nullptr) {
        head.reset();
        return;
    }
    
    // Create a new head that's a copy of the rhs
    shared_ptr<Node> newHead = make_shared<Node>();

    newHead->value = rhs.head->value;
    
    shared_ptr<Node> copy   = newHead;

    shared_ptr<Node> other         = rhs.head->next;
    
    while (other.get() != nullptr) {
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

void LinkedList::swap(LinkedList& other) noexcept {
    shared_ptr<Node> _head = head;
    head = other.head;
    other.head = _head;
}

void LinkedList::printList(ostream& os = cout) const {
    for (auto p = head; p != nullptr; p = p->next)
        os << p->value << " ";
    os << endl;
}

LinkedList::~LinkedList() {
    
    // The smart pointers will take care of deallocation
//        Node *p;
//
//        while (head != nullptr) {
//            p = head;
//            head = head->next;
//            delete p;
//        }
}

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

void LinkedList::deleteItem(ItemType v) {
    
    // This function points a pointer one before the node
    // that should be deleted. It first checks if the list is
    // empty or the item to be deleted if the first node.
    
    if (head == nullptr)
        return;
    if (head->value == v)
    {
//            Node *p = head;
        head = head->next;
//            delete p;
        return;
    }
//        Node *p = head;
    shared_ptr<Node> p;
    while (p.get() != nullptr) {
        if (p->next.get() != nullptr && v == p->next->value)
            break;
        p = p->next;
    }
    if (p.get() == nullptr) // not found
        return;
    //shared_ptr<Node> q = p->next;
    //p->next = q->next;
//        delete q;
    p->next = p->next->next;
}

bool LinkedList::findItem(ItemType v) {

    // return true or false if v is in List
    return true;
}

//void LinkedList::insertToRear(ItemType val) {
//
//    // inserts a node with value val at the end of the list
//}

// equality operator
bool LinkedList::operator==(const LinkedList& rhs) const noexcept {
    if (this == &rhs)
        return true;
    
    shared_ptr<Node> p      = head;
    shared_ptr<Node> other  = rhs.head;
    
    while (p.get() != nullptr) {
        if (other.get() == nullptr || p->value != other->value)
            return false;
        
        p       = p->next;
        other   = other->next;
    }
    
    return p.get() == nullptr && other.get() == nullptr;
}
