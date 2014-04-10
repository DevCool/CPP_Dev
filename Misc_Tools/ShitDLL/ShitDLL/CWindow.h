#pragma once

#include <Windows.h>
#include <WinBase.h>

#ifdef SHITDLL_EXPORTS
#define CWINDOWAPI __declspec(dllexport)
#else
#define CWINDOWAPI __declspec(dllimport)
#endif

#define KEYGRB_TMR 1001

LPCWSTR SZ_INFO1 = TEXT("Press F9 to hide the foreground window.");
LPCWSTR SZ_INFO2 = TEXT("Press F10 to unhide all hidden windows.");
LPCWSTR SZ_INFO3 = TEXT("Press F11 to hide this application.");
LPCWSTR SZ_INFO4 = TEXT("Press F12 to unhide this application.");

struct WSIZE
{
	int x;
	int y;
	int width;
	int height;
};

struct IWindow
{
	virtual VOID CreateWnd( LPCWSTR lpszWindowTitle, WSIZE wSize ) = 0;
	virtual INT Run( VOID ) = 0;
	virtual LRESULT MessageProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) = 0;

	virtual HWND GetWindow( VOID ) = 0;
	virtual HINSTANCE GetInstance( VOID ) = 0;

	virtual VOID Release( VOID ) = 0;

	HWND m_hWnd;
	BOOL m_bRunning;

	HINSTANCE m_hInst;
	HWND *m_pWindows;
};

typedef IWindow* WNDHANDLE;

#define CPPAPI extern "C"

CPPAPI CWINDOWAPI WNDHANDLE WINAPI GetInterface( VOID );
CPPAPI CWINDOWAPI LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam );
