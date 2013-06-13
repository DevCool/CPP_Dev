#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <windows.h>
#include <string>
using namespace std;

class CWindow
{
public:
    virtual ~CWindow();

    CWindow(HINSTANCE hInstance, string className, string windowTitle);

    HWND GetWindowsHandle(void);
    HINSTANCE GetWindowInstance(void);
    LRESULT MessageProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

    void SetRunning(bool bRunning);
    int Run(void);

private:
    HWND m_hWnd;
    HINSTANCE m_hInst;
    bool running;
};

LRESULT CALLBACK msgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

#endif // _WINDOW_H_
