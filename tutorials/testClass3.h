#ifndef _TESTCLASS3_H_
#define _TESTCLASS3_H_

#include "testClass.h"

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT
};

class testClass3 : public testClass
{
	private:
		SDL_Surface *images[5];
		const char *names[5];

	public:
		testClass3 (void);

		bool loadMedia (void);
		int start (const char *title, int x, int y, int w, int h, Uint32 flags);
		void close (void);
};

#endif

