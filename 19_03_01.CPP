#include <iostream>
using namespace std;

class Person { //base class
protected:
    string name;
    int age;
    string gender;

public:
    void enterDetails() { // member func
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Gender: ";
        cin >> gender;
    }

    void displayDetails() {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: " << gender << endl;
    }
};  // base class end

class Patient : public Person {   //child of person base class
private:
    string disease;
    string doctor;
public:
    void enterPatientDetails() {  // member func
        enterDetails();           // calling base class member func
        cout << "Enter Disease: ";
        cin >> disease;
        cout << "Enter Doctor Assigned: ";
        cin >> doctor;
    }
    void displayPatientDetails() {
        displayDetails(); // calling base class member func
        cout << "Disease: " << disease << endl;
        cout << "Doctor Assigned: " << doctor << endl;
    }
};  // child class end

int main() {
    Patient p;
    cout << "Enter Patient Details:\n";
    p.enterPatientDetails();
    cout << "\nPatient Details:\n";
    p.displayPatientDetails();
    return 0;
}