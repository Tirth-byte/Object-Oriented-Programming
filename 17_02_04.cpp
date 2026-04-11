#include <iostream>
using namespace std;
float ftoc(float fahrenheit) {
    return (fahrenheit - 32) * 5.0 / 9.0;
}
float ctof(float celsius) {
    return (celsius * 9.0 / 5.0) + 32;
}
int main() {
    float f, c,choice;
    switch (choice) {
        case 1:
            cout << "Enter temperature in Fahrenheit: ";
            cin >> f;
            cout << "Temperature in Celsius: " << ftoc(f) << endl;
            break;
        case 2:
            cout << "Enter temperature in Celsius: ";
            cin >> c;
            cout << "Temperature in Fahrenheit: " << ctof(c) << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
    }
     return 0;
}
vutual function 