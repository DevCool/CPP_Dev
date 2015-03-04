#ifndef CCAMERA_H
#define CCAMERA_H

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <algorithm>

class CCamera {

private:
	float camX, camY, camZ;
	float camPitch, camYaw;
	
public:
	CCamera(void);
	~CCamera(void);
	
	void lockCamera(void);
	void moveCamera(float, float);
	void moveCameraUp(float, float);
	void controlCamera(float, float, bool);
	void updateCamera(void);
	void Destroy(void);
	
	float getCamX(void);
	float getCamY(void);
	float getCamZ(void);
	float getCamPitch(void);
	float getCamYaw(void);

};

#endif
