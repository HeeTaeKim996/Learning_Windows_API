#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	WM_WINDOWPOSCHIANG 에 대한 내용입니다. 명칭 그대로입니다.

	※ GetSystemMetrics 에 대해 간략히 나옵니다
----------------------------------------------------------------------------------------------------*/


#if 1 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Sample_2");

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
	HDC hdc;

	static int sx, sy;

	switch (iMessage)
	{
	case WM_CREATE:
		sx = GetSystemMetrics(SM_CXSCREEN);
		sy = GetSystemMetrics(SM_CYSCREEN);
		/*	○ GetSystemMetrics
			 - 시스템의 다양한 설정값을 가져오는 함수. 윈도우의 크기 가 아닌, 디스플레이 화면의 크기 를
			   가져오는데도 사용
		*/


	case WM_WINDOWPOSCHANGING:
	{
		LPWINDOWPOS wp = (LPWINDOWPOS)lParam;

		if (wp->x < 30 && wp->x > -30)
		{
			wp->x = 0;
		}
		else if (wp->x + wp->cx > sx - 30 && wp->x - wp->cx < sx + 30)
		{
			wp->x = sx - wp->cx;
		}


		if (wp->y < 30 && wp->y > -30)
		{
			wp->y = 0;
		}
		else if (wp->y + wp->cy > sy - 30 && wp->y - wp->cy < sy + 30)
		{
			wp->y = sy - wp->cy;
		}
		

		return 0;

	}


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석



#endif // Total