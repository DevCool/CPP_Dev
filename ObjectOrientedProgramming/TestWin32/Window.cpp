#include "Window.h"
using namespace std;

namespace
{
    CWindow* cWnd = NULL;
}

CWindow::~CWindow()
{
}

CWindow::CWindow(HINSTANCE hInstance, string className, string windowTitle)
{
    cWnd = this;
    cWnd->m_hInst = hInstance;
    cWnd->running = false;

    WNDCLASSEX wcEx = {
        sizeof(WNDCLASSEX),
        CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS,
        msgProc,
        0, 0,
        hInstance,
        LoadIcon(NULL, IDI_APPLICATION),
        LoadCursor(NULL, IDC_ARROW),
        (HBRUSH)(COLOR_WINDOW+3),
        NULL,
        className.c_str(),
        LoadIcon(NULL, IDI_APPLICATION)
    };
    if(!RegisterClassEx(&wcEx))
        return;
    cWnd->m_hWnd = CreateWindow(
                                className.c_str(),
                                windowTitle.c_str(),
                                WS_CAPTION | WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
                                250, 250, 800, 600,
                                HWND_DESKTOP,
                                NULL,
                                hInstance,
                                NULL);
    if(!cWnd->m_hWnd)
        return;

    ShowWindow(cWnd->m_hWnd, SW_SHOWNORMAL);
    UpdateWindow(cWnd->m_hWnd);

    SetRunning(true);

    return;
}

HWND CWindow::GetWindowsHandle(void)
{
    return cWnd->m_hWnd;
}

HINSTANCE CWindow::GetWindowInstance(void)
{
    return cWnd->m_hInst;
}

LRESULT CWindow::MessageProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch(msg)
    {
    case WM_DESTROY:
        CloseWindow(this->m_hWnd);
        ExitProcess(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

LRESULT CALLBACK msgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    return cWnd->MessageProcedure(hwnd, msg, wparam, lparam);
}

void CWindow::SetRunning(bool bRunning)
{
    cWnd->running = bRunning;
}

int CWindow::Run(void)
{
    MSG msg = {0};
    while(running)
    {
        if(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            if(msg.message == WM_QUIT)
            {
                cWnd->running = false;
            }
        }
    }
    return (int)msg.wParam;
}
