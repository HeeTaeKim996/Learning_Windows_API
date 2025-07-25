#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	ScreenToClient, AdjustWindowRect�� ���� �ڵ��Դϴ�.

	�� ScreenToClient	: ���÷��� ȭ�� ���� ��ǥ��, �Ҵ��� HWND�� ClientRect ��ǥ�� ��ȯ
	    -> �Ʒ� �ڵ忡�� ScreenToClient�� �ִ� 'Q'  �� Ŀ���� ��Ȯ�� ���� �׸�����,
		   ScreenToClient �� ���� W�� Ŀ���� ���� �׸��� ����. ���� HWND�� ��ǥ�� 0, 0 ���� �ٲ㼭 
		   W�� �Ẹ��, �޴��� ���̸�ŭ Ŀ���� Y�Ʒ��� ���� �׷���
		   
	�� AdjustWindowRect	: MoveWindow, SetWindowPos �� ���, �޴���, �׵θ�? �β� ���� ������� �ʰ� 
	                      ClientRect�� ����.
						  AdjustWindowRect�� �Ҵ��� RECT��, �޴��� ����, �׵θ�? �β� ���� ����Ͽ�,
						  RECT�� �����Ͽ� RECT �� ��ȯ�ϴ� �Լ�
						  AdjustWondowRect�� rect�� ������, MoveWindow �Ǵ� SetWindowPos�� ���� �ʿ�

----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
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





#endif // �ּ�


#if 1 // �ڵ常
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

#endif // �ڵ常


#endif // Total