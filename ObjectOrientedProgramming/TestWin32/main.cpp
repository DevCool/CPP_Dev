#include "Window.h"
using namespace std;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
    string className, windowTitle;
    className = "TesClass";
    windowTitle = "Fuck Window";
    CWindow* cWnd = new CWindow(hInst, className, windowTitle);
    cWnd->Run();
    return 0;
}
