//
//  main.cpp
//  CS-30-Project-1
//
//  Created by Shawn Davidson on 2/28/22.
//
#if 1

#include <iostream>
#include <assert.h>
#include "Map.h"
#include <type_traits>

using namespace std;

#define CHECKTYPE(f, t) { auto p = (t)(f); (void)p; }

static_assert(std::is_default_constructible<Map>::value,
        "Map must be default-constructible.");
static_assert(std::is_copy_constructible<Map>::value,
        "Map must be copy-constructible.");

void ThisFunctionWillNeverBeCalled()
{
    CHECKTYPE(&Map::operator=,      Map& (Map::*)(const Map&));
    CHECKTYPE(&Map::empty,          bool (Map::*)() const);
    CHECKTYPE(&Map::size,           int  (Map::*)() const);
    CHECKTYPE(&Map::insert,         bool (Map::*)(const KeyType&, const ValueType&));
    CHECKTYPE(&Map::update,         bool (Map::*)(const KeyType&, const ValueType&));
    CHECKTYPE(&Map::insertOrUpdate, bool (Map::*)(const KeyType&, const ValueType&));
    CHECKTYPE(&Map::erase,          bool (Map::*)(const KeyType&));
    CHECKTYPE(&Map::contains,       bool (Map::*)(const KeyType&) const);
    CHECKTYPE(&Map::get,            bool (Map::*)(const KeyType&, ValueType&) const);
    CHECKTYPE(&Map::get,            bool (Map::*)(int, KeyType&, ValueType&) const);
    CHECKTYPE(&Map::swap,           void (Map::*)(Map&));
    
    CHECKTYPE(combine,  bool (*)(const Map&, const Map&, Map&));
    CHECKTYPE(subtract, void (*)(const Map&, const Map&, Map&));
}

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

void testGet2() {
    Map m;
    m.insert("A", 10);
    m.insert("B", 44);
    m.insert("C", 10);
    string all;
    double total = 0;
    for (int n = 0; n < m.size(); n++)
    {
        string k;
        double v;
        m.get(n, k, v);
        all += k;
        total += v;
    }
    cout << all << total;
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

void testString()
{
    Map m;
    assert(m.insert("Fred", 123));
    assert(m.insert("Ethel", 456));
    assert(m.size() == 2);
    double d = 42;
    assert(m.get("Fred", d)  &&  d == 123);
    d = 42;
    string s1;
    assert(m.get(0, s1, d)  &&
           ((s1 == "Fred"  &&  d == 123)  ||  (s1 == "Ethel"  &&  d == 456)));
    string s2;
    assert(m.get(1, s2, d)  &&  s1 != s2  &&
           ((s2 == "Fred"  &&  d == 123)  ||  (s2 == "Ethel"  &&  d == 456)));
}

void testEmptyMap() {
    Map m;
    
    // For an empty map:
    assert(m.size() == 0);      // test size
    assert(m.empty());          // test empty
    assert(!m.erase("Ricky"));  // nothing to erase
    
    KeyType key;
    ValueType value;
    assert(m.get(1, key, value) == false);
    assert(m.contains("") == false);
}

void testAssignment() {
    Map map;
    
    assert(map.size() == 0);
    
    map.insert("A", 0);
    map.insert("B", 1);
    map.insert("C", 2);
    map.insert("D", 3);
    map.insert("E", 4);
    map.insert("F", 5);
    
    map.dump();
    
    Map map2(map);
    
    map2.dump();
    
    Map emptyMap;
    
    map2 = emptyMap;
    
    map2.dump();
    
    map2 = map;
    
    map2.dump();
}

void testCombine() {
    Map m1;
    Map m2;
    
    Map emptyResult;
    assert(combine(m1, m2, emptyResult) == true);
    assert(emptyResult.size() == 0);
    
    m1.insert("AA", 0);
    m1.insert("BB", 1);
    m1.insert("CC", 2);
    
    m2.insert("DD", 3);
    m2.insert("EE", 4);
    m2.insert("FF", 5);
    
    Map result;
    assert(combine(m1, m2, result) == true);
    assert(result.size() == 6);
    
    result.dump();
    
    Map m2WithDuplicates;
    
    m2WithDuplicates.insert("CC", 2);
    m2WithDuplicates.insert("DD", 3);
    m2WithDuplicates.insert("EE", 4);
    m2WithDuplicates.insert("FF", 5);
    
    Map result2;
    assert(combine(m1, m2WithDuplicates, result2) == false);
    assert(result2.size() == 6);
    
    result.dump();
}

void testSubtract() {
    Map m1;
    Map m2;
    
    Map emptyResult;
    subtract(m1, m2, emptyResult);
    assert(emptyResult.size() == 0);
    
    m1.insert("AA", 0);
    m1.insert("BB", 1);
    m1.insert("CC", 2);
    m1.insert("DD", 3);
    m1.insert("EE", 4);
    m1.insert("FF", 5);
    
    m2.insert("BB", 1);
    m2.insert("DD", 3);
    m2.insert("FF", 5);

    Map everyOtherResult;

    subtract(m1, m2,everyOtherResult);
    
    assert(everyOtherResult.size() == 3);
    assert(everyOtherResult.contains("AA"));
    assert(everyOtherResult.contains("CC"));
    assert(everyOtherResult.contains("EE"));
}

int main() {
    myTest();
    
    testGet();
    testGet2();
    testEmptyString();
    testSwap();
    testString();
    testEmptyMap();
    testAssignment();
    testCombine();
    testSubtract();
    
    cout << endl;
    cout << "Passed all tests" << endl;

    return 0;
}

#endif
