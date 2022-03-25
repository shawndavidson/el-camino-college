//
//  main.cpp
//  CS-30-Project-2
//
//  Created by Shawn Davidson on 3/24/22.
//

#include <iostream>
#include <stdexcept>

using namespace std;

// The purpose of this class is to provide an exception that represents a null pointer
class null_ptr_exception : runtime_error {
public:
    null_ptr_exception(const char* msg) : runtime_error(msg) {};
};

template <typename T>
class smart_ptr {
public:
    smart_ptr();
      // Create a smart_ptr that is initialized to nullptr. The reference count
      // should be initialized to nullptr.
 
    explicit smart_ptr(T* &raw_ptr);
      // Create a smart_ptr that is initialized to raw_ptr. The reference count
      // should be one. No change is made to raw_ptr.
      
    explicit smart_ptr(T* &&raw_ptr);
      // Create a smart_ptr that is initialized to raw_ptr. The reference count
      // should be one. If the constructor fails raw_ptr is deleted.

    smart_ptr(const smart_ptr& rhs);
      // Copy construct a pointer from rhs. The reference count should be
      // incremented by one.

    smart_ptr(smart_ptr&& rhs);
      // Move construct a pointer from rhs.

    smart_ptr& operator=(const smart_ptr& rhs);
      // This assignment should make a shallow copy of the right-hand side's
      // pointer data. The reference count should be incremented as appropriate.

    smart_ptr& operator=(smart_ptr&& rhs);
      // This move assignment should steal the right-hand side's pointer data.
      
    bool clone();
      // If the smart_ptr is either nullptr or has a reference count of one, this
      // function will do nothing and return false. Otherwise, the referred to
      // object's reference count will be decreased and a new deep copy of the
      // object will be created. This new copy will be the object that this
      // smart_ptr points and its reference count will be one.
      
    int ref_count() const;
      // Returns the reference count of the pointed to data.

    T& operator*();
      // The dereference operator shall return a reference to the referred object.
      // Throws null_ptr_exception on invalid access.

    T* operator->();
      // The arrow operator shall return the pointer ptr_. Throws null_ptr_exception
      // on invalid access.

    ~smart_ptr();          // deallocate all dynamic memory
    
private:
    void smartDealloc();
    
private:
    T* ptr_;               // pointer to the referred object
    int* ref_;             // pointer to a reference count
};

// Default Constructor
template <typename T>
smart_ptr<T>::smart_ptr() : ptr_(nullptr), ref_(nullptr) {
}

// Constructor - Takes an L-Value
template <typename T>
smart_ptr<T>::smart_ptr(T* &raw_ptr) : ptr_(raw_ptr) {
    // Initialize the control block - may throw bad_alloc
    ref_ = new int(1);
}

// Constructor - Takes a R-Value
template <typename T>
smart_ptr<T>::smart_ptr(T* &&raw_ptr) : ptr_(raw_ptr) {
    // Initialize the control block
    try {
        ref_ = new int(1);
        raw_ptr = nullptr;
    }
    catch(bad_alloc& ex) {
        delete raw_ptr;
    }
}

// Copy Constructor
template <typename T>
smart_ptr<T>::smart_ptr(const smart_ptr& rhs) : ptr_(rhs.ptr_) {
    // Point to the control block of the given smart pointer
    ref_ = rhs.ref_;
    
    // Increment the singular reference counter
    if (ref_ == nullptr) {
        throw null_ptr_exception("Copy Constructor - Unable to increment control block (null pointer).");
    }
    
    (*ref_)++;
}

// Move Constructor
template <typename T>
smart_ptr<T>::smart_ptr(smart_ptr&& rhs) : ptr_(rhs.ptr_), ref_(rhs.ref_) {
    // Steal the pointer and counter block
    rhs.ptr_ = nullptr;
    rhs.ref_ = nullptr;
}

// Assignment Operator
template <typename T>
smart_ptr<T>& smart_ptr<T>::operator=(const smart_ptr<T>& rhs) {
    // Protect against an alias for *this being passed into the rhs
    if (this == &rhs)
        return *this;
    
    if (rhs.ref_ == nullptr) {
        throw null_ptr_exception("Assignment Operator - Unable to increment control block (null pointer).");
    }
    
    smartDealloc();
    
    // Point to the new data and its control block (from rhs)
    ptr_ = rhs.ptr_;
    ref_ = rhs.ref_;
    
    // Increment the singular reference counter to the existing control block
    // from the other pointer (rhs)
    (*ref_)++;
    
    return *this;
}

// Move Assignment Operator
template <typename T>
smart_ptr<T>& smart_ptr<T>::operator=(smart_ptr&& rhs) {
    // Protect against an alias for *this being passed into the rhs
    if (this == &rhs)
        return *this;
    
    if (rhs.ref_ == nullptr) {
        throw null_ptr_exception("Assignment Operator - Unable to increment control block (null pointer).");
    }
    
    smartDealloc();
    
    // Steal the new data and its control block (from rhs)
    ptr_ = rhs.ptr_;
    ref_ = rhs.ref_;
    
    rhs.ptr_ = nullptr;
    rhs.ref_ = nullptr;
    
    return *this;
}

template <typename T>
bool smart_ptr<T>::clone() {
    if (ptr_ == nullptr || ref_ == nullptr || *ref_ == 1)
        return false;
    
    // Decrement the reference count in the existing control block
    (*ref_)--;
    
    // Instantiate a deep copy the same data we're currently pointing to
    // and a new control block so it's independent
    ptr_ = new T((*ptr_));
    ref_ = new int(1);
    
    return true;
}

// Get the reference count
template <typename T>
int smart_ptr<T>::ref_count() const {
    if (ref_ == nullptr)
        return 0;
    
    return *ref_;
}

template <typename T>
T& smart_ptr<T>::operator*() {
    if (ptr_ == nullptr)
        throw null_ptr_exception("Unable to dereference internal raw pointer because it's nullptr.");
    return *ptr_;
}

template <typename T>
T* smart_ptr<T>::operator->() {
    if (ptr_ == nullptr)
        throw null_ptr_exception("Unable to dereference internal raw pointer because it's nullptr.");
    return ptr_;
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

// Deallocate dynamically allocated memory
template <typename T>
void smart_ptr<T>::smartDealloc() {
    // If the control block hasn't been allocated, we're uninitialized and
    // there is nothing to do.
    if (ref_ == nullptr)
        return;
    
    // If we're the last smart pointer pointing to this data, then deallocate
    // the data and the control block.
    // Otherwise, just decrement the reference count.
    if (*ref_ == 1) {
        delete ptr_;
        ptr_ = nullptr;
        
        delete ref_;
        ref_ = nullptr;
    }else {
        // Decrement the reference count
        ptr_ = nullptr;
        (*ref_)--;
    }
}

// Destructor
template <typename T>
smart_ptr<T>::~smart_ptr() {
    smartDealloc();
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

int main(int argc, const char * argv[]) {
    try {
        demo();
    }
    catch(null_ptr_exception& ex) {
        cout << "Caught the excepted null_ptr_exception" << endl;
    }
    
    testArrowOperator();
    
    testClone();
    
    return 0;
}
