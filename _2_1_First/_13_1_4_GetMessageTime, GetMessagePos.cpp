#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	GetMessageTime, GetMessagePos,
	GetDoubleClickTime, SM_CXDOUBLECLK, SM_CYDOUBLECLK 에 대한 코드입니다.
----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_TripleClick");


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



DWORD ct[5];
DWORD cp[5];

BOOL TestClicks(int n)
{
	if (n < 2 || n > 5) return FALSE;


	static DWORD dt = GetDoubleClickTime();
	static int dx = GetSystemMetrics(SM_CXDOUBLECLK);
	static int dy = GetSystemMetrics(SM_CYDOUBLECLK);
	/*	
		○ GetDoubleClickTime
		 - 더브를릭으로 인정할, 클릭간의 시차 상한값을 반환
	
	
		○ SM_CXDOUBLECLK vs SM_CYDOUBLECLK
		 - 더블클릭으로 인정할, (X, Y) 각각의 두 클릭 오차 상한값을 반환하는 플래그
	*/


	for (int i = 0; i < n - 1; i++)
	{
		if (ct[4 - i] - ct[4 - i - 1] > dt)							return FALSE;
		if(abs(LOWORD(cp[4 - i] - LOWORD(cp[4 - i - 1]))) > dx)		return FALSE;
		if (abs(HIWORD(cp[4 - i]) - HIWORD(cp[4 - i - 1])) > dy)	return FALSE;
	}

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR* Mes = TEXT("트리플 클릭 검출 테스트 프로그램");

	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		for (int i = 0; i < 4; i++)
		{
			ct[i] = ct[i + 1];
			cp[i] = cp[i + 1];
		}
		ct[4] = GetMessageTime(); // 메세지가 발생했을 때의 시간 ( unsigned long)
		cp[4] = GetMessagePos(); // ※ 메세지가 발생했을 때의 커서 Pos (unsigned long)

		if (TestClicks(3))
		{
			MessageBox(hWnd, TEXT("트리플 클릭이 검출되었습니다"), TEXT("알림"), MB_OK);
		}

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








#endif // 주석


#if 1 // 코드만
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_TripleClick");

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


DWORD ct[5];
DWORD cp[5];

BOOL TestClicks(int n)
{
	if (n < 2 || n > 5) return FALSE;

	static DWORD dt = GetDoubleClickTime();
	static int dx = GetSystemMetrics(SM_CXDOUBLECLK);
	static int dy = GetSystemMetrics(SM_CYDOUBLECLK);

	for (int i = 4; i > 4 - n + 1; i--)
	{
		if (ct[i] - ct[i - 1] > dt)							return FALSE;
		if (abs(LOWORD(cp[i]) - LOWORD(cp[i - 1])) > dx)	return FALSE;
		if (abs(HIWORD(cp[i]) - HIWORD(cp[i - 1])) > dy)		return FALSE;
	}

	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR* Mes = TEXT("트리플 클릭 검출 테스트 프로그램");

	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		for (int i = 0; i < 4; i++)
		{
			ct[i] = ct[i + 1];
			cp[i] = cp[i + 1];
		}
		ct[4] = GetMessageTime();
		cp[4] = GetMessagePos();

		if (TestClicks(3))
		{
			MessageBox(hWnd, TEXT("트리플 클릭이 검출됐습니다"), TEXT("알림"), MB_OK);
		}
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

#endif // 코드만


#endif // Total