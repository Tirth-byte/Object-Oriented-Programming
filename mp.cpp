/*
 * ============================================================
 *  ONLINE EXAMINATION SYSTEM
 *  Simple C++ console app with Admin and Student roles
 * ============================================================
 *  Admin  → add questions, create exams, view all results
 *  Student→ take exams, view personal result history
 * ============================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <limits>
using namespace std;

// ─── UTILITY ────────────────────────────────────────────────

// Clear the terminal screen 
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Wait for the user to press Enter before continuing
void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Print a centered title banner with === borders
void printBanner(const string& title) {
    int width = 60;
    cout << "\n" << string(width, '=') << "\n";
    cout << string((width - title.size()) / 2, ' ') << title << "\n";
    cout << string(width, '=') << "\n\n";
}

// ─── QUESTION ───────────────────────────────────────────────

/*
 * Stores a single MCQ question with 4 options (A–D),
 * the correct answer index (0=A, 1=B, ...), category, and marks.
 */
class Question {
    int id, correctIndex, marks;
    string text, category;
    vector<string> options; // always 4 options

public:
    Question(int id, const string& text,
             const vector<string>& opts, int correctIdx,
             const string& category = "General", int marks = 1)
        : id(id), correctIndex(correctIdx), marks(marks),
          text(text), category(category), options(opts) {}

    // Getters
    int    getId()           const { return id; }
    string getText()         const { return text; }
    string getCategory()     const { return category; }
    int    getMarks()        const { return marks; }
    int    getCorrectIndex() const { return correctIndex; }

    // Returns true if the given answer index matches the correct one
    bool isCorrect(int given) const { return given == correctIndex; }

    // Print the question with its options
    void display(int serial) const {
        cout << "\nQ" << serial << ". [" << category << " | +" << marks << " mark]\n";
        cout << "   " << text << "\n";
        char label = 'A';
        for (auto& opt : options)
            cout << "   " << label++ << ". " << opt << "\n";
    }
};

// ─── QUESTION BANK ──────────────────────────────────────────

/*
 * Holds all available questions and lets the admin add more.
 * Also provides a method to pick N random questions for an exam.
 */
class QuestionBank {
    vector<Question> questions;
    int nextId = 1;
    mt19937 rng{ random_device{}() }; // random number generator

public:
    void addQuestion(const string& text, const vector<string>& opts,
                     int correctIdx, const string& cat = "General", int marks = 1) {
        questions.emplace_back(nextId++, text, opts, correctIdx, cat, marks);
    }

    // Return n randomly picked, non-repeating questions
    vector<Question> getRandom(int n) {
        vector<Question> pool = questions;
        shuffle(pool.begin(), pool.end(), rng);
        n = min(n, (int)pool.size());
        return { pool.begin(), pool.begin() + n };
    }

    int total() const { return (int)questions.size(); }

    void listAll() const {
        printBanner("Question Bank");
        int i = 1;
        for (auto& q : questions) q.display(i++);
    }
};

// ─── TIMER ──────────────────────────────────────────────────

/*
 * Countdown timer for exams.
 * Call start() once, then use remainingFormatted() or isExpired().
 */
class Timer {
    chrono::steady_clock::time_point startTime;
    int totalSeconds;
    bool running = false;

public:
    explicit Timer(int seconds) : totalSeconds(seconds) {}

    void start() {
        startTime = chrono::steady_clock::now();
        running = true;
    }

    // Seconds elapsed since start()
    int elapsed() const {
        if (!running) return 0;
        return (int)chrono::duration_cast<chrono::seconds>(
            chrono::steady_clock::now() - startTime).count();
    }

    int remaining() const { return max(0, totalSeconds - elapsed()); }

    bool isExpired() const { return running && elapsed() >= totalSeconds; }

    // Returns time as "MM:SS"
    string remainingFormatted() const {
        int r = remaining();
        ostringstream oss;
        oss << setfill('0') << setw(2) << r / 60 << ":"
            << setfill('0') << setw(2) << r % 60;
        return oss.str();
    }
};

// ─── EXAM ───────────────────────────────────────────────────

/*
 * An exam has a title, duration, and a set of random questions
 * loaded from the QuestionBank by the admin.
 */
class Exam {
    int id, durationMinutes, questionCount;
    string title;
    vector<Question> questions;

public:
    Exam(int id, const string& title, int durMins, int qCount)
        : id(id), durationMinutes(durMins),
          questionCount(qCount), title(title) {}

    // Pull random questions from the bank
    void loadQuestions(QuestionBank& bank) {
        questions = bank.getRandom(questionCount);
    }

    int    getId()              const { return id; }
    string getTitle()           const { return title; }
    int    getDurationMinutes() const { return durationMinutes; }
    const  vector<Question>& getQuestions() const { return questions; }

    int getTotalMarks() const {
        int total = 0;
        for (auto& q : questions) total += q.getMarks();
        return total;
    }

    void displayInfo() const {
        cout << "  [" << id << "] " << title
             << " | " << questionCount << " Qs"
             << " | " << durationMinutes << " min"
             << " | Total marks: " << getTotalMarks() << "\n";
    }
};

// ─── RESULT REPORT ──────────────────────────────────────────

/*
 * Stores and displays a student's exam result.
 * Calculates grade and pass/fail automatically.
 */
class ResultReport {
    string studentName, examTitle;
    int score, totalMarks, totalQs;
    int correct, incorrect, unattempted, timeSec;

    // Assign letter grade based on percentage
    string grade() const {
        double p = percent();
        if (p >= 90) return "A+";
        if (p >= 80) return "A";
        if (p >= 70) return "B";
        if (p >= 60) return "C";
        if (p >= 50) return "D";
        return "F";
    }

public:
    ResultReport(const string& name, const string& exam,
                 int score, int total, int tq,
                 int corr, int incorr, int unatt, int timeSec)
        : studentName(name), examTitle(exam),
          score(score), totalMarks(total), totalQs(tq),
          correct(corr), incorrect(incorr), unattempted(unatt), timeSec(timeSec) {}

    double percent() const {
        return totalMarks > 0 ? (100.0 * score / totalMarks) : 0;
    }

    // Getters for admin summary table
    string getStudentName() const { return studentName; }
    string getExamTitle()   const { return examTitle; }
    int    getScore()       const { return score; }
    int    getTotalMarks()  const { return totalMarks; }
    double getPercent()     const { return percent(); }
    string getGrade()       const { return grade(); }

    void display() const {
        string line(62, '-');
        printBanner("RESULT REPORT");
        cout << line << "\n";
        cout << left << setw(25) << "Student"        << ": " << studentName << "\n";
        cout << left << setw(25) << "Exam"            << ": " << examTitle   << "\n";
        cout << line << "\n";
        cout << left << setw(25) << "Total Questions" << ": " << totalQs    << "\n";
        cout << left << setw(25) << "Correct"         << ": " << correct    << "\n";
        cout << left << setw(25) << "Incorrect"       << ": " << incorrect  << "\n";
        cout << left << setw(25) << "Unattempted"     << ": " << unattempted<< "\n";
        cout << line << "\n";
        cout << left << setw(25) << "Score"
             << ": " << score << " / " << totalMarks << "\n";
        cout << left << setw(25) << "Percentage"
             << ": " << fixed << setprecision(2) << percent() << "%\n";
        cout << left << setw(25) << "Grade" << ": " << grade() << "\n";
        cout << left << setw(25) << "Time Taken"
             << ": " << timeSec / 60 << " min " << timeSec % 60 << " sec\n";
        cout << line << "\n";
        cout << "\n  Result: " << (percent() >= 50 ? "PASS" : "FAIL") << "\n";
        cout << line << "\n";
    }
};

// ─── EXAM SESSION ───────────────────────────────────────────

/*
 * Runs an interactive exam for one student.
 * Shows a question list, lets student navigate and answer,
 * then scores everything when submitted (or time runs out).
 */
class ExamSession {
    string studentName;
    Exam& exam;
    vector<int> answers; // -1 = unattempted, 0–3 = A–D
    Timer timer;

public:
    ExamSession(const string& name, Exam& exam)
        : studentName(name), exam(exam),
          timer(exam.getDurationMinutes() * 60) {
        answers.assign(exam.getQuestions().size(), -1); // all unattempted
    }

    // Run the full exam loop and return the result
    ResultReport run() {
        auto& qs = exam.getQuestions();
        int n = (int)qs.size();
        timer.start();

        while (true) {
            clearScreen();
            printBanner(exam.getTitle());
            cout << "  Student : " << studentName << "\n";
            cout << "  Timer   : " << timer.remainingFormatted() << " remaining\n";
            cout << "  [0] Submit Exam\n\n";

            // Show each question with answered/not-answered status
            for (int i = 0; i < n; i++) {
                cout << "  [" << (i + 1) << "] Q" << (i + 1);
                if (answers[i] != -1)
                    cout << " [Answered: " << (char)('A' + answers[i]) << "]";
                else
                    cout << " [Not answered]";
                cout << "\n";
            }

            // Auto-submit if time's up
            if (timer.isExpired()) {
                cout << "\n  Time is up! Auto-submitting...\n";
                pause();
                break;
            }

            cout << "\nEnter question number (0 to submit): ";
            int choice;
            cin >> choice;
            if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); continue; }

            // Submit
            if (choice == 0) {
                cout << "Confirm submit? (y/n): ";
                char c; cin >> c;
                if (c == 'y' || c == 'Y') break;
                continue;
            }

            // Invalid number
            if (choice < 1 || choice > n) {
                cout << "Invalid choice.\n"; pause(); continue;
            }

            // Show selected question and record answer
            clearScreen();
            printBanner(exam.getTitle());
            cout << "  Timer : " << timer.remainingFormatted() << " remaining\n";
            qs[choice - 1].display(choice);

            if (answers[choice - 1] != -1)
                cout << "\n  Current answer: " << (char)('A' + answers[choice - 1]) << "\n";

            cout << "\nEnter answer (A/B/C/D) or 0 to go back: ";
            string ans; cin >> ans;

            if (ans == "0") continue;

            if (ans.size() == 1) {
                char ch = toupper(ans[0]);
                if (ch >= 'A' && ch <= 'D') {
                    answers[choice - 1] = ch - 'A'; // store 0–3
                    cout << "  Answer recorded.\n";
                    pause();
                } else {
                    cout << "  Invalid option.\n"; pause();
                }
            }

            if (timer.isExpired()) {
                cout << "\n  Time is up! Auto-submitting...\n";
                pause(); break;
            }
        }

        return evaluate();
    }

private:
    // Calculate score and build the result report
    ResultReport evaluate() {
        auto& qs = exam.getQuestions();
        int score = 0, correct = 0, incorrect = 0, unattempted = 0;

        for (int i = 0; i < (int)qs.size(); i++) {
            if (answers[i] == -1) {
                unattempted++;
            } else if (qs[i].isCorrect(answers[i])) {
                score += qs[i].getMarks();
                correct++;
            } else {
                incorrect++;
            }
        }

        return ResultReport(studentName, exam.getTitle(),
                            score, exam.getTotalMarks(),
                            (int)qs.size(),
                            correct, incorrect, unattempted,
                            timer.elapsed());
    }
};

// ─── USER (BASE CLASS) ──────────────────────────────────────

/*
 * Base class for Admin and Student.
 * Handles basic identity and login authentication.
 */
class User {
protected:
    int id;
    string name, username, password;

public:
    User(int id, const string& name,
         const string& username, const string& password)
        : id(id), name(name), username(username), password(password) {}

    virtual ~User() = default;

    // Check if entered credentials match this user
    bool authenticate(const string& u, const string& p) const {
        return username == u && password == p;
    }

    string getName()     const { return name; }
    string getUsername() const { return username; }

    virtual string getRole()  const = 0;
    virtual void   showMenu()       = 0;
};

// ─── ADMIN ──────────────────────────────────────────────────

class Admin : public User {
public:
    Admin(int id, const string& name,
          const string& uname, const string& pass)
        : User(id, name, uname, pass) {}

    string getRole() const override { return "Admin"; }

    void showMenu() override {
        cout << "  [1] Add Question\n";
        cout << "  [2] Create Exam\n";
        cout << "  [3] View Question Bank\n";
        cout << "  [4] View All Results\n";
        cout << "  [5] Logout\n";
    }
};

// ─── STUDENT ────────────────────────────────────────────────

class Student : public User {
    vector<ResultReport> history; // past exam results

public:
    Student(int id, const string& name,
            const string& uname, const string& pass)
        : User(id, name, uname, pass) {}

    string getRole() const override { return "Student"; }

    void showMenu() override {
        cout << "  [1] Take Exam\n";
        cout << "  [2] View My Results\n";
        cout << "  [3] Logout\n";
    }

    void addResult(const ResultReport& r) { history.push_back(r); }

    void viewHistory() const {
        if (history.empty()) { cout << "\n  No exams taken yet.\n"; return; }
        printBanner("My Exam History");
        for (auto& r : history) r.display();
    }
};

// ─── EXAM SYSTEM (MAIN CONTROLLER) ──────────────────────────

/*
 * Top-level controller. Manages all users, exams, and results.
 * Entry point is run() which shows the main login menu.
 */
class ExamSystem {
    QuestionBank         bank;
    vector<Exam>         exams;
    vector<Student>      students;
    vector<Admin>        admins;
    vector<ResultReport> allResults; // global result ledger
    int nextExamId = 1;
    int nextUserId = 1;

    // ── Setup default data at startup ────────────────────────
    void seedData() {
        // Default admin account
        admins.emplace_back(nextUserId++, "System Admin", "admin", "admin123");

        // Default student accounts
        students.emplace_back(nextUserId++, "Tirth Patel", "tirth", "pass123");
        students.emplace_back(nextUserId++, "Aryan Shah",  "aryan", "pass456");
        students.emplace_back(nextUserId++, "Priya Mehta", "priya", "pass789");

        // Seed sample questions
        bank.addQuestion("Which keyword allocates memory on the heap in C++?",
            {"malloc","new","alloc","create"}, 1, "C++", 2);
        bank.addQuestion("Time complexity of binary search?",
            {"O(n)","O(n^2)","O(log n)","O(1)"}, 2, "DSA", 2);
        bank.addQuestion("Which principle does OOP NOT follow?",
            {"Encapsulation","Inheritance","Polymorphism","Sequencing"}, 3, "OOP", 1);
        bank.addQuestion("What does 'virtual' enable in C++?",
            {"Templates","Overloading","Runtime polymorphism","Namespaces"}, 2, "C++", 2);
        bank.addQuestion("Which data structure uses LIFO order?",
            {"Queue","Stack","Heap","Graph"}, 1, "DSA", 1);
        bank.addQuestion("Output of: cout << 2 + 3 * 4 ?",
            {"20","14","12","24"}, 1, "C++", 1);
        bank.addQuestion("Worst-case O(n log n) sorting algorithm?",
            {"Bubble","Insertion","Quick","Merge"}, 3, "DSA", 2);
        bank.addQuestion("A class that cannot be instantiated is?",
            {"Template","Abstract","Derived","Static"}, 1, "OOP", 1);
        bank.addQuestion("Operator to access members via pointer?",
            {".","->","::","&"}, 1, "C++", 1);
        bank.addQuestion("What is 2^10?",
            {"512","1024","2048","256"}, 1, "Math", 1);

        // One default exam
        exams.emplace_back(nextExamId++, "C++ Fundamentals Quiz", 5, 5);
        exams.back().loadQuestions(bank);
    }

    // ── Auth helpers ─────────────────────────────────────────

    Student* findStudent(const string& u, const string& p) {
        for (auto& s : students)
            if (s.authenticate(u, p)) return &s;
        return nullptr;
    }

    Admin* findAdmin(const string& u, const string& p) {
        for (auto& a : admins)
            if (a.authenticate(u, p)) return &a;
        return nullptr;
    }

    // ── Admin actions ─────────────────────────────────────────

    void addQuestion() {
        cin.ignore();
        string text, cat;
        vector<string> opts(4);
        int idx, marks;

        cout << "\nQuestion text: "; getline(cin, text);
        cout << "Option A: ";       getline(cin, opts[0]);
        cout << "Option B: ";       getline(cin, opts[1]);
        cout << "Option C: ";       getline(cin, opts[2]);
        cout << "Option D: ";       getline(cin, opts[3]);
        cout << "Correct (1=A/2=B/3=C/4=D): "; cin >> idx; idx--;
        cin.ignore();
        cout << "Category: ";       getline(cin, cat);
        cout << "Marks: ";          cin >> marks;

        bank.addQuestion(text, opts, idx, cat, marks);
        cout << "\n  Added! Bank total: " << bank.total() << "\n";
    }

    void createExam() {
        cin.ignore();
        string title;
        int dur, qc;

        cout << "\nExam title: ";           getline(cin, title);
        cout << "Duration (minutes): ";     cin >> dur;
        cout << "Number of questions (max " << bank.total() << "): "; cin >> qc;

        exams.emplace_back(nextExamId++, title, dur, qc);
        exams.back().loadQuestions(bank);
        cout << "  Exam '" << title << "' created.\n";
    }

    void listExams() const {
        if (exams.empty()) { cout << "  No exams available.\n"; return; }
        cout << "\n  Available Exams:\n";
        for (auto& e : exams) e.displayInfo();
    }

    void adminViewResults() const {
        if (allResults.empty()) { cout << "  No results yet.\n"; return; }
        printBanner("All Exam Results");
        cout << left << setw(20) << "Student"
                     << setw(28) << "Exam"
                     << setw(10) << "Score"
                     << setw(10) << "%" 
                     << setw(6)  << "Grade" << "\n";
        cout << string(74, '-') << "\n";
        for (auto& r : allResults) {
            cout << left
                 << setw(20) << r.getStudentName()
                 << setw(28) << r.getExamTitle()
                 << setw(10) << (to_string(r.getScore()) + "/" + to_string(r.getTotalMarks()))
                 << setw(10) << (to_string((int)r.percent()) + "%")  // cast to int for display
                 << setw(6)  << r.getGrade() << "\n";
        }
    }

    // ── Student actions ──────────────────────────────────────

    void takeExam(Student& s) {
        if (exams.empty()) { cout << "  No exams available.\n"; return; }
        listExams();

        cout << "\nSelect exam ID: ";
        int id; cin >> id;

        // Find exam by ID
        Exam* chosen = nullptr;
        for (auto& e : exams) if (e.getId() == id) { chosen = &e; break; }

        if (!chosen) { cout << "  Exam not found.\n"; return; }
        if (chosen->getQuestions().empty()) { cout << "  Exam has no questions.\n"; return; }

        cout << "\n  Starting: " << chosen->getTitle()
             << "\n  Duration: " << chosen->getDurationMinutes() << " minutes"
             << "\n  Questions: " << chosen->getQuestions().size()
             << "\n  Total marks: " << chosen->getTotalMarks() << "\n";
        pause();

        ExamSession session(s.getName(), *chosen);
        ResultReport report = session.run();

        report.display();
        s.addResult(report);
        allResults.push_back(report);
        pause();
    }

    // ── Portals ──────────────────────────────────────────────

    void adminPortal(Admin& admin) {
        while (true) {
            clearScreen();
            printBanner("Admin — " + admin.getName());
            admin.showMenu();
            cout << "\nChoice: ";
            int ch; cin >> ch;

            switch (ch) {
                case 1: addQuestion();       pause(); break;
                case 2: createExam();        pause(); break;
                case 3: bank.listAll();      pause(); break;
                case 4: adminViewResults();  pause(); break;
                case 5: return; // logout
                default: cout << "Invalid.\n"; pause();
            }
        }
    }

    void studentPortal(Student& student) {
        while (true) {
            clearScreen();
            printBanner("Student — " + student.getName());
            student.showMenu();
            cout << "\nChoice: ";
            int ch; cin >> ch;

            switch (ch) {
                case 1: takeExam(student);       break;
                case 2: student.viewHistory();   pause(); break;
                case 3: return; // logout
                default: cout << "Invalid.\n";   pause();
            }
        }
    }

public:
    ExamSystem() { seedData(); }

    // ── Main login loop ───────────────────────────────────────
    void run() {
        while (true) {
            clearScreen();
            printBanner("Online Examination System");
            cout << "  [1] Login as Admin\n";
            cout << "  [2] Login as Student\n";
            cout << "  [3] Exit\n";
            cout << "\nChoice: ";

            int ch; cin >> ch;
            if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); continue; }
            if (ch == 3) { cout << "\n  Goodbye!\n\n"; break; }

            cout << "\nUsername: "; string u; cin >> u;
            cout << "Password: "; string p; cin >> p;

            if (ch == 1) {
                Admin* a = findAdmin(u, p);
                if (!a) { cout << "  Invalid credentials.\n"; pause(); continue; }
                adminPortal(*a);
            } else if (ch == 2) {
                Student* s = findStudent(u, p);
                if (!s) { cout << "  Invalid credentials.\n"; pause(); continue; }
                studentPortal(*s);
            }
        }
    }
};

// ─── MAIN ────────────────────────────────────────────────────

int main() {
    ExamSystem system;
    system.run();
    return 0;
}