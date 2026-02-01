// write a programe to find fectorial of given number 
// home_work_27_01_2.cpp
#include <iostream>
using namespace std;
int main()
{
    int num;
    unsigned long long factorial = 1;
    cout << "Enter a positive intiger: ";
    cin >> num;
    if (num < 0)
        cout << "Error! Factorial of nagative number doesn't exist." << endl;
    else
    {
        for (int i = 1; i <= num; ++i)
        {
            factorial *= i;
        }
        cout << "Factorial of " << num << " is " << factorial << endl;
    }
    return 0;
}