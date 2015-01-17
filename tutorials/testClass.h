#ifndef _TESTCLASS_H_
#define _TESTCLASS_H_

#include <cstdio>
#include <cstdlib>
#include <SDL2/SDL.h>

class testClass {
	public:
		SDL_Window* window;
		SDL_Surface *screen, *image;

		bool init(const char *sTitle, int x, int y, int nScreenWidth, int nScreenHeight, Uint32 uFlags);

	public:
		testClass();
		~testClass();

		virtual bool loadMedia();
		virtual int start(const char *sTitle, int x, int y, int nScreenWidth, int nScreenHeight, Uint32 uFlags);
		virtual void close();
};

#endif

