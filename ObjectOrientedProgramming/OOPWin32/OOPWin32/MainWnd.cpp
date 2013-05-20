#include "MainWnd.h"

//---------------------------------------------------------
WWindow::WWindow()
{
	// If we declare a window class with a default contructor,
	// we need to reset the window to a nothing
	_hwnd = NULL;
}
//---------------------------------------------------------
HWND WWindow::Create(HINSTANCE hinst,
					 LPCTSTR clsname,
					 LPCTSTR wndname,
					 HWND parent,
					 DWORD dStyle,
					 DWORD dXStyle,
					 int x,
					 int y,
					 int width,
					 int height)
{
	// When call the Create() method, we can use it to create a new window
	_hwnd = CreateWindowEx(dXStyle,
						   clsname,
						   wndname,
						   dStyle,
						   x,
						   y,
						   width,
						   height,
						   parent,
						   NULL,
						   hinst,
						   NULL);

	// We hope everything went alright and the window was created
	if(_hwnd != NULL)
		return _hwnd;

	// If something went wrong for example if the window could not
	// be created, return a "nothing" window
	return NULL;
}
//----------------------------------------------------------
BOOL WWindow::Show(int dCmdShow)
{
	// We will display the main window as a regular object and update it
	if(ShowWindow(_hwnd, dCmdShow) && UpdateWindow(_hwnd))
		return TRUE;
	return FALSE;
}
//----------------------------------------------------------
WWindow::operator HWND()
{
	// This overloaded operator allows us to use HWND anyway we want
	return _hwnd;
}
//----------------------------------------------------------
