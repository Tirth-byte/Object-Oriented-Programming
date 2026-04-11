#include <iostream>
#include <cmath>
using namespace std;

const float PI = 3.14159f;

float areaCircle(float radius) {
    return PI * radius * radius;
}
float areaTriangle(float base, float height) {
    return 0.5 * base * height;
}
float areaRectangle(float length, float width) {
    return length * width;
}
int main() {
    float radius, base, height, length, width;
    cout << "Enter radius of the circle: ";
    cin >> radius;  
    cout << "Area of the circle: " << areaCircle(radius) << endl;

    cout << "Enter base and height of the triangle: ";
    cin >> base >> height;
    cout << "Area of the triangle: " << areaTriangle(base, height) << endl;

    cout << "Enter length and width of the rectangle: ";
    cin >> length >> width;
    cout << "Area of the rectangle: " << areaRectangle(length, width) << endl;

     return 0;
}