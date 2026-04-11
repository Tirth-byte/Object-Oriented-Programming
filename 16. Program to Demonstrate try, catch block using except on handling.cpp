#include <iostream>
using namespace std;
void divide(int a, int b){
    try {
        if (b == 0){
            throw "Division by zero is not allowed!";
        }
        cout << "Result: " << (a / b) << endl;
    } 
    catch (const char* msg){
        cout << "Exception caught: " << msg << endl;
    }
}
int main(){
    int num1, num2;
    cout << "Enter two numbers: ";
    cin >> num1 >> num2;
    divide(num1, num2);
    return 0;
}
