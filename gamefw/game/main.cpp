#include "GameManager.h"

int main(int argc, char** argv)
{
	GameManager *gameManager = &GameManager::getGameManager();
	gameManager->runGameLoop();
	gameManager->destroyGameManager();

	return 0;
}

