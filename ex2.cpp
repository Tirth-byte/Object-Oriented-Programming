#include <iostream>
using namespace std;
int add(int a, int b) {
    return a + b;
}
int subtract(int a, int b) {
    return a - b;
}
int multiply(int a, int b) {
    return a * b;
}
double divide(int a, int b) {
    return (double)a / b;
}
int modulus(int a, int b) {
    return a % b;
}
int main() {
    int num1, num2;
    cout << "Enter two numbers: ";
    cin >> num1 >> num2;
    cout << "Addition: " << add(num1, num2) << endl;
    cout << "Subtraction: " << subtract(num1, num2) << endl;
    cout << "Multiplication: " << multiply(num1, num2) << endl;
    if (num2 != 0) {
        cout << "Division: " << divide(num1, num2) << endl;
        cout << "Modulus: " << modulus(num1, num2) << endl;
    } else {
        cout << "Cannot divide by zero" << endl;
    }
    return 0;
}