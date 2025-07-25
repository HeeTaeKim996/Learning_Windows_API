#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	GetKeyState �� ���� �ڵ��Դϴ�.
	����Ƽ�� void Update ������ Input.GetKey.. �� �Է��� Ȯ���ϴµ�, ������ ������ GetKeyState�� ����ϴ�
	�ɱ�. 
	�ƹ�ư WM_KEYDOWN �� ���� �Է½� �޼����� ȣ��������, GetKeyState�� ȣ������� �ش� Ű�� ���ȴ��� �� 
	Ȯ���ϴ� �ڵ��Դϴ�.
----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
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
			/* �� & 0xF000 �� ���
			    - GetKeyDown ���� Ű���带 ������ ���� ���¸� �ǹ��ϴ� ��, �������� 4��° ��Ʈ�� 1~8 ������ ����
				- �� ���� 0xFFF �� Ű������ ��� ���¸� ��Ÿ��
				- ����� Caps �� ���� �� �� �ִµ�, ĸ���� ������ ���� �ҹ���/�빮�� �� ���������� �ٲ۴�.
				  ���������� ���� �� �ڵ忡�� & 0x8000 �� ���ָ�, �� �� �� ���ÿ� ������ ����, �ѹ������� �� ����
				  ( ��Ȯ�� ������ ������, �� - ��, �� - �� Ű�� ���ÿ� ������ ����, �ش� Ű���� ��� ���¿� 
				    �ִ� �� �ϴ� )
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





#endif // �ּ�


#if 1 // �ڵ常
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

#endif // �ڵ常


#endif // Total