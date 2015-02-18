#include "functions.h"

float camX = -1.0, camY = 1.0, camZ = -2.0;
float camYaw = 0.0;
float camPitch = 0.0;

#ifndef M_PI
#define M_PI=3.1415926535
#endif

void lockCamera() {
	if (camPitch>90)
		camPitch=90;
	if (camPitch<-90)
		camPitch=-90;
	if(camYaw<0.0)
		camYaw+=360.0;
	if(camYaw>360.0)
		camYaw-=360.0;
}

void moveCamera(float dist, float dir) {
	float rad = (camYaw+dir)*M_PI/180.0;
	camX -= sin(rad)*dist;
	camZ -= cos(rad)*dist;
}

void moveCameraUp(float dist, float dir) {
	float rad = (camPitch+dir)*M_PI/180.0;
	camY += sin(rad)*dist;
}

void Control(float moveVel, float mouseVel, bool mousein) {
	if(mousein) {
		int MidX = 320;
		int MidY = 240;
		SDL_ShowCursor(SDL_DISABLE);
		int tmpx, tmpy;
		SDL_GetMouseState(&tmpx, &tmpy);
		camYaw += mouseVel*(MidX-tmpx);
		camPitch -= mouseVel*(MidY-tmpy);
		//lockCamera();
		SDL_WarpMouse(MidX, MidY);
		Uint8 *state = SDL_GetKeyState(NULL);

		if(state[SDLK_w]) {
			if((camPitch!=90) && (camPitch!=-90))
				moveCamera(moveVel, 180.0);
			moveCameraUp(moveVel, 180.0);
		}
		else if(state[SDLK_s]) {
			if((camPitch!=90) && (camPitch!=-90))
				moveCamera(moveVel, 0.0);
			moveCameraUp(moveVel, 0.0);
		}

		if(state[SDLK_a]) {
			moveCamera(moveVel, 270.0);
		}
		else if(state[SDLK_d]) {
			moveCamera(moveVel, 90.0);
		}
	}

	glRotatef(-camPitch, 1.0, 0.0, 0.0);
	glRotatef(-camYaw, 0.0, 1.0, 0.0);
}

void UpdateCamera() {
	glTranslatef(-camX, -camY, -camZ);
}

void drawCube(float size) {
	glBegin(GL_QUADS);
		// front face
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(size/2, size/2, -size/2);
		glVertex3f(-size/2, size/2, -size/2);
		glVertex3f(-size/2, -size/2, -size/2);
		glVertex3f(size/2, -size/2, -size/2);

		// left face
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(-size/2, size/2, -size/2);
		glVertex3f(-size/2, size/2, size/2);
		glVertex3f(-size/2, -size/2, size/2);
		glVertex3f(-size/2, -size/2, -size/2);

		// right face
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(size/2, size/2, -size/2);
		glVertex3f(size/2, -size/2, -size/2);
		glVertex3f(size/2, -size/2, size/2);
		glVertex3f(size/2, size/2, size/2);

		// back face
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(size/2, size/2, size/2);
		glVertex3f(-size/2, size/2, size/2);
		glVertex3f(-size/2, -size/2, size/2);
		glVertex3f(size/2, -size/2, size/2);

		// top face
		glColor3f(0.0, 1.0, 1.0);
		glVertex3f(size/2, size/2, size/2);
		glVertex3f(-size/2, size/2, size/2);
		glVertex3f(-size/2, size/2, -size/2);
		glVertex3f(size/2, size/2, -size/2);

		// bottom face
		glColor3f(0.5, 1.0, 0.1);
		glVertex3f(size/2, -size/2, -size/2);
		glVertex3f(size/2, -size/2, size/2);
		glVertex3f(-size/2, -size/2, size/2);
		glVertex3f(-size/2, -size/2, -size/2);
	glEnd();
}

