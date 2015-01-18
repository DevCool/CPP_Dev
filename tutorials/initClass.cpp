#include "initClass.h"

initClass::initClass( )
{
	window = NULL;
	screen = NULL;
}

bool initClass::init( const char *title, int x, int y, int w, int h, Uint32 flags )
{
	bool success = true;

	printf ("Initializing please wait... (this may take awhile).\n");

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "Sorry but cannot init SDL2.\nSDL Error: %s\n", SDL_GetError( ) );
		success = false;
	}
	else {
		window = SDL_CreateWindow( title, x, y, w, h, flags );
		if( window == NULL ) {
			printf ( "Sorry cannot create the main app window.\nSDL Error: %s\n", SDL_GetError( ) );
			success = false;
		}
		else {
			screen = SDL_GetWindowSurface( window );
		}
	}

	return success;
}

bool initClass::loadMedia( )
{
	bool success = true;

	return success;
}

int initClass::start( const char *title, int x, int y, int w, int h, Uint32 flags )
{
	if( !loadMedia() ) {
		printf( "Cannot continue, media not found...\n" );
		return -1;
	}
	else {
		if( !init( title, x, y, w, h, flags ) ) {
			printf( "Failed to initialize...\n" );
		}
		else {
			SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 255, 0, 255 ) );
			SDL_UpdateWindowSurface( window );
			SDL_Delay( 2000 );
		}
	}

	close( );
	return 0;
}

void initClass::close( )
{
	// Quit SDL and Destroy window
	SDL_DestroyWindow( window );
	window = NULL;

	SDL_Quit( );
}

