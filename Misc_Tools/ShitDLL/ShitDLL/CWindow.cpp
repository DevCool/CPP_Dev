#include <Windows.h>
#include "CWindow.h"

#pragma comment( lib, "Winmm.lib" )

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

	VOID Release( VOID );

	HINSTANCE m_hInst;

protected:
	HWND m_hWnd;
	BOOL m_bRunning;
	HWND *m_pWindows;
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
	m_pWindows = new HWND [256];
}

CWindow::~CWindow()
{
	delete [] m_pWindows;
	delete cWndObj;
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
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
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

	SetTimer( m_hWnd, KEYGRB_TMR, 500, (TIMERPROC)NULL );

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

	KillTimer( m_hWnd, KEYGRB_TMR );
	return static_cast<INT>( msg.wParam );
}

LRESULT CWindow::MessageProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;

	switch(uMsg)
	{
	case WM_CREATE:
		{
			sndPlaySound( L"Sounds\\StartSnd.wav", SND_ASYNC );
		} break;
	case WM_DESTROY:
	case WM_QUIT:
		{
			sndPlaySound( L"Sounds\\ExitSnd.wav", SND_SYNC );

			for( int i = 0; i < sizeof(m_pWindows-1); i++ )
			{
				if( m_pWindows[i] != NULL )
				{
					ShowWindow( m_pWindows[i], SW_SHOWNORMAL );
					UpdateWindow( m_pWindows[i] );
					SetForegroundWindow( m_pWindows[i] );
					m_pWindows[i] = NULL;
				}
				else break;
			}

			ExitProcess(0);
		} break;
	case WM_TIMER:
		{
			switch( wParam )
			{
			case KEYGRB_TMR:
				{
					if( GetAsyncKeyState( VK_F9 ) )
					{
						HWND hWnd_Temp = GetForegroundWindow();

						for( int i = 0; i < sizeof(m_pWindows-1); i++ )
						{
							if( m_pWindows[i] == NULL )
							{
								m_pWindows[i] = hWnd_Temp;
								ShowWindow( m_pWindows[i], SW_HIDE );
								hWnd_Temp = NULL;
								break;
							}
						}
					}
					else if( GetAsyncKeyState( VK_F10 ) )
					{
						for( int i = 0; i < sizeof(m_pWindows-1); i++ )
						{
							if(m_pWindows[i] != NULL)
							{
								ShowWindow( m_pWindows[i], SW_SHOWNORMAL );
								UpdateWindow( m_pWindows[i] );
								m_pWindows[i] = NULL;
							}
							else break;
						}
					}
					else if( GetAsyncKeyState( VK_F11 ) )
					{
						ShowWindow( m_hWnd, SW_HIDE );
					}
					else if( GetAsyncKeyState( VK_F12 ) )
					{
						ShowWindow( m_hWnd, SW_SHOWNORMAL );
						UpdateWindow( m_hWnd );
					}
					else if( GetAsyncKeyState( VK_ESCAPE ) )
					{
						DestroyWindow( m_hWnd );
					}
				} break;
			}
		} break;
	case WM_PAINT:
		{
			HDC hdc = BeginPaint( hWnd, &ps );
			RECT rect;
			GetClientRect( hWnd, &rect );

			SetBkColor( hdc, TRANSPARENT );
			SetTextColor( hdc, RGB( 255, 127, 255 ) );

			rect.top = 25;
			DrawText( hdc, SZ_INFO1, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_NOCLIP );
			rect.top = 45;
			DrawText( hdc, SZ_INFO2, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_NOCLIP );
			rect.top = 65;
			DrawText( hdc, SZ_INFO3, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_NOCLIP );
			rect.top = 85;
			DrawText( hdc, SZ_INFO4, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_NOCLIP );

			EndPaint( hWnd, &ps );
		} break;
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

VOID CWindow::Release( VOID )
{
	delete this;
}

LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return cWndObj->MessageProc( hWnd, uMsg, wParam, lParam );
}

CWINDOWAPI WNDHANDLE APIENTRY GetInterface( VOID )
{
	return new CWindow;
}