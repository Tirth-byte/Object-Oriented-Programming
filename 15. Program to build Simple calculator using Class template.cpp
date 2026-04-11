#include <iostream>
using namespace std;
template <typename T>
class Calculator 
{
public:
    T num1, num2;
    Calculator(T a, T b) : num1(a), num2(b) {}
    
    T add() { return num1 + num2; }
    T subtract() { return num1 - num2; }
    T multiply() { return num1 * num2; }
    T divide() 
    {
        if (num2 != 0){
            return num1 / num2;
        }
        else {
            cout << "Error! Division by zero." << endl;
            return 0;
        }
    }
};
int main() 
{
    double a, b;
    cout << "Enter two numbers: ";
    cin >> a >> b;
    Calculator<double> calc(a, b);
    cout << "Addition: " << calc.add() << endl;
    cout << "Subtraction: " << calc.subtract() << endl;
    cout << "Multiplication: " << calc.multiply() << endl;
    cout << "Division: " << calc.divide() << endl;
    return 0;
}
