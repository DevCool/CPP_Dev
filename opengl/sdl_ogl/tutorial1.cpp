#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#ifndef GL_UNSIGNED_SHORT_5_6_5
#define GL_UNSIGNED_SHORT_5_6_5 0x8363
#endif
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

SDL_Surface* screen;

int width = 800;
int height = 600;
float angle = 0.0;

void initGL() {
	glClearColor(0.1, 0.5, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, width, height);
	gluPerspective(45.0, (float)width/(float)height, 0.5, 1000.0);
	gluLookAt(3.0, 3.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
}

void resizeGL(int width, int height) {
	if (height==0) height=1;
	if (width==0) width=1;
	float ratio=1.0*width/height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,width,height);
	gluPerspective(45, ratio, 0.5, 1000.0);
	glMatrixMode(GL_MODELVIEW);	
}

void update() {
	if (angle >= 360.0) {
		angle -= 0.05;
	}
	else if (angle <= 0.0) {
		angle += 0.05;
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glRotatef(angle, 1.0, 0.0, 0.0);
	glPushMatrix();
	glBegin(GL_POLYGON);
		// front
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(1.0, 1.0, 0.0);
		glVertex3f(-1.0, 1.0, 0.0);
		glVertex3f(-1.0, -1.0, 0.0);
		glVertex3f(1.0, -1.0, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
		// back
		glColor3f(1.0, 0.0, 1.0);
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(-1.0, 1.0, 1.0);
		glVertex3f(-1.0, -1.0, 1.0);
		glVertex3f(1.0, -1.0, 1.0);
	glEnd();

	glBegin(GL_POLYGON);
		// side 1
		glColor3f(0.0, 1.0, 1.0);
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(1.0, 1.0, 0.0);
		glVertex3f(1.0, -1.0, 0.0);
		glVertex3f(1.0, -1.0, 1.0);
	glEnd();

	glBegin(GL_POLYGON);
		// side 2
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(-1.0, 1.0, 0.0);
		glVertex3f(-1.0, 1.0, 1.0);
		glVertex3f(-1.0, -1.0, 1.0);
		glVertex3f(-1.0, -1.0, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
		// top
		glColor3f(0.5, 0.4, 0.7);
		glVertex3f(1.0, 1.0, 0.0);
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(-1.0, 1.0, 1.0);
		glVertex3f(-1.0, 1.0, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
		// bottom
		glColor3f(0.2, 1.0, 0.0);
		glVertex3f(-1.0, -1.0, 1.0);
		glVertex3f(-1.0, -1.0, 0.0);
		glVertex3f(1.0, -1.0, 0.0);
		glVertex3f(1.0, -1.0, 1.0);
	glEnd();
	glFlush();
	glPopMatrix();

	SDL_GL_SwapBuffers();
}

int main(int argc, char *args[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE|SDL_OPENGL);
	bool running = true;
	Uint32 start;
	SDL_Event event;

	initGL();

	while (running) {
		start = SDL_GetTicks();
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) { running = false; }
			else if (event.type == SDL_VIDEORESIZE) { resizeGL(width, height); }
			else if (event.type == SDL_KEYUP) {
				if (event.key.keysym.sym == SDLK_ESCAPE) { running = false; }
			}
		}

		update();
		display();

		if (1000/60 > (SDL_GetTicks()-start))
			SDL_Delay(1000/60 > (SDL_GetTicks()-start));
	}

	SDL_Quit();
	return 0;
}

