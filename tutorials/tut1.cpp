#include "testClass.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main (int argc, char* args[]) {
	testClass test;
	test.start("SDL Tutorial 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
}

