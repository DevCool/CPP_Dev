#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>

extern float camX, camY, camZ;
extern float camYaw;
extern float camPitch;

void lockCamera();
void moveCamera(float, float);
void moveCameraUp(float, float);
void Control(float, float, bool);
void UpdateCamera();
void drawCube(float);

#endif

