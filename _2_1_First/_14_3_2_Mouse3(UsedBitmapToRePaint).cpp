#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	Mouse 3 �����Դϴ�. 
	WM_PAINT �� ���� �����͸� ��Ʈ�� �� ����Ͽ� �׸��� ����Դϴ�. ���������� ���Ǵ� ����̶� �մϴ�.

	��Ʈ���� ����ҽ�, ������ �׸� �� �ֽ��ϴ�. HBITMAP �� ���� �޸� ����� �ֽ��ϴ�

	���� ��Ʈ�ʿ� ���� �ڼ��� ������ �����̶� �ϴ�, 
	�̹� �ڵ�� ' WM_PAINT �� ��Ʈ���� �̷��� ����ϴ±��� ' ��� �����Ͻø� �˴ϴ�.
----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
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





#endif // �ּ�


#if 1 // �ڵ常
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

#endif // �ڵ常


#endif // Total