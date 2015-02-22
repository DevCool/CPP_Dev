#include "functions.h"

#ifndef GL_UNSIGNED_SHORT_5_6_5
#define GL_UNSIGNED_SHORT_5_6_5 0x8363
#endif
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

#define BOOL				short int
#define TRUE				1
#define	FALSE				0

#define WIDTH				800
#define HEIGHT			600
#define CUBE_LIST		10

SDL_Surface *screen;

float angle;

unsigned int texture;
bool mousein = false;
bool tester = true;

void cleanup(void) {
	mousein = false;
	SDL_ShowCursor(SDL_ENABLE);
	IMG_Quit();
	SDL_Quit();
}

unsigned int loadTexture(const char *filename) {
	unsigned int id;
	SDL_Surface *image;

	image = IMG_Load(filename);

	if (image == NULL) {
		printf("bad image\n");
		cleanup();
		exit(-1);
	}

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SDL_FreeSurface(image);
	return id;
}

unsigned int loadTextureAlpha(const char *filename) {
	unsigned int id;
	SDL_Surface *image;

	image = IMG_Load(filename);

	if (image == NULL) {
		printf("bad image\n");
		cleanup();
		exit(-1);
	}

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SDL_FreeSurface(image);
	return id;
}

void loadassets() {
	int flags;
	int initted;

	flags = IMG_INIT_JPG|IMG_INIT_PNG;
	initted = IMG_Init(flags);

	if ((initted&flags) != flags) {
		printf("IMG_Init: Failed to init required jpg and png support!\n");
		printf("IMG_Init: %s\n", IMG_GetError());
		SDL_Quit();
		exit(-1);
	}

	texture = loadTexture("grass.png");
}

void init() {
	glClearColor(0.1, 0.5, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, WIDTH, HEIGHT);
	gluPerspective(45.0, (float)(WIDTH/HEIGHT), 0.1, 1000.0);
	gluLookAt(camX, camY, camZ, camX+camYaw, camY+camPitch, camX-camYaw, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glClearDepth(1.0);
	glNewList(CUBE_LIST, GL_COMPILE);
	drawCube(1.0);
	glEndList();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

void update() {
	if ((angle >= 0.0) && tester) {
		angle += (80*0.01);
		if (angle >= 360.0) { angle = 360.0; tester = false; }
	}
	else if ((angle <= 360.0) && !tester) {
		angle -= (80*0.01);
		if (angle <= 0.0) { angle = 0.0; tester = true; }
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	Control(0.2, 0.2, mousein);
	UpdateCamera();

	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
		glTexCoord2f(5, 5); glVertex3f(50.0, 0.0, 50.0);
		glTexCoord2f(5, 0);	glVertex3f(-50.0, 0.0, 50.0);
		glTexCoord2f(0, 0);	glVertex3f(-50.0, 0.0, -50.0);
		glTexCoord2f(0, 5); glVertex3f(50.0, 0.0, -50.0);
	glEnd();

	for(int i=0; i<5; i++) {
		for(int j=0; j<10; j++) {
			glPushMatrix();
			glTranslatef(sin(i+j)*5.0, 1.0, cos(i+j)*5.0);
			glRotatef(angle, 1.0, 1.0, 0.0);
			glCallList(CUBE_LIST);
			glPopMatrix();
		}
	}
	glFlush();
	SDL_GL_SwapBuffers();
}

int main(int argc, char *args[]) {
	BOOL running;

	printf("Starting please wait...\n");

	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE | SDL_OPENGL);
	SDL_WM_SetCaption("SDL/OpenGL Tutorial", NULL);

	running = true;
	tester = true;
	Uint32 start;
	SDL_Event event;

	loadassets();
	printf("Assets loaded...			[OK]\n");
	init();

	while(running) {
		start = SDL_GetTicks();
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) running = false;
			if(event.type == SDL_KEYUP) {
				if(event.key.keysym.sym == SDLK_ESCAPE) {
					running = false;
				}
			}
			if(event.type == SDL_MOUSEBUTTONDOWN) {
				mousein = true;
			}
			if(event.type == SDL_KEYDOWN) {
				if(event.key.keysym.sym == SDLK_p) {
					mousein = false;
					SDL_ShowCursor(SDL_ENABLE);
				}
			}
		}

		display();
		update();

		if (1000/60 > (SDL_GetTicks()-start))
			SDL_Delay(1000/60 > (SDL_GetTicks()-start));

		//printf("Angle value: %2f\n", angle);
	}

	cleanup();
	return 0;
}

