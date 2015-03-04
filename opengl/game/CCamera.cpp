#include "CCamera.h"

CCamera::CCamera(void) {
	camX = -5.0;
	camY = 1.0;
	camZ = -10.0;
	camPitch = camYaw = 0.0;
}

CCamera::~CCamera(void) {
}

void CCamera::lockCamera(void) {
	if(camPitch > 90.0)
		camPitch = 90.0;
	if (camPitch < -90.0)
		camPitch = -90.0;
	if(camYaw < 0.0)
		camYaw += 360.0;
	if(camYaw > 360.0)
		camYaw -= 360.0;
}

void CCamera::moveCamera(float dist, float dir) {
	float rad = (camYaw + dir) * M_PI / 180.0;
	camX -= sin(rad)*dist;
	camZ -= cos(rad)*dist;
}

void CCamera::moveCameraUp(float dist, float dir) {
	float rad = (camPitch + dir) * M_PI / 180.0;
	camY += sin(rad)*dist;
}

void CCamera::controlCamera(float moveVel, float mouseVel, bool mousein) {
	if(mousein) {
		int MidX = 320;
		int MidY = 240;
		SDL_ShowCursor(SDL_DISABLE);
		int tmpx, tmpy;
		SDL_GetMouseState(&tmpx, &tmpy);
		camYaw += mouseVel * (MidX - tmpx);
		camPitch += mouseVel * (MidY - tmpy);
		//lockCamera();
		SDL_WarpMouse(MidX, MidY);
		Uint8* keys = SDL_GetKeyState(NULL);
		
		if(keys[SDLK_w]) {
			if((camPitch != 90.0) && (camPitch != -90.0))
				moveCamera(moveVel, 0.0);
			moveCameraUp(moveVel, 0.0);
		}
		else if(keys[SDLK_s]) {
			if((camPitch != 90.0) && (camPitch != -90.0))
				moveCamera(moveVel, 180.0);
			moveCameraUp(moveVel, 180.0);
		}
		
		if(keys[SDLK_a]) {
			moveCamera(moveVel, 90.0);
		}
		else if(keys[SDLK_d]) {
			moveCamera(moveVel, 270.0);
		}
	}
	
	glRotatef(-camPitch, 1.0, 0.0, 0.0);
	glRotatef(-camYaw, 0.0, 1.0, 0.0);
}

void CCamera::updateCamera(void) {
	glTranslatef(-camX, -camY, -camZ);
}

void CCamera::Destroy(void) {
	delete this;
}

float CCamera::getCamX(void) {
	return camX;
}

float CCamera::getCamY(void) {
	return camY;
}

float CCamera::getCamZ(void) {
	return camZ;
}

float CCamera::getCamPitch(void) {
	return camPitch;
}

float CCamera::getCamYaw(void) {
	return camYaw;
}