#include <Windows.h>
#include "Game.h"

class TestGame : public Game
{
public:
	//Constructor
	TestGame (HINSTANCE hInstance);
	//Destructor
	~TestGame ();

	void Update (float dt) override;
	void Render () override;
	bool Init () override;
};

TestGame::TestGame (HINSTANCE hInstance) : Game (hInstance)
{
}

TestGame::~TestGame ()
{
}

bool TestGame::Init ()
{
	if (!Game::Init ())
		return false;

	return true;
}

void TestGame::Update (float dt)
{
}

void TestGame::Render ()
{
	m_pd3dDevice->Clear (NULL, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB (255, 0, 255), 0.0f, NULL);

	m_pd3dDevice->Present (NULL, NULL, NULL, NULL);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//Create a TestGame pointer
	TestGame* tGame = new TestGame (hInstance);

	if (!tGame->Init ())
		return 0;

	return (tGame->Run ());
}
