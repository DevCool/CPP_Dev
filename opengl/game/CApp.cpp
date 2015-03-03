#include "CApp.h"

COLORS::COLORS(float r, float g, float b) {
	red = r;
	green = g;
	blue = b;
}

CApp::CApp(void) {
	screen = NULL;
	running = true;
	myColors.push_back(new colors(1.0, 0.0, 1.0));
	myColors.push_back(new colors(0.0, 0.0, 1.0));
	myColors.push_back(new colors(0.0, 1.0, 0.0));
	myColors.push_back(new colors(1.0, 0.0, 0.0));
	myColors.push_back(new colors(1.0, 1.0, 0.0));
	myColors.push_back(new colors(0.0, 1.0, 1.0));
}

CApp::~CApp(void) {
	Cleanup();
}

int CApp::Start(int width, int height) {
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "Error: Cannot initialise SDL!" << endl
		<< SDL_GetError() << endl;
		return -1;
	}
	
	if((screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE | SDL_OPENGL | SDL_GL_DOUBLEBUFFER)) != 0) {
		SDL_WM_SetCaption("My Game (OpenGL)", NULL);
		InitOpenGL(width, height);
		
		SDL_Event event;
		
		while(running) {
			start = SDL_GetTicks();
			while(SDL_PollEvent(&event)) {
				if(event.type == SDL_QUIT) {
					running = false;
				}
				else if(event.type == SDL_KEYDOWN) {
					KeyHandler();
				}
			}
			
			Render();
			Update();
			
			if(1000/GAME_FPS > (SDL_GetTicks()-start)) {
				SDL_Delay(1000/GAME_FPS > (SDL_GetTicks()-start));
			}
		}
	}
	else {
		cout << "Couldn't create the SDL Window!" << endl;
		return -1;
	}
	
	return 0;
}

void CApp::InitOpenGL(int width, int height) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glViewport(0, 0, width, height);
	gluPerspective(45.0, (float)width/(float)height, 0.1, 1000.0);
	gluLookAt(50.0, 20.0, -35.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	
	//myCube1 = DrawCube(myColors, 0.0, 0.0, -5.0, 2.0);
}

void CApp::Cleanup(void) {
	for(unsigned int i = 0; i < myColors.size(); i++)
		delete myColors[i];
	
	myColors.clear();
	SDL_FreeSurface(screen);
	SDL_Quit();
}

void CApp::KeyHandler(void) {
	keys = SDL_GetKeyState(NULL);
	
	if (keys[SDLK_ESCAPE]) {
		running = false;
	}
}

void CApp::Render(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glColor3f(myColors[2]->red, myColors[2]->green, myColors[2]->blue);
	for(float i = -50; i < 50; i += 1) {
		glBegin(GL_LINES);
		//Horizontal lines
		glVertex3f(-50, 0.0, i);
		glVertex3f(50, 0.0, i);
		
		//Vertical lines
		glVertex3f(i, 0.0, -50);
		glVertex3f(i, 0.0, 50);
		glEnd();
	}

	glPushMatrix();
	for(float i = 0; i < 30; i += 3) {
		for(float j = 3; j < 30; j += 3) {
			glLoadIdentity();
			DrawCube(myColors, -j, 1.5, 0.0, 3.0);
		}
		glLoadIdentity();
		DrawCube(myColors, 0.0, 1.5, i, 3.0);
	}

	for(float i = 0; i < 33; i += 3) {
		for(float j = 3; j < 33; j += 3) {
			glLoadIdentity();
			glTranslatef(-30.0, 0.0, 30.0);
			DrawCube(myColors, j, 1.5, 0.0, 3.0);
		}
		glLoadIdentity();
		glTranslatef(-30.0, 0.0, 30.0);
		DrawCube(myColors, 0.0, 1.5, -i, 3.0);
	}
	glPopMatrix();
	
	glFlush();	
	SDL_GL_SwapBuffers();
}

void CApp::Update(void) {
}

void CApp::Destroy(void) {
	delete this;
}

void CApp::DrawCube(vector<colors*> cols, float x, float y, float z, float size) {
	glTranslatef(x, y, z);
	glBegin(GL_QUADS);
		// front side
		glColor3f(cols[0]->red, cols[0]->green, cols[0]->blue);
		glVertex3f(size / 2, size / 2, size / 2);
		glVertex3f(-size / 2, size / 2, size / 2);
		glVertex3f(-size / 2, -size / 2, size / 2);
		glVertex3f(size / 2, -size / 2, size / 2);

		// back side
		glColor3f(cols[1]->red, cols[1]->green, cols[1]->blue);
		glVertex3f(size / 2, size / 2, -size / 2);
		glVertex3f(-size / 2, size / 2, -size / 2);
		glVertex3f(-size / 2, -size / 2, -size / 2);
		glVertex3f(size / 2, -size / 2, -size / 2);		
		
		// left side
		glColor3f(cols[2]->red, cols[2]->green, cols[2]->blue);
		glVertex3f(-size / 2, size / 2, size / 2);
		glVertex3f(-size / 2, size / 2, -size / 2);
		glVertex3f(-size / 2, -size / 2, -size / 2);
		glVertex3f(-size / 2, -size / 2, size / 2);		
		
		// right side
		glColor3f(cols[3]->red, cols[3]->green, cols[3]->blue);
		glVertex3f(size / 2, size / 2, -size / 2);
		glVertex3f(size / 2, size / 2, size / 2);
		glVertex3f(size / 2, -size / 2, size / 2);
		glVertex3f(size / 2, -size / 2, -size / 2);
		
		// top side
		glColor3f(cols[4]->red, cols[4]->green, cols[4]->blue);
		glVertex3f(size / 2, size / 2, -size / 2);
		glVertex3f(-size / 2, size / 2, -size / 2);
		glVertex3f(-size / 2, size / 2, size / 2);
		glVertex3f(size / 2, size / 2, size / 2);
		
		// bottom side
		glColor3f(cols[5]->red, cols[5]->green, cols[5]->blue);
		glVertex3f(-size / 2, -size / 2, -size / 2);
		glVertex3f(-size / 2, -size / 2, size / 2);
		glVertex3f(size / 2, -size / 2, size / 2);
		glVertex3f(size / 2, -size / 2, -size / 2);
	glEnd();
	glEndList();
}
