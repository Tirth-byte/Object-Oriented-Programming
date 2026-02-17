// with parameter without retunrn value
#include <iostream>
using namespace std;
void addNumbers(int x, int y) {
    int sum = x + y;
    cout << "The sum of " << x << " and " << y << " is: " << sum << endl;
}
int main()
{
    int x, y;
    addNumbers(5, 3);
    return 0;
}