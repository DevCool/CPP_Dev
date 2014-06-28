#include "program.hpp"

program::program():
	_running(true) {

}

program::~program() {

}

int program::Start() {
	loopClass newLoop;
	newLoop.SetRunning(true);
	
	do {
		newLoop.MainProgram();
	} while (_running);
	
	return 0;
}

