//
//  main.cpp
//  RainfallStatistics
//
//  Created by Shawn Davidson on 8/30/21.
//

#include <iostream>
#include <limits>

#define NUMOFMONTHS 12

using namespace std;

int main() {
    // insert code here...
    double rainfall[12];
    double total    = 0;
    double max = std::numeric_limits<double>::min();
    double min = std::numeric_limits<double>::max();
    double average;

    for (int i = 0; i < NUMOFMONTHS; i++) {
        cout << "Enter rainfall for month " << i+1 << ": ";
        cin >> rainfall[i];
        
        if (rainfall[i] < 0) {
            cout << "Unable to accept negative values. Please try again!" << endl;
            i--;
            continue;
        }
        
        // Compute statistics
        total += rainfall[i];
        
        if (rainfall[i] > max)
            max = rainfall[i];
        
        if (rainfall[i] < min)
            min = rainfall[i];
    }
    
    // Compute average
    average = total / NUMOFMONTHS;
    
    // Display statistics
    cout << endl << endl;
    cout << "Rainfall statistics: " << endl;
    cout << "Total   : " << total << endl;
    cout << "Average : " << average << endl;
    cout << "Min     : " << min << endl;
    cout << "Max     : " << max << endl;
    cout << endl;
    
    //    for (int i = 0; i < 12; i++) {
    //        cout << rainfall[i] << " ";
    //    }
    
    return 0;
}
