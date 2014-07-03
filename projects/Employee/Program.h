#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>

#include "Employee.h"

using namespace std;

class Program {

	private:
		bool _running;
		int _ID;

		vector<Employee> _employees;

		int Menu();
		void AddEmployee(string name, double pay);
		void RemoveEmployee();
		void ShowEmployees();

		void AddOne();
		void WriteFile();
		void LoadFile(vector<Employee> &v);

	public:
		Program();
		~Program();

		int Start();

};

#endif //_PROGRAM_HPP_
