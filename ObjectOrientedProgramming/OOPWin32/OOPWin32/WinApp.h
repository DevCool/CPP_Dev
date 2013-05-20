#pragma once
#include <windows.h>

//--------------------------------------------------------
class WApplication
{
public:
	// This contructor will initialize the application
	WApplication(
		HINSTANCE hInstance,
		LPCTSTR ClassName,
		WNDPROC WndProc,
		LPCTSTR MenuName = NULL
		);

	// Class Registration
	void Register();

protected:
	// Global variable that holds the application
	WNDCLASSEX _WndClsEx;
};
//--------------------------------------------------------
