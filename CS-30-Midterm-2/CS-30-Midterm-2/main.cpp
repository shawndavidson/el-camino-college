//
//  main.cpp
//  CS-30-Midterm-2
//
//  Created by Shawn Davidson on 5/3/22.
//

/* #1
 
#include <iostream>
using namespace std;
class Base {
public:
     Base() { cout << "A" << endl; }
     virtual ~Base() { cout << "B" << endl; }
};
 
class Derived : public Base {
public:
     Derived() { cout << "C" << endl; }
     ~Derived() { cout << "D" << endl; }
};
 
int main() {
    Base *ptr = new Derived();
    delete ptr;
}
*/

/* #2
#include <iostream>
using namespace std;
class Person {
public:
    virtual void eat() {cout << "Yummy" << endl;}
    virtual void speak() {cout << "Hello" << endl;}
    virtual void sleep() {cout << "ZZZZ" << endl;}
};
class Student : public Person{
public:
    void speak() {cout << "I love school" << endl;}
    void study() {cout << "Studying for Midterm test"
                       << endl;}
    void getReadyForTest () {
        study();
        sleep(); }
};
class ElCaminoStudent : public Student {
public:
    void speak() {cout << "Go Warriors!" << endl;}
    void sleep() {cout << "ZZZ... CS2 ...ZZZZ" << endl;}
    void getReadyForCS2Test() {
        study();
        eat();
        sleep();
} };
int main( ) {
    Person* array[3];
    array[0] = new Person();
    array[1] = new Student();
    array[2] = new ElCaminoStudent;
    for (int i=0; i < 3; i++) {
        array[i]->eat();
        array[i]->speak();
        array[i]->sleep();
}
Student * sp = new Student();
    ElCaminoStudent *ecp = new ElCaminoStudent;
    sp->getReadyForTest();
    ecp->getReadyForCS2Test();
}
*/

/* #3
#include <iostream>
using namespace std;
class Base
{
public:
     void output(int n)
     {
          cout << "Hello Base" << n << endl;
     }
};
class Derived : public Base
{
public:
     // This hides the output(int n) member function
     // from Base class
     void output()
     {
          cout << "Hello Derived Class!" << endl;
     }
};
int main() {
     Base b;
     b.output(1);
     Derived d;
     d.output();
     d.Base::output(2);
}
*/

/* #4
#include <iostream>
using namespace std;
class A {
public:
     virtual void output()  { cout << "A" << endl;     }
};
 
class B : public A {
public:
     void output()  { cout << "B" << endl;     }
};
 
int main(){
     A *a = new A();
a->output();
     A *b = new B();
b->output();
     delete a, b;
}
 */

/* #5
#include <iostream>
using namespace std;
 
class Person
{
public:
     void Play()
     {    cout << "Person::Play" << endl; }
     void Study()
     {    cout << "Person::Study" << endl; }
};
 
class Student: public Person {
public:
     virtual void Study()
     {    cout << "Student::Study" << endl; }
};
 
class CS_Student : public Student
{
public:
     void Play()
     {    cout << "CS_Student::Play!" <<endl; }
     void Study()
     {    cout << "CS_Student::Study!" << endl; }
};
 
void activity( Person &s ) {
    s.Play();
    s.Study();
}
 
int main()
{
     CS_Student cs_student;
     activity(cs_student);
}
 */

/* #6 */
#include <iostream>
using namespace std;
 
class Person
{
public:
     void Play()
     {    cout << "Person::Play" << endl; }
     void Study()
     {    cout << "Person::Study" << endl; }
};
 
class Student: public Person
{
public:
     virtual void Study()
     {    cout << "Student::Study" << endl; }
};
 
class CS_Student : public Student
{
public:
     void Play()
     {    cout << "CS_Student::Play!" <<endl; }
     void Study()
     {    cout << "CS_Student::Study!" << endl; }
};
 
void activity( Student &s ) {
s.Play();
s.Study(); }
int main()
{
     CS_Student cs_student;
     activity(cs_student);
}


/* #7
#include <iostream>
using namespace std;
class Other
{
public:
     Other(int n) { cout << "Other::" << n + 10 << endl; }
     ~Other() { cout << "~Other::-15" << endl; }
};
class Base {
     int value;
public:
     Base(int n): value(n) { cout << "Base::" << n << endl; }
     ~Base() { cout << "~Base::" << -value << endl; }
};
 
class D1 : public Base
{
Other o;
public:
     D1(int n): Base(n),o(n) {
         cout << "D1::" << n + 5 << endl; }
     ~D1() { cout << "~D1::-10" << endl; }
};
 
int main() {
    D1 d(5);
}
*/
