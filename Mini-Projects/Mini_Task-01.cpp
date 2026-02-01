#include<iostream>
using namespace std;
int main()
{
    int itemCount;
    float price, total = 0.0, taxRate = 0.07, taxAmount, finalAmount;

    cout << "Enter the number of items: ";
    cin >> itemCount;

    for(int i = 1; i <= itemCount; i++)
    {
        cout << "Enter price of item " << i << ": ";
        cin >> price;
        total += price;
    }

    taxAmount = total * taxRate;
    finalAmount = total + taxAmount;

    cout << "\n----- Bill Summary -----\n";
    cout << "Total Amount: $" << total << endl;
    cout << "Tax Amount (7%): $" << taxAmount << endl;
    cout << "Final Amount to Pay: $" << finalAmount << endl;

    return 0;
}