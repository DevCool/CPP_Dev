#include <windows.h>
#include <scrnsave.h>

LRESULT WINAPI ScreenSaverProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_CREATE:
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        case WM_PAINT:
        break;
        default:
            return DefScreenSaverProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

BOOL WINAPI ScreenSaverConfigureDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

BOOL WINAPI RegisterDialogClasses(HANDLE hInst)
{
    return TRUE;
}
