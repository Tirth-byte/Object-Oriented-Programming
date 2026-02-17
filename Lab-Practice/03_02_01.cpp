// write a programe to demonstrate all the artehmetic opraters in c++
#include <iostream>
using namespace std;
int main()
{
    int a, b;
    cout << "Enter two numbers: " << endl;
    cin >> a >> b;

    cout << "Arithmetic operators demonstration:" << endl;
    cout << "Addition: " << a << " + " << b << " = " << a + b << endl;
    cout << "subtraction: " << a << " - " << b << " = " << a - b << endl;
    cout << "Multiplication: " << a << " * " << b << " = " << a * b << endl;
    cout << "Division: " << a << " / " << b << " = " << a / b << endl;
    cout << "Modulus: " << a << " % " << b << " = " << a % b << endl;
    cout << "Pre-Increment: " << a << "++ = " << ++a << endl;
    cout << "Pre-Decrement: " << b << "-- = " << --b << endl;
    cout << "Post-Increment: " << a << "++ = " << a++ << endl;
    cout << "Post-Decrement: " << b << "-- = " << b-- << endl;
    cout << "Final values: a = " << a << " and b = " << b << endl;
    return 0;
}


   