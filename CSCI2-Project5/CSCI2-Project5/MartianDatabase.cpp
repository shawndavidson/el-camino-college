//
//  MartianDatabase.cpp
//  CSCI2-Project5
//
//  Created by Shawn Davidson on 11/20/21.
//
#include <iostream>
#include <algorithm>
#include <math.h>
#include "MartianDatabase.h"

using namespace std;

//////////////////////////////////////////////
// Martian
//////////////////////////////////////////////
void Martian::print() {
    cout << fname_ << " " << lname_ << " " << SSN_ << endl;
}

//////////////////////////////////////////////
// MartianDatabase
//////////////////////////////////////////////
// creates a new empty Martian Database initialized with the
// contents of filename.
MartianDatabase::MartianDatabase(std::istream& infile) : m_numMartians(0) {
    // Reset the file stream
    infile.clear();
    infile.seekg(0, std::ios::beg);
    
    string line;
    string fname;
    string lname;
    string SSN;
    
    int numLinesRead = 0;
    
    // Read in the file line by line
    while (!infile.eof()) {
        // Read a line which contains info for a martian as follows:
        // Format: FirstName LastName SSN
        infile >> fname >> lname >> SSN;
        if (!infile)
            break;
        
        // If you want to consume and ignore the rest of the line the
        // number is found on, follow this with
        infile.ignore(10000, '\n');
        
        struct Martian m(fname, lname, SSN);
        
        if (!addMartian(m))
            break;
        else
            numLinesRead++;
    }
    
    cout << endl;
    cout << "Read in " << numLinesRead << " lines..." << endl;
    cout << endl << endl;
}

// deletes all the dynamically created memory
MartianDatabase::~MartianDatabase() {
    // Deallocate all martian objects but ONLY from the unsorted array
    // so we avoid deallocating each martian object more than once
    for(int i = 0; i < m_numMartians; i++) {
        delete m_unsorted[i];
    }
}

// add item m to database, return true if successfully added.
bool MartianDatabase::addMartian(const Martian &m) {
    if (m_numMartians >= MAX_MARTIANS)
        return false;
    
    Martian* myMartian = new Martian(m.fname_, m.lname_, m.SSN_);
    
    m_unsorted[m_numMartians]   = myMartian;
    
    m_fname[m_numMartians]      = myMartian;
    
    m_lname[m_numMartians]      = myMartian;

    m_ssn[m_numMartians]        = myMartian;
    
    m_numMartians++;
    
    // Sort everything again...
    sort(m_fname, m_fname + m_numMartians, compareFnameSort);
    sort(m_lname, m_lname + m_numMartians, compareLnameSort);
    sort(m_ssn, m_ssn + m_numMartians, compareSSNSort);

    return true;
}

// Binary search a sorted database for a given value using a comparison function
int MartianDatabase::binarySearch(
      Martian* db[MAX_MARTIANS],
      string value,
      int (*compareFunc)(const Martian*, const string&))
{
    if (m_numMartians == 0)
        return -1;
    
    size_t low     = 0;
    size_t high    = m_numMartians-1;
    
    while (low <= high) {
        size_t mid     = floor(low + high) / 2;

        int comparison = compareFunc(db[mid], value);
        
        if (comparison < 0)
            low = mid+1;
        else if(comparison > 0)
            high = mid-1;
        else
            return (int)mid;
    };
    
    return -1;
}

// Binary search comparator by SSN. Returns -1 if m's SSN comes before ssn, 1 if it
// comes after, or 0 if it's the same.
int MartianDatabase::compareSSNBinarySearch(const Martian* m, const string& ssn) {
    if (m->SSN_ < ssn)
        return -1;
    else if (m->SSN_ > ssn)
        return 1;
    // They must be equal
    return 0;
}

// Binary search comparator by first name. Returns -1 if m's SSN comes before ssn, 1 if
// it comes after, or 0 if it's the same.
int MartianDatabase::compareFnameBinarySearch(const Martian* m, const string& fname)
{
    if (m->fname_ < fname)
        return -1;
    else if (m->fname_ > fname)
        return 1;
    // They must be equal
    return 0;
}

// Binary search comparator by last name. Returns -1 if m's SSN comes before ssn, 1 if
// it comes after, or 0 if it's the same.
int MartianDatabase::compareLnameBinarySearch(const Martian* m, const string& lname)
{
    if (m->lname_ < lname)
        return -1;
    else if (m->lname_ > lname)
        return 1;
    // They must be equal
    return 0;
}

// Remove an element from a sorted array of Martians. Returns true if successful, false otherwise.
bool MartianDatabase::deleteSortedArrayItem(Martian* db[MAX_MARTIANS], int index) {
    if (index < 0 || index >= m_numMartians)
        return false;
        
    // Remove item from the array but preserve the order
    for (int i = index; i < m_numMartians - 1; i++) {
        db[i] = db[i+1];
    }
    
    return true;
}

// delete item with the ssn in database, return true if successfully
// deleted.
bool MartianDatabase::deleteMartian(std::string ssn) {
    // Find it in the array that's sorted by SSN
    int ssnIndex = binarySearch(m_ssn, ssn, compareSSNBinarySearch);
    
    if (ssnIndex != -1) {
        int foundInSortedArrays = 0;
        int foundInUnsortedArrays = 0;
        
        // Cache the first and last names for finding in the other sorted databases
        string fname = m_ssn[ssnIndex]->fname_;
        string lname = m_ssn[ssnIndex]->lname_;
        
        // Delete the pointer from the unsorted array
        for (int i = 0; i < m_numMartians; i++) {
            if (m_unsorted[i] == m_ssn[ssnIndex])
            {
                m_unsorted[i] = m_unsorted[m_numMartians-1];
                foundInUnsortedArrays++;
                break;
            }
        }
        
        // Release the Martian object once
        Martian* deletedMartian = m_ssn[ssnIndex];
        
        // Delete from database sorted by SSN
        if (deleteSortedArrayItem(m_ssn, ssnIndex))
            foundInSortedArrays++;
        
        // Delete from database sorted by first name
        int fnameIndex = binarySearch(m_fname, fname, compareFnameBinarySearch);
        
        if (fnameIndex != -1) {
            if (deleteSortedArrayItem(m_fname, fnameIndex))
                foundInSortedArrays++;
        }
        
        // Delete from database sorted by last name
        int lnameIndex = binarySearch(m_lname, lname, compareLnameBinarySearch);
        
        if (lnameIndex != -1) {
            if (deleteSortedArrayItem(m_lname, lnameIndex))
                foundInSortedArrays++;
        }
        
        delete deletedMartian;
        
        m_numMartians--;

        return foundInSortedArrays == 3 && foundInUnsortedArrays == 1;
    }
    
    return false;
}

// return true if the database does not contain any items, false
// otherwise.
bool MartianDatabase::isEmpty() {
    return m_numMartians == 0;
}

// return true if the database is at its maximum storage, false
// otherwise.
bool MartianDatabase::isFull() {
    return m_numMartians == MAX_MARTIANS;
}

// prints the list of Martians, sorted by last name, sorted
// by first name and by MSSN.
void MartianDatabase::printMartians(Criteria type) {
    cout << endl << endl;
    
    switch (type) {
        case Criteria::first:
            // Print sorted by first name
            cout << "Sorted by First Name:" << endl;
            for (int i = 0; i < m_numMartians; i++) {
                m_fname[i]->print();
            }
            break;
        case Criteria::last:
            // Print sorted by last name
            cout << "Sorted by Last Name:" << endl;
            for (int i = 0; i < m_numMartians; i++) {
                m_lname[i]->print();
            }
            break;
        case Criteria::ssn:
            // Print sorted by MSSN
            cout << "Sorted by MSSN:" << endl;
            for (int i = 0; i < m_numMartians; i++) {
                m_ssn[i]->print();
            }
            break;
    };
    cout << endl << endl;
}

// Sort comparison helper for two Martian objects by their first name
bool MartianDatabase::compareFnameSort(const Martian* m1, const Martian* m2) {
    return m1->fname_ < m2->fname_;
}

// Sort comparison helper for two Martian objects by their last name
bool MartianDatabase::compareLnameSort(const Martian* m1, const Martian* m2) {
    return m1->lname_ < m2->lname_;
}

// Sort comparison helper for two Martian objects by their SSN
bool MartianDatabase::compareSSNSort(const Martian* m1, const Martian* m2) {
    return m1->SSN_ < m2->SSN_;
}




