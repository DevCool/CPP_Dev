#include "initClass.h"

int main( int argc, char *args[] )
{
	initClass test;
	return test.start( "SDL Tutorial - Basic Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN );
}

