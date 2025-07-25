#if 1 // Total
/*----------------------------------------------------------------------------------------------------
	WM_ACTIVAGTE, WM_ACTIVATEAPP 에 대한 코드입니다.
	공통적으로 윈도우가 활성화/비활성화될 때 발동됩니다.

	추후 공부할 WM_SETFOCUS (17장, 28장 예정) 와도 유사해보이는데,
	WM_ACTIVATE 는 윈도우가 활성화/비활성화될 때 발동,
	WM_SETFOCUS 는 키보드 입력 받을 수 있(없)게 될 때 발동
	의 차이가 있습니다.
	둘 모두 공통적으로 부모 윈도우에서 우선적으로 발동합니다.
----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK PopupProc(HWND, UINT, WPARAM, LPARAM);

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

	WndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	WndClass.lpfnWndProc = PopupProc;
	WndClass.lpszClassName = TEXT("PopupClass");
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
	static TCHAR Mes[128];
	static HWND hPopup;

	switch (iMessage)
	{
	case WM_CREATE:
		hPopup = CreateWindow(TEXT("PopupClass"), TEXT("팝업_윈도우"), 
			WS_POPUPWINDOW | WS_CAPTION | WS_VISIBLE,
			410, 100, 300, 300,
			hWnd, (HMENU)0, g_hInst, NULL);
		return 0;

	case WM_ACTIVATEAPP: 
		// ※ 어플리캐이션(최중부모 윈도우 또는 자식 중 하나만이라도..) 가 활성화/비활성화 될 때 발동
		if (wParam == TRUE)
		{
			ShowWindow(hPopup, SW_SHOWNOACTIVATE);
			// ※ SW_SHOWNOACTIVATE : 창은 보이지만(최소화안되지만), INACTIVATE 상태로 처리
		}
		else
		{
			ShowWindow(hPopup, SW_HIDE);
		}
		return 0;

	case WM_ACTIVATE: // ※ 해당 윈도우가 활성화/비활성화 될 때 발동
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			lstrcpy(Mes, TEXT("비활성화 상태입니다"));
		}
		else
		{
			lstrcpy(Mes, TEXT("저는 지금 활성화되어있습니다"));
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 10, Mes, lstrlen(Mes));
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}


LRESULT CALLBACK PopupProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static TCHAR Mes[128];

	switch (iMessage)
	{
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			lstrcpy(Mes, TEXT("비활성화 상태입니다"));
		}
		else
		{
			lstrcpy(Mes, TEXT("저는 지금 활성화되어있습니다"));
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 10, 10, Mes, lstrlen(Mes));
		EndPaint(hWnd, &ps);

		return 0;

	case WM_CLOSE:
		ShowWindow(hWnd, SW_HIDE);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}




#endif // 주석



#endif // Total