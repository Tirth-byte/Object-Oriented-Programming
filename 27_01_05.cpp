// find the biggest number among three numbers and check if all are equal
#include <iostream>
using namespace std;

int main()
{
    int a, b, c;
    cout << "Enter three numbers: " << endl;
    cin >> a >> b >> c;

    if (a == b && b == c)
        cout << "All three numbers are equal" << endl;
    else if (a >= b && a >= c)
        cout << a << " is the biggest number" << endl;
    else if (b >= a && b >= c)
        cout << b << " is the biggest number" << endl;
    else
        cout << c << " is the biggest number" << endl;

    return 0;
}
