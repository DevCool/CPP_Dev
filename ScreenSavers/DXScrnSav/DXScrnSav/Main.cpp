#include <Windows.h>
#include <d3d9.h>
#include <ScrnSave.h>
#include <CommCtrl.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "ComCtl32.lib")
#ifdef _UNICODE
#pragma comment(lib, "ScrnSavw.lib")
#else
#pragma comment(lib, "ScrnSave.lib")
#endif

LPDIRECT3D9 g_pDirect = NULL;
LPDIRECT3DDEVICE9 g_pDirectDevice = NULL;

#define TIMER 1

int Width, Height; // Screen width/height

//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D( HWND hWnd )
{
    // Create the D3D object, which is needed to create the D3DDevice.
    if( NULL == ( g_pDirect = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice. Most parameters are
    // zeroed out. We set Windowed to TRUE, since we want to do D3D in a
    // window, and then set the SwapEffect to "discard", which is the most
    // efficient method of presenting the back buffer to the display.  And 
    // we request a back buffer format that matches the current desktop display 
    // format.
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

    // Create the Direct3D device. Here we are using the default adapter (most
    // systems only have one, unless they have multiple graphics hardware cards
    // installed) and requesting the HAL (which is saying we want the hardware
    // device rather than a software one). Software vertex processing is 
    // specified since we know it will work on all cards. On cards that support 
    // hardware vertex processing, though, we would see a big performance gain 
    // by specifying hardware vertex processing.
    if( FAILED( g_pDirect->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pDirectDevice ) ) )
    {
        return E_FAIL;
    }

    // Device state would normally be set here

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
    if( g_pDirectDevice != NULL )
        g_pDirectDevice->Release();

    if( g_pDirect != NULL )
        g_pDirect->Release();
}

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
    if( NULL == g_pDirectDevice )
        return;

    // Clear the backbuffer to a blue color
    g_pDirectDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 0, 255 ), 1.0f, 0 );

    // Begin the scene
    if( SUCCEEDED( g_pDirectDevice->BeginScene() ) )
    {
        // Rendering of scene objects can happen here

        // End the scene
        g_pDirectDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    g_pDirectDevice->Present( NULL, NULL, NULL, NULL );
}

LRESULT WINAPI ScreenSaverProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HDC hDC;
	static RECT rect;

	switch( uMsg ) {
		case WM_CREATE:
			GetClientRect( hWnd, &rect );
			Width = rect.right;
			Height = rect.bottom;

			InitD3D( hWnd );
			SetTimer( hWnd, TIMER, 10, NULL );
		return 0;
		
		case WM_DESTROY:
			KillTimer( hWnd, TIMER );
			Cleanup();
		return 0;

		case WM_TIMER:
			Render();
		return 0;
	}

	return DefScreenSaverProc( hWnd, uMsg, wParam, lParam );
}

BOOL WINAPI ScreenSaverConfigureDialog( HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return FALSE;
}

BOOL WINAPI RegisterDialogClasses(HANDLE hInst)
{
	return TRUE;
}