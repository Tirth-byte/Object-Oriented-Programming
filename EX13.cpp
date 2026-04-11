#include <iostream>
#include <fstream>
using namespace std;
int main(){
    string filename = "example.txt";
    string data;

    ofstream outfile(filename, ios::out);
    if(outfile) {
        outfile << "Helloi, this is a file handling example in c++. \n";
        outfile << "File handling allows reading and writing to files. \n";
        outfile.close();
        cout << "Data written to file successfully. \n"<< endl;
    } else {
        cout << "Unable to open file for writing. \n"<<endl;
        return 1;
    }
}
