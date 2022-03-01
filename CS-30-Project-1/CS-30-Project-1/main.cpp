//
//  main.cpp
//  CS-30-Project-1
//
//  Created by Shawn Davidson on 2/28/22.
//

#include <iostream>
#include <assert.h>
#include "Map.h"

void test1() {
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
}

int main(int argc, const char * argv[]) {
    test1();
    
    
    return 0;
}
