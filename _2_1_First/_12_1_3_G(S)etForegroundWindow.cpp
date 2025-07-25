#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	G(S)etForegroundWindow , SWP_TOPMOST 에 대한 코드입니다.
	
	SetForegroundWindow 로 특정 HWND를 포그라운드 윈도우로 설정합니다. (나머지 윈도우들은 백그라운드 )
	
	SWP_TOPMOST를 SetWindowPos로 설정시, 해당 HWND 는 최소화 또는 닫기 가 되지 않는 한,
	항상 Z순서의 최상위에 위치합니다.
----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_G(S)etForgroundWidnow");

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
	static HWND hNotePad;
	const TCHAR* Mes = TEXT("1:메모장 즉시 활성화, 2: 메모리 1초 후에 활성화,")
		TEXT("3: 1초후 스스로 활성화, 4: 1초후 메모장 SWP_TOPMOST 처리(최소화하지 않는 한 고정 TOPMOST)");

	switch (iMessage)
	{
	case WM_CREATE:
		hNotePad = FindWindow(TEXT("NotePad"), NULL);
		if (hNotePad == NULL)
		{
			MessageBox(NULL, TEXT("이 예제를 시행하기 전에 메모장을 먼저 실행하십시오."),
				TEXT("알림"), MB_OK);
			
			return -1;
		}
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case '1':
			SetForegroundWindow(hNotePad);
			break;

		case '2':
			SetTimer(hWnd, 2, 1'000, NULL);
			break;

		case '3':
			SetTimer(hWnd, 3, 1'000, NULL);
			break;

		case '4':
			SetTimer(hWnd, 4, 1'000, NULL);
		}
		return 0;

	case WM_TIMER:
		switch (wParam)
		{
		case 2:
			KillTimer(hWnd, 2);
			SetForegroundWindow(hNotePad);
			break;

		case 3:
			KillTimer(hWnd, 3);
			SetForegroundWindow(hWnd);
			break;

		case 4:
			KillTimer(hWnd, 4);
			SetWindowPos(hNotePad, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
			break;

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


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_G(S)etForgroundWidnow");

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
	static HWND hNotePad;
	const TCHAR* Mes = TEXT("1: 메모장 즉시 활성화,  2: 메모리 1초후에 활성화,  ")
		TEXT("3: 1초후 스스로 활성화,  4: 메모장 SWP_TOPMOST 처리(최소화하지 않는 한 고정 TOPMOST)");


	switch (iMessage)
	{
	case WM_CREATE:
		hNotePad = FindWindow(TEXT("notepad"), NULL);
		if(hNotePad == NULL)
		{
			MessageBox(NULL, TEXT("이 예제를 시행하기 전에 메모장을 먼저 실행하십시오"),
				TEXT("알림"), MB_OK);

			return -1;
		}
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case '1':
			SetForegroundWindow(hNotePad);
			break;

		case '2':
			SetTimer(hWnd, 2, 1'000, NULL);
			break;

		case '3':
			SetTimer(hWnd, 3, 1'000, NULL);
			break;

		case '4':
			SetWindowPos(hNotePad, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			break;
		}
		return 0;

	case WM_TIMER:
		switch (wParam)
		{
		case 2:
			KillTimer(hWnd, 2);
			SetForegroundWindow(hNotePad);
			break;

		case 3:
			KillTimer(hWnd, 3);
			SetForegroundWindow(hWnd);
			break;
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