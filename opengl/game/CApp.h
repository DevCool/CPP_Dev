#ifndef CAPP_H
#define CAPP_H

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#include "CCamera.h"
#include "CObjLoader.h"

#ifdef _TEST_GAME_
#define			SCREEN_WIDTH			800
#define			SCREEN_HEIGHT			600
#endif

#define			GAME_FPS				60

typedef struct COLORS {
	float red, green, blue;
	COLORS(float r, float g, float b);
} colors, *lpColors;

class CApp {

public:
	CApp(void);
	~CApp(void);

	int Start(int width, int height);

private:
	void InitOpenGL(int width, int height);
	void Cleanup(void);

	void KeyHandler(void);
	void Render(void);
	void Update(void);
	void Destroy(void);
	
	void DrawCube(vector<colors*> cols, float x, float y, float z, float size);

private:
	Uint8 *keys;
	Uint32 start;
	bool running, mousein;
	vector<colors*> myColors;
	vector<CVector3> vertexList1;

protected:
	SDL_Surface* screen;
	int myCube1, myMonkey1;
	CObjLoader objLoader;
	CCamera objCamera;

};

extern "C"
typedef CApp* cApp;

#endif
