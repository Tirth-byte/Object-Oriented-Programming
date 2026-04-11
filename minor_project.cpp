/*
 * ╔══════════════════════════════════════════════════════════════╗
 * ║              HOSTEL MANAGEMENT SYSTEM                       ║
 * ║  Manage room allocations, student records & mess fees       ║
 * ╚══════════════════════════════════════════════════════════════╝
 *
 *  Features:
 *    • Add / Search / Display student records
 *    • Allocate & deallocate rooms with capacity checks
 *    • Track mess fee payments and outstanding balances
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// ─── Constants ───────────────────────────────────────────────────
const int MAX_STUDENTS  = 100;
const int MAX_ROOMS     = 50;
const int MAX_CAPACITY  = 4;       // max students per room
const float DEFAULT_MESS_FEE = 5000.0f;

// ─── Utility: draw a horizontal rule ─────────────────────────────
void drawLine(int width = 70) {
    cout << "  ";
    for (int i = 0; i < width; i++) cout << '-';
    cout << '\n';
}

void drawDoubleLine(int width = 70) {
    cout << "  ";
    for (int i = 0; i < width; i++) cout << '=';
    cout << '\n';
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  CLASS : Student
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
class Student {
private:
    int    rollNo;
    string name;
    int    age;
    string department;
    string contactNo;

public:
    Student()
        : rollNo(0), name(""), age(0), department(""), contactNo("") {}

    Student(int r, string n, int a, string d, string c)
        : rollNo(r), name(n), age(a), department(d), contactNo(c) {}

    // ── Getters ──
    int    getRollNo()     const { return rollNo; }
    string getName()       const { return name; }
    string getDepartment() const { return department; }
    string getContact()    const { return contactNo; }

    // ── Input ──
    void input() {
        cout << "\n  ┌─ Student Registration ─────────────────────┐\n";
        cout << "  │  Roll No    : "; cin >> rollNo;
        cout << "  │  Name       : "; cin >> name;
        cout << "  │  Age        : "; cin >> age;
        cout << "  │  Department : "; cin >> department;
        cout << "  │  Contact No : "; cin >> contactNo;
        cout << "  └─────────────────────────────────────────────┘\n";
    }

    // ── Tabular display (single row) ──
    void displayRow() const {
        cout << "  │ " << setw(6)  << rollNo
             << " │ " << setw(14) << left << name << right
             << " │ " << setw(4)  << age
             << " │ " << setw(10) << left << department << right
             << " │ " << setw(12) << left << contactNo << right
             << " │\n";
    }

    // ── Compact card ──
    void displayCard() const {
        cout << "  ┌── Student #" << rollNo << " ──────────────────────┐\n";
        cout << "  │  Name       : " << name        << '\n';
        cout << "  │  Age        : " << age         << '\n';
        cout << "  │  Department : " << department  << '\n';
        cout << "  │  Contact    : " << contactNo   << '\n';
        cout << "  └──────────────────────────────────────┘\n";
    }
};

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  CLASS : Room
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
class Room {
private:
    int roomNo;
    int capacity;
    int currentOccupancy;
    int occupantRolls[MAX_CAPACITY];

public:
    Room()
        : roomNo(0), capacity(MAX_CAPACITY), currentOccupancy(0) {
        for (int i = 0; i < MAX_CAPACITY; i++)
            occupantRolls[i] = 0;
    }

    void setRoomNo(int rn)   { roomNo = rn; }
    int  getRoomNo()   const { return roomNo; }
    int  getOccupancy() const { return currentOccupancy; }
    int  getCapacity()  const { return capacity; }

    // ── Check if a student is already in this room ──
    bool hasStudent(int roll) const {
        for (int i = 0; i < currentOccupancy; i++)
            if (occupantRolls[i] == roll) return true;
        return false;
    }

    // ── Allocate ──
    bool allocate(int roll) {
        if (currentOccupancy >= capacity) return false;
        if (hasStudent(roll))             return false;
        occupantRolls[currentOccupancy++] = roll;
        return true;
    }

    // ── Deallocate ──
    bool deallocate(int roll) {
        for (int i = 0; i < currentOccupancy; i++) {
            if (occupantRolls[i] == roll) {
                // shift remaining occupants
                for (int j = i; j < currentOccupancy - 1; j++)
                    occupantRolls[j] = occupantRolls[j + 1];
                occupantRolls[--currentOccupancy] = 0;
                return true;
            }
        }
        return false;
    }

    // ── Display ──
    void displayRow() const {
        string status = (currentOccupancy == capacity) ? "FULL" : "OPEN";
        cout << "  │ " << setw(6) << roomNo
             << " │ " << setw(4)  << currentOccupancy
             << " / " << setw(1) << capacity
             << " │ " << setw(6)  << left << status << right
             << " │  ";
        for (int i = 0; i < currentOccupancy; i++) {
            cout << occupantRolls[i];
            if (i < currentOccupancy - 1) cout << ", ";
        }
        if (currentOccupancy == 0) cout << "--";
        cout << '\n';
    }
};

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  CLASS : MessFee
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
class MessFee {
private:
    int   rollNo;
    float totalFee;
    float amountPaid;

public:
    MessFee()
        : rollNo(0), totalFee(DEFAULT_MESS_FEE), amountPaid(0.0f) {}

    MessFee(int r, float total)
        : rollNo(r), totalFee(total), amountPaid(0.0f) {}

    int   getRollNo()    const { return rollNo; }
    float getTotalFee()  const { return totalFee; }
    float getAmountPaid() const { return amountPaid; }
    float getBalance()   const { return totalFee - amountPaid; }

    void setRollNo(int r)       { rollNo = r; }
    void setTotalFee(float f)   { totalFee = f; }

    bool pay(float amount) {
        if (amount <= 0 || amount > getBalance()) return false;
        amountPaid += amount;
        return true;
    }

    void displayRow() const {
        string payStatus;
        if (getBalance() <= 0)
            payStatus = "PAID";
        else if (amountPaid > 0)
            payStatus = "PARTIAL";
        else
            payStatus = "UNPAID";

        cout << "  │ " << setw(6)  << rollNo
             << " │ " << setw(10) << fixed << setprecision(2) << totalFee
             << " │ " << setw(10) << amountPaid
             << " │ " << setw(10) << getBalance()
             << " │ " << setw(8) << left << payStatus << right
             << " │\n";
    }
};

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  HELPER: find index of a student by roll number
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
int findStudent(Student students[], int count, int roll) {
    for (int i = 0; i < count; i++)
        if (students[i].getRollNo() == roll) return i;
    return -1;
}

int findRoom(Room rooms[], int roomCount, int roomNo) {
    for (int i = 0; i < roomCount; i++)
        if (rooms[i].getRoomNo() == roomNo) return i;
    return -1;
}

int findMessFee(MessFee fees[], int feeCount, int roll) {
    for (int i = 0; i < feeCount; i++)
        if (fees[i].getRollNo() == roll) return i;
    return -1;
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  DISPLAY: show the main menu
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void showMenu() {
    cout << "\n";
    drawDoubleLine(50);
    cout << "         H O S T E L   M A N A G E R\n";
    drawDoubleLine(50);
    cout << "  [1]  Add Student\n";
    cout << "  [2]  Display All Students\n";
    cout << "  [3]  Search Student by Roll No\n";
    drawLine(50);
    cout << "  [4]  Allocate Room\n";
    cout << "  [5]  Deallocate Room\n";
    cout << "  [6]  Display Room Status\n";
    drawLine(50);
    cout << "  [7]  Pay Mess Fee\n";
    cout << "  [8]  Display Mess Fee Status\n";
    drawLine(50);
    cout << "  [9]  Exit\n";
    drawDoubleLine(50);
    cout << "  >> Enter your choice: ";
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  MAIN
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
int main() {
    Student  students[MAX_STUDENTS];
    Room     rooms[MAX_ROOMS];
    MessFee  fees[MAX_STUDENTS];

    int studentCount = 0;
    int roomCount    = 0;
    int feeCount     = 0;

    // Pre-initialise rooms 101 – 110
    for (int i = 0; i < 10; i++) {
        rooms[i].setRoomNo(101 + i);
        roomCount++;
    }

    int choice;

    cout << "\n";
    drawDoubleLine(56);
    cout << "  ╔══════════════════════════════════════════════════╗\n";
    cout << "  ║        HOSTEL MANAGEMENT SYSTEM  v1.0           ║\n";
    cout << "  ║   Room Allocations • Students • Mess Fees       ║\n";
    cout << "  ╚══════════════════════════════════════════════════╝\n";
    drawDoubleLine(56);

    do {
        showMenu();
        cin >> choice;

        switch (choice) {

        // ──────────────────────────────────────────────────────
        //  1. ADD STUDENT
        // ──────────────────────────────────────────────────────
        case 1: {
            if (studentCount >= MAX_STUDENTS) {
                cout << "\n  ⚠  Maximum student limit reached!\n";
                break;
            }
            Student temp;
            temp.input();

            if (findStudent(students, studentCount, temp.getRollNo()) != -1) {
                cout << "\n  ⚠  Roll No " << temp.getRollNo()
                     << " already exists! Registration cancelled.\n";
                break;
            }

            students[studentCount] = temp;

            // auto-create a mess fee record
            fees[feeCount].setRollNo(temp.getRollNo());
            fees[feeCount].setTotalFee(DEFAULT_MESS_FEE);
            feeCount++;

            studentCount++;
            cout << "\n  ✓  Student registered successfully!  (Mess fee of ₹"
                 << DEFAULT_MESS_FEE << " assigned)\n";
            break;
        }

        // ──────────────────────────────────────────────────────
        //  2. DISPLAY ALL STUDENTS
        // ──────────────────────────────────────────────────────
        case 2: {
            if (studentCount == 0) {
                cout << "\n  ⚠  No students registered yet.\n";
                break;
            }
            cout << "\n";
            drawLine(62);
            cout << "  │ " << setw(6)  << "Roll"
                 << " │ " << setw(14) << left << "Name" << right
                 << " │ " << setw(4)  << "Age"
                 << " │ " << setw(10) << left << "Dept" << right
                 << " │ " << setw(12) << left << "Contact" << right
                 << " │\n";
            drawLine(62);
            for (int i = 0; i < studentCount; i++)
                students[i].displayRow();
            drawLine(62);
            cout << "  Total students: " << studentCount << '\n';
            break;
        }

        // ──────────────────────────────────────────────────────
        //  3. SEARCH STUDENT
        // ──────────────────────────────────────────────────────
        case 3: {
            int roll;
            cout << "\n  Enter Roll No to search: ";
            cin >> roll;

            int idx = findStudent(students, studentCount, roll);
            if (idx == -1) {
                cout << "\n  ✗  No student found with Roll No " << roll << ".\n";
            } else {
                students[idx].displayCard();
            }
            break;
        }

        // ──────────────────────────────────────────────────────
        //  4. ALLOCATE ROOM
        // ──────────────────────────────────────────────────────
        case 4: {
            int roll, roomNo;
            cout << "\n  Enter Student Roll No : ";
            cin >> roll;

            if (findStudent(students, studentCount, roll) == -1) {
                cout << "\n  ✗  Student not found. Register the student first.\n";
                break;
            }

            // Show available rooms
            {
                bool anyAvailable = false;
                cout << "\n";
                drawLine(44);
                cout << "  │  Room  │ Slots Free │ Status │\n";
                drawLine(44);
                for (int i = 0; i < roomCount; i++) {
                    int free = rooms[i].getCapacity() - rooms[i].getOccupancy();
                    if (free > 0) {
                        cout << "  │ " << setw(6) << rooms[i].getRoomNo()
                             << " │ " << setw(5) << free << "/"
                             << rooms[i].getCapacity()
                             << "     │ OPEN   │\n";
                        anyAvailable = true;
                    }
                }
                drawLine(44);
                if (!anyAvailable) {
                    cout << "  ⚠  All rooms are full!\n";
                    break;
                }
            }

            cout << "\n  Enter Room No         : ";
            cin >> roomNo;

            int rIdx = findRoom(rooms, roomCount, roomNo);
            if (rIdx == -1) {
                cout << "\n  ✗  Room " << roomNo << " does not exist.\n";
                break;
            }

            // check if student is already in any room
            for (int i = 0; i < roomCount; i++) {
                if (rooms[i].hasStudent(roll)) {
                    cout << "\n  ⚠  Student " << roll
                         << " is already in Room " << rooms[i].getRoomNo()
                         << ". Deallocate first.\n";
                    rIdx = -1;
                    break;
                }
            }
            if (rIdx == -1) break;

            if (rooms[rIdx].allocate(roll)) {
                cout << "\n  ✓  Student " << roll
                     << " allocated to Room " << roomNo << ".\n";
            } else {
                cout << "\n  ✗  Room " << roomNo
                     << " is full! (capacity " << rooms[rIdx].getCapacity() << ")\n";
            }
            break;
        }

        // ──────────────────────────────────────────────────────
        //  5. DEALLOCATE ROOM
        // ──────────────────────────────────────────────────────
        case 5: {
            int roll;
            cout << "\n  Enter Student Roll No to remove: ";
            cin >> roll;

            bool removed = false;
            for (int i = 0; i < roomCount; i++) {
                if (rooms[i].deallocate(roll)) {
                    cout << "\n  ✓  Student " << roll
                         << " removed from Room " << rooms[i].getRoomNo() << ".\n";
                    removed = true;
                    break;
                }
            }
            if (!removed)
                cout << "\n  ✗  Student " << roll << " is not assigned to any room.\n";
            break;
        }

        // ──────────────────────────────────────────────────────
        //  6. DISPLAY ROOM STATUS
        // ──────────────────────────────────────────────────────
        case 6: {
            cout << "\n";
            drawLine(50);
            cout << "  │  Room  │ Occ    │ Status │  Occupants\n";
            drawLine(50);
            for (int i = 0; i < roomCount; i++)
                rooms[i].displayRow();
            drawLine(50);
            break;
        }

        // ──────────────────────────────────────────────────────
        //  7. PAY MESS FEE
        // ──────────────────────────────────────────────────────
        case 7: {
            int roll;
            float amount;
            cout << "\n  Enter Student Roll No : ";
            cin >> roll;

            int fIdx = findMessFee(fees, feeCount, roll);
            if (fIdx == -1) {
                cout << "\n  ✗  No fee record found for Roll No " << roll << ".\n";
                break;
            }

            cout << "  Outstanding balance   : ₹" << fixed << setprecision(2)
                 << fees[fIdx].getBalance() << '\n';

            if (fees[fIdx].getBalance() <= 0) {
                cout << "  ✓  All fees already paid!\n";
                break;
            }

            cout << "  Enter payment amount  : ₹";
            cin >> amount;

            if (fees[fIdx].pay(amount)) {
                cout << "\n  ✓  Payment of ₹" << amount << " recorded.\n";
                cout << "     Remaining balance : ₹" << fees[fIdx].getBalance() << '\n';
            } else {
                cout << "\n  ✗  Invalid amount. Must be > 0 and ≤ balance.\n";
            }
            break;
        }

        // ──────────────────────────────────────────────────────
        //  8. DISPLAY MESS FEE STATUS
        // ──────────────────────────────────────────────────────
        case 8: {
            if (feeCount == 0) {
                cout << "\n  ⚠  No fee records found.\n";
                break;
            }
            cout << "\n";
            drawLine(66);
            cout << "  │ " << setw(6)  << "Roll"
                 << " │ " << setw(10) << "Total"
                 << " │ " << setw(10) << "Paid"
                 << " │ " << setw(10) << "Balance"
                 << " │ " << setw(8) << left << "Status" << right
                 << " │\n";
            drawLine(66);
            for (int i = 0; i < feeCount; i++)
                fees[i].displayRow();
            drawLine(66);
            break;
        }

        // ──────────────────────────────────────────────────────
        //  9. EXIT
        // ──────────────────────────────────────────────────────
        case 9:
            cout << "\n";
            drawDoubleLine(50);
            cout << "  THANK YOU FOR USING HOSTEL MANAGEMENT SYSTEM!\n";
            drawDoubleLine(50);
            break;e

        default:
            cout << "\n  ✗  Invalid choice. Please select 1–9.\n";
        }

    } while (choice != 9);

    return 0;
}
