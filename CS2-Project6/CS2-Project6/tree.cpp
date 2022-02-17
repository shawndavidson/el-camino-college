//
//  main.cpp
//  CS2-Project6
//
//  Created by Shawn Davidson on 12/7/21.
//

#include <iostream>
#include <string>

using namespace std;

typedef string ItemType;

struct WordNode {
    ItemType m_data;
    
    WordNode *m_left;
    WordNode *m_right;
    
    // You may add additional data members and member functions in WordNode
    int      m_count;
    
    // Constructor
    WordNode(const ItemType& data = ItemType(), WordNode* left = nullptr, WordNode* right = nullptr, int count = 1);
};

// Constructor
WordNode::WordNode(const ItemType& data, WordNode* left, WordNode* right, int count)
: m_data(data), m_left(left), m_right(right), m_count(count)
{
}

class WordTree {
    
private:
    WordNode *root;
    
public:

      // default constructor
    WordTree() : root(nullptr) { };

      // copy constructor
    WordTree(const WordTree& rhs);

      // assignment operator
    const WordTree& operator=(const WordTree& rhs);

      // Inserts v into the WordTree
    void add(ItemType v);

      // Returns the number of distince words / nodes
    int distinctWords() const;

      // Returns the total number of words inserted, including duplicate
      // values
    int totalWords() const;

      // Prints the LinkedList
    friend ostream& operator<<(ostream &out, const WordTree& rhs);

      // Destroys all the dynamically allocated memory
      // in the tree.
    ~WordTree();
    
private:
    void    destroy(WordNode* node);
    void    addRecur(WordNode*& node, const ItemType& v);
    int     distinctWords(const WordNode* node) const;
    int     totalWords(const WordNode* node) const;
    void    print(ostream& out, const WordNode* node) const;
    void    swap(WordTree& other);
    void    copy(WordNode*& newNode, const WordNode* originalNode);
    
};

// copy constructor
WordTree::WordTree(const WordTree& rhs) {
    if (this != &rhs) {
        copy(root, rhs.root);
    }
}

// Copy a subtree (copy constructor helper)
void WordTree::copy(WordNode*& node, const WordNode* other) {
    // Base case - we've reached a terminal node
    if (other == nullptr) {
        node = nullptr;
        return;
    }
    
    // Make a copy then traverse the left and right subtrees (pre-order traversal)
    node = new WordNode(other->m_data, nullptr, nullptr, other->m_count);

    copy(node->m_left, other->m_left);
    copy(node->m_right, other->m_right);
}

// assignment operator
const WordTree& WordTree::operator=(const WordTree& rhs) {
    if (this == &rhs)
        return *this;
    
    // Use the copy-swap idiom (allows us to leverage our copy constructor - reuse)
    WordTree temp(rhs);
    swap(temp);
    
    return *this;
}

// Swap internal state (used to implement copy-swap idiom)
void WordTree::swap(WordTree& other) {
    // Swap root nodes and we're done
    WordNode* _root = this->root;
    this->root = other.root;
    other.root = _root;
}

// Destructor
WordTree::~WordTree() {
    destroy(root);
}

// Destroy (deallocate) a subtree recursively (destructor helper)
void WordTree::destroy(WordNode* node) {
    if (node == nullptr)
        return;
    
    // Deallocate nodes using a post-order traversal (handle subtrees first)
    destroy(node->m_left);
    destroy(node->m_right);
    delete node;
}

// Add an item
void WordTree::add(ItemType v) {
    addRecur(root, v);
}

// Add an item recursively (helper to add)
void WordTree::addRecur(WordNode*& node, const ItemType& v) {
    // Base case - we've reached a terminal node where this item belongs
    if (node == nullptr) {
        // node is a pointer reference so it will update the parent node's edge
        node = new WordNode(v);
        return;
    }
    
    // Traverse subtrees
    if (v < node->m_data)
        addRecur(node->m_left, v);
    else if (v > node->m_data)
        addRecur(node->m_right, v);
    else {
        // Item is already in the list so increment our count to track duplicate items
        node->m_count++;
    }
}

// Returns the number of distince words / nodes
int WordTree::distinctWords() const
{
    return distinctWords(root);
}

// Returns the number of distinct words/nodes for a subtree (recursively)
int WordTree::distinctWords(const WordNode* node) const {
    // Base case - we've reached a terminal node
    if (node == nullptr)
        return 0;
    
    return 1 + distinctWords(node->m_left) + distinctWords(node->m_right);
}

// Returns the total number of words inserted, including duplicate
// values
int WordTree::totalWords() const
{
    return totalWords(root);
}

// Returns the total number of words inserted, including duplicate
// values for a subtree (recursively)
int WordTree::totalWords(const WordNode* node) const
{
    // Base case - we've reached a terminal node
    if (node == nullptr)
        return 0;
    
    return node->m_count + totalWords(node->m_left) + totalWords(node->m_right);
}

// Print a subtree to an output stream
void WordTree::print(ostream& out, const WordNode* node) const {
    // Base case - we've reached a terminal node
    if (node == nullptr)
        return;
    
    // Traverse tree in-order to ensure a sorted sequence goes to the output stream
    print(out, node->m_left);

    out << node->m_data << " " << node->m_count << endl;

    print(out, node->m_right);
}

// Output stream operator for WordTree (friend)
ostream& operator<<(ostream &out, const WordTree& rhs) {
    rhs.print(out, rhs.root);
    return out;
}

///////////////////////////////
/// Main
/// /////////////////////////
#include <sstream>

int main(int argc, const char * argv[]) {
    // Test add, distinctWords, and totalWords
    cout << endl << endl;
    cout << "Testing add(), distinctWords(), and totalWords()..." << endl;
    {
        WordTree t;
        
        t.add("Skyler");
        t.add("Walter");
        t.add("Walter");
        t.add("Walter");

        assert(t.distinctWords() == 2);
        assert(t.totalWords() == 4);
    }
    // Test output stream operator
    cout << endl << endl;
    cout << "Testing operator<<()..." << endl;
    
    {
        WordTree t;

            t.add("Skyler");
            t.add("Walter");
            t.add("Walter");
            t.add("Hank");
            t.add("Gus");
            t.add("Walter");
            t.add("Gus");

            cout << t;
    }
    
    // Test copy constructor
    cout << endl << endl;
    cout << "Testing the copy constructor<<()..." << endl;
    {
        WordTree t;

            t.add("Skyler");
            t.add("Walter");
            t.add("Walter");
            t.add("Hank");
            t.add("Gus");
            t.add("Walter");
            t.add("Gus");

        WordTree t2(t);
        
        // Ensure that the word counts are identical
        assert(t.distinctWords() == t2.distinctWords());
        assert(t.totalWords() == t2.totalWords());
        
        // Ensure that a print out of the nodes is identical
        stringstream s1, s2;
        s1 << t;
        s2 << t2;
        assert(s1.str() == s2.str());
        
        // TODO: test invoking the copy ctor with itself
    }
    // Test the assignment operator
    cout << endl << endl;
    cout << "Testing the assignment operator..." << endl;
    {
        WordTree t;

            t.add("Papi");
            t.add("PeeWee");
            t.add("Baby");
            t.add("Bunsy");
            t.add("PeeWee");
            t.add("Papi");

        WordTree t2;
        
        t2 = t;
        
        cout << t2;
        
        assert(t2.distinctWords() == 4);
        assert(t2.totalWords() == 6);
        
        // Tricky! Try assigning to itself
        t2 = t2;
        
        assert(t2.distinctWords() == 4);
        assert(t2.totalWords() == 6);
    }
    // Test adding a large number of words
    cout << endl << endl;
    cout << "Testing the add() with a large number of words" << endl;
    {
        WordTree t;
        int distinct = 5000;
        
        stringstream s;
        for (int i = 0; i < distinct; i++) {
            s.clear();
            s << "Name" << i;
            t.add(s.str());
            t.add(s.str());
            if (i % 500 == 0)
                cout << ".";
        }
        assert(t.distinctWords() == distinct);
        assert(t.totalWords() == distinct * 2);
        
        cout << t;
    }
    return 0;
}
