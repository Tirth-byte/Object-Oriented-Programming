#include <iostream>
using namespace std;
class abc {
    int a;
public:
    abc(int x)
    {
        a = x;
    }
    void getdata()
    {
        cout << "The value of a is: " << a << endl;     
}
   operator int()
    {
         return a;
    }
};
int main()
{
    abc obj1(10);
    obj1.getdata();
    int x; // implicit conversion from abc to int
    x = obj1; // explicit conversion from abc to int
    cout << "Class to Basic " << x << endl; // Output:
    return 0;
}