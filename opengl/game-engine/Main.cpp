#include "GameClass.h"

int main(int argc, char* args[]) {

	GameClass* gameObjPtr = &GameClass::getGameClass();
	return gameObjPtr->Start();

}

