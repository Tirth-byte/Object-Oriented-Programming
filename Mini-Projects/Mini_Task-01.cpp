#include<iostream>
using namespace std;
int main()
{
    int itemCount;
    float price, total = 0.0, taxRate = 0.07, taxAmount, finalAmount; // 7% tax rate

    cout << "Enter the number of items: ";
    cin >> itemCount;                      // Input for number of items

    for(int i = 1; i <= itemCount; i++)
    {
        cout << "Enter price of item " << i << ": ";
        cin >> price;
        total += price;
    }

    taxAmount = total * taxRate;        
    finalAmount = total + taxAmount;     
cout << endl;
cout << "========================================" << endl;
cout << "           BILL SUMMARY                 " << endl;
cout << "========================================" << endl << endl;
cout << "  Subtotal:                    ₹" << total << endl;
cout << "  Tax (7%):                    ₹" << taxAmount << endl;
cout << "  --------------------------------------" << endl;
cout << "  TOTAL TO PAY:                ₹" << finalAmount << endl;
cout << "========================================" << endl << endl;
    return 0;
}
