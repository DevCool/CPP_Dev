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

struct coordinate
{
	float x,y,z;
	coordinate(float a,float b,float c) : x(a),y(b),z(c) {};
};

struct face
{
	int facenum;
	bool four;
	int faces[4];
	face(int facen,int f1,int f2,int f3) : facenum(facen)
	{
		faces[0]=f1;
		faces[1]=f2;
		faces[2]=f3;
		four=false;
	}
	face(int facen,int f1,int f2,int f3,int f4) : facenum(facen)
	{
		faces[0]=f1;
		faces[1]=f2;
		faces[2]=f3;
		faces[3]=f4;
		four=true;
	}
};

class program
{
	private:
	bool running;
	SDL_Event event;
	SDL_Surface* window;
	Uint32 start;
	int cube;
	float angle;

	void Init();
	void Update();
	void Render();

	void Keyboard();
	int LoadObject(const char* filename);

	public:
	program();
	~program();

	int Start();
};

#endif

