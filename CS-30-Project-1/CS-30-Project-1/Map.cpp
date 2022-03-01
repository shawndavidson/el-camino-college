//
//  Map.cpp
//  CS-30-Project-1
//
//  Created by Shawn Davidson on 2/28/22.
//

#include <assert.h>
#include "Map.h"

using namespace std;

// Constructor
Map::Map() : m_pRoot(nullptr), m_nSize(0) {
}

// Destructor
Map::~Map() {
    deallocate(m_pRoot);
}

// Delete all dynamically allocated memory
void Map::deallocate(Map::Node* node) {
    // Base case
    if (node == nullptr)
        return;
    
    // Use a recursive post-order traversal to free all the memory allocated to nodes in our binary search tree
    deallocate(node->left);
    deallocate(node->right);
    
    delete(node);
}

// Retrieve the number of items in our Map
int Map::size() const {
    return m_nSize;
}

// Check if our Map is empty
bool Map::empty() const {
    assert(m_pRoot == nullptr);
    
    return m_nSize == 0;
}

// Swap internal state (useful for things such as the copy swap idiom)
void Map::swap(Map& other) {
    if (&other == this)
        return;
    
    // Swap the pointers to our roots
    Map::Node* root = this->m_pRoot;
    this->m_pRoot = other.m_pRoot;
    other.m_pRoot = root;
    
    // Swap the counters that track our size
    int size = this->m_nSize;
    this->m_nSize = other.m_nSize;
    other.m_nSize = size;
    
    // If we add any additional state, handle it here...
}

// Insert an item into the Map
bool Map::insert(const KeyType& key, const ValueType& value) {
    return insert(m_pRoot, key, value, false);
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
    return insert(m_pRoot, key, value, true);
}

bool Map::update(const KeyType& key, const ValueType& value) {
    // This additional search will be on the order of log N. However,
    // O(2 * log N) is still O(log N) so I think it's okay for this exercise.
    // We're trading off maintainability for performance.
    return this->contains(key) ? insert(m_pRoot, key, value, true) : false;
}

// Helper to insert an item into the Map recursively
bool Map::insert(Node*& node, const KeyType& key, const ValueType& value, bool updateIfPresent)
{
    // Base case - we've reached the location where we should store the node
    if (node == nullptr) {
        node = new Node(key, value);
        m_nSize++;
        
        return true;
    }
    
    if (key < node->key)
        return insert(node->left, key, value, updateIfPresent);
    
    if (key > node->key)
        return insert(node->right, key, value, updateIfPresent);
    
    // Invariant: This key is already in the Map
    
    if (updateIfPresent) {
        // Update the existing key to map to the new value
        node->value = value;
        return true;
    }
    
    return false;
}

void Map::dump() {
    cerr << endl;

    dump(m_pRoot);
    
    cerr << endl;
}

void Map::dump(const Node* node) {
    if (node == nullptr)
        return;
        
    dump(node->left);
    
    cerr << node->key << "=>" << node->value << ", ";
    
    dump(node->right);
}

bool Map::get(const KeyType& key, ValueType& value) const {
    return get(m_pRoot, key, value);
}

bool Map::get(const Node* node, const KeyType& key, ValueType& value) const {
    // Base case - the node wasn't found
    if (node == nullptr)
        return false;
    
    if (key < node->key)
        return get(node->left, key, value);
    
    if (key > node->key)
        return get(node->right, key, value);
    
    // We've find our node so let's pass back the value by reference
    value   = node->value;
    
    return true;
}

bool Map::contains(const KeyType& key) const {
    ValueType value;
    return get(key, value);
}
