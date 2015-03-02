#include "Camera.h"

Camera::Camera() {
	camX = 0.0;
	camY = 1.0;
	camZ = 0.0;

	camYaw = camPitch = 0.0;
}

Camera::~Camera() {
}

Camera& Camera::getCamera() {
	static Camera* myCamera = NULL;

	if (myCamera == NULL) {
		myCamera = new Camera();

		cout << "Camera Started!" << endl;
	}

	return *myCamera;
}

void Camera::destroyCamera() {
	Camera *myCamera = &getCamera();
	delete myCamera;

	cout << "Camera Stop!" << endl;
}

void Camera::lockCamera(void) {
	if (camPitch > 90.0)
		camPitch = 90.0;
	if (camPitch < -90.0)
		camPitch = -90.0;
	if (camYaw < 0.0)
		camYaw += 360.0;
	if (camYaw > 360.0)
		camYaw -= 360.0;
}

void Camera::moveCamera(float dist, float dir) {
	float rad = (camYaw+dir)*M_PI/180.0;
	camX -= sin(rad)*dist;
	camZ -= cos(rad)*dist;
}

void Camera::moveCameraUp(float dist, float dir) {
	float rad = (camPitch+dir)*M_PI/180.0;
	camY += sin(rad)*dist;
}

void Camera::controlCamera(float moveVel, float mouseVel, bool mousein) {
	if (mousein) {
		int MidX = 320;
		int MidY = 240;
		SDL_ShowCursor(SDL_DISABLE);
		int tmpx, tmpy;
		SDL_GetMouseState(&tmpx, &tmpy);
		camYaw += mouseVel*(MidX-tmpx);
		camPitch += mouseVel*(MidY-tmpy);
		//lockCamera();
		SDL_WarpMouse(MidX, MidY);
		Uint8 *keys = SDL_GetKeyState(NULL);

		if (keys[SDLK_w]) {
			if ((camPitch != 90) && (camPitch != -90))
				moveCamera(moveVel, 0.0);
			moveCameraUp(moveVel, 0.0);
		}
		else if (keys[SDLK_s]) {
			if ((camPitch != 90) && (camPitch != -90))
				moveCamera(moveVel, 180.0);
			moveCameraUp(moveVel, 180.0);
		}

		if (keys[SDLK_a]) {
			moveCamera(moveVel, 90.0);
		}
		else if (keys[SDLK_d]) {
			moveCamera(moveVel, 270.0);
		}
	}

	glRotatef(-camPitch, 1.0, 0.0, 0.0);
	glRotatef(-camYaw, 0.0, 1.0, 0.0);
}

void Camera::updateCamera(void) {
	glTranslatef(-camX, -camY, -camZ);
}

float Camera::getCamX(void) {
	return camX;
}

float Camera::getCamY(void) {
	return camY;
}

float Camera::getCamZ(void) {
	return camZ;
}

float Camera::getCamPitch(void) {
	return camPitch;
}

float Camera::getCamYaw(void) {
	return camYaw;
}
