 // basic example of user defind function
#include <iostream>
using namespace std;

int add(int a, int b) {
    return a+b;
}
int subtract(int a, int b) {
    return a-b;
}
int multiply(int a, int b) {
    return a*b;
}
float divide(int a, int b) {
    if(b == 0){
        cout << "Error ! Division by zero.";
        return 0;
    }
    else {
        return(float)a/b;
    }
}
int Modulus(int a,int b){
    return a % b;
}
int main() {
    int num1 , num2;
    char operation;
    cout<<"Enter two numbers: ";
    cin>>num1 >> num2;

    cout<<"Enter an operater (+, -, *, /, %):";
    cin >> operation;
    switch(operation){
        case '+':
        cout << "Result: " << add(num1, num2) << endl;
        break;
        case '-':
        cout << "Result: " << subtract(num1, num2) << endl;
        break;
        case '*':
        cout << "Result: " << multiply(num1, num2) << endl;
        break;
        case '/':
        cout << "Result: " << divide(num1, num2) << endl;
        break;
        case '%':
        cout << "Result: " << Modulus(num1, num2) << endl;
        break;
        default:
        cout << "Invalid operator!" << endl;
    }
    return 0;
}in this code give input 10 0 and / it should show Error ! Division by zero. but with this we are getting one 0 also whyShow more14:14The Issue
When b == 0, your divide function does two things:
cppif(b == 0){
    cout << "Error ! Division by zero.";
    return 0;   // ← This 0 is returned back to main
}
Then in main, you have:
cppcout << "Result: " << divide(num1, num2) << endl;
//                    ^^^^^^^^^^^^^^^^^^
//                    This prints whatever divide() returns
```

So the output becomes:
```
Error ! Division by zero.Result: 0
The cout in main always prints the return value of divide(), and since you return 0 on error, it prints that 0.

The Fix
You have a couple of clean options:
Option 1 — Handle printing inside divide() and return early before main prints:
cppfloat divide(int a, int b) {
    if(b == 0){
        cout << "Error! Division by zero." << endl;
        return 0;
    }
    return (float)a / b;
}

// In main, only print if b is not zero
case '/':
    if(num2 != 0)
        cout << "Result: " << divide(num1, num2) << endl;
    else
        divide(num1, num2); // just triggers the error message
    break;
Option 2 — Check in main directly (cleaner approach):
cppcase '/':
    if(num2 == 0)
        cout << "Error! Division by zero." << endl;
    else
        cout << "Result: " << divide(num1, num2) << endl;
    break;
Option 3 — Keep logic in divide() and print nothing in main:
This is the simplest fix — just move all output responsibility to divide() and don't embed it inside cout <<:
cppfloat divide(int a, int b) {
    if(b == 0){
        cout << "Error! Division by zero." << endl;
        return 0;
    }
    return (float)a / b;
}

// In main:
case '/':
    {
        float result = divide(num1, num2);
        if(num2 != 0)
            cout << "Result: " << result << endl;
    }
    break;

Option 2 is the most straightforward — keep divide() pure (only math, no printing) and handle all user messaging in main.// basic example of user defind function
#include <iostream>
using namespace std;
int add(int a, int b) {
    return a+b;
}
int subtract(int a, int b) {
    return a-b;
}
int multiply(int a, int b) {
    return a*b;
}
float divide(int a, int b) {
    if(b == 0){
        cout << "Error ! Division by zero.";    }
    else {
        return(float)a/b;
    }
}
int Modulus(int a,int b){
    return a % b;
}
int main() {
    int num1 , num2;
    char operation;
    cout<<"Enter two numbers: ";
    cin>>num1 >> num2;
    cout<<"Enter an operater (+, -, *, /, %):";
    cin >> operation;
    switch(operation){
        case '+':
        cout << "Result: " << add(num1, num2) << endl;
        break;
        case '-':
        cout << "Result: " << subtract(num1, num2) << endl;
        break;
        case '*':
        cout << "Result: " << multiply(num1, num2) << endl;
        break;
        case '/':
        cout << "Result: " << divide(num1, num2) << endl;
        break;
        case '%':
        cout << "Result: " << Modulus(num1, num2) << endl;
        break;
        default:
        cout << "Invalid operator!" << endl;
    }
    return 0;
} will this working fine nowShow more14:18Not Quite — There's Still a Problem
You removed the return 0; but the function still has undefined behavior.