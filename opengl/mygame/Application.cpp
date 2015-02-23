#include "Application.h"

Application::Application() {
	cout << "Main Application Started!" << endl;

	_camera = &Camera::getCamera();
	_objLoader = &ObjLoader::getObjectLoader();

	_testObject = 0;
	_running = true;
	_mousein = false;
//	_tester = true;
	_angle = 0.0;
}

Application::~Application() {
	_mousein = false;
	SDL_ShowCursor(SDL_ENABLE);

	if (_camera != NULL) {
		_camera->destroyCamera();
	}

	if (_objLoader != NULL) {
		_objLoader->destroyObjectLoader();
	}

	SDL_Quit();
}

Application& Application::getApplication(void) {
	static Application* myApp = NULL;

	if (myApp == NULL) {
		myApp = new Application();
	}

	return *myApp;
}

void Application::destroyApplication(void) {
	Application* myApp = &getApplication();
	delete myApp;

	cout << "Application Destroyed!" << endl;	
}

void Application::InitGL(void) {
	glClearColor(0.1, 0.5, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	gluPerspective(45.0, (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);

	_testObject = _objLoader->loadObject("./data/test.obj");

	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
}

void Application::Render(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluLookAt(_camera->getCamX(), _camera->getCamY(), _camera->getCamZ(), _camera->getCamX()+_camera->getCamYaw(), _camera->getCamY()+_camera->getCamPitch(), _camera->getCamZ()+_camera->getCamYaw(), 0.0, 1.0, 0.0);
	glLoadIdentity();

	_camera->controlCamera(0.2, 0.2, _mousein);
	_camera->updateCamera();

	glBegin(GL_QUADS);
		glColor3f(1.0, 0.0, 0.0); glVertex3f(50.0, 0.0, 50.0);
		glColor3f(1.0, 0.5, 0.0); glVertex3f(-50.0, 0.0, 50.0);
		glColor3f(1.0, 0.2, 0.5); glVertex3f(-50.0, 0.0, -50.0);
		glColor3f(0.5, 1.0, 0.0); glVertex3f(50.0, 0.0, -50.0);
	glEnd();

	glCallList(_testObject);

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
			if (event.type == SDL_MOUSEBUTTONDOWN) { _mousein = true; }
			KeyHandler();
		}

		Render();
		Update();

		if (1000/GAME_FPS > (SDL_GetTicks()-start))
			SDL_Delay(1000/GAME_FPS > (SDL_GetTicks()-start));
	}

	destroyApplication();

	return 0;
}

void Application::KeyHandler(void) {
	Uint8 *keys = SDL_GetKeyState(NULL);

	if (keys[SDLK_ESCAPE]) {
		_running = false;
	}
	else if (keys[SDLK_p]) {
		_mousein = false;
		SDL_ShowCursor(SDL_ENABLE);
	}
}

