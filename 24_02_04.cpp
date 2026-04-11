#include <iostream>
using namespace std;

class PrimeNumber {
private:
    int number;

public:
    void readNumber() {
        cout << "Enter a number: ";
        cin >> number;
    }

    void checkPrime() {
        if (number <= 1) {
            cout << number << " is NOT a prime number." << endl;
            return;
        }

        bool isPrime = true;

        for (int i = 2; i*i <= number; i++) {
            if (number % i == 0) {
                isPrime = false;
                break;
            }
        }

        if (isPrime)
            cout << number << " is a PRIME number." << endl;
        else
            cout << number << " is NOT a prime number." << endl;
    }
};

int main() {
    PrimeNumber obj;  
    obj.readNumber();  
    obj.checkPrime();  
    return 0;
}