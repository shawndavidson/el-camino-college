//
//  main.cpp
//  CS-30-Project-2
//
//  Created by Shawn Davidson on 3/15/22.
//

#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class InvalidSize : public runtime_error {
public:
    InvalidSize(const char* msg) : runtime_error(msg) {};
};

// The purpose of this class is to implement an exception caused
// by attempting to pop an item from an empty stack
class StackEmpty : public runtime_error {
public:
    StackEmpty(const char* msg) : runtime_error(msg) {};
};

// The purpose of this class is to implement an exception caused
// by attempting to push an item to a full stack
class StackFull : public runtime_error {
public:
    // Constructor
    StackFull(const char* msg, int value)
    : runtime_error(msg),
      m_value(value) {}
    
    // Retrieve the value given when the error occured
    int GetValue() const {
        return m_value;
    }
    
private:
    const int m_value;
};

class IntStack
{
public:
    // MaxSize should be an unsigned int, but for the sake of example...
    IntStack(int MaxSize)
    {
        if (MaxSize < 0)
        {
            throw InvalidSize("Cannot create a negative size stack");
        }

        data.resize(MaxSize);
        cur_index = 0;
    }

    void push(int new_data)
    {
        if (cur_index == data.size())
        {
            throw StackFull("Push to full stack", new_data);
        }
        else
        {
            data.at(cur_index) = new_data;
            cur_index++;
        }
    }

    int pop()
    {
        if (cur_index == 0)
        {
            throw StackEmpty("Pop from empty stack");
        }
        else
        {
            // pop off the int and return it
            cur_index--;
            return data.at(cur_index);
        }
    }

private:
    vector<int> data;
    unsigned int cur_index;
};

int main()
{
    // Testing Constructor
    try {
        IntStack c_test(-10);
        
        c_test.push(3);
        c_test.push(4);
        c_test.pop();
        c_test.pop();
    }
    catch(exception& e) {
        cerr << e.what() << endl;
    }

    // Testing push
    try {
        IntStack push_test(5);

        for (unsigned int i = 0; i < 7; i++) {
            push_test.push(i);
        }
    }
    catch(StackFull& e) {
        cerr << e.what() << ", Value " << e.GetValue() << endl;
    }
    catch(exception& e) {
        cerr << e.what() << endl;
    }
    
    // Testing pop
    try {
        IntStack pop_test(2);

        pop_test.push(1);
        pop_test.push(2);
        pop_test.pop();
        pop_test.pop();
        pop_test.pop();
    }
    catch(exception& e) {
        cerr << e.what() << endl;
    }
    
    cout << "Completed!" << endl;
}
