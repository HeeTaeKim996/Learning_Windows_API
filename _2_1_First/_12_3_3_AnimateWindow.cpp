#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	AnimateWindow에 대한 코드입니다. 애니매이션 작동은 안됩니다. 코드 잘못적은건지, 버전 차이인지, 
	쓸모 없는 기능 같아서 작동안해도 생략 했습니다.
----------------------------------------------------------------------------------------------------*/


#if 1 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_AnimWin");

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
	const TCHAR* Mes = TEXT("마우스 왼쪽 버튼을 누르시면 애니매이션을 볼 수 있습니다.");
	int xPos;

	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		ShowWindow(hWnd, SW_HIDE);

		xPos = (LOWORD(wParam) - 10) / 50;
		switch (xPos)
		{
		case 0:
			AnimateWindow(hWnd, 500, AW_SLIDE | AW_HOR_POSITIVE);
			break;

		case 1:
			AnimateWindow(hWnd, 500, AW_SLIDE | AW_HOR_NEGATIVE);
			break;

		case 2:
			AnimateWindow(hWnd, 500, AW_SLIDE | AW_VER_POSITIVE);
			break;

		case 3:
			AnimateWindow(hWnd, 500, AW_SLIDE | AW_VER_NEGATIVE);
			break;

		case 4:
			AnimateWindow(hWnd, 500, AW_SLIDE | AW_HOR_POSITIVE | AW_VER_POSITIVE);
			break;

		case 5:
			AnimateWindow(hWnd, 500, AW_SLIDE | AW_HOR_NEGATIVE | AW_VER_NEGATIVE);
			break;

		case 6:
			AnimateWindow(hWnd, 500, AW_BLEND);
			break;

		case7:
		default:
			AnimateWindow(hWnd, 500, AW_CENTER);
			break;
		}

		InvalidateRect(hWnd, NULL, TRUE);
		SetForegroundWindow(hWnd);
		
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc, 10, 10, Mes, lstrlen(Mes));
		
		for (int i = 10; i <= 360; i += 50)
		{
			Rectangle(hdc, i, 50, i + 50, 100);
		}

		EndPaint(hWnd, &ps);

		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
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


	switch (iMessage)
	{


	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // 코드만


#endif // Total