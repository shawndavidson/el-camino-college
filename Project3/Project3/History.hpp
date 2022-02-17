//
//  History.hpp
//  Project3
//
//  Created by Shawn Davidson on 10/18/21.
//

#ifndef History_hpp
#define History_hpp

#include "globals.h"

class History
{
  public:
    History(int nRows, int nCols);
    ~History();
    
    bool record(int r, int c);
    void display() const;
    
private:
    int m_rows;
    int m_cols;
    
    char *m_pGrid;
};

#endif /* History_hpp */
