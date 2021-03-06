#include "testClass2.h"

testClass2::testClass2 ()
{
	window = NULL;
	screen = NULL;
	image = NULL;
}

bool testClass2::loadMedia ()
{
	bool success = true;

	image = SDL_LoadBMP ("data/hello2.bmp");
	if (image == NULL) {
		printf ("SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	return success;
}

int testClass2::start (const char *sTitle, int nPosX, int nPosY, int nWidth, int nHeight, Uint32 uFlags)
{
	if (!loadMedia ()) {
		printf ("Loading media failed... cannot continue!\n");
		return -1;
	}
	else {
		if (!init (sTitle, nPosX, nPosY, nWidth, nHeight, uFlags)) {
			printf ("Failed to initialize...\n");
		}
		else {
			bool quit = false;

			// Event handler
			SDL_Event e;

			// While app running
			while (!quit) {
				while (SDL_PollEvent (&e) != 0) {
					if (e.type == SDL_QUIT)
						quit = true;
				}

				SDL_BlitSurface (image, NULL, screen, NULL);
				SDL_UpdateWindowSurface (window);
			}
		}
	}

	close();
	return 0;
}

void testClass2::close (void)
{
	SDL_FreeSurface (image);
	image = NULL;

	// Destroy window and Quit SDL
	SDL_DestroyWindow (window);
	window = NULL;

	SDL_Quit();
}

