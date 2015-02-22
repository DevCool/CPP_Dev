#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>

#define		SCREEN_WIDTH		800
#define		SCREEN_HEIGHT		600
#define		GAME_FPS		60

using namespace std;

class Application
{
	private:
		bool _running;
		SDL_Surface* _screen;

		Application();
		~Application();

	public:
		void InitGL(void);
		void Render(void);
		void Update(void);
		int Start(void);
		void KeyHandler(void);

		static Application& getApplication(void);
		static void destroyApplication(void);
};

#endif
