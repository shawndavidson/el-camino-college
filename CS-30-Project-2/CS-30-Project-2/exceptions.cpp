//
//  main.cpp
//  CS-30-Project-2
//
//  Created by Shawn Davidson on 3/15/22.
//

#include <vector>
#include <iostream>

using namespace std;

// The purpose of this class is to provide a common base class to
// implement an exception
class MyExceptionBase : public exception {
public:
    // Constructor
    MyExceptionBase(const char* msg) : m_msg(msg) {}
    
    // Copy Constructor
    MyExceptionBase(const MyExceptionBase& rhs) : m_msg(rhs.m_msg) {}
    
    // Destructor
    virtual ~MyExceptionBase() {}
    
    // Retrieve the error message
    virtual const char* what() const throw() {
        return m_msg.c_str();
    }
    
    // Assignment Operator
    MyExceptionBase& operator=(const MyExceptionBase& rhs) {
        // If rhs is an alias for this, there's nothing to do
        if (&rhs == this)
            return *this;
        
        m_msg   = rhs.m_msg;
        
        return *this;
    }
    
private:
    std::string m_msg;
};

class InvalidSize : public MyExceptionBase {
public:
    InvalidSize(const char* msg) : MyExceptionBase(msg) {};
};

// The purpose of this class is to implement an exception caused
// by attempting to pop an item from an empty stack
class StackEmpty : public MyExceptionBase {
public:
    StackEmpty(const char* msg) : MyExceptionBase(msg) {};
};

// The purpose of this class is to implement an exception caused
// by attempting to push an item to a full stack
class StackFull : public MyExceptionBase {
public:
    // Constructor
    StackFull(const char* msg, int value)
    : MyExceptionBase(msg), m_value(value) {}
    
    // Copy Constructor
    StackFull(const StackFull& rhs)
    : MyExceptionBase(rhs), m_value(rhs.m_value) {};
    
    // Destructor
    virtual ~StackFull() {}
    
    // Retrieve the value given when the error occured
    virtual int GetValue() const {
        return m_value;
    }
    
    // Assignment Operator
    StackFull& operator=(const StackFull& rhs) {
        // If rhs is an alias for this, there's nothing to do
        if (&rhs == this)
            return *this;
        
        MyExceptionBase::operator=(rhs);
        
        m_value = rhs.m_value;
        
        return *this;
    }
    
private:
    int         m_value;
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
    catch(MyExceptionBase& e) {
        cerr << e.what() << endl;
    }

    // Testing push
    try {
        IntStack push_test(5);

        for (unsigned int i = 0; i < 7; i++) {
            push_test.push(i);
        }
    }
    catch(MyExceptionBase& e) {
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
    catch(MyExceptionBase& e) {
        cerr << e.what() << endl;
    }
    
    cout << "Completed!" << endl;
}
