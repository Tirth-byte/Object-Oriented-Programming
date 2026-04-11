#include <iostream>
using namespace std;

class abc{
  int a;

public:
  abc(int a1){
    a = a1;
  }

  void getdata(){
    cout << "The value of a is : " << a << endl;
  }
};

int main(){
  int b = 10;
  abc obj1(b);

  obj1.getdata();

  return 0;
}