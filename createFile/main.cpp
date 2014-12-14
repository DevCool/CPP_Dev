#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ofstream outFile("..\\..\\Data.txt", ios::out);
    outFile.clear();
    int grade;
    for(int i = 0; i < 6; i++ ) {
        cout << "Enter a grade: ";
        cin >> grade;
        outFile << grade << endl;
    }
    outFile.close();
    cout << "All finished." << endl;
    return 0;
}
