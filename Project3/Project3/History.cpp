//
//  History.cpp
//  Project3
//
//  Created by Shawn Davidson on 10/18/21.
//

#include "History.hpp"
#include <iostream>

using namespace std;

History::History(int nRows, int nCols)
: m_rows(nRows),
  m_cols(nCols)
{
    // Simulate a 2-dimension array with a single array
    m_pGrid = new char[nRows * nCols];
    
    // Fill the grid with dots
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            *(m_pGrid + r*m_cols + c) = '.';
}

History::~History() {
    delete [] m_pGrid;
}

bool History::record(int r, int c)
{
    if (r < 1 || r > MAXROWS || c < 1 || c > MAXCOLS)
        return false;
    
    // Reference the char at the specific position but convert
    // row and column to zero-based indices
    char& ch = *(m_pGrid + (r-1)*m_cols + (c-1));

    if (ch == '.') {
        ch = 'A';
    }else if (ch >= 'A' && ch < 'Z')
    {
        ch++;
    }
    
    return true;
}


void History::display() const
{
    // Draw the history
    clearScreen();

    for (int r = 0; r < m_rows; r++)
    {
        for (int c = 0; c < m_cols; c++)
            //cout << grid[r][c];
            cout << *(m_pGrid + r*m_cols + c);
        cout << endl;
    }
    cout << endl;
}

