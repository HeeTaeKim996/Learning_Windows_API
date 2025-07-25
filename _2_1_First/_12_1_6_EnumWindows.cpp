#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	EnumWindows	에 대한 코드입니다.


	○ EnumWindows : 최상위 부모 HWND 들에게, (1) 함수를 호출. (2) 는 (1)함수에 들어갈 인자 LPARAM
----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_EnumWindows");

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





HWND hList;


BOOL CALLBACK MyEnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	TCHAR str[300];
	TCHAR Cap[255];
	RECT rt;

	GetWindowText(hWnd, Cap, 255);
	GetWindowRect(hWnd, &rt);
	wsprintf(str, TEXT("핸들 = 0x%x(%d), 캡션 = %s, 좌표 = (%d, %d, %d, %d)"),
		hWnd, hWnd, Cap, rt.left, rt.top, rt.right, rt.bottom);
	SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)str);

	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR* Mes = TEXT("윈도우 바닥을 왼쪽 마우스 버튼으로 클릭하면 윈도우 목록을 보여드릴게요.")
		TEXT("  (여기 텍스트를 클릭하세요. 하단은 리스트라, 마우스 좌클릭 해도 인식 못합니다)");

	switch (iMessage)
	{
	case WM_CREATE:
		hList = CreateWindow(TEXT("listbox"), NULL, 
			WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT | WS_VSCROLL,
			10, 10, 100, 200,
			hWnd, (HMENU)NULL, g_hInst, NULL);
		return 0;

	case WM_LBUTTONDOWN:
		SendMessage(hList, LB_RESETCONTENT, 0, 0);
		EnumWindows(MyEnumWindowsProc, NULL);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 5, 5, Mes, lstrlen(Mes));
		EndPaint(hWnd, &ps);
		return 0;

	case WM_SIZE:
		MoveWindow(hList, 0, 50, LOWORD(lParam), HIWORD(lParam) - 50, TRUE);
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
LPCTSTR lpszClass = TEXT("Learning_EnumWindows");

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

HWND hList;

BOOL CALLBACK MyEnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	TCHAR str[300];
	TCHAR Cap[255];
	RECT rt;

	GetWindowText(hWnd, Cap, 255);
	GetWindowRect(hWnd, &rt);
	wsprintf(str, TEXT("핸들 = 0x%x(%d), 캡션 = %s, 좌표 = (%d, %d, %d, %d)"),
		hWnd, hWnd, Cap, rt.left, rt.top, rt.right, rt.bottom);
	SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)str);

	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR* Mes = TEXT("윈도우 바닥을 왼쪽 마우스 버튼으로 클릭하면 윈도우 목록을 보여드릴게요.")
		TEXT("  (여기 텍스트를 클릭하세요. 하단은 리스트라, 마우스 좌클릭 해도 인식 못합니다)");

	switch (iMessage)
	{
	case WM_CREATE:
		hList = CreateWindow(TEXT("listbox"), NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT | WS_VSCROLL,
			10, 10, 100, 200,
			hWnd, (HMENU)NULL, g_hInst, NULL);
		return 0;

	case WM_LBUTTONDOWN:
		SendMessage(hList, LB_RESETCONTENT, 0, 0);
		EnumWindows(MyEnumWindowsProc, NULL);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 5, 5, Mes, lstrlen(Mes));
		EndPaint(hWnd, &ps);
		return 0;

	case WM_SIZE:
		MoveWindow(hList, 0, 50, LOWORD(lParam), HIWORD(lParam) - 50, TRUE);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // 코드만


#endif // Total