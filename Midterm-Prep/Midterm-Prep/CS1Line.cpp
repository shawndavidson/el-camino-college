//
//  CS1Line.cpp
//  Midterm-Prep
//
//  Created by Shawn Davidson on 10/13/21.
//

#include "CS1Line.hpp"

CS1Line::CS1Line(int a, int b, int c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

bool CS1Line::isOnLine(int x, int y) const {
    return (this->a*x) + (this->b*y) + this->c == 0;
}

double CS1Line::getSlope() const {
    return -(double)this->a / this->b;
}
