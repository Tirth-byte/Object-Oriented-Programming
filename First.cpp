// print helloe world using vurtual function
#include <iostream>
using namespace std;
class Base {
    public:
      virtual void display() {
        cout << "Hello, World!" << endl;
      }
};
