#include <iostream>
using namespace std;

long long factorial(int n);
long long power(int base, int exp);
bool isPrime(int n);
int digitSum(int n);
bool isPalindrome(int n);
double average(int a, int b);
double average(int a, int b, int c);  

int main() 
{
    cout << "====== SIMPLE MATH TOOLKIT ======" << endl << endl;

    int n, base, exp;
    int a, b, c;

    // Factorial 
    cout << "1. FACTORIAL FUNCTION" << endl;
    cout << "Enter a number: ";
    cin >> n;
    cout << "Factorial of " << n << " is: " 
         << factorial(n) << endl << endl;

    // Power
    cout << "2. POWER FUNCTION" << endl;
    cout << "Enter base: ";
    cin >> base;
    cout << "Enter exponent: ";
    cin >> exp;
    cout << base << "^" << exp << " is: " 
         << power(base, exp) << endl << endl;

    // Prime Check 
    cout << "3. PRIME CHECK FUNCTION" << endl;
    cout << "Enter a number: ";
    cin >> n;
    cout << "Is " << n << " Prime? " 
         << (isPrime(n) ? "Yes" : "No") << endl << endl;

    // Digit Sum
    cout << "4. DIGIT SUM FUNCTION" << endl;
    cout << "Enter a number: ";
    cin >> n;
    cout << "Digit Sum of " << n << " is: " 
         << digitSum(n) << endl << endl;

    // Palindrome 
    cout << "5. PALINDROME CHECK FUNCTION" << endl;
    cout << "Enter a number: ";
    cin >> n;
    cout << "Is " << n << " Palindrome? " 
         << (isPalindrome(n) ? "Yes" : "No") << endl << endl;

    // Average (2 numbers) 
    cout << "6. AVERAGE FUNCTION (2 Numbers)" << endl;
    cout << "Enter two numbers: ";
    cin >> a >> b;
    cout << "Average is: " 
         << average(a, b) << endl << endl;

    // Average (3 numbers)
    cout << "7. AVERAGE FUNCTION (3 Numbers)" << endl;
    cout << "Enter three numbers: ";
    cin >> a >> b >> c;
    cout << "Average is: " 
         << average(a, b, c) << endl;

    return 0;
}
// FUNCTION DEFINITIONS
long long factorial(int n)
{
    long long fact = 1;
    for(int i = 1; i <= n; i++)
        fact = fact * i;

    return fact;
}

long long power(int base, int exp)
{
    long long result = 1;
    for(int i = 1; i <= exp; i++)
        result = result * base;

    return result;
}

bool isPrime(int n)
{
    if(n <= 1) return false;

    for(int i = 2; i < n; i++)
        if(n % i == 0)
            return false;

    return true;
}

int digitSum(int n)
{
    int sum = 0;

    while(n > 0)
    {
        sum = sum + (n % 10);
        n = n / 10;
    }

    return sum;
}

bool isPalindrome(int n)
{
    int original = n;
    int reverse = 0;

    while(n > 0)
    {
        reverse = reverse * 10 + n % 10;
        n = n / 10;
    }

    return original == reverse;
}
// FUNCTION OVERLOADING
double average(int a, int b)
{
    return (a + b) / 2.0;
}

double average(int a, int b, int c)
{
    return (a + b + c) / 3.0;
}