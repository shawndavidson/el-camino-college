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

    WordTree(WordNode* w) : root(w) { };
    
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

    // Removes the word from the tree. Returns true if the word is
    // in the tree, false if it is not.
    bool remove(ItemType v);
    
    friend WordNode* expand_leaf(WordTree* t, ItemType x, ItemType y);
    friend bool same_tree(WordTree* t1, WordTree* t2);
    
    int height() const;
    
private:
    void    destroy(WordNode* node);
    void    addRecur(WordNode*& node, const ItemType& v);
    int     distinctWords(const WordNode* node) const;
    int     totalWords(const WordNode* node) const;
    void    print(ostream& out, const WordNode* node) const;
    void    swap(WordTree& other);
    void    copy(WordNode*& newNode, const WordNode* originalNode);
    WordNode* detachMin(WordNode* node, WordNode* parent);
    int height(WordNode* node) const;
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

// Removes the word from the tree. Returns true if the word is
// in the tree, false if it is not.
bool WordTree::remove(ItemType v) {
    WordNode** parent_link = nullptr;
    WordNode* node      = root;
    
    // Traverse the tree to find the node containing v
    while (node != nullptr && v != node->m_data) {
        if (v < node->m_data) {
            parent_link = &node->m_left;
            node = node->m_left;
        }else if (v > node->m_data) {
            parent_link = &node->m_right;
            node = node->m_right;
        }
    }
    
    // Invariant: node is nullptr OR it's the node we want to remove
    if (node == nullptr)
        return false;
    
    // If there are multiple occurances of the word just remove one
    if (node->m_count > 1) {
        node->m_count--;
        return true;
    }
    
    if (node->m_left == nullptr && node->m_right == nullptr) {
        *parent_link = nullptr;
    }
    // Does the node have ONLY one child (simulate a boolean XOR operation)?
    else if ((node->m_left == nullptr) != (node->m_right == nullptr)) {
        // Set our parent's link to point directly to our only child
        if (parent_link != nullptr) {
            if (node->m_left != nullptr)
                *parent_link = node->m_left;
            else
                *parent_link = node->m_right;
        }
    }else { // Must have 2 children
        // Find the smallest on the right subtree (inorder successor)
        WordNode* successor = detachMin(node->m_right, nullptr);
        successor->m_left  = node->m_left;
        if (node->m_right != successor)
            successor->m_right = node->m_right;
        else
            successor->m_right = nullptr;
        
        if (parent_link == nullptr) {
            root = successor;
        }else {
            *parent_link = successor;
        }
    }
        
    delete node;
    
    return true;
}

// Detach the node with the smallest item (inorder successor) from a subtree
WordNode* WordTree::detachMin(WordNode* node, WordNode* parent) {
    if (node == nullptr)
        return nullptr;
    
    if (node->m_left == nullptr) {
        // Detach the parent from this node and replace it with our
        // right child, if there is one.
        if (parent != nullptr)
            parent->m_left = node->m_right;
        
        return node;
    }
    return detachMin(node->m_left, node);
}

int WordTree::height() const {
    return height(root);
}

int WordTree::height(WordNode* node) const {
    if (node == nullptr)
        return 0;
    // Is this a leaf node?
    if (node->m_left == nullptr && node->m_right == nullptr)
        return 0;
    
    return std::max(height(node->m_left), height(node->m_right)) + 1;
}


bool same_tree_recur(WordNode* T1, WordNode* T2) {
    if (T1 == nullptr && T2 == nullptr)
        return true;
    
    if ((T1 != nullptr) != (T2 != nullptr))
        return false;
    
    if (T1->m_data != T2->m_data)
        return false;
    
    // Check left and right subtrees for "sameness"
    return same_tree_recur(T1->m_left, T2->m_left) && same_tree_recur(T2->m_right, T2->m_right);
}

bool same_tree(WordTree* t1, WordTree* t2) {
    WordNode* root1 = t1->root;
    WordNode* root2 = t2->root;
    
    return same_tree_recur(root1, root2);
}

///////////////////////////////
/// Final Study Guide
/// /////////////////////////
void expand_leaf_recur(WordNode*& node, WordNode* T, ItemType x, ItemType y) {
    if (T == nullptr) {
        node = nullptr;
        return;
    }
    
    node = new WordNode(T->m_data, nullptr, nullptr, T->m_count);
    
    // Is this node internal?
    if (T->m_left != nullptr || T->m_right != nullptr) {
        expand_leaf_recur(node->m_left, T->m_left, x, y);
        expand_leaf_recur(node->m_right, T->m_right, x, y);
    }
    else { // it's not internal so it must be leaf
        node->m_left = new WordNode(x, nullptr, nullptr, 1);
        node->m_right = new WordNode(y, nullptr, nullptr, 1);
    }
}

WordNode* expand_leaf(WordTree* t, ItemType x, ItemType y) {
    WordNode* root = nullptr;
    expand_leaf_recur(root, t->root, x, y);
    return root;
}

template <typename T>
void selectionSort(T arr[], int N)
{
    for (int i = N-1; i > 0; i--) {
        int largestIndex = 0;
        
        // Find the largest in the unsorted portion of the array
        for (int j = 0; j <= i; j++) {
            if (arr[j] > arr[largestIndex])
                largestIndex = j;
        }
        
        swap(arr[i], arr[largestIndex]);
    }
}

template <typename T>
void bubbleSort(T arr[], int N) {
    for (int i = N-1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
        }
    }
}

template <typename T>
void swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

/// ///////////////////////////////
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
//    cout << endl << endl;
//    cout << "Testing the add() with a large number of words" << endl;
//    {
//        WordTree t;
//        int distinct = 5000;
//
//        stringstream s;
//        for (int i = 0; i < distinct; i++) {
//            s.clear();
//            s << "Name" << i;
//            t.add(s.str());
//            t.add(s.str());
//            if (i % 500 == 0)
//                cout << ".";
//        }
//        assert(t.distinctWords() == distinct);
//        assert(t.totalWords() == distinct * 2);
//
//        cout << t;
//    }
    // Test add, distinctWords, and totalWords
    cout << endl << endl;
    cout << "Testing remove()..." << endl;
    {
        WordTree t;
        
        t.add("50");
        t.add("40");
        t.add("70");
        t.add("60");
        t.add("80");

        cout << "Original list:" << endl;
        cout << t;
        
//        assert(t.distinctWords() == 2);
//        assert(t.totalWords() == 4);
        string num = "40";
        t.remove(num);
        
        cout << endl;
        cout << "After removing the " << num << ":" << endl;
        cout << t;
    }
    cout << endl << endl;
    cout << "Testing remove() part 2..." << endl;
    {
        WordTree t;
        
        t.add("Skyler");
        t.add("Walter");
        t.add("Walter");
        t.add("Hank");
        t.add("Hank");
        t.add("Jessie");
        t.add("Gus");

        cout << t;
        t.remove("Hank");
        cout << "Removing Hank..." << endl;
        cout << t;
        t.remove("Hank");
        cout << "Removing Hank..." << endl;
        cout << t;
    }
    cout << endl << endl;
    cout << "Testing expand_leaf()" << endl;
    {
        WordTree t;
        
        t.add("5");
        t.add("3");
        
        cout << endl << endl;
        cout << "Before expand_leaf()" << endl;
        cout << t;
        cout << endl << endl;
        int height = t.height();
        cout << "The height of the tree is: " << height << endl;
        
        WordNode* root = expand_leaf(&t, "9", "12");
        
        WordTree t2(root);
        cout << endl << endl;
        cout << "After expand_leaf()" << endl;
        cout << t2;
        
        cout << endl << endl;
        int height2 = t2.height();
        cout << "The height of the tree is: " << height2 << endl;
    }
    cout << endl << endl;
    cout << "Testing same_tree()" << endl;
    {
        WordTree t1;
        
        t1.add("Skyler");
        t1.add("Walter");
        t1.add("Walter");
        t1.add("Hank");
        t1.add("Hank");
        t1.add("Jessie");
        t1.add("Gus");
        
        WordTree t2(t1);
        
        assert(same_tree(&t1, &t2) == true);
        assert(same_tree(&t1, &t1) == true);
        
        t2.add("Jimmy");
        t2.add("Bob");
        
        assert(same_tree(&t1, &t2) == false);
        assert(same_tree(&t2, &t2) == true);
    }
    
    cout << endl << endl;
    cout << "Testing selectionSort()" << endl;
    {
        int a[] = { 12, 9, 3, 6, 4, 1 };
        
        int length = sizeof(a) / sizeof(a[0]);
        
        selectionSort(a, length);
        
        cout << "a = ";
        for (int i = 0; i < length; i++)
            cout << a[i] << ", ";
    }
    cout << endl << endl;
    cout << "Testing bubbleSort()" << endl;
    {
        int a[] = { 12, 9, 3, 6, 4, 1 };
        
        int length = sizeof(a) / sizeof(a[0]);
        
        bubbleSort(a, length);
        
        cout << "a = ";
        for (int i = 0; i < length; i++)
            cout << a[i] << ", ";
    }
    return 0;
}
