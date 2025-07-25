#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	ScreenToClient, AdjustWindowRect에 대한 코드입니다.

	○ ScreenToClient	: 디스플레이 화면 기준 좌표를, 할당한 HWND의 ClientRect 좌표로 반환
	    -> 아래 코드에서 ScreenToClient가 있는 'Q'  는 커서에 정확히 원을 그리지만,
		   ScreenToClient 가 없는 W는 커서에 원을 그리지 않음. 만약 HWND의 좌표를 0, 0 으로 바꿔서 
		   W를 써보면, 메뉴바 높이만큼 커서의 Y아래로 원이 그려짐
		   
	○ AdjustWindowRect	: MoveWindow, SetWindowPos 의 경우, 메뉴바, 테두리? 두께 등은 고려하지 않고 
	                      ClientRect를 조정.
						  AdjustWindowRect는 할당한 RECT를, 메뉴바 유무, 테두리? 두께 등을 고려하여,
						  RECT를 조정하여 RECT 를 변환하는 함수
						  AdjustWondowRect로 rect를 조정후, MoveWindow 또는 SetWindowPos로 적용 필요

----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
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
	RECT crt;

	switch (iMessage)
	{
	case WM_CREATE:
		SetRect(&crt, 0, 0, 900, 600);
		AdjustWindowRect(&crt, WS_OVERLAPPEDWINDOW, FALSE);
		SetWindowPos(hWnd, NULL, 0, 0, crt.right - crt.left, crt.bottom - crt.top,
			SWP_NOMOVE | SWP_NOZORDER);
		
		return 0;
		
	
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Ellipse(hdc, 0, 0, 900, 600);
		EndPaint(hWnd, &ps);
		return 0;


	case WM_KEYDOWN:
		switch (wParam)
		{
			POINT pt;

		case 'Q':
			hdc = GetDC(hWnd);

			GetCursorPos(&pt);

			ScreenToClient(hWnd, &pt);
			Ellipse(hdc, pt.x - 5, pt.y - 5, pt.x + 5, pt.y + 5);

			ReleaseDC(hWnd, hdc);

			break;


		case 'W':
			hdc = GetDC(hWnd);

			GetCursorPos(&pt);

			Ellipse(hdc, pt.x - 5, pt.y - 5, pt.x + 5, pt.y + 5);

			ReleaseDC(hWnd, hdc);

			break;
		}
		
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


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT crt;


	switch (iMessage)
	{
	case WM_CREATE:
		SetRect(&crt, 0, 0, 900, 600);
		AdjustWindowRect(&crt, WS_OVERLAPPEDWINDOW, FALSE);
		SetWindowPos(hWnd, NULL, 0, 0, crt.right - crt.left, crt.bottom - crt.top,
			SWP_NOMOVE | SWP_NOZORDER);

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Ellipse(hdc, 0, 0, 900, 600);
		EndPaint(hWnd, &ps);
		return 0;


	case WM_KEYDOWN:
		switch (wParam)
		{
			POINT pt;

		case 'Q':
			hdc = GetDC(hWnd);

			GetCursorPos(&pt);
			
			ScreenToClient(hWnd, &pt);
			Ellipse(hdc, pt.x - 5, pt.y - 5, pt.x + 5, pt.y + 5);

			ReleaseDC(hWnd, hdc);

			break;

		case 'W':
			hdc = GetDC(hWnd);

			GetCursorPos(&pt);

			Ellipse(hdc, pt.x - 5, pt.y - 5, pt.x + 5, pt.y + 5);

			ReleaseDC(hWnd, hdc);

			break;
		}

		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // 코드만


#endif // Total