#include <iostream>
using namespace std;

#define MAX 100

// UI
void line() {
    cout << "\n==================================================\n";
}

void title(string t) {
    line();
    cout << "            " << t << endl;
    line();
}

// BASE CLASS
class Employee {
protected:
    int id;
    string name;
    float baseSalary;

public:
    virtual void getData() {
        cout << "Enter ID          : "; cin >> id;
        cin.ignore();
        cout << "Enter Name        : "; getline(cin, name);
        cout << "Enter Base Salary : "; cin >> baseSalary;
    }

    virtual float calculateSalary() {
        return baseSalary;
    }

    virtual void display() {
        cout << "ID            : " << id << endl;
        cout << "Name          : " << name << endl;
        cout << "Base Salary   : " << baseSalary << endl;
    }

    int getID() { return id; }

    virtual void edit() {
        cin.ignore();
        cout << "Edit Name        : "; getline(cin, name);
        cout << "Edit Base Salary : "; cin >> baseSalary;
    }
};

// MANAGER
class Manager : public Employee {
    float bonus;

public:
    void getData() {
        Employee::getData();
        cout << "Enter Bonus      : "; cin >> bonus;
    }

    float calculateSalary() {
        return baseSalary + bonus;
    }

    void display() {
        cout << "[Manager]\n";
        Employee::display();
        cout << "Bonus         : " << bonus << endl;
        cout << "Total Salary  : " << calculateSalary() << endl;
        line();
    }

    void edit() {
        Employee::edit();
        cout << "Edit Bonus     : "; cin >> bonus;
    }
};

// DEVELOPER
class Developer : public Employee {
    int hours;
    float rate;

public:
    void getData() {
        Employee::getData();
        cout << "Overtime Hours : "; cin >> hours;
        cout << "Rate per Hour  : "; cin >> rate;
    }

    float calculateSalary() {
        return baseSalary + (hours * rate);
    }

    void display() {
        cout << "[Developer]\n";
        Employee::display();
        cout << "Overtime Hrs  : " << hours << endl;
        cout << "Rate          : " << rate << endl;
        cout << "Total Salary  : " << calculateSalary() << endl;
        line();
    }

    void edit() {
        Employee::edit();
        cout << "Edit Hours     : "; cin >> hours;
        cout << "Edit Rate      : "; cin >> rate;
    }
};

// STORAGE (NO POINTERS)
Manager managers[MAX];
Developer developers[MAX];
int mCount = 0, dCount = 0;

// ADD
void addEmployee() {
    int type;
    title("ADD EMPLOYEE");

    cout << "1. Manager\n2. Developer\nChoose Type: ";
    cin >> type;

    if (type == 1 && mCount < MAX) {
        managers[mCount].getData();
        mCount++;
    }
    else if (type == 2 && dCount < MAX) {
        developers[dCount].getData();
        dCount++;
    }
    else {
        cout << "Storage Full!\n";
    }
}

// SHOW
void showAll() {
    title("ALL EMPLOYEES");

    if (mCount == 0 && dCount == 0) {
        cout << "No Employees Found!\n";
        return;
    }

    for (int i = 0; i < mCount; i++)
        managers[i].display();

    for (int i = 0; i < dCount; i++)
        developers[i].display();
}

// SEARCH
void searchEmployee() {
    int id;
    cout << "Enter ID to Search: ";
    cin >> id;

    for (int i = 0; i < mCount; i++) {
        if (managers[i].getID() == id) {
            managers[i].display();
            return;
        }
    }

    for (int i = 0; i < dCount; i++) {
        if (developers[i].getID() == id) {
            developers[i].display();
            return;
        }
    }

    cout << "Employee Not Found!\n";
}

// EDIT
void editEmployee() {
    int id;
    cout << "Enter ID to Edit: ";
    cin >> id;

    for (int i = 0; i < mCount; i++) {
        if (managers[i].getID() == id) {
            managers[i].edit();
            cout << "Updated!\n";
            return;
        }
    }

    for (int i = 0; i < dCount; i++) {
        if (developers[i].getID() == id) {
            developers[i].edit();
            cout << "Updated!\n";
            return;
        }
    }

    cout << "Employee Not Found!\n";
}

// DELETE
void deleteEmployee() {
    int id;
    cout << "Enter ID to Delete: ";
    cin >> id;

    for (int i = 0; i < mCount; i++) {
        if (managers[i].getID() == id) {
            for (int j = i; j < mCount - 1; j++)
                managers[j] = managers[j + 1];
            mCount--;
            cout << "Deleted!\n";
            return;
        }
    }

    for (int i = 0; i < dCount; i++) {
        if (developers[i].getID() == id) {
            for (int j = i; j < dCount - 1; j++)
                developers[j] = developers[j + 1];
            dCount--;
            cout << "Deleted!\n";
            return;
        }
    }

    cout << "Employee Not Found!\n";
}

// DEMO (NO INPUT ✅)
void demo() {
    title("DEMO DATA");

    managers[mCount++] = Manager();
    managers[mCount - 1] = Manager();
    managers[mCount - 1].getData(); // optional remove if needed

    developers[dCount++] = Developer();
    developers[dCount - 1].getData();

    cout << "Demo Added (you can modify if needed)\n";
}

// MAIN
int main() {
    int choice;

    do {
        title("EMPLOYEE PAYROLL SYSTEM");

        cout << "1. Add Employee\n";
        cout << "2. Show All Employees\n";
        cout << "3. Search Employee\n";
        cout << "4. Edit Employee\n";
        cout << "5. Delete Employee\n";
        cout << "6. Demo Data\n";
        cout << "7. Exit\n";

        line();
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: showAll(); break;
            case 3: searchEmployee(); break;
            case 4: editEmployee(); break;
            case 5: deleteEmployee(); break;
            case 6: demo(); break;
            case 7: cout << "Goodbye!\n"; break;
            default: cout << "Invalid Choice!\n";
        }

    } while (choice != 7);

    return 0;
}