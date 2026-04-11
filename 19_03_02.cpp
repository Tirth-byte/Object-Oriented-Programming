#include <iostream>
using namespace std;

class base {
private:
    int privatevar = 10;

protected:
    int protectedvar = 20;

public:
    int publicvar = 30;

    int getPrivateVar() {
        return privatevar;
    }
};

class derived : public base {
public:
    void display() {
        cout << "Private Variable: " << getPrivateVar() << endl;
        cout << "Protected Variable: " << protectedvar << endl;
        cout << "Public Variable: " << publicvar << endl;
    }
};

int main() {
    derived obj;
    obj.display();
    cout << "public variable from main: " << obj.publicvar << endl;
    return 0;
}