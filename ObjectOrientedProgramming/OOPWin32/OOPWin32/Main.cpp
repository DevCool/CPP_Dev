#include <windows.h>
#include "WinApp.h"
#include "MainWnd.h"

//----------------------------------------------------------
LRESULT CALLBACK MainWndProc(HWND hWnd,
							 UINT Msg,
							 WPARAM wParam,
							 LPARAM lParam);
//----------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInst,
				   LPSTR lpCmdLine,
				   int nCmdShow)
{
	MSG msg = {0};
	LPCTSTR ClsName = L"Win32OOP";
	LPCTSTR WndName = L"Object-Oriented Win32 Programming";

	// Initialize the application class
	WApplication WinApp(hInstance, ClsName, MainWndProc);
	WinApp.Register();

	// Create the main window
	WWindow m_mainWindow;
	m_mainWindow.Create(hInstance, ClsName, WndName);
	// Display the main window
	m_mainWindow.Show();

	// Process the main window's messages
	while(WM_QUIT != msg.message)
	{
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == TRUE)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// Here we do rendering stuff for directX
	}

	return (int) msg.wParam;
}
//----------------------------------------------------------
LRESULT CALLBACK MainWndProc(HWND hWnd,
							 UINT Msg,
							 WPARAM wParam,
							 LPARAM lParam)
{
	switch(Msg)
	{
	case WM_QUIT:
		PostQuitMessage(0);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		}
		return 0;
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}
//----------------------------------------------------------
