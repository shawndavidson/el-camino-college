//
//  Circle.hpp
//  Midterm-Prep
//
//  Created by Shawn Davidson on 10/13/21.
//

#ifndef Circle_hpp
#define Circle_hpp

class Circle {
private:
    double r;
    
public:
    Circle(double r);
    
    double getCircumference() const;
    double getArea() const;
};

#endif /* Circle_hpp */
