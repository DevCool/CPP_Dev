#ifndef _TESTCLASS_H_
#define _TESTCLASS_H_

#include "initClass.h"

class testClass : public initClass
{
	public:
		SDL_Surface *image;

		testClass();
		bool loadMedia();
		int start(const char *sTitle, int x, int y, int nScreenWidth, int nScreenHeight, Uint32 uFlags);
		void close();
};

#endif

