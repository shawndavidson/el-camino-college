//
//  main.cpp
//  CS-30-Project-2
//
//  Created by Shawn Davidson on 3/24/22.
//

#include <iostream>
#include <stdexcept>
#include <assert.h>

#include <vector> // for testing

using namespace std;

class null_ptr_exception : runtime_error {
public:
    null_ptr_exception(const char* msg = "") : runtime_error(msg)
    {
    };
};

template <typename T>
class smart_ptr {
public:
    smart_ptr() noexcept;
      // Create a smart_ptr that is initialized to nullptr. The reference count
      // should be initialized to nullptr.
 
    explicit smart_ptr(T* &raw_ptr);
      // Create a smart_ptr that is initialized to raw_ptr. The reference count
      // should be one. No change is made to raw_ptr.
      
    explicit smart_ptr(T* &&raw_ptr);
      // Create a smart_ptr that is initialized to raw_ptr. The reference count
      // should be one. If the constructor fails raw_ptr is deleted.

    smart_ptr(const smart_ptr& rhs) noexcept;
      // Copy construct a pointer from rhs. The reference count should be
      // incremented by one.

    smart_ptr(smart_ptr&& rhs) noexcept;
      // Move construct a pointer from rhs.

    smart_ptr& operator=(const smart_ptr& rhs) noexcept;
      // This assignment should make a shallow copy of the right-hand side's
      // pointer data. The reference count should be incremented as appropriate.

    smart_ptr& operator=(smart_ptr&& rhs) noexcept;
      // This move assignment should steal the right-hand side's pointer data.
      
    bool clone();
      // If the smart_ptr is either nullptr or has a reference count of one, this
      // function will do nothing and return false. Otherwise, the referred to
      // object's reference count will be decreased and a new deep copy of the
      // object will be created. This new copy will be the object that this
      // smart_ptr points and its reference count will be one.
      
    int ref_count() const noexcept;
      // Returns the reference count of the pointed to data.

    T& operator*();
      // The dereference operator shall return a reference to the referred object.
      // Throws null_ptr_exception on invalid access.

    T* operator->();
      // The arrow operator shall return the pointer ptr_. Throws null_ptr_exception
      // on invalid access.

    ~smart_ptr();          // deallocate all dynamic memory
    
private:
    void detach() noexcept;
    
private:
    T* ptr_;               // pointer to the referred object
    int* ref_;             // pointer to a reference count
};

// Default Constructor
// Exception Safety - No throw
template <typename T>
smart_ptr<T>::smart_ptr() noexcept
 : ptr_(nullptr), ref_(nullptr) {
}

// Constructor for a raw pointer that accepts an L-Value
// Exception Safety - Strong
template <typename T>
smart_ptr<T>::smart_ptr(T* &raw_ptr)
{
    // Initialize the control block - may throw bad_alloc
    // Don't change object state until after allocation to provide a
    // strong guarantee with respect to expection safety.
    ref_ = new int{1};
    ptr_ = raw_ptr;
}

// Constructor for a raw pointer take accepts a R-Value
// Exception Safety - Strong
template <typename T>
smart_ptr<T>::smart_ptr(T* &&raw_ptr) {
    // Initialize the control block
    try {
        // Don't change object state until after allocation to provide a
        // strong guarantee with respect to expection safety.
        ref_    = new int(1);
        
        // Steal data from the rhs
        ptr_    = raw_ptr;
        raw_ptr = nullptr;
    }
    catch(exception& ex) {
        delete raw_ptr;
        throw;
    }
}

// Copy Constructor for a smart pointer (L-Value)
// Exception Safety - No throw
template <typename T>
smart_ptr<T>::smart_ptr(const smart_ptr& rhs) noexcept
 : ptr_(rhs.ptr_), ref_(rhs.ref_) {
     if (ref_) {
        (*ref_)++;
     }
}

// Move Copy Constructor (R-Value)
// Exception Safety - No throw
template <typename T>
smart_ptr<T>::smart_ptr(smart_ptr&& rhs) noexcept
 : ptr_(rhs.ptr_), ref_(rhs.ref_) {
    // Steal the pointer and counter block then nullify the rhs
    rhs.ptr_ = nullptr;
    rhs.ref_ = nullptr;
}

// Assignment Operator
// Exception Safety - No throw
template <typename T>
smart_ptr<T>& smart_ptr<T>::operator=(const smart_ptr<T>& rhs) noexcept {
    // Protect against an alias for *this being passed into the rhs
    if (this == &rhs)
        return *this;
    
    detach();
    
    // Point to the new data and its control block (from rhs)
    ptr_ = rhs.ptr_;
    ref_ = rhs.ref_;
    
    // Increment the singular reference counter to the existing control block
    // from the other pointer (rhs)
    (*ref_)++;
    
    return *this;
}

// Move Assignment Operator
// Exception Safety - No throw
template <typename T>
smart_ptr<T>& smart_ptr<T>::operator=(smart_ptr&& rhs) noexcept {
    // Protect against an alias for *this being passed into the rhs
    if (this == &rhs)
        return *this;
    
    detach();
    
    // Steal the new data and its control block (from rhs)
    ptr_ = rhs.ptr_;
    ref_ = rhs.ref_;
    
    rhs.ptr_ = nullptr;
    rhs.ref_ = nullptr;
    
    return *this;
}

template <typename T>
// Exception Safety - Strong
bool smart_ptr<T>::clone() {
    if (ptr_ == nullptr || ref_ == nullptr || *ref_ <= 1)
        return false;

    T*      newPtr_{};
    int*    newRef_{};
    
    // Instantiate a deep copy the same data we're currently pointing to
    // and a new control block so it's independent
    try {
        // Clone the data and the control block
        newPtr_ = new T{ (*ptr_) };
        newRef_ = new int{1};
                
        // Decrement the reference count in the original control block
        (*ref_)--;
        
        // Switch to the new cloned data and control block
        ptr_ = newPtr_;
        ref_ = newRef_;
    }
    catch(exception& ex) {
        delete newPtr_;
        throw;
    }
    
    return true;
}

// Get the reference count
// Exception Safety - No throw
template <typename T>
int smart_ptr<T>::ref_count() const noexcept {
    if (ref_ == nullptr)
        return 0;
    
    return *ref_;
}

// Dereferencing Operator
// Exception Safety - Strong
template <typename T>
T& smart_ptr<T>::operator*() {
    if (ptr_ == nullptr) {
        throw null_ptr_exception();
    }
    return *ptr_;
}

// Arrow Operator
// Exception Safety - Strong
template <typename T>
T* smart_ptr<T>::operator->() {
    if (ptr_ == nullptr) {
        throw null_ptr_exception();
    }
    return ptr_;
}

// Detach by deallocating or decrementing reference count
// Exception Safety - no throw
template <typename T>
void smart_ptr<T>::detach() noexcept {
    // If the control block hasn't been allocated, we're uninitialized and
    // there is nothing to do.
    if (ref_ == nullptr)
        return;
    
    // If we're the last pointer, then deallocate everything.
    // Otherwise, decrement the reference count.
    if (*ref_ == 1) {
        delete ptr_;
        delete ref_;
    }else {
        // Decrement the reference count
        (*ref_)--;
    }
    
    ptr_ = nullptr;
    ref_ = nullptr;
}

// Destructor
template <typename T>
smart_ptr<T>::~smart_ptr() {
    detach();
}

struct Point { int x = 2; int y = -5; };

void testArrowOperator ( ) {

   smart_ptr<Point> sp { new Point };
   cout << sp->x << " " << sp->y << endl;   // prints 2 -5
}

void testClone() {
     smart_ptr<double> dsp1 { new double {3.14} };
     smart_ptr<double> dsp2, dsp3;
     
     dsp3 = dsp2 = dsp1;

     cout << dsp1.ref_count() << " " << dsp2.ref_count() << " " << dsp3.ref_count() << endl;
       // prints 3 3 3
     cout << *dsp1 << " " << *dsp2 << " " << *dsp3 << endl;
       // prints 3.14 3.14 3.14

     dsp1.clone();        // returns true

     cout << dsp1.ref_count() << " " << dsp2.ref_count() << " " << dsp3.ref_count() << endl;
       // prints 1 2 2
     cout << *dsp1 << " " << *dsp2 << " " << *dsp3 << endl;
       // prints 3.14 3.14 3.14
}

void demo() {
    int* p { new int { 42 } };
    smart_ptr<int> sp1 { p };

    cout << "Ref count is " << sp1.ref_count() << endl;    // Ref Count is 1
    {
       smart_ptr<int> sp2 { sp1 };
       cout << "Ref count is " << sp1.ref_count() << endl;    // Ref Count is 2
       cout << "Ref count is " << sp2.ref_count() << endl;    // Ref Count is 2
    }
    cout << "Ref count is " << sp1.ref_count() << endl;    // Ref Count is 1
    
    smart_ptr<int> sp3;

    cout << "Ref count is " << sp3.ref_count() << endl;    // Ref Count is 0
    
    sp3 = sp1;

    cout << "Ref count is " << sp1.ref_count() << endl;    // Ref Count is 2
    cout << "Ref count is " << sp3.ref_count() << endl;    // Ref Count is 2

    smart_ptr<int> sp4 = std::move(sp1);

    cout << *sp4 << " " << *sp3 << endl;        // prints 42 42
    cout << *sp1 << endl;                       // throws null_ptr_exception
}

void test() {
    int* p { new int { 10 } };

    smart_ptr<int> sp1{p}, sp2{};
    
    assert(sp1.ref_count() == 1);
    assert(*sp1 == 10);
    assert(sp2.ref_count() == 0);
    
    try {
        // Expected to throw a null_ptr_exception
        *sp2;
        assert(false);
    }
    catch(null_ptr_exception& ex) {
    }
    
    sp2 = sp1;
    
    assert(sp1.ref_count() == 2);
    assert(sp2.ref_count() == 2);
    assert(*sp1 == 10 && *sp2 == 10);
    
    assert( sp2.clone() == true );
    assert(*sp1 == 10);
    assert(*sp2 == 10);
    assert(sp1.ref_count() == 1);
    assert(sp2.ref_count() == 1);
    
    *sp2 = 20;
    assert(*sp1 == 10);
    assert(*sp2 == 20);
    
    smart_ptr<int> sp3;
    
    assert(sp3.clone() == false);
    
    assert(sp3.ref_count() == 0);

    smart_ptr<int> sp4(sp3), sp5{new int{123}};
    
    assert(sp4.ref_count() == 0);
    
    sp4 = sp5;
    
    assert(*sp4 == 123);
    assert(sp4.ref_count() == 2);
        
    assert(*sp5 == 123);
    assert(sp5.ref_count() == 2);
    
    // Test the copy contstructor
    smart_ptr<int> sp6(sp5);
    assert(*sp4 == 123);
    assert(*sp5 == 123);
    assert(*sp6 == 123);
    assert(sp4.ref_count() == 3);
    assert(sp6.ref_count() == 3);
    assert(sp5.ref_count() == 3);
    
    // Test the move copy constructor
    smart_ptr<int> sp7(std::move(sp6));
    
    assert(*sp4 == 123);
    assert(*sp5 == 123);
    try {
        *sp6;
        assert(false);
    }
    catch(null_ptr_exception& ex) {
    }
    assert(*sp7 == 123);
    
    assert(sp4.ref_count() == 3);
    assert(sp5.ref_count() == 3);
    assert(sp6.ref_count() == 0);
    assert(sp7.ref_count() == 3);
}

void testObject() {
    string* p = new string{"Hello"};
    smart_ptr<string> sp1{p};
    
    cout << *sp1 << " World!" << endl;
    
    assert(*sp1 == "Hello");
    assert(sp1.ref_count() == 1);
    
    smart_ptr<string> sp2;
    
    sp2 = sp1;
    
    assert(*sp1 == "Hello");
    assert(sp1.ref_count() == 2);
    assert(*sp2 == "Hello");
    assert(sp2.ref_count() == 2);
    {
        smart_ptr<string> sp3(std::move(sp1));
        {
            smart_ptr<string> sp4(std::move(sp2));
            assert(*sp3 == "Hello");
            assert(*sp4 == "Hello");

            assert(sp3.ref_count() == 2);
            assert(sp4.ref_count() == 2);
        }
        assert(sp3.ref_count() == 1);
    }
    try {
        // Expected to throw a null_ptr_exception
        *sp1;
        *sp2;
        assert(false);
    }
    catch(null_ptr_exception& ex) {
    }
    assert(sp1.ref_count() == 0);
    assert(sp2.ref_count() == 0);

    
    string* p2 = new string{"Hola!"};
    smart_ptr<string> s5(p2);
    vector< smart_ptr<string> > v(10, s5);
    
    assert(s5.ref_count() == 11);
    for(auto it = begin(v); it != end(v); it++) {
        smart_ptr<string>& sp_ = *it;
        assert(*sp_ == "Hola!");
        assert( sp_.ref_count() == 11);
    }
}

int main() {
    try {
        demo();
    }
    catch(null_ptr_exception& ex) {
        cout << "Caught the expected null_ptr_exception" << endl;
    }
    
    testArrowOperator();
    
    testClone();
    
    testObject();
    
    test();
    
    
    return 0;
}
