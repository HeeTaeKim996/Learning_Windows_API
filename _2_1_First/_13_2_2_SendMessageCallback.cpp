#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	앞선 메세지 데드락과 관련한 추가 코드입니다.
	앞선 장에서 다 처리하려 했는데, 괜히 코드 복잡해 보일 것 같아 따로 적었습니다.

	앞장 내용이 훨씬 중요하니, 그것만 봐도 충분할 것 같습니다. PostMessage로 웬만함 해결되지 않을까 싶습니다
----------------------------------------------------------------------------------------------------*/


#if 1 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LockProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;

LPCTSTR lpszClass = TEXT("Learning_SendMEssgaeCallback");
LPCTSTR lockClass = TEXT("LockClass");

HWND hWndMain;


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
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_VREDRAW | CS_HREDRAW;


	int inputNumber = atoi(lpszCmdParam);
	LPCTSTR registerClass;
	int xPos, yPos;
	switch (inputNumber)
	{
	case 1:
		WndClass.lpfnWndProc = WndProc;
		WndClass.lpszClassName = lpszClass;
		registerClass = lpszClass;
		xPos = yPos = 100;

		break;

	case 2:
		WndClass.lpfnWndProc = LockProc;
		WndClass.lpszClassName = lockClass;
		registerClass = lockClass;
		xPos = 600;
		yPos = 100;

		break;

	default:
		MessageBox(NULL, TEXT("CMD 에서 정수 1 또는 2를 입력하여 시행하세요"), TEXT("알림"), MB_OK);
		return 0;
	}


	RegisterClass(&WndClass);

	hWnd = CreateWindow(registerClass, registerClass, WS_OVERLAPPEDWINDOW,
		xPos, yPos, 400, 300,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}


VOID CALLBACK SendAsyncProc(HWND, UINT uMessage, ULONG_PTR dwData, LRESULT lParam)
{
	MessageBox(hWndMain, TEXT("다른 윈도우에서 작업을 완료했습니다"), TEXT("sEND1"), MB_OK);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HWND hSend2;
	TCHAR Mes[128];
	static int time;

	switch (iMessage)
	{
	case WM_CREATE:
		time = 0;
		SetTimer(hWnd, 0, 1'000, NULL);
		return 0;

	case WM_TIMER:
		hdc = GetDC(hWnd);
		
		wsprintf(Mes, TEXT("%d 초 지났습니다"), ++time);
		TextOut(hdc, 100, 100, Mes, lstrlen(Mes));

		ReleaseDC(hWnd, hdc);

		return 0;

	case WM_LBUTTONDOWN:
		hSend2 = FindWindow(lockClass, NULL);
		if (hSend2)
		{
			SendMessageCallback(hSend2, WM_USER + 1, 0, 0, SendAsyncProc, NULL);
		}
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}



LRESULT CALLBACK LockProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_USER + 1:
		MessageBox(hWnd, TEXT("OK를 누르면, 작업이 끝난 처리 됩니다"), TEXT("알림"), MB_OK);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}


#endif // 주석




#endif // Total