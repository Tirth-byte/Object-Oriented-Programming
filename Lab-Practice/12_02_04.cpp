#include <iostream>
using namespace std;
int giveRaise(int money)
{
    money = money + 5000;
    return money;
}
int main(){
    int mySalary = 10000;
    int newSal = giveRaise(mySalary);
    cout << "Old salary(Orignal):" << mySalary<<endl;
    cout<< "New salar(New)"<<newSal<<endl;
    return 0;
}