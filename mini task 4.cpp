#include <iostream>
#include <cmath>

using namespace std;

class Point {
private:
    double x, y;

public:
    // Constructor
    Point(double x_val = 0, double y_val = 0) {
        x = x_val;
        y = y_val;
    }

    // + operator for adding two Point objects
    Point operator+(Point p) {
        return Point(x + p.x, y + p.y);
    }

    // - operator for subtracting two Point objects
    Point operator-(Point p) {
        return Point(x - p.x, y - p.y);
    }

    // == operator to compare two Point objects
    bool operator==(Point p) {
        return (x == p.x && y == p.y);
    }

    // * operator for scalar multiplication
    Point operator*(double scalar) {
        return Point(x * scalar, y * scalar);
    }

    // distance between two points
    double distance(Point p) {
        return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
    }

    // display point
    void display() {
        cout << "(" << x << ", " << y << ")";
    }

    // input point
    void input() {
        cout << "Enter x coordinate: ";
        cin >> x;
        cout << "Enter y coordinate: ";
        cin >> y;
    }
};
 
class Line {
private:
    Point start;
    Point end;

public:
    // Constructor
    Line(Point s = Point(), Point e = Point()) {
        start = s;
        end = e;
    }

    // translate line
    Line operator+(Point p) {
        return Line(start + p, end + p);
    }

    // compare two lines
    bool operator==(Line l) {
        return (start == l.start && end == l.end) ||
               (start == l.end && end == l.start);
    }

    // find length
    double length() {
        return start.distance(end);
    }

    // midpoint of line
    Point midpoint() {
        return (start + end) * 0.5;
    }

    // display line
    void display() {
        cout << "Line [Start: ";
        start.display();
        cout << " , End: ";
        end.display();
        cout << "]";
    }
};

int main() {

    int choice;
    Point p1, p2, translation;
    Line line1;

    cout << "============================================\n";
    cout << " 2D GEOMETRY TOOLKIT (Operator Overloading)\n";
    cout << "============================================\n";

    do {
        cout << "\nMENU\n";
        cout << "1. Add Two Points\n";
        cout << "2. Subtract Two Points\n";
        cout << "3. Compare Two Points\n";
        cout << "4. Distance Between Points\n";
        cout << "5. Create Line and Find Length\n";
        cout << "6. Translate Line\n";
        cout << "7. Compare Two Lines\n";
        cout << "0. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch(choice) {

        case 1:
            cout << "\nEnter Point 1\n";
            p1.input();

            cout << "Enter Point 2\n";
            p2.input();

            cout << "Result: ";
            (p1 + p2).display();
            cout << endl;
            break;

        case 2:
            cout << "\nEnter Point 1\n";
            p1.input();

            cout << "Enter Point 2\n";
            p2.input();

            cout << "Result: ";
            (p1 - p2).display();
            cout << endl;
            break;

        case 3:
            cout << "\nEnter Point 1\n";
            p1.input();

            cout << "Enter Point 2\n";
            p2.input();

            if(p1 == p2)
                cout << "Points are Equal\n";
            else
                cout << "Points are Not Equal\n";
            break;

        case 4:
            cout << "\nEnter Point 1\n";
            p1.input();

            cout << "Enter Point 2\n";
            p2.input();

            cout << "Distance = " << p1.distance(p2) << endl;
            break;

        case 5:
            cout << "\nEnter Start Point\n";
            p1.input();

            cout << "Enter End Point\n";
            p2.input();

            line1 = Line(p1, p2);

            line1.display();
            cout << endl;

            cout << "Length of Line = " << line1.length() << endl;
            break;

        case 6:
            cout << "\nEnter Start Point\n";
            p1.input();

            cout << "Enter End Point\n";
            p2.input();

            line1 = Line(p1, p2);

            cout << "Enter Translation Vector\n";
            translation.input();

            cout << "Translated Line: ";
            (line1 + translation).display();
            cout << endl;
            break;

        case 7:
        {
            Point a,b,c,d;

            cout << "\nLine 1\n";
            a.input();
            b.input();

            cout << "\nLine 2\n";
            c.input();
            d.input();

            Line l1(a,b);
            Line l2(c,d);

            if(l1 == l2)
                cout << "Lines are Equivalent\n";
            else
                cout << "Lines are Different\n";

            break;
        }

        case 0:
            cout << "\nExiting Program...\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while(choice != 0);

    return 0;
}