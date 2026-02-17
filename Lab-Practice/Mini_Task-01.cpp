#include <iostream>
using namespace std;

int main()
{
    string customerName,ItemName,Address;
    int itemCount;
    int quantity;
    double price;
    double subtotal = 0;
    double discount = 0;
    double tax = 0;
    double total = 0;

    cout << "=====================================\n";
    cout << "        SIMPLE BILLING SYSTEM\n";
    cout << "=====================================\n";

    cout << "Enter Customer Name: ";
    cin  >> customerName;
    cout << "-------------------------------------\n";

    cout << "Enter Address: ";
    cin >> Address;
    cout << "-------------------------------------\n";

    cout << "Enter Number of Items: ";
    cin >> itemCount;

    cout << "\nEnter Item Details\n";
    cout << "-------------------------------------\n";

    for (int i = 1; i <= itemCount; i++)
    {
        cout << "Item " << i << " Name: ";
        cin >> ItemName;

        cout << "Item " << i << " Price: ";
        cin >> price;

        cout << "Item " << i << " Quantity: ";
        cin >> quantity;

        subtotal = subtotal + (price * quantity);
    }

    // Discount
    if (subtotal >= 1000)
    {
        discount = subtotal * 10 / 100;
    }

    // Tax
    tax = (subtotal - discount) * 5 / 100;

    // Total amount
    total = subtotal - discount + tax;

    cout << "\n\n=====================================\n";
    cout << "              FINAL BILL\n";
    cout << "=====================================\n";
    cout << "Customer Name : " << customerName << endl;
    cout << "Address       : " << Address << endl;
    cout << "-------------------------------------\n";
    cout << "Item Details:\n";
    for (int i = 1; i <= itemCount; i++)
    { 
        cout << "Item " << i << " Name: " << ItemName << endl;
        cout << "Item " << i << " Price: ₹ " << price << endl;
        cout << "Item " << i << " Quantity: " << quantity << endl;
    }
    cout << "-------------------------------------\n";
    cout << "Subtotal      : ₹ " << subtotal << endl;
    cout << "Discount      : ₹ " << discount << endl;
    cout << "Tax (5%)      : ₹ " << tax << endl;
    cout << "-------------------------------------\n";
    cout << "Total Payable : ₹ " << total << endl;
    cout << "=====================================\n";
    cout << "     THANK YOU FOR SHOPPING!\n";
    cout << "=====================================\n";

    return 0;
}
