#include "testClass2.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main (int argc, char *args[])
{
	testClass2 test;
	return test.start ("SDL Tutorial 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
}

