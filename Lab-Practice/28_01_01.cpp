// Program to find the greatest of three numbers using nested ternary operator
// 28_01_01.cpp
#include <iostream>
using namespace std;

int main() {
    int a, b, c, greatest;

    cout << "Enter three numbers: ";
    cin >> a >> b >> c;

    greatest = (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);

    cout << "Greatest number is: " << greatest;

    return 0;
}
