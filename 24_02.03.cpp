#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int age;
    int rollNumber;

public:
    void readStudentInfo() {
        cout << "Enter student's name: ";
        getline(cin >> ws, name); 
        
        cout << "Enter student's age: ";
        cin >> age;
        
        cout << "Enter student's roll number: ";
        cin >> rollNumber;
    }

    void printStudentInfo() {
        cout << "--- Student Record ---" << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Roll Number: " << rollNumber << endl;
    }
};
int main() 
{
    Student s;
    s.readStudentInfo();
    s.printStudentInfo();
    
    return 0;
}