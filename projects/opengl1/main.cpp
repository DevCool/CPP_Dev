#include <SDL/SDL.h>

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface* screen=SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);
	bool running=true;
	Uint32 start;
	SDL_Event event;
	while(running)
	{
		start=SDL_GetTicks();
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					running=false;
					break;
			}
		}
		if(1000/30>(SDL_GetTicks()-start))
			SDL_Delay(1000/30-(SDL_GetTicks()-start));
	}
	SDL_Quit();
	return 0;
}

