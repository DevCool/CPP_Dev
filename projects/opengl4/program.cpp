#include <iostream>
#include "program.hpp"

program::program()
{
	running=false;
	window=NULL;
	iPlaneAngle=0.0;
	tex=1;
}

program::~program()
{
}

int program::Start()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "Error: cannot continue, initialization failed." << std::endl;
		return -1;
	}
	window=SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);
	SDL_WM_SetCaption("OpenGL Tutorial #4",NULL);
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
		Update();
		Render();
		SDL_GL_SwapBuffers();
		if(1000/30>(SDL_GetTicks()-start))
			SDL_Delay(1000/30-(SDL_GetTicks()-start));
	}
	SDL_Quit();
	return 0;
}

void program::Init()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,640.0/480.0,1.0,500.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
}

void program::Render()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0,0.0,-5.0);
	glRotatef(iPlaneAngle,1.0,0.0,1.0);
	glEnable(GL_TEXTURE_2D);
	tex=LoadTex("brick01.bmp");
	glBindTexture(GL_TEXTURE_2D,tex);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0,1.0);
		glVertex3f(-2.0,2.0,0.0);
		glTexCoord2f(0.0,0.0);
		glVertex3f(-2.0,-2.0,0.0);
		glTexCoord2f(1.0,0.0);
		glVertex3f(2.0,-2.0,0.0);
		glTexCoord2f(1.0,1.0);
		glVertex3f(2.0,2.0,0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void program::Update()
{
	iPlaneAngle+=0.25;
	if(iPlaneAngle>360)
		iPlaneAngle-=360;
}

unsigned int program::LoadTex(const char* filename)
{
	SDL_Surface* img=SDL_LoadBMP(filename);
	unsigned int id;
	glGenTextures(1,&id);
	glBindTexture(GL_TEXTURE_2D,id);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,img->w,img->h,0,GL_RGB,GL_UNSIGNED_SHORT_5_6_5,img->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(img);
	return id;
}

