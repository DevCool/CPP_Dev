#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>


SDL_Surface* screen=NULL;

void init()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,640.0/480.0,1.0,500.0);
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0,0.0,0.0);
	glVertex3f(0.0,2.0,-5.0);
	glVertex3f(-2.0,-2.0,-5.0);
	glVertex3f(2.0,-2.0,-5.0);
	glEnd();
}

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	screen=SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);
	bool running=true;
	Uint32 start;
	SDL_Event event;
	init();
	while(running)
	{
		start=SDL_GetTicks();
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					running=false;
					break;
			}
		}
		display();
		SDL_GL_SwapBuffers();
		if(1000/30>(SDL_GetTicks()-start))
			SDL_Delay(1000/30-(SDL_GetTicks()-start));
	}
	SDL_Quit();
	return 0;
}

