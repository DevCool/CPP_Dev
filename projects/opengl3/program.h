#ifndef _program_h_
#define _program_h_

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

class program
{
	private:
	bool running;
	SDL_Event event;
	SDL_Surface* window;
	Uint32 start;
	const int iTriangle,iCube;
	float iCubeAngle;
	
	void Update();
	void Render();
	void Init();
	
	void DisplayLists();
	
	public:
	program();
	~program();
	
	int Start();
};

#endif

