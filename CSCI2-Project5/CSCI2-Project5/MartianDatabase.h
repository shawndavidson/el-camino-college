//
//  MartianDatabase.hpp
//  CSCI2-Project5
//
//  Created by Shawn Davidson on 11/20/21.
//

#ifndef MartianDatabase_hpp
#define MartianDatabase_hpp

#include <string>

using namespace std;

const int MAX_MARTIANS = 100;

struct Martian {
    std::string fname_;
    std::string lname_;
    std::string SSN_;
    Martian(std::string fn, std::string ln, std::string ssn)
       : fname_(fn), lname_(ln), SSN_(ssn) { }

    // you may add other things to the structure
    void print();
};

enum class Criteria { first, last, ssn};

class MartianDatabase {
public:
     // creates a new empty Martian Database initialized with the
     // contents of filename.
    MartianDatabase(std::istream& infile);
        
     // add item m to database, return true if successfully added.
    bool addMartian(const Martian &m);
    
    // delete item with the ssn in database, return true if successfully
    // deleted.
    bool deleteMartian(std::string ssn);
    
    // return true if the database does not contain any items, false
    // otherwise.
    bool isEmpty();
    
    // return true if the database is at its maximum storage, false
    // otherwise.
    bool isFull();
    
    // prints the list of Martians, sorted by last name, sorted
    // by first name and by MSSN.
    void printMartians(Criteria type);

     // deletes all the dynamically created memory
    ~MartianDatabase();
private:
    Martian* m_unsorted[MAX_MARTIANS];
    Martian* m_fname[MAX_MARTIANS];
    Martian* m_lname[MAX_MARTIANS];
    Martian* m_ssn[MAX_MARTIANS];

    // you may add other private members to the class
    size_t   m_numMartians;
    
    // Sort comparison helper for two Martian objects by their first name
    static bool compareFnameSort(const Martian* m1, const Martian* m2);
    
    // Sort comparison helper for two Martian objects by their last name
    static bool compareLnameSort(const Martian* m1, const Martian* m2);
    
    // Sort comparison helper for two Martian objects by their SSN
    static bool compareSSNSort(const Martian* m1, const Martian* m2);
    
    // Binary search a database for a given value using a comparison function
    int binarySearch(Martian* db[MAX_MARTIANS], string value, int (*compareFunc)(const Martian*, const string&));
    
    // Binary search comparator by SSN. Returns -1 if m's SSN comes before ssn, 1 if it
    // comes after, or 0 if it's the same.
    static int compareSSNBinarySearch(const Martian* m, const string& ssn);
    
    // Binary search comparator by first name. Returns -1 if m's SSN comes before ssn, 1 if
    // it comes after, or 0 if it's the same.
    static int compareFnameBinarySearch(const Martian* m, const string& fname);

    // Binary search comparator by last name. Returns -1 if m's SSN comes before ssn, 1 if
    // it comes after, or 0 if it's the same.
    static int compareLnameBinarySearch(const Martian* m, const string& lname);
    
    // Remove an element from a sorted array of Martians. Returns true if successful, false otherwise.
    bool deleteSortedArrayItem(Martian* db[MAX_MARTIANS], int index);
};

#endif /* MartianDatabase_hpp */
