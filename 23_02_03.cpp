// using function overloading find volume of cube and cylinder and sphere
#include <iostream>
#include <cmath>
#define PI 3.14
using namespace std;
double volumeCube(float side) {
    return pow(side, 3);
}

double volumeCylinder(float radius, float height) {
    return PI * radius * radius * height;
}

double volumeSphere(float radius) {
    return (4.0/3.0) * PI * pow(radius, 3);
}

int main()
{
    float side, radius, height;
    
    cout << "Enter side length of the cube: ";
    cin >> side;
    cout << "Volume of the cube: " << volumeCube(side) << endl;

    cout << "Enter radius and height of the cylinder: ";
    cin >> radius >> height;
    cout << "Volume of the cylinder: " << volumeCylinder(radius, height) << endl;

    cout << "Enter radius of the sphere: ";
    cin >> radius;
    cout << "Volume of the sphere: " << volumeSphere(radius) << endl;

    return 0;
}