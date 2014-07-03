#include "Employee.h"

Employee::Employee() {
	_name = "";
	_payRate = 0;
}

Employee::Employee(string name, double payRate) {
	_name = name;
	_payRate = payRate;
}

Employee::~Employee() {
}

string Employee::getName() {
	return _name;
}

void Employee::setName(string name) {
	_name = name;
}

double Employee::getPayRate() {
	return _payRate;
}

void Employee::setPayRate(double payRate) {
	_payRate = payRate;
}

string Employee::toString() {
	stringstream stm;
	stm.clear();
	stm << _name << ":" << _payRate;
	return stm.str();
}
