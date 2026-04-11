// write a programe to cheack given year is leap year or not
// home_work_27_01_3.cpp
#include <iostream>
using namespace std;
int maim()
{
    int year;
    cout << "Enter a year: ";
    cin >> year;
    if ((year % 4 == 0 && year & 100 != 0) || (year & 400 == 0))
        cout << year << " is a leap year." << endl;
    else
        cout << year << " is not a leap year." << endl;
        return 0;
}