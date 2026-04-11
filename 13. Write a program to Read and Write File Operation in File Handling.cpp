#include <iostream>
#include <fstream>
using namespace std;
int main() {
    string filename = "example.txt"; 
	string data;

    ofstream outFile(filename, ios::out); //Open file for writing only,outFile object of ofstream
    if (outFile) {
        outFile << "Hello, this is a file handling example in C++.\n";
        outFile << "File handling allows reading and writing to files.\n";
        outFile.flush(); // Ensure data is written before closing the file 
        outFile.close();
        cout << "Data written to file successfully." << endl;
    } else {
        cout << "Unable to open file for writing." << endl;
        return 1; // Exit with error
    }
    
    // check the file exists before reading
    ifstream inFile(filename); // inFile is an object of ifstream
    if (!inFile) {
        cout << "Error: File does not exist or cannot be opened." << endl;
        return 1; // Exit with error
    }

    // Reading the data from file
    cout << "Reading from file: " << endl;
    // Reads one line from the file at a time and stores it in data
    while (getline(inFile, data)) { 
        cout << data << endl;  // display read line 
    }
    inFile.close();
    return 0;
}
