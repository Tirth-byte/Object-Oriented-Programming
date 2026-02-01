// write a programe to take input of time and say its good morning or good afternoon or good night
// 28_01_02.cpp
#include <iostream>
using namespace std;   

int main() {
    int hour;
    cout << "Enter the hour (0-23): ";
    cin >> hour;

    if (hour >= 0 && hour < 12) {
        cout << "Good Morning!" << endl;
    } else if (hour >= 12 && hour < 18) {
        cout << "Good Afternoon!" << endl;
    } else {
        cout << "Good Night!" << endl;
    }

    return 0;
}