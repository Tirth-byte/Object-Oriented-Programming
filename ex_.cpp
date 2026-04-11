#include <iostream>
using namespace std;
class Alpha{
    public:
    Alpha(){
        cout << "Object created" << endl;
    }
    ~Alpha() {
        cout << "object destroyed" << endl;
    }
};
int main() {
    {
        Alpha A1;
        cout<<"Inside block"<<endl;
    }
    cout << "Outside Block" << endl;
}