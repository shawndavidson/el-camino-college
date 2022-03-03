//
//  main.cpp
//  CS-30-Project-1
//
//  Created by Shawn Davidson on 2/28/22.
//

#include <iostream>
#include <assert.h>
#include "Map.h"

using namespace std;

void myTest() {
    Map map;
    
    assert(map.size() == 0);
    
    map.insert("G", 0);
    map.insert("D", 1);
    map.insert("Z", 2);
    map.insert("E", 3);
    map.insert("F", 4);
    map.insert("R", 5);
    
    assert(map.size() == 6);
    
    map.dump();
    
    // Attempt to insert the same key again, it should fail
    assert(map.insert("R", 10) == false);
    assert(map.size() == 6);
    
    // Attempt to insert the same key using insertOrUpdate which should succeed
    assert(map.insertOrUpdate("R", 11) == true);
    assert(map.size() == 6);
    
    ValueType value = -1;
    assert(map.get("R", value) == true);
    // Ensure get didn't change value since it failed
    assert(value == 11);
    
    // TODO: Ensure that the value for key "R" is now 11
    ValueType value2 = -1;
    assert(map.get("R", value2) == true);
    assert(value2 == 11);
    
    ValueType value3 = -1;
    
    assert(map.get("G", value3) == true);
    assert(value3 == 0);
    
    assert(map.get("D", value3) == true);
    assert(value3 == 1);
    
    assert(map.get("Z", value3) == true);
    assert(value3 == 2);

    assert(map.get("E", value3) == true);
    assert(value3 == 3);

    assert(map.get("F", value3) == true);
    assert(value3 == 4);

    assert(map.get("R", value3) == true);
    assert(value3 == 11);

    map.insert("ZZ", 100);
    assert(map.contains("ZZ") == true);
    assert(map.contains("NotAKey") == false);
    
    map.dump();
    
    assert(map.update("G", 123) == true);
    
    ValueType value4 = -1;
    assert(map.get("G", value4) == true);
    assert(value4 == 123);
    
    map.dump();
    
    KeyType     key5;
    ValueType   value5;
    
    assert(map.get(0, key5, value5) == true);
    assert(key5 == "D");
    assert(value5 == 1);
    
    assert(map.get(1, key5, value5) == true);
    assert(key5 == "E");
    assert(value5 == 3);
    
    assert(map.get(2, key5, value5) == true);
    assert(key5 == "F");
    assert(value5 == 4);
    
    assert(map.get(3, key5, value5) == true);
    assert(key5 == "G");
    assert(value5 == 123);
    
    assert(map.get(4, key5, value5) == true);
    assert(key5 == "R");
    assert(value5 == 11);
    
    assert(map.get(5, key5, value5) == true);
    assert(key5 == "Z");
    assert(value5 == 2);
    
    assert(map.get(6, key5, value5) == true);
    assert(key5 == "ZZ");
    assert(value5 == 100);
}

void testGet() {
    Map gpas;
    gpas.insert("Fred", 2.956);
    gpas.insert("Ethel", 3.538);
    double v;
    string k1;
    assert(gpas.get(1,k1,v)  &&  (k1 == "Fred"  ||  k1 == "Ethel"));
    string k2;
    assert(gpas.get(1,k2,v)  &&  k2 == k1);
}

void testEmptyString() {
    Map gpas;
    gpas.insert("Fred", 2.956);
    assert(!gpas.contains(""));
    gpas.insert("Ethel", 3.538);
    gpas.insert("", 4.000);
    gpas.insert("Lucy", 2.956);
    assert(gpas.contains(""));
    gpas.erase("Fred");
    assert(gpas.size() == 3  &&  gpas.contains("Lucy")  &&  gpas.contains("Ethel")  &&
                gpas.contains(""));
}

void testSwap() {
    Map m1;
    m1.insert("Fred", 2.956);
    Map m2;
    m2.insert("Ethel", 3.538);
    m2.insert("Lucy", 2.956);
    m1.swap(m2);
    assert(m1.size() == 2  &&  m1.contains("Ethel")  &&  m1.contains("Lucy")  &&
           m2.size() == 1  &&  m2.contains("Fred"));
}

int main(int argc, const char * argv[]) {
    myTest();
    
    testGet();
    testEmptyString();
    testSwap();
    
    return 0;
}
