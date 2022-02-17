//
//  main.cpp
//  CircleClass
//
//  Created by Shawn Davidson on 8/30/21.
//

#include <iostream>

using namespace std;

class Circle {
private:
    double          radius;
    const double    pi = 3.14159;
    
public:
    Circle() {
        this->radius = 0.0;
    }
    
    Circle(double radius) {
        this->radius = radius;
    }
    
    double getRadius() {
        return this->radius;
    }
    
    void setRadius(double radius) {
        this->radius = radius;
    }
    
    double getArea() {
        return this->pi * this->radius * this->radius;
    }
    
    double getDiameter() {
        return this->radius * 2.0;
    }
    
    double getCircumference() {
        return 2 * this->pi * this->radius;
    }
};

int main() {
    double radius;
    
    cout << "Enter radius: ";
    cin >> radius;
    
    Circle circle(radius);
    
    cout << endl << endl;
    cout << "Area          :" << circle.getArea() << endl;
    cout << "Diameter      :" << circle.getDiameter() << endl;
    cout << "Circumference :" << circle.getCircumference() << endl;
    cout << endl;
    
    return 0;
}
