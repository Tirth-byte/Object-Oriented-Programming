#include<iostream>
using namespace std;
int main()
{
    int a,b, temp;
    cout<<"Enter two numbers: ";
    cin>>a>>b;
    temp = a;
    a = b;
    b = temp;
    cout<<"After swapping first number is: "<<a<<endl;
    cout<<"After swapping second number is: "<<b<<endl;
    return 0;
}