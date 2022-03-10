//
//  Map.hpp
//  CS-30-Project-1
//
//  Created by Shawn Davidson on 2/28/22.
//

#ifndef Map_h
#define Map_h

#include <iostream>
#include <string>

using KeyType   = std::string;
using ValueType = double;


///////////////////////////////////////////////////////////////////////////////
/// Map
///////////////////////////////////////////////////////////////////////////////
class Map
{
  public:
    Map();              // Create an empty map (i.e., one with no key/value pairs)
    Map(const Map& rhs);// Copy Constructor
    ~Map();             // Destructor - free dynamically allocated memory
    
    bool empty() const; // Return true if the map is empty, otherwise false.

    int size() const;   // Return the number of key/value pairs in the map.

    bool insert(const KeyType& key, const ValueType& value);
      // If key is not equal to any key currently in the map, and if the
      // key/value pair can be added to the map, then do so and return true.
      // Otherwise, make no change to the map and return false (indicating
      // that either the key is already in the map).

    bool update(const KeyType& key, const ValueType& value);
      // If key is equal to a key currently in the map, then make that key no
      // longer map to the value it currently maps to, but instead map to
      // the value of the second parameter; return true in this case.
      // Otherwise, make no change to the map and return false.

    bool insertOrUpdate(const KeyType& key, const ValueType& value);
      // If key is equal to a key currently in the map, then make that key no
      // longer map to the value it currently maps to, but instead map to
      // the value of the second parameter; return true in this case.
      // If key is not equal to any key currently in the map then add it and
      // return true. In fact this function always returns true.

    bool erase(const KeyType& key);
      // If key is equal to a key currently in the map, remove the key/value
      // pair with that key from the map and return true.  Otherwise, make
      // no change to the map and return false.

    bool contains(const KeyType& key) const;
      // Return true if key is equal to a key currently in the map, otherwise
      // false.

    bool get(const KeyType& key, ValueType& value) const;
      // If key is equal to a key currently in the map, set value to the
      // value in the map that that key maps to, and return true.  Otherwise,
      // make no change to the value parameter of this function and return
      // false.

    bool get(int i, KeyType& key, ValueType& value) const;
      // If 0 <= i < size(), copy into the key and value parameters the
      // key and value of one of the key/value pairs in the map and return
      // true.  Otherwise, leave the key and value parameters unchanged and
      // return false.  (See below for details about this function.)

    void swap(Map& other);
      // Exchange the contents of this map with the other one.
    
    void dump() const;
      // Dump debugging info to the error stream
    
    Map& operator=(const Map& rhs);
      // Assignment Operator
    
    // Private Data Member(s)
private:
    // Node definition for a BST (Binary Search Tree)
    struct Node {
        // Default Constructor
        Node(const KeyType& key = KeyType(), const ValueType& value = ValueType())
         : key(key), value(value), left(nullptr), right(nullptr)
        {};

        KeyType     key;
        ValueType   value;
        
        struct Node* left;
        struct Node* right;
    } *m_pRoot;
    
    int m_nSize;
    
    // Private Method(s)
private:
    void copy(Node*& node, const Node* otherNode);
      // Helper to deep copy another Map recursively
    void deallocate(Map::Node* node);
      // Helper to release all memory for all nodes recursively
    bool insert(Node*& node, const KeyType& key, const ValueType& value, bool updateIfPresent);
      // Helper to insert a node that uses recursion
    bool get(const Node* node, const KeyType& key, ValueType& value) const;
      // Helper to get a node that uses recursion
    bool get(Node* node, int& currentIndex, int targetIndex, KeyType& key, ValueType& value) const;
      // Helper to get a node by index that uses recursion
    bool erase(Node*& node, const KeyType& key);
      // Helper to erase a node that uses recursion
    void dump(const Node* node) const;
      // Helper to dumb that uses recursion
};

///////////////////////////////////////////////////////////////////////////////
/// Non-Member Functions
///////////////////////////////////////////////////////////////////////////////
bool combine(const Map& m1, const Map& m2, Map& result);

void subtract(const Map& m1, const Map& m2, Map& result);

#endif /* Map_h */
