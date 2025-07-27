#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	Mouse 3 버전입니다. 
	WM_PAINT 에 사용될 데이터를 비트맵 을 사용하여 그리는 방법입니다. 실전에서도 사용되는 방법이라 합니다.

	비트맵을 사용할시, 빠르게 그릴 수 있습니다. HBITMAP 에 대한 메모리 비용은 있습니다

	추후 비트맵에 대해 자세히 공부할 예정이라 하니, 
	이번 코드는 ' WM_PAINT 때 비트맵을 이렇게 사용하는구나 ' 라고 이해하시면 됩니다.
----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Mouse3");
HBITMAP hBit;

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
	HDC hdc, hMemDC;
	HBITMAP OldBitmap;
	static int x;
	static int y;
	static BOOL bNowDraw = FALSE;
	PAINTSTRUCT ps;


	switch (iMessage)
	{
	case WM_CREATE:
		hdc = GetDC(hWnd);
		hBit = CreateCompatibleBitmap(hdc, 1024, 768);
		hMemDC = CreateCompatibleDC(hdc);

		OldBitmap = (HBITMAP)SelectObject(hMemDC, hBit);

		SelectObject(hMemDC, GetStockObject(LTGRAY_BRUSH));
		Rectangle(hMemDC, 0, 0, 1024, 768);

		SelectObject(hMemDC, OldBitmap);
		DeleteDC(hMemDC);

		ReleaseDC(hWnd, hdc);

		return 0;

	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		bNowDraw = TRUE;

		return 0;


	case WM_MOUSEMOVE:
		if (bNowDraw == TRUE)
		{
			hdc = GetDC(hWnd);
			hMemDC = CreateCompatibleDC(hdc);

			OldBitmap = (HBITMAP)SelectObject(hMemDC, hBit);

			MoveToEx(hdc, x, y, NULL);
			MoveToEx(hMemDC, x, y, NULL);

			x = LOWORD(lParam);
			y = HIWORD(lParam);
			LineTo(hdc, x, y);
			LineTo(hMemDC, x, y);

			SelectObject(hMemDC, OldBitmap);
			DeleteDC(hMemDC);

			ReleaseDC(hWnd, hdc);

		}
		return 0;


	case WM_LBUTTONUP:
		bNowDraw = FALSE;
		return 0;


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		hMemDC = CreateCompatibleDC(hdc);
		OldBitmap = (HBITMAP)SelectObject(hMemDC, hBit);

		BitBlt(hdc, 0, 0, 1024, 768, hMemDC, 0, 0, SRCCOPY);

		SelectObject(hMemDC, OldBitmap);
		DeleteDC(hMemDC);

		EndPaint(hWnd, &ps);
		return 0;


	case WM_DESTROY:
		DeleteObject(hBit);
		PostQuitMessage(0);
		return 0;



	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석


#if 1 // 코드만
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Mouse3");
HBITMAP hBit;

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
	HDC hdc, hMemDC;
	HBITMAP OldBitmap;
	static int x;
	static int y;
	static BOOL bNowDraw = FALSE;
	PAINTSTRUCT ps;



	switch (iMessage)
	{
	case WM_CREATE:
		hdc = GetDC(hWnd);
		hBit = CreateCompatibleBitmap(hdc, 1024, 768);
		hMemDC = CreateCompatibleDC(hdc);

		OldBitmap = (HBITMAP)SelectObject(hMemDC, hBit);

		SelectObject(hMemDC, GetStockObject(LTGRAY_BRUSH));
		Rectangle(hMemDC, 0, 0, 1024, 768);

		SelectObject(hMemDC, OldBitmap);
		DeleteDC(hMemDC);

		ReleaseDC(hWnd, hdc);

		return 0;


	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		bNowDraw = TRUE;

		
		return 0;


	case WM_MOUSEMOVE:
		if (bNowDraw == TRUE)
		{
			hdc = GetDC(hWnd);
			hMemDC = CreateCompatibleDC(hdc);

			OldBitmap = (HBITMAP)SelectObject(hMemDC, hBit);

			MoveToEx(hdc, x, y, NULL);
			MoveToEx(hMemDC, x, y, NULL);

			x = LOWORD(lParam);
			y = HIWORD(lParam);
			LineTo(hdc, x, y);
			LineTo(hMemDC, x, y);

			SelectObject(hMemDC, OldBitmap);
			DeleteDC(hMemDC);

			ReleaseDC(hWnd, hdc);

		}
		return 0;


	case WM_LBUTTONUP:
		bNowDraw = FALSE;

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		hMemDC = CreateCompatibleDC(hdc);
		OldBitmap = (HBITMAP)SelectObject(hMemDC, hBit);

		BitBlt(hdc, 0, 0, 1024, 768, hMemDC, 0, 0, SRCCOPY);

		SelectObject(hMemDC, OldBitmap);
		DeleteDC(hMemDC);

		EndPaint(hWnd, &ps);

		return 0;

	case WM_DESTROY:
		DeleteObject(hBit);
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // 코드만


#endif // Total