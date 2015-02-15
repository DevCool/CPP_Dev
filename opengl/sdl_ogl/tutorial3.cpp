#include <cstdio>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#ifndef GL_UNSIGNED_SHORT_5_6_5
#define GL_UNSIGNED_SHORT_5_6_5 0x8363
#endif
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

#define WIDTH				800
#define HEIGHT			600
#define CUBE_LIST		1

SDL_Surface *screen;
float angle;
bool tester;

void drawCube(float size) {
	glBegin(GL_QUADS);
		// front face
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(size/2, size/2, -size/2);
		glVertex3f(-size/2, size/2, -size/2);
		glVertex3f(-size/2, -size/2, -size/2);
		glVertex3f(size/2, -size/2, -size/2);

		// left face
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(-size/2, size/2, -size/2);
		glVertex3f(-size/2, size/2, size/2);
		glVertex3f(-size/2, -size/2, size/2);
		glVertex3f(-size/2, -size/2, -size/2);

		// right face
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(size/2, size/2, -size/2);
		glVertex3f(size/2, -size/2, -size/2);
		glVertex3f(size/2, -size/2, size/2);
		glVertex3f(size/2, size/2, size/2);

		// back face
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(size/2, size/2, size/2);
		glVertex3f(-size/2, size/2, size/2);
		glVertex3f(-size/2, -size/2, size/2);
		glVertex3f(size/2, -size/2, size/2);

		// top face
		glColor3f(0.0, 1.0, 1.0);
		glVertex3f(size/2, size/2, size/2);
		glVertex3f(-size/2, size/2, size/2);
		glVertex3f(-size/2, size/2, -size/2);
		glVertex3f(size/2, size/2, -size/2);

		// bottom face
		glColor3f(0.5, 1.0, 0.1);
		glVertex3f(size/2, -size/2, -size/2);
		glVertex3f(size/2, -size/2, size/2);
		glVertex3f(-size/2, -size/2, size/2);
		glVertex3f(-size/2, -size/2, -size/2);
	glEnd();
}

void init() {
	glClearColor(0.1, 0.5, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, WIDTH, HEIGHT);
	gluPerspective(45.0, (float)(WIDTH/HEIGHT), 0.1, 1000.0);
	gluLookAt(0.0, 1.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);

	glNewList(CUBE_LIST, GL_COMPILE);
	drawCube(1.0);
	glEndList();
}

void update() {
	if ((angle >= 0.0) && tester) {
		angle += (20*0.01);
		if (angle >= 360.0) { angle = 360.0; tester = false; }
	}
	else if ((angle <= 360.0) && !tester) {
		angle -= (20*0.01);
		if (angle <= 0.0) { angle = 0.0; tester = true; }
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glBegin(GL_QUADS);
		glColor3f(1.0, 0.5, 0.1);
		glVertex3f(50.0, 0.0, 50.0);
		glVertex3f(-50.0, 0.0, 50.0);
		glVertex3f(-50.0, 0.0, -50.0);
		glVertex3f(50.0, 0.0, -50.0);
	glEnd();

	glLoadIdentity();
	glTranslatef(0.0, 1.0, 0.0);
	glRotatef(angle, 1.0, 1.0, 0.0);
	glCallList(CUBE_LIST);

	SDL_GL_SwapBuffers();
}

int main(int argc, char *args[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE | SDL_OPENGL);
	SDL_WM_SetCaption("SDL Game", NULL);

	bool running = true;
	tester = true;
	Uint32 start;
	SDL_Event event;

	init();

	while (running) {
		start = SDL_GetTicks();
		while (SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) running = false;
			if(event.type == SDL_KEYUP) {
				if (event.key.keysym.sym == SDLK_ESCAPE) running = false;
			}
		}

		display();
		update();

		if (1000/60 > (SDL_GetTicks()-start))
			SDL_Delay(1000/60 > (SDL_GetTicks()-start));

		//printf("Angle value: %2f\n", angle);
	}

	SDL_Quit();
	return 0;
}

