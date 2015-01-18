#include "testClass.h"

testClass::testClass()
{
	window = NULL;
	screen = NULL;
	image = NULL;
}

bool testClass::loadMedia()
{
	bool success = true;

	image = SDL_LoadBMP ("data/hello.bmp");
	if (image == NULL) {
		printf ("SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	return success;
}

int testClass::start(const char *sTitle, int x, int y, int nScreenWidth, int nScreenHeight, Uint32 uFlags)
{
	if (!loadMedia()) {
		printf("Cannot continue, media not found...\n");
		return -1;
	}
	else {
		if (!init(sTitle, x, y, nScreenWidth, nScreenHeight, uFlags)) {
			printf ("Failed to initialize...\n");
		}
		else {
			SDL_BlitSurface (image, NULL, screen, NULL);
			SDL_UpdateWindowSurface (window);
			SDL_Delay (2000);
		}
	}

	close();
	return 0;
}

void testClass::close()
{
	SDL_FreeSurface(image);
	image = NULL;

	// Quit SDL and Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}

