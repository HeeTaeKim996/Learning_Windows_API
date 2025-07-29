#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	ColDial 에 대한 코드입니다. Windows.h 에서 제공하는 타입 및 함수입니다.
----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_ColDial");

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



COLORREF Color = RGB(0, 0, 255);

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH MyBrush, OldBrush;
	CHOOSECOLOR COL;
	static COLORREF crTemp[16];
	

	switch (iMessage)
	{
	case WM_CREATE:
		for (int i = 0; i < 16; i++)
		{
			crTemp[i] = RGB(0, 0, i * 8 + 128);
		}
		return 0;

	case WM_LBUTTONDOWN:
		memset(&COL, 0, sizeof(CHOOSECOLOR));
		COL.lStructSize = sizeof(CHOOSECOLOR);
		COL.hwndOwner = hWnd;
		COL.lpCustColors = crTemp;
		if (ChooseColor(&COL) != 0)
		{
			Color = COL.rgbResult;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		MyBrush = CreateSolidBrush(Color);
		OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);
		Rectangle(hdc, 10, 10, 300, 200);
		
		DeleteObject(SelectObject(hdc, OldBrush));

		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
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

COLORREF Color = RGB(0, 0, 255);


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH MyBrush, OldBrush;
	CHOOSECOLOR COL;
	static COLORREF crTemp[16];



	switch (iMessage)
	{
	case WM_CREATE:
		for (int i = 0; i < 16; i++)
		{
			crTemp[i] = RGB(0, 0, i * 8 + 128);
		}
		return 0;

	case WM_LBUTTONDOWN:
		memset(&COL, 0, sizeof(CHOOSECOLOR));
		COL.lStructSize = sizeof(CHOOSECOLOR);
		COL.hwndOwner = hWnd;
		COL.lpCustColors = crTemp;
		if (ChooseColor(&COL) != 0)
		{
			Color = COL.rgbResult;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		MyBrush = CreateSolidBrush(Color);
		OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);
		Rectangle(hdc, 10, 10, 300, 200);

		DeleteObject(SelectObject(hdc, OldBrush));

		EndPaint(hWnd, &ps);
		return 0;

		
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;


		
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // 코드만


#endif // Total