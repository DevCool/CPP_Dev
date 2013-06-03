#include "Game.h"

namespace
{
	//Create a global pointer to a game object
	Game* g_pGame = NULL;
};

LRESULT CALLBACK MainWindowProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//Return the user defined msg proc from global view
	return g_pGame->MsgProc (hWnd, uMsg, wParam, lParam);
}

Game::Game (HINSTANCE hInstance)
{
	m_hGameWindow = NULL;
	m_hGameInstance = hInstance;
	m_ClientWidth = 800;
	m_ClientHeight = 600;
	m_wsGameTitle = L"DirectX9 Game";
	m_bPaused = false;
	g_pGame = this;
}

Game::~Game ()
{
	//Release objects from memory if needed
}

int Game::Run ()
{
	//Message loop

	MSG msg = {0};
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage (&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			//TranslateMessage
			TranslateMessage (&msg);
			//Dispatch Message
			DispatchMessage (&msg);
		}
		else // game update, render
		{
			if (!m_bPaused) //Game is not paused
			{
				//update
				Update (0.0f);
				//render
				Render ();
			}
			else //If we are paused
			{
				//Sleep for X milliseconds
				Sleep (100);
			}
		}
	}

	return static_cast<int> (msg.wParam);
}

HWND Game::GetGameWindow () const
{
	return m_hGameWindow;
}

HINSTANCE Game::GetGameInstance () const
{
	return m_hGameInstance;
}

float Game::GetAspectRatio () const
{
	return static_cast<float> (m_ClientWidth) / m_ClientHeight;
}

bool Game::Init ()
{
	//Try and initialize game window
	if (!InitGameWindow ())
		return false;
	//Try and initialize direct 3d
	if (!InitDirect3D ())
		return false;

	//If succeeded
	return true;
}

bool Game::InitGameWindow ()
{
	//Create a window class
	WNDCLASSEX wndClass = {
		sizeof (WNDCLASSEX),
		CS_HREDRAW | CS_VREDRAW,
		MainWindowProc,
		0,
		0,
		m_hGameInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		static_cast<HBRUSH> (GetStockObject (BLACK_BRUSH)),
		NULL,
		L"Direct3D9_MainWindow",
		LoadIcon(NULL, IDI_APPLICATION)
	};

	//Register the window class
	if (!RegisterClassEx (&wndClass))
		return false;

	//Make it so the window width and height
	//are that of the requested client size
	RECT rWndRect = {
		0, 0,
		m_ClientWidth,
		m_ClientHeight
	};
	//Custom window style
	DWORD dwStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;
	AdjustWindowRect (&rWndRect, dwStyle, FALSE);
	int width = rWndRect.right - rWndRect.left;
	int height = rWndRect.bottom - rWndRect.top;

	//Create our window
	m_hGameWindow = CreateWindow (
		L"Direct3D9_MainWindow",
		m_wsGameTitle.c_str (),
		dwStyle,
		GetSystemMetrics (SM_CXSCREEN) / 2 - width / 2,
		GetSystemMetrics (SM_CYSCREEN) / 2 - height / 2,
		width,
		height,
		NULL,
		NULL,
		m_hGameInstance,
		NULL);

	//Check if window is created
	if (!m_hGameWindow)
		return false;

	//Show our window
	ShowWindow (m_hGameWindow, SW_SHOW);

	return true;
}

bool Game::InitDirect3D ()
{
	//To be filled in later
	return true;
}

LRESULT Game::MsgProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage (0);
		return 0;
	}

	return DefWindowProc (hWnd, uMsg, wParam, lParam);
}

