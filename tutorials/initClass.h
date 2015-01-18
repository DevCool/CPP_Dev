#ifndef _INITCLASS_H_
#define _INITCLASS_H_

#include <cstdio>
#include <cstdlib>
#include <SDL2/SDL.h>

class initClass {
	public:
		SDL_Window *window;
		SDL_Surface *screen;

		initClass( );

		virtual bool init( const char *title, int x, int y, int w, int h, Uint32 flags );
		virtual bool loadMedia( );
		virtual int start( const char *title, int x, int y, int w, int h, Uint32 flags );
		virtual void close( );
};

#endif

