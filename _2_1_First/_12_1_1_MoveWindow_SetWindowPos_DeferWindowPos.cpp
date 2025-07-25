#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	GetClientRect, GetWindowRect, ScreenToClient, 
	MoveWindow, SetWindowPos, EndDeferWindow 에 대한 코드입니다.


	○ GetClientRect		: 화면 크기 
	○ GetWindowRect		: 해당 윈도우의 화면 기준 위치 반환. 
	                      부모의 ClientRect 기준의 좌표를 구하려면, 추가로 ScreenToClient 필요
	○ ScreenToClient	: 화면 기준의 좌표를, 할당한 HWND의 ScreenRect 기준 좌표로 변환

	○ MoveWindowPos		: 기본적인 Window 위치, 크기를 옮기는 함수
	○ SetWindowPos		: MoveWindowPos의 위치, 크기 조정에 더해, Z순서 조정 및 부가 옵션이 추가로 있음
	○ EndDeferWindows	: 다수의 HWND를 동시에 SetWindowPos 할 때 사용
----------------------------------------------------------------------------------------------------*/


#if 1 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MoveWindow, SetWindowPos, DeferWindowPos");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_VREDRAW | CS_HREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static RECT crt;
	static HWND hBtn[5];
	
	
	switch (iMessage)
	{
	case WM_CREATE:

		GetClientRect(hWnd, &crt);
		for (int i = 0; i < 5; i++)
		{
			hBtn[i] = CreateWindow(TEXT("button"), TEXT("test"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				crt.right / 2, i * 100, 50, 100,
				hWnd, (HMENU)i, g_hInst, NULL);
		}
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			RECT pos;
			GetWindowRect(hBtn[LOWORD(wParam)], &pos);

			POINT pt = { pos.left, pos.top };
			ScreenToClient(hWnd, &pt);

			RECT size;
			GetClientRect(hBtn[LOWORD(wParam)], &size);
			if (LOWORD(wParam) < 2)
			{
				MoveWindow(hBtn[LOWORD(wParam)], min(pt.x + 50, crt.right - size.right), pt.y, 
					size.right, size.bottom, TRUE);
			}
			else
			{
				SetWindowPos(hBtn[LOWORD(wParam)], NULL, max(pt.x - 50, size.right), pt.y,
					0, 0, SWP_NOZORDER | SWP_NOSIZE);
			}

			break;
		}

		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
			HDWP hdwp;
		case VK_RIGHT:
			hdwp = BeginDeferWindowPos(5);
			for (int i = 0; i < 5; i++)
			{
				hdwp = DeferWindowPos(hdwp, hBtn[i], NULL, crt.right - 50, i * 100, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			}
			EndDeferWindowPos(hdwp);
			break;

		case VK_LEFT:
			hdwp = BeginDeferWindowPos(5);
			for (int i = 0; i < 5; i++)
			{
				hdwp = DeferWindowPos(hdwp, hBtn[i], NULL, 0, i * 100, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			}
			EndDeferWindowPos(hdwp);
			break;
		}

		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석

 


























































#if 0 // 코드만
#include <Windows.h>
#include "resource.h"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MoveWindow, SetWindowPos, DeferWindowPos");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_VREDRAW | CS_HREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static RECT crt;
	static HWND hBtn[5];

	switch (iMessage)
	{
	case WM_CREATE:
		GetClientRect(hWnd, &crt);
		for (int i = 0; i < 5; i++)
		{
			hBtn[i] = CreateWindow(TEXT("button"), TEXT("test"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				crt.right / 2, i * 100, 50, 100,
				hWnd, (HMENU)i, g_hInst, NULL);
		}
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			RECT pos;
			GetWindowRect(hBtn[LOWORD(wParam)], &pos);

			POINT pt = { pos.left, pos.top };
			ScreenToClient(hWnd, &pt);

			RECT size;
			GetClientRect(hBtn[LOWORD(wParam)], &size);
			if (LOWORD(wParam) < 2)
			{
				MoveWindow(hBtn[LOWORD(wParam)], min(pt.x + 50, crt.right - size.right), pt.y, size.right, size.bottom,
					TRUE);
			}
			else
			{
				SetWindowPos(hBtn[LOWORD(wParam)], NULL, max(pt.x - 50, size.right), pt.y, 0, 0,
					SWP_NOZORDER | SWP_NOSIZE);
			}
			break;
		}

		return 0;



	case WM_KEYDOWN:
		switch (wParam)
		{
			HDWP hdwp;
		case VK_RIGHT:
			hdwp = BeginDeferWindowPos(5);
			for (int i = 0; i < 5; i++)
			{
				hdwp = DeferWindowPos(hdwp, hBtn[i], NULL, crt.right - 50, i * 100, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			}
			EndDeferWindowPos(hdwp);
			break;

		case VK_LEFT:
			hdwp = BeginDeferWindowPos(5);
			for (int i = 0; i < 5; i++)
			{
				hdwp = DeferWindowPos(hdwp, hBtn[i], NULL, 0, i * 100, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			}
			EndDeferWindowPos(hdwp);
			break;
		}


	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // 코드만


#endif // Total