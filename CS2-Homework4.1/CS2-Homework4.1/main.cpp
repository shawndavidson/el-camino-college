//
//  main.cpp
//  CS2-Homework4
//
//  Created by Shawn Davidson on 11/7/21.
//

#include <iostream>
#include <string>
#include "LinkedList.hpp"

using namespace std;


//////////////////////////////////////////////////////////////////////
// Main
//////////////////////////////////////////////////////////////////////

int main(int argc, const char * argv[]) {
    {
        cout << endl;
        cout << "Testing ::get()" << endl;
        
        LinkedList<string> ls;
        ls.insertToFront("Jack");
        ls.insertToFront("Germaine");
        ls.insertToFront("Agatha");
        ls.insertToFront("Agnes");

        for (int k = 0; k < ls.size(); k++)
        {
            string x;
            ls.get(k, x);
            cout << x << endl;
        }
        //    must write
        //
        //        Agnes
        //        Agatha
        //        Germaine
        //        Jack
    }
    {
        cout << endl;
        cout << "Testing ::get()" << endl;
        
        LinkedList<string> ls;
        ls.insertToFront("George");
        ls.insertToFront("Louise");
        ls.insertToFront("Lionel");
        ls.insertToFront("Helen");

        ls.printList();
        ls.printReverse();
        
        //must write
        //
        //    Helen Lionel Louise George
        //    George Louise Lionel Helen
    }
    {
        cout << endl;
        cout << "Testing ::append()" << endl;
        
        LinkedList<string> e1;
            e1.insertToFront("bell");
            e1.insertToFront("biv");
            e1.insertToFront("devoe");
            LinkedList<string> e2;
            e2.insertToFront("Andre");
            e2.insertToFront("Big Boi");
            e1.append(e2);  // adds contents of e2 to the end of e1
            string s;
            assert(e1.size() == 5  &&  e1.get(3, s)  &&  s == "Big Boi");
            assert(e2.size() == 2  &&  e2.get(1, s)  &&  s == "Andre");
            LinkedList<string> e3;
            e3.insertToFront("Rare Essence");
            e3.insertToFront("JunkYard");
            e3.insertToFront("Chuck Brown");
            e3.append(e3);
            assert(e3.size() == 6  &&  e3.get(3, s)  &&  s == "Chuck Brown");
    }
    {
        cout << endl;
        cout << "Testing ::reverseList()" << endl;
        
        LinkedList<string> e1;
           e1.insertToFront("Sam");
           e1.insertToFront("Carla");
           e1.insertToFront("Cliff");
           e1.insertToFront("Norm");

           e1.reverseList();  // reverses the contents of e1
           string s;
           assert(e1.size() == 4  &&  e1.get(0, s)  &&  s == "Sam");
    }
    {
        cout << endl;
        cout << "Testing ::swap()" << endl;
        
        LinkedList<string> e1;
        e1.insertToFront("A");
        e1.insertToFront("B");
        e1.insertToFront("C");
        e1.insertToFront("D");
        LinkedList<string> e2;
        e2.insertToFront("X");
        e2.insertToFront("Y");
        e2.insertToFront("Z");
        e1.swap(e2);  // exchange contents of e1 and e2
        string s;
        assert(e1.size() == 3  &&  e1.get(0, s)  &&  s == "Z");
        assert(e2.size() == 4  &&  e2.get(2, s)  &&  s == "B");
    }
    
    return 0;
}

