// with perameter with return 
#include<iostream>
using namespace std;
int addNumbers(int x, int y)
{
    int sum = x + y;
    return sum;
}
int main()
{
    int num1 = 10, num2 = 20;
    int result = addNumbers(num1, num2);
    cout << "The sum of " << num1 << " and " << num2 << " is: " << result << endl;
    return 0;
}