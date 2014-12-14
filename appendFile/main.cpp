#include <iostream>
#include <istream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main()
{
    bool running = false;
    int grade;
    string fileName;
    char cont;
    cout << "Enter filename: ";
    getline(cin, fileName);
    ofstream outFile(fileName.c_str(), ios::app);
    if(!outFile.is_open()) {
        cout << "File didn't exist.. creating." << endl;
        outFile.open(fileName.c_str(), ios::out);

        running = true;

        do {
            for(int i = 0; i < 6; i++) {
                cout << "Enter a grade: ";
                cin >> grade;
                outFile << grade << endl;
            }

            fflush(stdin);
            cout << "Enter more grades? (y/n): ";
            cin >> cont;
            switch(cont) {
            case 'y': case 'Y':
                cout << "Enter more grades..." << endl;
                break;
            case 'n': case 'N':
                cout << "You quit..." << endl;
                running = false;
                break;
            default:
                cout << "Don't recognize input." << endl;
                running = true;
            }
        } while(running);
    }
    else {
        cout << "File exists appending to it." << endl;
        running = true;

        do {
            for(int i = 0; i < 6; i++) {
                cout << "Enter a grade: ";
                cin >> grade;
                outFile << grade << endl;
            }

            cout << "Enter more grades? (y/n): ";
            cin >> cont;
            switch(cont) {
            case 'y': case 'Y':
                cout << "Enter more grades..." << endl;
                break;
            case 'n': case 'N':
                cout << "You quit..." << endl;
                running = false;
                break;
            default:
                cout << "Don't recognize input." << endl;
                running = true;
            }
        } while(running);
    }

    outFile.close();
    cout << "Application finished!" << endl;
    return 0;
}
