#include "Application.h"

Application::Application() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
	  cerr << "Error: Couldn't initialize SDL!" << endl;
	  cerr << SDL_GetError() << endl;
	}
	
	cout << "Main Application Started!" << endl;

	_objLoader = &ObjLoader::getObjectLoader();
	_camera = &Camera::getCamera();

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
	
	SDL_FreeSurface(_screen);
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

/*
	for (int i = 1; i <= 10; i++) {
	  for (int j = 1; j <= 5; j++) {
	    glPushMatrix();
	      glTranslatef((cos(i-j)*tan(i+2.0))/2.0, 1.0, cos(i+j)*25.0);
	      glCallList(_testObject);
	    glPopMatrix();
	  }
	}
 */

	glPushMatrix();
	DrawSpiralTowers();
	glFlush();
	SDL_GL_SwapBuffers();
	glPopMatrix();
}

void Application::Update(void) {
}

int Application::Start(void) {
	_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE | SDL_OPENGL | SDL_GL_DOUBLEBUFFER);
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

void Application::CreatePyramid(float x, float y, float z, int width, int height) {
	glBegin(GL_TRIANGLES);
	// These vertices create the back side
	glColor3ub(255, 0, 0);		glVertex3f(x, y + height, z);
	glColor3ub(0, 255, 255);	glVertex3f(x - width, y - height, z - width);
	glColor3ub(255, 0, 255);	glVertex3f(x + width, y - height, z - width);
	
	// These vertices create the Front Side
	glColor3ub(255, 0, 0);		glVertex3f(x, y + height, z);
	glColor3ub(0, 255, 255);	glVertex3f(x + width, y - height, z + width);
	glColor3ub(255, 0, 255);	glVertex3f(x - width, y - height, z + width);
	
	// These vertices create the Front Left Side
	glColor3ub(255, 0, 0);		glVertex3f(x, y + height, z);
	glColor3ub(0, 255, 255);	glVertex3f(x - width, y - height, z + width);
	glColor3ub(255, 0, 255);	glVertex3f(x - width, y - height, z - width);
	
	// These vertices create the Front Right Side
	glColor3ub(255, 0, 0);		glVertex3f(x, y + height, z);
	glColor3ub(0, 255, 255);	glVertex3f(x + width, y - height, z - width);
	glColor3ub(255, 0, 255);	glVertex3f(x + width, y - height, z + width);
	glEnd();
	
	// Now render the bottom of the Pyramid
	glBegin(GL_QUADS);
	glColor3ub(255, 0, 0);		glVertex3f(x - width, y - height, z + width);
	glColor3ub(0, 255, 255);	glVertex3f(x + width, y - height, z + width);
	glColor3ub(255, 0, 255);	glVertex3f(x + width, y - height, z - width);
	glColor3ub(0, 0, 255);		glVertex3f(x - width, y - height, z - width);
	glEnd();
}

void Application::DrawSpiralTowers(void) {
	const float PI = 3.14159;
	const float kIncrease = PI / 16.0;
	const float kMaxRotation = PI * 6;
	float radius = 40;
	
	// Keep looping until we go past the max degrees of rotation (which is 3 full rotations)
	for(float degree = 0; degree < kMaxRotation; degree += kIncrease) {
		float x = float(radius * cos(degree));
		float z = float(radius * sin(degree));
		
		CreatePyramid(x, 3, z, 1, 3);
		
		radius -= 40 / (kMaxRotation / kIncrease);
	}
}
