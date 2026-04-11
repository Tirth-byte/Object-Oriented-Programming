#include<iostream>
using namespace std;
int main()
{
    int n,sum=0;
    cout<<"Enter the value of n: ";
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        sum += i; // sum = sum+i;
    }
    cout<<"The sum of the first "<< n <<" natural numbers is :"<< sum << endl;
    return 0;
}