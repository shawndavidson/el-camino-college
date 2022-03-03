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

// Copy Constructor
Map::Map(const Map& rhs) : m_pRoot(nullptr), m_nSize(rhs.m_nSize) {
    if (&rhs == this)
        return;
    
    // Perform a deep copy of the given Map
    copy(this->m_pRoot, rhs.m_pRoot);
}

// Deep copy the binary search tree from a given Map recursively
void Map::copy(Node*& node, const Node* otherNode) {
    if (otherNode == nullptr)
        return;
    
    // Perform a pre-order traversal to copy another Map
    node = new Node(otherNode->key, otherNode->value);
    
    copy(node->left, otherNode->left);
    copy(node->right, otherNode->right);
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
    
    // If we add any additional internal state, handle it here...
}

// Insert an item into the Map
bool Map::insert(const KeyType& key, const ValueType& value) {
    return insert(m_pRoot, key, value, false);
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
    return insert(m_pRoot, key, value, true);
}

bool Map::update(const KeyType& key, const ValueType& value) {
    // Leveraging contains() requires an additional search which is O(log N) + O(log N). However,
    // O(2 * log N) is still O(log N) so I think it's okay for this exercise.
    // We're trading off maintainability and ease of implementation for performance.
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

void Map::dump() const {
    cerr << endl;

    dump(m_pRoot);
    
    cerr << endl;
}

void Map::dump(const Node* node) const {
    if (node == nullptr)
        return;
        
    // Perform an In-order traversal of the binary search tree to dump in sorted order
    dump(node->left);
    
    cerr << node->key << "=>" << node->value << ", ";
    
    dump(node->right);
}

// Assignment operator
Map& Map::operator=(const Map& rhs) {
    if (&rhs == this)
        return *this;
    
    // Use the copy swap idiom trick
    Map temp(rhs);
    temp.swap(*this);
    
    return *this;
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

// Retrieve a key-value pair by index
bool Map::get(int i, KeyType& key, ValueType& value) const {
    int currentIndex = 0;
    return get(m_pRoot, currentIndex, i, key, value);
}

// Helper to retrieve a key-value pair by index using recursion
bool Map::get(Node* node, int& currentIndex, int targetIndex, KeyType& key, ValueType& value) const {
    if (node == nullptr)
        return false;
    
    // Use an in-order traversal to check the left and right subtrees to make the indexing ascending in sorted order
    if (get(node->left, currentIndex, targetIndex, key, value))
        return true;
    
    // Is the node at this index the one we're looking for?
    if (currentIndex == targetIndex) {
        key     = node->key;
        value   = node->value;
        
        return true;
    }
    
    // Only advance the index for non-null nodes
    currentIndex++;
    
    return get(node->right, currentIndex, targetIndex, key, value);
}

bool Map::contains(const KeyType& key) const {
    ValueType value;
    return get(key, value);
}

bool Map::erase(const KeyType& key) {
    if (erase(m_pRoot, key)) {
        m_nSize--;
        return true;
    }
    
    return false;
}

bool Map::erase(Node*& node, const KeyType& key) {
    if (node == nullptr) {
        return false;
    }
    
    if (key < node->key)
        return erase(node->left, key);
    
    if (key > node->key)
        return erase(node->right, key);
    
    // Invariant: This node matches the key we're looking for
    
    // Is this node a leaf (no children)?
    if (node->left == nullptr && node->right == nullptr) {
        // Detach this node from its parent
        delete node;
        node = nullptr;

        return true;
    }else if ((node->left == nullptr) != (node->right == nullptr)) {
        // Handle a node with only one child
        Node* temp = node;
        
        // Replace the node with it's only child
        if (node->left != nullptr)
            node = node->left;
        else if (node->right != nullptr)
            node = node->right;
        
        delete temp;

        return true;
    }
    
    // Invariant: The node must have two children
    // Replace this node with the key-value from the largest node from the left subtree
    Node* maxLeftDescendent         = node->left;

    while (maxLeftDescendent->right != nullptr) {
        maxLeftDescendent       = maxLeftDescendent->right;
    }

    node->key   = maxLeftDescendent->key;
    node->value = maxLeftDescendent->value;

    // Recursively delete the largest descendent from the left subtree since we've taken on it's value. It should only have 1 child at the most.
    return erase(node->left, maxLeftDescendent->key);
}

///////////////////////////////////////////////////////////////////////////////
/// Non-Member Functions
///////////////////////////////////////////////////////////////////////////////
// Combine key-value pairs from m1 and m2
// result = m1 + m2
bool combine(const Map& m1, const Map& m2, Map& result) {
    // O(N)
    result = Map(m1);
    
    bool hasDuplicateKey = false;
    
    KeyType     key;
    ValueType   value;
    
    int m2Size = m2.size(); // O(N)

    for (int i = 0; i < m2Size; i++) { // O(N)
        if (!m2.get(i, key, value)) { // O(log N)
            // What do I do? Throw?
        }
        
        if (!result.insert(key, value)) // O(log N)
            hasDuplicateKey = true;
    }
    
    return !hasDuplicateKey;
}

// Subtract key-value pairs in m2 from m1
// result = m1 - m2
void subtract(const Map& m1, const Map& m2, Map& result) {
    result = Map(m1); // O(N)
    
    KeyType     key;
    ValueType   value;
    
    int m2Size = m2.size(); // O(N)

    for (int i = 0; i < m2Size; i++) { // O(N)
        if (!m2.get(i, key, value)) { // O(log N)
            // What do I do? Throw?
        }
        
        if (!result.erase(key)) { // O(log N)
            // What do I do? Throw?
        }
    }

    return;
}
