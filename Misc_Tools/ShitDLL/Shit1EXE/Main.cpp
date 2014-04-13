#include "Windows.h"
#include "CWindow.h"

#pragma comment( lib, "ShitDLL.lib" )

#define WIN32_LEAN_AND_MEAN

int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nShowCmd )
{
	WSIZE wSize = { 100, 100, 350, 320 };
	IWindow *WndInterface = GetInterface();

	if(WndInterface)
	{
		WndInterface->CreateWnd(L"Test Title", wSize );
		WndInterface->Run();
		WndInterface->Release();
		UnregisterClass(L"Main_ClAsS", hInstance);
	}

	return TRUE;
}
