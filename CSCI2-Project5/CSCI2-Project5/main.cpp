//
//  main.cpp
//  CSCI2-Project5
//
//  Created by Shawn Davidson on 11/20/21.
//

#include <iostream>
#include <fstream>
#include "MartianDatabase.h"

int main() {
    // Prompt the user to enter a filename
    string filename;
    
    cout << "Please enter a filename: ";
    cin >> filename;
    
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: Cannot open file: " << filename << endl;
    }
    
    MartianDatabase db(infile);
    
    infile.close();
    
    char selection;

    bool done = false;
    
    while (!done) {
        cout << endl << endl;
        
        cout << "Main Menu:"            << endl;
        cout << "=====================" << endl;
        cout << "1. Add a Martian"      << endl;
        cout << "2. Delete a Martian"   << endl;
        cout << "3. Check if empty"     << endl;
        cout << "4. Check if full"      << endl;
        cout << "5. Print all"          << endl;
        cout << "6. Quit"               << endl;
        
        cout << "Enter a selection: ";
        cin >> selection;
        
        switch(selection) {
            case '1':   // Add a Martian
                {
                    string fname;
                    string lname;
                    string ssn;
                    
                    cout << "First name:    ";
                    cin >> fname;
                    
                    cout << "Last name:     ";
                    cin >> lname;
                    
                    cout << "SSN:           ";
                    cin >> ssn;
                    
                    Martian newMartian(fname, lname, ssn);
                    
                    if (db.addMartian(newMartian))
                        cout << "Add successful!" << endl;
                    else
                        cout << "Unable to add new martian." << endl;
                }
                break;
            case '2':   // Delete a Martian
                {
                    string ssn;
                    cout << "Enter a SSN to delete: ";
                    cin >> ssn;
                    
                    if (db.deleteMartian(ssn))
                        cout << "Deletion successful!" << endl;
                    else
                        cout << "Unable to delete SSN: " << ssn << endl;
                }
                break;
            case '3':   // Check if empty
                if (db.isEmpty())
                    cout << "The database is empty." << endl;
                else
                    cout << "The database is NOT empty" << endl;
                break;
            case '4':   // Check if full
                if (db.isFull())
                    cout << "The database is full." << endl;
                else
                    cout << "The database is NOT full" << endl;
                break;
            case '5':   // Print all
                db.printMartians(Criteria::first);
                db.printMartians(Criteria::last);
                db.printMartians(Criteria::ssn);
                break;
            case '6':   // Quit
                done = true;
                break;
            default:
                // do nothing
                break;
        }
    }
    cout << endl << endl;
    
    cout << "Thank you. Exiting..." << endl;
    
    exit(0);
}
