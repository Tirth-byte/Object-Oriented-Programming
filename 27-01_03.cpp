#include<iostream>
using namespace std;
int main()
{
    int num;
    cout<<"Enter an integer: ";
    cin>>num;
    if(num > 0)
        cout<< num <<" is a positive number"<<endl;
    else if(num < 0)
        cout<< num <<" is a negative number"<<endl;
    else
    cout<< "the number is zero"<<endl;
    return 0;
}