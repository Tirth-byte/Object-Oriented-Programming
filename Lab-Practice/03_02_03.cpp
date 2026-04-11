#include <iostream>
using namespace std;
int main()
{
    int num;
    int reverse = 0;
    cout << "Enter a number: ";
    cin>>num;
    while(num>0)
    {
        int digit = num % 10;
        reverse = reverse*10 + digit;
        num /= 10;
    }
    cout << "the reverse of the number is : "<< reverse << endl;
    return 0;
}