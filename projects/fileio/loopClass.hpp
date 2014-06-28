#ifndef _loopClass_hpp_
#define _loopClass_hpp_

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class loopClass {
	private:
		string _getInput;
		bool _running;
	
	public:
		loopClass();
		~loopClass();
		
		void MainProgram();
		bool GetRunning();
		void SetRunning(bool running);
};

#endif

