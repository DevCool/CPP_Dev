#include "Windows.h"
#include "CWindow.h"

#define WIN32_LEAN_AND_MEAN
#pragma comment( lib, "ShitDLL.lib" )

int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nShowCmd )
{
	WSIZE wSize = { 100, 100, 350, 375 };
	IWindow *WndInterface = GetInterface();

	if(WndInterface)
	{
		WndInterface->CreateWnd(L"Test Title", wSize );
		WndInterface->Run();
	}

	delete [] WndInterface;
	return TRUE;
}
