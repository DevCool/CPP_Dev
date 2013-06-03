#ifndef GAME_H
#define GAME_H

#include <Windows.h>
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

protected:
	//Attributes
	HWND			m_hGameWindow;
	HINSTANCE		m_hGameInstance;
	UINT			m_ClientWidth;
	UINT			m_ClientHeight;
	bool			m_bPaused;
	std::wstring	m_wsGameTitle;
};

#endif //!GAME_H
