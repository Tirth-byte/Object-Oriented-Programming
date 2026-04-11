#include <iostream>
using namespace std;
template <typename T>
T swapValues(T &a, T &b) 
{
    T temp = a;
    a = b;
    b = temp;
}

int main() 
{
    int x = 10, y = 20;
    double p = 1.5, q = 2.5;
    char c1 = 'A', c2 = 'B';
    
    cout << "Before swapping: x = " << x << ", y = " << y << endl;
    swapValues(x, y);
    cout << "After swapping: x = " << x << ", y = " << y << endl;
    
    cout << "Before swapping: p = " << p << ", q = " << q << endl;
    swapValues(p, q);
    cout << "After swapping: p = " << p << ", q = " << q << endl;
    
    cout << "Before swapping: c1 = " << c1 << ", c2 = " << c2 << endl;
    swapValues(c1, c2);
    cout << "After swapping: c1 = " << c1 << ", c2 = " << c2 << endl;
    
    return 0;
}

