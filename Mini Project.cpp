#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// Maximum number of rooms in the hostel
const int MAX_ROOMS = 50;

// Student Class
class Student {
private:
  int rollNo;
  string name;
  string course;
  string phoneNo;
  int roomNo;
  double messFeeTotal;
  double messFeePaid;

public:
  // 1. Default Constructor
  Student() {
    rollNo = 0;
    name = "Unknown";
    course = "Unknown";
    phoneNo = "N/A";
    roomNo = 0;
    messFeeTotal = 0.0;
    messFeePaid = 0.0;
  }

  // 2. Parameterized Constructor
  Student(int r, string n, string c, string p) {
    rollNo = r;
    name = n;
    course = c;
    phoneNo = p;
    roomNo = 0; // 0 means Not allocated yet
    messFeeTotal = 0.0;
    messFeePaid = 0.0;
  }

  // 3. Destructor
  ~Student() {
    // Simple destructor (Nothing to clean up since no pointers are used)
  }

  // 4. Function Overloading for Paying Fees (Partial Payment)
  void payFee(double amount) {
    messFeePaid += amount;
    cout << "\n\t[SUCCESS] Payment of Rs." << amount << " successful!\n";
  }

  // 5. Function Overloading for Paying Fees (Full Payment)
  void payFee() {
    double amount = messFeeTotal - messFeePaid;
    if (amount <= 0) {
      cout << "\n\t[INFO] No dues left. Fee is already fully paid.\n";
      return;
    }
    messFeePaid = messFeeTotal;
    cout << "\n\t[SUCCESS] Full remaining payment of Rs." << amount
         << " successful!\n";
  }

  // Setters
  void allocateRoom(int rNo) { roomNo = rNo; }

  void addMessFee(double amount) { messFeeTotal += amount; }

  // Getters
  int getRollNo() { return rollNo; }
  int getRoomNo() { return roomNo; }
  string getName() { return name; }

  // Display detailed record
  void displayStudent() {
    cout << "\n\t----------------------------------------";
    cout << "\n\tRoll Number : " << rollNo;
    cout << "\n\tName        : " << name;
    cout << "\n\tCourse      : " << course;
    cout << "\n\tPhone       : " << phoneNo;
    if (roomNo != 0)
      cout << "\n\tRoom No     : " << roomNo;
    else
      cout << "\n\tRoom No     : Not Allocated";
    cout << "\n\tMess Fee    : Rs." << messFeeTotal;
    cout << "\n\tFee Paid    : Rs." << messFeePaid;
    cout << "\n\tDue Amount  : Rs." << (messFeeTotal - messFeePaid);
    cout << "\n\t----------------------------------------\n";
  }

  // Display short record for tables
  void displayShort() {
    cout << left << setw(10) << rollNo << setw(20) << name << setw(15)
         << (roomNo == 0 ? "NA" : to_string(roomNo)) << "Rs." << setw(12)
         << messFeeTotal - messFeePaid << endl;
  }
};

// Hostel Management Class
class Hostel {
private:
  Student students[100]; // Array of objects (Max 100 students)
  bool rooms[MAX_ROOMS +
             1]; // Boolean Array: true means occupied, false means empty
  int studentCount;

public:
  // Constructor
  Hostel() {
    studentCount = 0;
    for (int i = 0; i <= MAX_ROOMS; ++i) {
      rooms[i] = false; // Initialize all rooms to empty
    }
  }

  // Destructor
  ~Hostel() {
    // Cleaning up process (Nothing special needed here)
  }

  // Helper method to find a student by roll number
  int findStudent(int rNo) {
    for (int i = 0; i < studentCount; i++) {
      if (students[i].getRollNo() == rNo) {
        return i; // Found, return index
      }
    }
    return -1; // Not found
  }

  void addStudent() {
    if (studentCount >= 100) {
      cout << "\n\t[ERROR] Hostel is full! Cannot add more students.\n";
      return;
    }

    int r;
    string n, c, p;
    cout << "\n\t--- ADD NEW STUDENT ---\n";
    cout << "\tEnter Roll No: ";
    cin >> r;

    // Validation: Check for duplicate roll no
    if (findStudent(r) != -1) {
      cout << "\n\t[ERROR] Student with this Roll Number already exists!\n";
      return;
    }

    cin.ignore(10000, '\n'); // clear input buffer before using getline
    cout << "\tEnter Name: ";
    getline(cin, n);
    cout << "\tEnter Course: ";
    getline(cin, c);
    cout << "\tEnter Phone No: ";
    getline(cin, p);

    // Uses Parameterized Constructor
    students[studentCount] = Student(r, n, c, p);
    studentCount++;

    cout << "\n\t[SUCCESS] Student Added Successfully!\n";
  }

  void allocateRoom() {
    int rNo;
    cout << "\n\t--- ALLOCATE ROOM ---\n";
    cout << "\tEnter Student Roll No: ";
    cin >> rNo;

    int index = findStudent(rNo);
    if (index == -1) {
      cout << "\n\t[ERROR] Student not found!\n";
      return;
    }

    if (students[index].getRoomNo() != 0) {
      cout << "\n\t[WARNING] Student is already allocated Room No: "
           << students[index].getRoomNo() << "\n";
      return;
    }

    int allocRoom;
    cout << "\tEnter Room Number to Allocate (1 to " << MAX_ROOMS << "): ";
    cin >> allocRoom;

    if (allocRoom < 1 || allocRoom > MAX_ROOMS) {
      cout << "\n\t[ERROR] Invalid Room Number!\n";
      return;
    }

    if (rooms[allocRoom] == true) {
      cout << "\n\t[ERROR] Room is already occupied!\n";
      return;
    }

    students[index].allocateRoom(allocRoom);
    rooms[allocRoom] = true;
    cout << "\n\t[SUCCESS] Room " << allocRoom << " Allocated Successfully!\n";
  }

  void freeRoom() {
    int roomNum;
    cout << "\n\t--- DE-ALLOCATE ROOM ---\n";
    cout << "\tEnter Room Number to free (1 to " << MAX_ROOMS << "): ";
    cin >> roomNum;

    if (roomNum < 1 || roomNum > MAX_ROOMS) {
      cout << "\n\t[ERROR] Invalid Room Number!\n";
      return;
    }

    if (rooms[roomNum] == false) {
      cout << "\n\t[INFO] Room is already empty!\n";
      return;
    }

    // Find the student in this room
    for (int i = 0; i < studentCount; i++) {
      if (students[i].getRoomNo() == roomNum) {
        students[i].allocateRoom(0); // 0 means De-allocated
        rooms[roomNum] = false;
        cout << "\n\t[SUCCESS] Room freed from Student '"
             << students[i].getName() << "' successfully!\n";
        return;
      }
    }
  }

  void addMessFee() {
    int rNo;
    double amt;
    cout << "\n\t--- ADD MESS FEE ---\n";
    cout << "\tEnter Student Roll No: ";
    cin >> rNo;

    int index = findStudent(rNo);
    if (index == -1) {
      cout << "\n\t[ERROR] Student not found!\n";
      return;
    }

    cout << "\tEnter Mess Fee Amount to add: Rs.";
    cin >> amt;

    if (amt <= 0) {
      cout << "\n\t[ERROR] Invalid Amount!\n";
      return;
    }

    students[index].addMessFee(amt);
    cout << "\n\t[SUCCESS] Fee Added Successfully!\n";
  }

  void payMessFee() {
    int rNo;
    cout << "\n\t--- PAY MESS FEE ---\n";
    cout << "\tEnter Student Roll No: ";
    cin >> rNo;

    int index = findStudent(rNo);
    if (index == -1) {
      cout << "\n\t[ERROR] Student not found!\n";
      return;
    }

    int choice;
    cout << "\n\t1. Pay Custom Amount";
    cout << "\n\t2. Pay Full Due Amount";
    cout << "\n\tEnter Choice: ";
    cin >> choice;

    if (choice == 1) {
      double amt;
      cout << "\tEnter Amount to Pay: Rs.";
      cin >> amt;
      if (amt > 0) {
        students[index].payFee(amt); // Demonstration of Function Overloading
      } else {
        cout << "\n\t[ERROR] Invalid amount!\n";
      }
    } else if (choice == 2) {
      students[index].payFee(); // Demonstration of Function Overloading
    } else {
      cout << "\n\t[ERROR] Invalid Choice!\n";
    }
  }

  void viewStudent() {
    int rNo;
    cout << "\n\t--- SEARCH STUDENT RECORD ---\n";
    cout << "\tEnter Student Roll No: ";
    cin >> rNo;

    int index = findStudent(rNo);
    if (index == -1) {
      cout << "\n\t[ERROR] Student not found!\n";
      return;
    }

    students[index].displayStudent();
  }

  void viewAllStudents() {
    if (studentCount == 0) {
      cout << "\n\t[INFO] No students found in the record!\n";
      return;
    }
    cout << "\n\t==========================================================\n";
    cout << "\t" << left << setw(10) << "Roll No" << setw(20) << "Name"
         << setw(15) << "Room No"
         << "Due Fee" << endl;
    cout << "\t==========================================================\n";
    for (int i = 0; i < studentCount; i++) {
      cout << "\t";
      students[i].displayShort();
    }
    cout << "\t==========================================================\n";
  }
};

// Main Menu Display
void displayMenu() {
  cout << "\n\n\t=========================================";
  cout << "\n\t         HOSTEL MANAGEMENT SYSTEM        ";
  cout << "\n\t=========================================";
  cout << "\n\t1. Add New Student";
  cout << "\n\t2. Allocate Room";
  cout << "\n\t3. De-allocate Room";
  cout << "\n\t4. Add Mess Fee Tracker";
  cout << "\n\t5. Pay Mess Fee";
  cout << "\n\t6. View Student Record";
  cout << "\n\t7. View All Students";
  cout << "\n\t8. Exit";
  cout << "\n\t=========================================";
  cout << "\n\tSelect an option (1-8): ";
}

int main() {
  Hostel myHostel;
  int choice;

  cout << "\n\tWelcome to the Hostel Management Mini-Project!\n";

  while (true) {
    displayMenu();
    cin >> choice;

    // Validating invalid input characters (e.g., user enters a letter instead
    // of number)
    if (cin.fail()) {
      cin.clear();
      cin.ignore(10000, '\n');
      cout << "\n\t[ERROR] Invalid input! Please enter a number.\n";
      continue;
    }

    switch (choice) {
    case 1:
      myHostel.addStudent();
      break;
    case 2:
      myHostel.allocateRoom();
      break;
    case 3:
      myHostel.freeRoom();
      break;
    case 4:
      myHostel.addMessFee();
      break;
    case 5:
      myHostel.payMessFee();
      break;
    case 6:
      myHostel.viewStudent();
      break;
    case 7:
      myHostel.viewAllStudents();
      break;
    case 8:
      cout << "\n\tExiting... Thank you for using the system!\n\n";
      return 0; // Exits the program properly
    default:
      cout << "\n\t[ERROR] Invalid option! Please try again.\n";
    }
  }
  return 0;
}
