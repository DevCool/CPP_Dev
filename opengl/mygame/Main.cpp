#include "Application.h"

int main(int argc, char* args[]) {
	Application *myApp = &Application::getApplication();
	myApp->Start();
	myApp->destroyApplication();

	return 0;
}

