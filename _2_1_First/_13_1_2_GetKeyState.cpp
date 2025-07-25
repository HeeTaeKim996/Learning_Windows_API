#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	GetKeyState 에 대한 코드입니다.
	유니티는 void Update 내에서 Input.GetKey.. 로 입력을 확인하는데, 윈도우 버전은 GetKeyState를 사용하는
	걸까. 
	아무튼 WM_KEYDOWN 은 문자 입력시 메세지를 호출하지만, GetKeyState는 호출시점에 해당 키가 눌렸는지 를 
	확인하는 코드입니다.
----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_GetKeyState");

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


#define ACC 2

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int x = 100, y = 100;
	static int delta = 1;
	BOOL bPress;
	RECT rt;

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 20, NULL);
		return 0;

	case WM_TIMER:
		bPress = FALSE;
		if (GetKeyState(VK_LEFT) & 0x8000) 
			/* ○ & 0xF000 와 토글
			    - GetKeyDown 에서 키보드를 눌렀을 때의 상태를 의미하는 건, 하위에서 4번째 비트의 1~8 까지의 숫자
				- 그 밑의 0xFFF 는 키보드의 토글 상태를 나타냄
				- 토글은 Caps 를 예로 들 수 있는데, 캡스를 눌렀다 때면 소문자/대문자 를 영구적으로 바꾼다.
				  마찬가지로 만약 이 코드에서 & 0x8000 을 없애면, 온 우 를 동시에 눌렀다 때면, 한방향으로 쭉 간다
				  ( 정확히 원리는 모르지만, 왼 - 우, 하 - 상 키를 동시에 눌렀다 때면, 해당 키들이 토글 상태에 
				    있는 듯 하다 )
			*/
		{
			x -= (delta / ACC);
			bPress = TRUE;
		}
		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			x += (delta / ACC);
			bPress = TRUE;
		}
		if (GetKeyState(VK_UP) & 0x8000)
		{
			y -= (delta / ACC);
			bPress = TRUE;
		}
		if (GetKeyState(VK_DOWN) & 0x8000)
		{
			y += (delta / ACC);
			bPress = TRUE;
		}

		
		if (bPress)
		{
			delta = min(delta + 1, ACC * 10);
			SetRect(&rt, x - 20, y - 40, x + 20, y + 40);
			InvalidateRect(hWnd, &rt, TRUE);
		}
		else
		{
			delta = 1;
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc, x, y, TEXT("#"), 1);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		KillTimer(hWnd, 1);
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
LPCTSTR lpszClass = TEXT("Learning_GetKeyState");

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

#define ACC 2
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int x = 100, y = 100;
	static int delta = 1;
	BOOL bPress;
	RECT rt;



	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 20, NULL);
		return 0;


	case WM_TIMER:
		bPress = FALSE;
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			x -= (delta / ACC);
			bPress = TRUE;
		}
		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			x += (delta / ACC);
			bPress = TRUE;
		}
		if (GetKeyState(VK_UP) & 0x8000)
		{
			y -= (delta / ACC);
			bPress = TRUE;
		}
		if (GetKeyState(VK_DOWN) & 0x8000)
		{
			y += (delta / ACC);
			bPress = TRUE;
		}

		if (bPress)
		{
			delta = min(delta + 1, ACC * 10);
			SetRect(&rt, x - 20, y - 40, x + 20, y + 40);
			InvalidateRect(hWnd, &rt, TRUE);
		}
		else
		{
			delta = 1;
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc, x, y, TEXT("#"), 1);
		
		EndPaint(hWnd, &ps);
		
		return 0;


	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // 코드만


#endif // Total