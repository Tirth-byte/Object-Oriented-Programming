#include <iostream>
using namespace std;
class Student {
private:
    string name;
    int age;
    string course;

public:
    Student(string n, int a, string c) {
        name = n;
        age = a;
        course = c;
    }
    void display() {
        cout << "Student Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Course: " << course << endl;
    }
};
int main() {
    string name, course;
    int age;

    cout << "Enter Student Name: ";
    getline(cin, name);

    cout << "Enter Age: ";
    cin >> age;

    cout << "Enter Course: ";
    getline(cin, course);
    Student s1(name, age, course);

    cout << "\n--- Student Profile ---\n";
    s1.display();

    return 0;
}