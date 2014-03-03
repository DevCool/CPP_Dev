#include <Windows.h>
#include <WinBase.h>
#include <WinGDI.h>

#include "GlobalDefines.h"

#pragma comment(lib, "Msimg32.lib")

bool bRunning = false;

HWND hWndMain = NULL;
HWND hWndWindows[256];
HWND* pWndArray = hWndWindows;

HINSTANCE g_hInst = NULL;

//-----------------------------------------------------------------------------------

void TimerFunc(void);
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

//-----------------------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc,
		0, 0, hInstance, LoadIcon(NULL, IDI_APPLICATION), LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW+3), (LPCTSTR)NULL, "TestDevClass", LoadIcon(NULL, IDI_APPLICATION)
	};

	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Cannot register class.", "Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	HANDLE hMutex = CreateMutex(NULL, FALSE, "TestDev App");

	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		MessageBox(NULL, "App already running..", "Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	g_hInst = hInstance;

	hWndMain = CreateWindow(
		"TestDevClass",
		"TestDev App",
		WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
		100, 100, 400, 340,
		HWND_DESKTOP,
		(HMENU)NULL,
		hInstance,
		(LPVOID*)NULL);

	if(!hWndMain)
	{
		MessageBox(NULL, "Cannot create window.", "Error", MB_OK | MB_ICONERROR);
		UnregisterClass("TestDevClass", hInstance);
		return 1;
	}

	ShowWindow(hWndMain, SW_SHOWNORMAL);
	UpdateWindow(hWndMain);

	SetTimer(hWndMain, TIMER_KP, 750, (TIMERPROC)TimerFunc);

	bRunning = true;

	MSG msg = {0};

	while(bRunning)
	{
		while(GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if(msg.message == WM_QUIT)
			bRunning = false;
	}

	KillTimer(hWndMain, TIMER_KP);
	UnregisterClass("TestDevClass", hInstance);
	return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	HDC hdc = NULL;
	PAINTSTRUCT ps;

	switch(msg)
	{
	case WM_CREATE:
		{
			HWND hWnd1 = CreateWindow(
				"STATIC",
				HWND1_TXT,
				WS_VISIBLE|WS_CHILD|SS_CENTER,
				((400 / 2) - (320 / 2)), 10, 320, 20,
				hwnd,
				(HMENU)IDC_STATIC,
				g_hInst,
				NULL);

			HWND hWnd2 = CreateWindow(
				"STATIC",
				HWND2_TXT,
				WS_VISIBLE|WS_CHILD|SS_CENTER,
				((400 / 2) - (320 / 2)), 40, 320, 20,
				hwnd,
				(HMENU)IDC_STATIC,
				g_hInst,
				NULL);

			HWND hWnd3 = CreateWindow(
				"STATIC",
				HWND3_TXT,
				WS_VISIBLE|WS_CHILD|SS_CENTER,
				((400 / 2) - (200 / 2)), 75, 200, 40,
				hwnd,
				(HMENU)IDC_STATIC,
				g_hInst,
				NULL);

/*			HWND hWnd4 = CreateWindow(
				"STATIC",
				CODEDBY_ST_TEXT,
				WS_VISIBLE|WS_CHILD|SS_CENTER,
				((400 / 2) - (200 / 2)), 290, 200, 20,
				hwnd,
				(HMENU)IDC_STATIC,
				g_hInst,
				NULL); */
		} break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		{
			hdc = BeginPaint(hwnd, &ps);
			char szText[] = CODEDBY_ST_TEXT;
			TRIVERTEX vertices1[2];
			TRIVERTEX vertices2[2];
			TRIVERTEX vertices3[2];
			TRIVERTEX vertex[2];
			RECT rect;
			GRADIENT_RECT gRect, gRect2, gRect3, gRect4;

				GetClientRect(hwnd, &rect);

				vertices1[0].x = 10; //10
				vertices1[0].y = 230; //270
				vertices1[0].Red = 0x0000;
				vertices1[0].Green = 0x8000;
				vertices1[0].Blue = 0x8000;
				vertices1[0].Alpha = 0x0000;

				vertices1[1].x = 40;
				vertices1[1].y = 250;
				vertices1[1].Red = 0x0000;
				vertices1[1].Green = 0x8000;
				vertices1[1].Blue = 0x8000;
				vertices1[1].Alpha = 0x0000;

				vertices2[0].x = 355;	//385
				vertices2[0].y = 230; //250
				vertices2[0].Red = 0x0000;
				vertices2[0].Green = 0x8000;
				vertices2[0].Blue = 0x8000;
				vertices2[0].Alpha = 0x0000;

				vertices2[1].x = 385;
				vertices2[1].y = 250;
				vertices2[1].Red = 0x0000;
				vertices2[1].Green = 0x8000;
				vertices2[1].Blue = 0x8000;
				vertices2[1].Alpha = 0x0000;

				vertices3[0].x = 10;
				vertices3[0].y = 210;
				vertices3[0].Red = 0x0000;
				vertices3[0].Green = 0x8000;
				vertices3[0].Blue = 0x8000;
				vertices3[0].Alpha = 0x0000;

				vertices3[1].x = 385;
				vertices3[1].y = 230;
				vertices3[1].Red = 0x0000;
				vertices3[1].Green = 0x8000;
				vertices3[1].Blue = 0x8000;
				vertices3[1].Alpha = 0x0000;

				vertex[0].x = 10;
				vertex[0].y = 250;
				vertex[0].Red = 0x0000;
				vertex[0].Green = 0x8000;
				vertex[0].Blue = 0x8000;
				vertex[0].Alpha = 0x0000;

				vertex[1].x = 385;
				vertex[1].y = 270;
				vertex[1].Red = 0x0000;
				vertex[1].Green = 0xd000;
				vertex[1].Blue = 0xd000;
				vertex[1].Alpha = 0x0000;

				gRect.UpperLeft = 0;
				gRect.LowerRight = 1;

				gRect2.UpperLeft = 0;
				gRect2.LowerRight = 1;

				gRect3.UpperLeft = 0;
				gRect3.LowerRight = 1;

				gRect4.UpperLeft = 0;
				gRect4.LowerRight = 1;

				GradientFill(hdc, vertex, 2, &gRect, 1, GRADIENT_FILL_RECT_H);
				GradientFill(hdc, vertices1, 2, &gRect2, 1, GRADIENT_FILL_RECT_H);
				GradientFill(hdc, vertices2, 2, &gRect3, 1, GRADIENT_FILL_RECT_H);
				GradientFill(hdc, vertices3, 2, &gRect4, 1, GRADIENT_FILL_RECT_H);

				SetTextColor(hdc, RGB(255, 127, 255));
				SetBkMode(hdc, TRANSPARENT);
				rect.left = 117;
				rect.top = 235;
				DrawText(hdc, szText, sizeof(szText), &rect, DT_SINGLELINE | DT_NOCLIP);
			EndPaint(hwnd, &ps);
		} break;
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
	
	return 0;
}

int i = 0;

void TimerFunc(void)
{
	if(GetAsyncKeyState(VK_F5))
	{
		i = 0;
		while(i < sizeof(pWndArray))
		{
			if(pWndArray[i] == NULL)
			{
				pWndArray[i] = GetForegroundWindow();
				ShowWindow(pWndArray[i], SW_HIDE);
				break;
			}
			++i;
		}
	}
	else if(GetAsyncKeyState(VK_F6))
	{
		i = 0;
		while(i < sizeof(pWndArray))
		{
			if(pWndArray[i] != NULL)
			{
				ShowWindow(pWndArray[i], SW_SHOWNORMAL);
				UpdateWindow(pWndArray[i]);
				pWndArray[i] = NULL;
			}
			++i;
			if(i == sizeof(pWndArray))
				break;
		}
	}
	else if(GetAsyncKeyState(VK_F10))
	{
		ShowWindow(hWndMain, SW_HIDE);
	}
	else if(GetAsyncKeyState(VK_F11))
	{
		ShowWindow(hWndMain, SW_SHOWNORMAL);
		UpdateWindow(hWndMain);
	}
}
