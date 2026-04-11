// write a programe to find the number is positive , nagative or zero using nested if else
// 28_01_03.cpp
#include <iostream>
using namespace std;
int main()
{
    int n;
    cout << "Enter a number: ";
    cin >> n;
    if (n>0)
    {
        cout << "The number is positive.";
    }
    else
    {
        if (n<0)
        {
            cout << "The number is negative.";
        }
        else
        {
            cout << "The number is zero.";
        }
    }
}
    return 0;
}