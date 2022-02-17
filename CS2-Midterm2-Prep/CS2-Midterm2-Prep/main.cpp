//
//  main.cpp
//  CS2-Midterm2-Prep
//
//  Created by Shawn Davidson on 11/10/21.
//

#include <iostream>
#include <queue>
#include <stack>

using namespace std;

// Print all items (destructive)
void print(queue<int>& q) {
    cout << endl;
    while( !q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

void print_recurse(stack<int>& q) {
    if (q.empty())
        return;
    
    int item = q.top();
    q.pop();
    print_recurse(q);
    
    cout << item << " ";
}

// Print all items (destructive)
void print(stack<int>& q) {
    cout << "Bottom> ";
    print_recurse(q);
    cout << " <Top" << endl;
}


queue<int> copy_queue(queue<int>& Q) {
    queue<int> result(Q);
    
    return result;
}

void test_copy_queue() {
    queue<int> q;
    
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);
    
    queue<int> q2 = copy_queue(q);

    cout << "q => " << endl;
    print(q);

    cout << "q2 => " << endl;
    print(q2);
    
}

using ItemType = int;

void SelectItem(stack<ItemType> &S, ItemType n) {
    if (S.empty())
        return;
    
    stack<ItemType> temp;
    
    // Pop items off and on to a temporary stack until we find n
    while (!S.empty() && S.top() != n) {
        ItemType item = S.top();
        S.pop();
        temp.push(item);
    }
    
    // Invariant: Item n is on the top OR the stack is empty
    bool found = !S.empty() && S.top() == n;
    
    // If we found the item, pop it off the stack
    if (found)
        S.pop();
    
    // Put the other items back onto the stack from our temporary
    while (!temp.empty()) {
        S.push(temp.top());
        temp.pop();
    }
    
    // Restore the found item to the top of the stack, if applicable
    if (found)
        S.push(n);

    return;
}

void test_SelectItem() {
    stack<ItemType> s;
    
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    
    SelectItem(s, 10);
    
    print(s);
}

ItemType stackAt(stack<ItemType>& s, int n) {
    if (s.size() == 0 || s.size() < n)
        return -1;
    
    stack<ItemType> temp(s);

    for (int i = 0; i < n - 1; i++) {
        temp.pop();
    }
    
    return temp.top();
}

void deleteAllItems(stack<ItemType>& s, ItemType value) {
    stack<ItemType> temp;
    
    while(!s.empty()) {
        if (s.top() != value)
            temp.push(s.top());
        s.pop();
    }
    
    while (!temp.empty()) {
        s.push(temp.top());
        temp.pop();
    }
}


void test_stack_manip() {
    stack<int> s;
    
    for (int i = 10; i <= 100; i += 10) {
        s.push(i);
    }
    
    cout << "Stack:" << endl;
    
    cout << "First item = " << stackAt(s, 1) << endl;
    cout << "Third item = " << stackAt(s, 3) << endl;
    cout << "Bottom item = " << stackAt(s, (int)s.size()) << endl;
    cout << "100th item = " << stackAt(s, 100) << endl;

    print(s);
}

void test_deleteAllItems() {
    stack<int> s;
    
    for (int i = 10; i <= 100; i += 10) {
        s.push(i);
        s.push(i);
        s.push(i);
    }
    
    cout << "Stack:" << endl;
    
    deleteAllItems(s, 110);
    
    print(s);
}

int main(int argc, const char * argv[]) {
    // insert code here...

    cout << "Testing copy_queue" << endl;
    test_copy_queue();
    
    cout << "Testing SelectItem" << endl;
    test_SelectItem();
    
    cout << "Testing stackAt" << endl;
    test_stack_manip();
    
    cout << "Testing deleteAllItems" << endl;
    test_deleteAllItems();
    
    return 0;
}
