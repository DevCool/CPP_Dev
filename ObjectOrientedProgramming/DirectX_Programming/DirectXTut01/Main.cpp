#include "DirectX.h"

#pragma comment( lib, "d3d9.lib" )

DirectX *MyDirectX;

LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {

	switch( uMsg ) {
		
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;

	case WM_CHAR:
		switch( wParam ) {

		case VK_ESCAPE:
			PostQuitMessage( 0 );
			break;

		default:
			break;
		
		}
		break;

	default:
		return DefWindowProc( hWnd, uMsg, wParam, lParam );
		break;
	
	}

	return 0;

}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
	
	MyDirectX = new DirectX();
	WNDCLASSEX wndClass;

	wndClass.cbSize = sizeof( WNDCLASSEX );
	wndClass.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = ( HBRUSH )GetStockObject( BLACK_BRUSH );
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon( NULL, IDI_APPLICATION );
	wndClass.hIconSm = LoadIcon( NULL, IDI_WINLOGO );
	wndClass.hCursor = LoadCursor( NULL, IDC_ARROW );
	wndClass.lpfnWndProc = ( WNDPROC )WndProc;
	wndClass.lpszClassName = "MainWndClass";
	wndClass.lpszMenuName = ( LPCSTR )NULL;

	if( !RegisterClassEx( &wndClass ) ) {
		MessageBox( HWND_DESKTOP, "Cannot register the main window\nclass.", "Error", MB_OK | MB_ICONERROR );
		return 0;
	}

	HWND hWndMain = CreateWindowEx(
		WS_EX_STATICEDGE,
		"MainWndClass",
		"DirectX Tutorial #1",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		800, 600,
		HWND_DESKTOP,
		( HMENU )NULL,
		( HINSTANCE )hInstance,
		( LPVOID* )NULL
	);

	if( !hWndMain ) {
		MessageBox( HWND_DESKTOP, "Cannot create the main window.", "Error", MB_OK | MB_ICONERROR );
		UnregisterClass( "MainWndClass", hInstance );
		return 0;
	}

	ShowWindow( hWndMain, SW_SHOWNORMAL );
	UpdateWindow( hWndMain );

	MyDirectX->Init( hWndMain );

	MSG msg = {0};

	while( msg.message != WM_QUIT ) {
		
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) {
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		// Do game rendering/updating here
		MyDirectX->Render( );

	}

	MyDirectX->CleanDirectX( );
	delete [] MyDirectX;
	UnregisterClass( "MainWndClass", hInstance );
	return 0;

}