#if 1 // Total
/*----------------------------------------------------------------------------------------------------
	WM_PAINT 에 대한 설명과, UpdateWindow 에 대한 내용입니다.
	WM_PAINT 는 먼저 메세지 큐에 인큐됐다 하더라도, 나머지 메세지들이 모두 처리된 후에 처리됩니다.

	윈도우가 작업 처리중, WM_PAINT가 들어가 있는 상황에서, 새로운 WM_PAINT가 들어오면,
	두 InvalidateRect 의 rect 영역을 합친 후, 마지막에 처리하여, 효율을 높이기 위함입니다.

	UpdateWindow 는 즉각 WM_PAINT를 시행하도록 하는 코드입니다.
	마치 SendMessage(WM_PAINT).. 와 매우 유사한데, 
	단 하나의 차이점은 UpdateWindow 는 InvalidateRect 의 영역이 없을 경우, 시행이 되지 않는다라는
	차이점이 하나 있습니다.

	아래는 위 내용들을 보여주는 코드입니다. 굳이 따라 적을 필요는 없고, 위 내용만 숙지하면 됩니다.
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
	PAINTSTRUCT ps;
	static BOOL isEllipse;

	switch (iMessage)
	{
	case WM_CREATE:
		isEllipse = TRUE;
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		if (isEllipse)
		{
			Ellipse(hdc, 10, 10, 100, 100);
		}
		else
		{
			Rectangle(hdc, 10, 10, 100, 100);
		}
		return 0;


	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		isEllipse = !isEllipse;
		
		hdc = GetDC(hWnd);

		InvalidateRect(hWnd, NULL, TRUE);
		if (iMessage == WM_RBUTTONDOWN)
		{
			UpdateWindow(hWnd);
		}
		Sleep(1'000);

		ReleaseDC(hWnd, hdc);
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석


#endif // Total