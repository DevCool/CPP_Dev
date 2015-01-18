#include "testClass3.h"

testClass3::testClass3 (void)
{
	window = NULL;
	screen = NULL;
	for (int i = 0; i < 5; i++)
		images[i] = NULL;

	// Set the names of our images
	names[KEY_PRESS_SURFACE_DEFAULT]	= "data/none_pressed.bmp";
	names[KEY_PRESS_SURFACE_UP]			= "data/up_pressed.bmp";
	names[KEY_PRESS_SURFACE_DOWN]		= "data/down_pressed.bmp";
	names[KEY_PRESS_SURFACE_LEFT]		= "data/left_pressed.bmp";
	names[KEY_PRESS_SURFACE_RIGHT]		= "data/right_pressed.bmp";
}

bool testClass3::loadMedia (void)
{
	bool success = true;

	for (int i = 0; i < 5; i++) {
		images[i] = SDL_LoadBMP (names[i]);
		if (images[i] == NULL) {
			printf ("SDL Error: %s\n", SDL_GetError ());
			success = false;
		}
	}

	return success;
}

int testClass3::start (const char *title, int x, int y, int w, int h, Uint32 flags)
{
	if (!loadMedia ()) {
		printf ("Cannot continue... loading media failed.\n");
		return -1;
	}
	else {
		if (!init (title, x, y, w, h, flags)) {
			printf ("Initializing failed!\n");
		}
		else {
			bool quit = false;
			SDL_Event e;

			while (!quit) {
				while (SDL_PollEvent (&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
				}

				SDL_BlitSurface (images[KEY_PRESS_SURFACE_DEFAULT], NULL, screen, NULL);
				SDL_UpdateWindowSurface (window);
			}
		}
	}

	close ();
	return 0;
}

void testClass3::close (void)
{
	for (int i = 0; i < 5; i++) {
		SDL_FreeSurface (images[i]);
		images[i] = NULL;
	}

	// Destroy window and quit SDL
	SDL_DestroyWindow (window);
	window = NULL;

	SDL_Quit ();
}

