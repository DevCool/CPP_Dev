#include "CApp.h"

bool CApp::OnInit() {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,				8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,				8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,				8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,				8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,				16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,				32);

	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,			8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,		8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,			8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,		8);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,		1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,		2);

	if((Surf_Display = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == NULL) {
		printf("Cannot create game window.\nSDL Error: %s\n", SDL_GetError());
		return false;
	}

	glClearColor(0, 0, 0, 0);
	glViewport(0, 0, 800, 600);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, 800, 600, 0, 1, -1);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);

	glLoadIdentity();

	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	return true;
}

