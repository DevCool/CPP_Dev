#ifndef _CAPP_H_
#define _CAPP_H_

#include <cstdio>
#include <cmath>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

class CApp {
	private:
		bool			Running;

		SDL_Surface*	Surf_Display;

		float posX, posY;

	public:
		CApp();

		int OnExecute();

	public:
		bool OnInit();
		void OnEvent(SDL_Event* Event);
		void OnLoop();
		void OnRender();
		void OnCleanup();
};

#endif

