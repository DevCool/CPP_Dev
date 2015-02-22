#include "Application.h"

Application::Application() {
	_running = true;
}

Application::~Application() {
}

Application& Application::getApplication(void) {
	static Application* myApp = NULL;

	if (myApp == NULL) {
		myApp = new Application();

		std::cout << "Create Main Application!" << endl;
	}

	return *myApp;
}

void Application::destroyApplication(void) {
	Application* myApp = &getApplication();
	delete myApp;

	cout << "Application Destroyed!" << endl;	
}

void Application::InitGL(void) {
	glClearColor(1.0, 0.5, 0.5, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	gluPerspective(45.0, (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.5, 1000.0);
	gluLookAt(0.0, 0.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
}

void Application::Render(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SDL_GL_SwapBuffers();
}

void Application::Update(void) {
}

int Application::Start(void) {
	SDL_Init(SDL_INIT_EVERYTHING);
	_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE | SDL_OPENGL);
	SDL_WM_SetCaption("My Test Game (SDL/OpenGL)", NULL);

	Uint32 start;
	SDL_Event event;

	InitGL();

	while (_running) {
		start = SDL_GetTicks();

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) { _running = false; }
			KeyHandler();
		}

		Render();
		Update();

		if (1000/GAME_FPS > (SDL_GetTicks()-start))
			SDL_Delay(1000/GAME_FPS > (SDL_GetTicks()-start));
	}

	SDL_Quit();

	return 0;
}

void Application::KeyHandler(void) {
	Uint8 *keys = SDL_GetKeyState(NULL);

	if (keys[SDLK_ESCAPE]) {
		_running = false;
	}
}

