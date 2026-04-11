// write a proggrame demonstrating cunstrocter with multipul objects
#include <iostream>
using namespace std;
class Rectangle {
    int length, width;
public:
    Rectangle(int l, int w) : length(l), width(w) {
        cout << "Rectangle created with length: " << length << " and width: " << width << endl;
    }
    int area() {
        return length * width;
    }

void displayarea() {
    cout << "Area of rangle is: " << area() << endl;
}
};
int main() {
      cout << "Creating multiple Rectangle objects:" << endl;   
    Rectangle rect1(10, 5);
    rect1.displayarea();

    Rectangle rect2(7, 3);
    rect2.displayarea();

    Rectangle rect3(12, 8);
    rect3.displayarea();

    return 0;
}
