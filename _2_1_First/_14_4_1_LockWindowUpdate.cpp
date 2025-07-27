#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	LockWindowUpdate 에 대한 코드입니다.
	3D 모델링의 경우, 화면은 그리는데 연산량이 많기 때문에, 화면을 그리는 도중의 과정이 화면에 출력되면
	안됩니다.
	이를 방지하고자, LockWindowUpdate 를 사용합니다.

	LockWindowUpdate 의 인자로 HWND 를 넣으면, 해당 HWND 에 그림이 그려지지 않습니다.
	다시 LockWindowUpdate에 인자로 NULL 을 넣으면, 락을 잠갔던 HWND 가 있다면, 그 HWND의 락이 해제됩니다.
	

	아래 코드는 앞선 _14_3_2 의 Mouse3 코드에서, 단 2줄만을 추가한 코드입니다.
	WM_LMOUSEBUTTONDOWN 에서 LockWindowUpdate(hWnd); 
	WM_LMOUSEBUTTONUP 에서 LockWindowUpdate(NULL);
	이렇게 2줄만을 추가한 코드입니다.

----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_LockWindowUpdate");
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
		LockWindowUpdate(hWnd); // LockWindowUpdate

		return 0;


	case WM_MOUSEMOVE:
		if (bNowDraw)
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
		LockWindowUpdate(NULL); // LockWindowUpdate

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
LPCTSTR lpszClass = TEXT("Learning_LockWindowUpdate");
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
		LockWindowUpdate(hWnd);

		return 0;

	case WM_MOUSEMOVE:
		if (bNowDraw)
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
		LockWindowUpdate(NULL);

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