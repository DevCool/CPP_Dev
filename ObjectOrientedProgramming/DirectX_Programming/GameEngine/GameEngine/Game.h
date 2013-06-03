#ifndef GAME_H
#define GAME_H

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>

class Game
{
public:
	//Constructor
	Game (HINSTANCE hInstance);
	//Destructor
	virtual ~Game ();

	//Main application loop
	int Run ();

	//Getter methods
	HWND		GetGameWindow () const;
	HINSTANCE	GetGameInstance () const;
	float		GetAspectRatio () const;

	//Framework methods
	virtual bool Init ();
	virtual void Update (float dt) = 0;
	virtual void Render () = 0;
	virtual LRESULT MsgProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	//Initialize game window
	bool InitGameWindow ();
	//Initialize Direct3D
	bool InitDirect3D ();
	//Initialize present parameters
	bool InitPresentParameters();

protected:
	//Attributes
	HWND			m_hGameWindow;
	HINSTANCE		m_hGameInstance;
	UINT			m_ClientWidth;
	UINT			m_ClientHeight;
	bool			m_bPaused;
	bool			m_bFullscreen;
	std::wstring	m_wsGameTitle;

	//DirectX Attributes
	IDirect3D9*				m_pd3d;
	IDirect3DDevice9*		m_pd3dDevice;
	D3DPRESENT_PARAMETERS	m_d3dpp;
};

#endif //!GAME_H
