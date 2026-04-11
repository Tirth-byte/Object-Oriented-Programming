#include <iostream>
using namespace std;

class shape {
public:
    virtual void draw() = 0; // pure virtual function
}; 

class Circle : public shape {
public:
    void draw() {
        cout << "Drawing a Circle" << endl;
    }
};

class Rectangle : public shape {
public:
    void draw() {
        cout << "Drawing a Rectangle" << endl;
    }
};

int main() {
    shape* shapePtr;   

    Circle circle;
    Rectangle rectangle;

    shapePtr = &circle;
    shapePtr->draw();

    shapePtr = &rectangle;
    shapePtr->draw();

    return 0;
}