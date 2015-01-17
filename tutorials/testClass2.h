#ifndef _TESTCLASS2_H_
#define _TESTCLASS2_H_

#include "testClass.h"

class testClass2 : public testClass
{
	public:
		testClass2 ();
		~testClass2 ();

		bool loadMedia (void);
		int start (const char *sTitle, int nPosX, int nPosY, int nWidth, int nHeight, Uint32 uFlags);
		void close (void);
};

#endif

