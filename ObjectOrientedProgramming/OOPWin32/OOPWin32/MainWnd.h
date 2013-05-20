#pragma once
#include <windows.h>

//--------------------------------------------------------
class WWindow
{
public:
	// We will use a default constructor to declare a window
	WWindow();
	// The Create() method will be used to init a window
	HWND Create(HINSTANCE hinst,
				LPCTSTR clsname,
				LPCTSTR wndname,
				HWND parent   = NULL,
				DWORD dStyle  = WS_OVERLAPPEDWINDOW,
				DWORD dXStyle = 0L,
				int x		  = CW_USEDEFAULT,
				int y         = CW_USEDEFAULT,
				int width	  = CW_USEDEFAULT,
				int height    = CW_USEDEFAULT);

	// This method will be used to display the window
	BOOL Show(int dCmdShow = SW_SHOWNORMAL);

	// Because each window is of the HWND, we will need a way
	// to recognize the window handle when used in our application
	operator HWND();

protected:
	// This will be a global handle available to
	// this and other windows
	HWND _hwnd;
};
//--------------------------------------------------------
