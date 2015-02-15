#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#ifndef GL_UNSIGNED_SHORT_5_6_5
#define GL_UNSIGNED_SHORT_5_6_5 0x8363
#endif
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

SDL_Surface* screen;
bool running;
int width;
int height;
unsigned int fps;

void initWindow() {
	glClearColor(0.1, 0.5, 1.0, 1.0);
	glClearDepth(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, width, height);
	gluPerspective(45.0, (float)width/(float)height, 0.5, 1000.0);
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SDL_GL_SwapBuffers();
}

int main(int argc, char *args[]) {
	SDL_Init(SDL_INIT_EVERYTHING);

	width = 800;
	height = 600;

	screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE | SDL_OPENGL);
	SDL_WM_SetCaption("SDL/OpenGL Tutorial 2", NULL);

	fps = 1000/60;
	running = true;
	Uint32 start;
	SDL_Event event;

	initWindow();

	while (running) {
		start = SDL_GetTicks();
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) running = false;
			else if (event.type == SDL_KEYUP) {
				if (event.key.keysym.sym == SDLK_ESCAPE) running = false;
			}
		}

		display();

		if (fps > (SDL_GetTicks()-start)) SDL_Delay(fps > (SDL_GetTicks()-start));
	}

	SDL_Quit();
	return 0;
}

