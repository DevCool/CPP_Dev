#include <iostream>
#include "Application.h"

int main(int argc, char* args[]) {
	Application *myApp = &Application::getApplication();
	return myApp->Start();
}
