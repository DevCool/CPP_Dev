#include <Windows.h>
#include "CWindow.h"

class CWindow : public IWindow
{
public:
	CWindow();
	~CWindow();

	VOID CreateWnd( LPCWSTR lpszWindowTitle, WSIZE wSize );
	INT Run( VOID );
	LRESULT MessageProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	HWND GetWindow( VOID );
	HINSTANCE GetInstance( VOID );

	HINSTANCE m_hInst;

protected:
	HWND m_hWnd;
	BOOL m_bRunning;
};

namespace
{
	CWindow *cWndObj = NULL;
};

CWindow::CWindow()
{
	cWndObj = this;
	m_hWnd = NULL;
	m_bRunning = false;
	m_hInst = NULL;
}

CWindow::~CWindow()
{
	delete [] this;
}

VOID CWindow::CreateWnd( LPCWSTR lpszWindowTitle, WSIZE wSize )
{
	WNDCLASSEX wc;

	ZeroMemory( &wc, sizeof( WNDCLASSEX ) );
	wc.cbSize = sizeof( WNDCLASSEX );
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = m_hInst;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = (LPCWSTR)NULL;
	wc.lpszClassName = L"Main_ClAsS";
	wc.hIconSm = LoadIcon( NULL, IDI_APPLICATION );

	if(!RegisterClassEx(&wc))
	{
		 MessageBox( NULL, L"Cannot register class.", L"Shit Error", MB_OK | MB_ICONERROR );
		 return;
	}

	m_hWnd = CreateWindowEx(
		WS_EX_TOPMOST,
		L"Main_ClAsS",
		lpszWindowTitle,
		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		wSize.x, wSize.y,
		wSize.width, wSize.height,
		HWND_DESKTOP,
		NULL,
		m_hInst,
		NULL
		);

	if(!m_hWnd)
	{
		MessageBox( NULL, L"Cannot create the main window of this application.", L"Error", MB_OK | MB_ICONERROR );
		return;
	}

	ShowWindow( m_hWnd, SW_SHOWNORMAL );
	UpdateWindow( m_hWnd );

	m_bRunning = true;
}

INT CWindow::Run( VOID )
{
	MSG msg = {0};

	while( m_bRunning )
	{
		while( GetMessage( &msg, NULL, 0, 0 ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		if( msg.message == WM_QUIT ) m_bRunning = false;;
	}

	return static_cast<INT>( msg.wParam );
}

LRESULT CWindow::MessageProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_QUIT:
		ExitProcess(0);
		break;
	default:
		return DefWindowProc( hWnd, uMsg, wParam, lParam );
	}

	return 0;
}

HWND CWindow::GetWindow( VOID )
{
	return m_hWnd;
}

HINSTANCE CWindow::GetInstance( VOID )
{
	return m_hInst;
}

LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return cWndObj->MessageProc( hWnd, uMsg, wParam, lParam );
}

CWINDOWAPI WNDHANDLE APIENTRY GetInterface( VOID )
{
	return new CWindow;
}