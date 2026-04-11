#include <iostream>
#include <iomanip>   // This header brings all the manipulators 

using namespace std;

int main() {
    
    int num = 255;                 
    double pi = 3.1415926535;   

    // ---------------- endl ----------------
    // endl = "Go to next line AND flush the output"
    // Basically, a polite Enter key 
    cout << "Demonstrating endl manipulator" << endl;
    cout << "This is printed on a new line" << endl << endl;

    // ---------------- setw & setfill ----------------
    // setw(n) : reserves 'n' spaces for output
    // setfill(c) : fills empty spaces with character 'c'
    cout << "Demonstrating setw and setfill" << endl;
    cout << setfill('*');          // Filling empty space with stars 
    cout << setw(10) << 123 << endl;
    cout << setw(10) << 456 << endl;

    // ---------------- setprecision ----------------
    // setprecision(p) : controls how many digits are shown
    // Pi gets chopped here (don’t tell mathematicians)
    cout << "Demonstrating setprecision" << endl;
    cout << setprecision(3) << pi << endl;
    cout << setprecision(5) << pi << endl;

    // ---------------- setbase ----------------
    // setbase(b) : changes the number system
    // Same number, different outfits 
    cout << "Demonstrating setbase" << endl;
    cout << "Decimal: " << setbase(10) << num << endl; 
    cout << "Octal  : " << setbase(8)  << num << endl;  
    cout << "Hex    : " << setbase(16) << num << endl;  

    return 0;  
}
