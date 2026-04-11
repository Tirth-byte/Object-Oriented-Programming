// call by reference
#include <iostream>
using namespace std;
// the & symbol is creating a refrance 
void swapeNumbers(int &x,&y){
    int temp = x;
    x = y;
    y = temp;
}
int main() {
    int a=10;
    int b=20;
    cout << "before Swap a =" << a << ", b=" << b << endl;
    swapeNumbers(a,b);
    cout << "After swap: a=" << ", b = "<< b << endl;
     return 0;
}