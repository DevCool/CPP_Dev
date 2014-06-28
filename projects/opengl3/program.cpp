#include <iostream>
#include "program.h"

program::program(): iTriangle(1), iCube(2)
{
	running=false;
	window=NULL;
	iCubeAngle=0.0;
}

program::~program()
{
}

int program::Start()
{
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1)
	{
		std::cerr << "Error: SDL cannot be initiated..." << std::endl;
		return -1;
	}
	window=SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);
	SDL_WM_SetCaption("OpenGL Triangles", NULL);
	running=true;
	Init();
	while(running)
	{
		start=SDL_GetTicks();
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				running=false;
		}
		Render();
		SDL_GL_SwapBuffers();
		Update();
		if(1000/30>(SDL_GetTicks()-start))
			SDL_Delay(1000/30-(SDL_GetTicks()-start));
	}
	SDL_Quit();
	return 0;
}

void program::Update()
{
	iCubeAngle+=0.5;
	if(iCubeAngle>360)
		iCubeAngle-=360;
}

void program::Render()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(2.0,0.0,-10.0);
	glCallList(iTriangle);
	glPushMatrix();
	glLoadIdentity();
	glRotatef(45,0.0,0.0,1.0);
	glTranslatef(0.0,0.0,-10.0);
	glRotatef(iCubeAngle,0.0,1.0,1.0);
	glCallList(iCube);
	glPopMatrix();
}

void program::Init()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,640.0/480.0,1.0,500.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	DisplayLists();
}

void program::DisplayLists()
{
	glNewList(iTriangle,GL_COMPILE);
	glBegin(GL_TRIANGLES);
		glColor3f(1.0,0.0,0.0);
		glVertex3f(0.0,2.0,0.0);
		glColor3f(0.0,1.0,0.0);
		glVertex3f(-2.0,-2.0,0.0);
		glColor3f(0.0,0.0,1.0);
		glVertex3f(2.0,-2.0,0.0);
	glEnd();
	glEndList();
	glNewList(iCube,GL_COMPILE);
	glBegin(GL_QUADS);
		//front face
		glVertex3f(2.0/2,2.0/2,2.0/2);
		glVertex3f(-2.0/2,2.0/2,2.0/2);
		glVertex3f(-2.0/2,-2.0/2,2.0/2);
		glVertex3f(2.0/2,-2.0/2,2.0/2);
		//left face
		glVertex3f(-2.0/2,2.0/2,2.0/2);
		glVertex3f(-2.0/2,2.0/2,-2.0/2);
		glVertex3f(-2.0/2,-2.0/2,-2.0/2);
		glVertex3f(-2.0/2,-2.0/2,2.0/2);
		//back face
		glVertex3f(2.0/2,2.0/2,-2.0/2);
		glVertex3f(-2.0/2,2.0/2,-2.0/2);
		glVertex3f(-2.0/2,-2.0/2,-2.0/2);
		glVertex3f(2.0/2,-2.0/2,-2.0/2);
		//right face
		glVertex3f(2.0/2,2.0/2,-2.0/2);
		glVertex3f(2.0/2,2.0/2,2.0/2);
		glVertex3f(2.0/2,-2.0/2,2.0/2);
		glVertex3f(2.0/2,-2.0/2,-2.0/2);
		//top face
		glVertex3f(2.0/2,2.0/2,2.0/2);
		glVertex3f(-2.0/2,2.0/2,2.0/2);
		glVertex3f(-2.0/2,2.0/2,-2.0/2);
		glVertex3f(2.0/2,2.0/2,-2.0/2);
		//bottom face
		glVertex3f(2.0/2,-2.0/2,2.0/2);
		glVertex3f(-2.0/2,-2.0/2,2.0/2);
		glVertex3f(-2.0/2,-2.0/2,-2.0/2);
		glVertex3f(2.0/2,-2.0/2,-2.0/2);
	glEnd();
	glEndList();
}

