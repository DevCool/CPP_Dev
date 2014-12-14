#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main()
{
    int grade, total, count;
    double average = 0.0;
    total = 0;
    count = 0;
    string fileName;
    cout << "Enter a filename: ";
    getline(cin, fileName);
    ifstream inFile(fileName.c_str(), ios::in);
    if(!inFile.is_open()) {
        cout << "File couldn't be opened." << endl;
        return 1;
    }
    while(!inFile.eof()) {
        inFile >> grade;
        total += grade;
        ++count;
        cout << grade << endl;
    }
    inFile.close();
    cout << "All done." << endl;
    average = total / count;
    cout << "The average grade is: " << average << endl;
    return 0;
}
