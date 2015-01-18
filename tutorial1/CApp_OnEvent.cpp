#include "CApp.h"

void CApp::OnEvent(SDL_Event* Event) {
	if(Event->type == SDL_QUIT) {
		Running = false;
	}
	else if(Event->type == SDL_KEYDOWN) {
		if(Event->key.keysym.sym == SDLK_UP) {
			posY += cos(5.0f * 3.1415962f * 0.25f);
		}
		else if(Event->key.keysym.sym == SDLK_DOWN) {
			posY += -cos(5.0f * 3.1415962f * 0.25f);
		}
		else if(Event->key.keysym.sym == SDLK_LEFT) {
			posX += cos(5.0f * 3.1415962f * 0.25f);
		}
		else if(Event->key.keysym.sym == SDLK_RIGHT) {
			posX += -cos(5.0f * 3.1415962f * 0.25f);
		}
	}
	else if(Event->type == SDL_KEYUP) {
		if(Event->key.keysym.sym == SDLK_ESCAPE) {
			Running = false;
		}

		posY = posY;
		posX = posX;
	}
}

