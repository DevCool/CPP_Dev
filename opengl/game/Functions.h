#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <cmath>
#include "CCamera.h"
#include "CObjLoader.h"

CCamera camObj;

bool raysphere(float xc,float yc, float zc,float xd,float yd, float zd,float xs,float ys, float zs,float r,float* dist=NULL,coordinate* point=NULL);
bool rayplane(float nx,float ny,float nz,float xs,float ys,float zs,float xd,float yd,float zd,coordinate p1,coordinate p2,coordinate p3,coordinate p4,float* dist=NULL,coordinate* point=NULL);
float trianglearea(coordinate p1,coordinate p2,coordinate p3);
bool spheresphere(coordinate& c1,float r1,coordinate c2,float r2);
float pointdistance(coordinate c1,coordinate c2);
void moveTo(coordinate c);
coordinate camPos();
bool sphereplane(coordinate& sp, coordinate vn,coordinate p1,coordinate p2,coordinate p3, coordinate p4,float r);

#endif

