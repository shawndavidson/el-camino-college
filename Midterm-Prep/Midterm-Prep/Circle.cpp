//
//  Circle.cpp
//  Midterm-Prep
//
//  Created by Shawn Davidson on 10/13/21.
//

#include "Circle.hpp"
#include <math.h>

Circle::Circle(double r) {
    this->r = r;
}

double Circle::getCircumference() const {
    return 2 * M_PI * this->r;
}

double Circle::getArea() const {
    return M_PI * this->r * this->r;
}
