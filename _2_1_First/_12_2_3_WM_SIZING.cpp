#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	WM_SIZING �ڵ� ���� �����Դϴ�. 
	WM_SIZING�� ũ�� �����߿� �ߵ�, WM_SIZE �� ���� �Ϸ��� �ߵ�. �׿ܿ� ���� �����ϴ�.
----------------------------------------------------------------------------------------------------*/


#if 1 // �ּ�
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


const TCHAR* Items[] = { TEXT("Apple"), TEXT("Orange"), TEXT("Melon"), TEXT("Grape"), TEXT("Strawberry") };
HWND hList;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	RECT crt;

	switch (iMessage)
	{
	case WM_CREATE:
		hList = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT,
			0, 0, 0, 0,
			hWnd, (HMENU)NULL, g_hInst, NULL);
		for (int i = 0; i < 5; i++)
		{
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)Items[i]);
		}

		return 0;

	case WM_SIZE:
		GetClientRect(hWnd, &crt);
		MoveWindow(hList, crt.left, crt.top, crt.right, crt.bottom, TRUE);
		return 0;

	case WM_SIZING: // �� WM_SIZE�� ���� �Ϸ���. WM_SIZING �� ������ �ߵ�
		if (wParam == WMSZ_LEFT)
		{
			((RECT*)lParam)->left = ((RECT*)lParam)->left / 100 * 100;
			return 1;
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // �ּ�




#endif // Total