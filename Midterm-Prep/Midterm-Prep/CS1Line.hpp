//
//  CS1Line.hpp
//  Midterm-Prep
//
//  Created by Shawn Davidson on 10/13/21.
//

#ifndef CS1Line_hpp
#define CS1Line_hpp

class CS1Line {
private:
    int a, b, c;
    
public:
    CS1Line(int a, int b, int c);
    
    bool isOnLine(int x, int y) const;
    
    double getSlope() const;
};

#endif /* CS1Line_hpp */
