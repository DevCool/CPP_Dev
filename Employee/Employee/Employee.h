#ifndef _EMPLOYEE_HPP_
#define _EMPLOYEE_HPP_

#include <iostream>
#include <sstream>
using namespace std;

class Employee {
    private:
        string _name;
		double _payRate;

	public:
		Employee();
		Employee(string name, double payRate);
		~Employee();

        string getName();
        void setName(string name);
        double getPayRate();
        void setPayRate(double payRate);

        string toString();
};

#endif //_EMPLOYEE_HPP_
