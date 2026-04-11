#include <iostream>
using namespace std;
int cube(int number) {
    return number * number * number;
}
int main() {
    int num;
    cout << "Enter a number: ";
    cin >> num;
    int result = cube(num);
    cout << "The cube of " << num << " is: " << result << endl
    return 0;
}