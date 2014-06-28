#include "loopClass.hpp"

loopClass::loopClass():
	_getInput(""), _running(false) {

}

loopClass::~loopClass() {

}

void loopClass::MainProgram() {
	//Get user input for filename
	cout << "Enter filename: "; getline (cin, _getInput);
	ofstream outFile (_getInput.c_str (), ios::out);
	
	_getInput.clear ();
	cin.clear();
	cin.sync();
	
	cout << "Enter some text when you want to quit just type: !quit\nok.."
		 << endl << endl;
	getline (cin, _getInput);
	
	while (getline (cin >> ws, _getInput) || !_getInput.compare ("!quit") ) {
		outFile << _getInput << endl;
	}
	outFile.close ();
	cout << "End of output to file...";	
}

bool loopClass::GetRunning() {
	return _running;
}

void loopClass::SetRunning(bool running) {
	_running = running;
}

