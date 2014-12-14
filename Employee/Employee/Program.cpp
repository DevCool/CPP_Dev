#include "Program.h"

#pragma warning (disable: 4800)
#pragma warning (disable: 4805)

Program::Program() {
	_running = true;
	_employees.clear();
	_ID = 0;
}

Program::~Program() {
}

int Program::Menu() {
	int choice;
	cin.clear();
	cin.sync();
	cout << endl;
    cout << "0. Exit the program" << endl;
    cout << "1. Add Employee" << endl;
    cout << "2. Remove Employee" << endl;
    cout << "3. Show Employees" << endl;
    cout << "4. Write Employees to a file" << endl;
    cout << "5. Load Employees from a file" << endl;
    cout << "6. Clear Employees list" << endl;
    cout << endl;
    cout << "What is your choice? ";
    cin >> choice;
    return choice;
}

void Program::AddEmployee(string name, double pay) {
	Employee empObj(name, pay);
	_employees.push_back(empObj);
	cout << "Employee added." << endl;
}

void Program::RemoveEmployee() {
	int choice;
	cin.clear();
	cin.sync();
	ShowEmployees();
	cout << "Who do you want removed? ";
	cin >> choice;
	int cnt = 0;
	vector<Employee> _newEmps;
	_newEmps.clear();
	_employees.begin();
	while ((unsigned int)cnt < _employees.size()) {
		if (cnt != (choice-1))
			_newEmps.push_back(_employees[cnt]);
		else if(choice <= 0) {
			cin.clear();
			cin.sync();
			return;
		}
		++cnt;
	}
	_employees.clear();
	_employees = _newEmps;
	cout << "Removed that person." << endl;
}

void Program::ShowEmployees() {
	cout << endl;
	cout << "Employee List              FILE # " << _ID << endl;
	cout << "===========================================" << endl;
	if (_employees.size() > 0) {
		for (unsigned int i = 0; i < _employees.size(); ++i)
			cout << i + 1 << ". " << _employees[i].toString() << endl;
	}
	else {
		cout << "No valid data in the employee list..." << endl;
	}
	cout << "===========================================" << endl;
	cout << endl;
}

void Program::AddOne() {
	string name;
	double pay;
    cin.clear();
    cin.sync();
    cout << endl << "Enter his/her name: ";
    getline(cin, name);
    cin.clear();
    cin.sync();
    cout << "Enter the person's pay: ";
    cin >> pay;
    AddEmployee(name, pay);
}

void Program::WriteFile() {
	string fileName = "";
	ofstream outFile;
	cin.clear();
	cin.sync();
	cout << "Enter a filename (without extension): ";
	getline(cin, fileName);
	if (fileName.empty()) {
		cout << "Error: No filename given." << endl;
	}
	else {
		fileName += ".dat";
		outFile.open(fileName.c_str(), ios::out | ios::binary);
		if (!outFile.is_open()) {
			cout << "Error: File cannot be created." << endl;
			return;
		}
/*		outFile << "#FILE#" << _ID << endl;
		for (unsigned int i = 0; i < _employees.size(); ++i)
			outFile << _employees[i].toString() << endl;
 */
		stringstream ss;
		ss << "#FILE#" << _ID << endl;
		for (unsigned int i = 0; i < _employees.size(); ++i)
			ss << _employees[i].toString() << endl;
		ss.seekg(0, ss.beg);
		int posB = (int)ss.tellg();
		ss.seekg(0, ss.end);
		int posE = (int)ss.tellg();
		int length = posE - posB;
		ss.seekg(0, ss.beg);
		outFile.seekp(0, ios::beg);
		char *a = new char[length];
		ss.read(a, length);
		bool currentBit; char currentByte;
		for (int i = 0; i < length; i++) {
			currentByte = a[i];
			currentBit = currentByte >> 7;
			currentByte = (currentByte << 1) | (currentBit);
			a[i] = currentByte;
		}
		outFile.write(a, length);
		outFile.close();
		cout << "File was written: " << fileName << endl;
	}
}

void Program::LoadFile(vector<Employee> &v) {
	string t;
	v.clear();
	cin.clear();
	cin.sync();
	cout << "Enter a filename (without extension): ";
	getline(cin, t);
	if (t.empty()) {
		cout << "Enter a filename next time." << endl;
		return;
	}
	else {
		string line;
		double line2;
		t += ".dat";
		ifstream inFile(t.c_str(), ios::in | ios::binary);
		if (!inFile.is_open()) {
			cout << "File not found!" << endl;
			return;
		}
		stringstream ss;
		inFile.seekg(0, ios::beg);
		int posB = (int)inFile.tellg();
		inFile.seekg(0, ios::end);
		int posE = (int)inFile.tellg();
		int length = posE - posB;
		inFile.seekg(0, ios::beg);
		ss.seekp(0, ss.beg);
		char *a = new char[length];
		inFile.read(a, length);
		inFile.close();
		bool currentBit; unsigned char currentByte;
		for (int i = 0; i < length; i++) {
			currentByte = a[i];
			currentBit = currentByte & 1;
			currentByte = (currentBit << 7) | (currentByte >> 1);
			a[i] = currentByte;
		}
		ss.write(a, length);
		getline(ss, line);
		size_t offset = line.rfind("#");
		if (offset != string::npos) {
			_ID = atoi(string(line.begin() + offset + 1, line.end()).c_str());
		}
		Employee e;
		while (getline(ss >> ws, line, ':') >> ws >> line2) {
			e.setName(line);
			e.setPayRate(line2);
			v.push_back(e);
		}

		// Reading in to program here...
/*		getline(inFile, line);
		size_t offset = line.rfind('#');
		if (offset != string::npos) {
			_ID = stoi(string(line.begin() + offset + 1, line.end()));
		}
		Employee e;
		while (getline(inFile >> ws, line, ':') >> ws >> line2) {
			e.setName(line);
			e.setPayRate(line2);
			v.push_back(e);
		}
 */
		cout << "Employee List " << _ID << " loaded." << endl;
	}
}

int Program::Start() {
	srand((unsigned int)time(NULL));
	_ID = rand() % 1000 + 250;
	int choice = 0x20;
	while (_running && choice != 0) {
		choice = Menu();
		switch (choice) {
			case 1:
				AddOne();
				break;
			case 2:
				RemoveEmployee();
				break;
			case 3:
				ShowEmployees();
				break;
			case 4:
				WriteFile();
				break;
			case 5:
				LoadFile(_employees);
				break;
			case 6:
				_employees.clear();
				_ID = rand() % 1000 + 250;
				cout << "Employee list has been cleared..." << endl;
				break;
			case 0:
				_running = false;
				break;
			default:
				cout << "Don't recognize your input." << endl;
		}
	}
	return 0;
}
