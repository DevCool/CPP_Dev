#ifndef APPLICATION_H
#define APPLICATION_H

#define		SCREEN_WIDTH		800
#define		SCREEN_HEIGHT		600
#define		GAME_FPS		60

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>

#include "Camera.h"
#include "ObjLoader.h"

using namespace std;

class Application
{
	private:
		float _angle;
		bool _running, _mousein; // _tester;

		int _testObject;
		SDL_Surface* _screen;

		Camera* _camera;
		ObjLoader* _objLoader;

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
