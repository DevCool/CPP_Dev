#ifndef CAMERA_H
#define CAMERA_H

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <cstdio>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <iostream>

#ifndef M_PI
#define M_PI 3.1415926535
#endif

using namespace std;

class Camera
{
	private:
		Camera();
		~Camera();

	public:
		void lockCamera(void);
		void moveCamera(float, float);
		void moveCameraUp(float, float);
		void controlCamera(float, float, bool);
		void updateCamera(void);

		float getCamX(void);
		float getCamY(void);
		float getCamZ(void);
		float getCamPitch(void);
		float getCamYaw(void);

		static Camera& getCamera();
		static void destroyCamera();

	protected:
		float camX, camY, camZ;
		float camYaw, camPitch;
};

#endif
