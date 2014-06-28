#ifndef _program_hpp_
#define _program_hpp_

#include <iostream>
#include "loopClass.hpp"

using namespace std;

class program {
	private:
		bool _running;
		
	public:
		program();
		~program();
		
		int Start();
};

#endif

