#ifndef _program_hpp_
#define _program_hpp_

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#ifndef GL_UNSIGNED_SHORT_5_6_5
#define GL_UNSIGNED_SHORT_5_6_5 0x8363
#endif
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

class program
{
	private:
	bool running;
	SDL_Event event;
	SDL_Surface* window;
	Uint32 start;
	float iPlaneAngle;
	unsigned int tex;
	
	void Render();
	void Update();
	void Init();
	
	unsigned int LoadTex(const char* filename);
	
	public:
	program();
	~program();
	
	int Start();
};

#endif

