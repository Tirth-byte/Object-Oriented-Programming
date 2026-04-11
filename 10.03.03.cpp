#include <iostream>
using namespace std;

class rectangle {
    int width, length;
    float area;

public:
    // Constructor to initialize width and length
    rectangle(int w, int l) {
        width = w;
        length = l;
        area = width * length;
    }

    void showrec() {
        cout << "\nWidth: " << width;
        cout << "\nLength: " << length;
        cout << "\nArea: " << area << endl;
    }
};

class triangle {
    int base, height;
    float area;

public:
    // Constructor to initialize base and height
    triangle(int b, int h) {
        base = b;
        height = h;
        area = 0.5 * base * height;
    }

    void showtri() {
        cout << "\nBase: " << base;
        cout << "\nHeight: " << height;
        cout << "\nArea: " << area << endl;
    }
};

int main() {
    rectangle r(10, 5);
    triangle t(8, 6);

    r.showrec();
    t.showtri();

    return 0;
}