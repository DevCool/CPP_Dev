#include "WinApp.h"

//--------------------------------------------------------
WApplication::WApplication(HINSTANCE hInstance,
						   LPCTSTR ClassName,
						   WNDPROC WndProc,
						   LPCTSTR MenuName)
{
	// Initializing the application using the application
	// member variable
	_WndClsEx.cbSize = sizeof(WNDCLASSEX);
	_WndClsEx.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
	_WndClsEx.lpfnWndProc = WndProc;
	_WndClsEx.cbClsExtra = 0;
	_WndClsEx.cbWndExtra = 0;
	_WndClsEx.hInstance = hInstance;
	_WndClsEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	_WndClsEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	_WndClsEx.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	_WndClsEx.lpszMenuName = MenuName;
	_WndClsEx.lpszClassName = ClassName;
	_WndClsEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
}
//--------------------------------------------------------
void WApplication::Register()
{
	RegisterClassEx(&_WndClsEx);
}
//--------------------------------------------------------
