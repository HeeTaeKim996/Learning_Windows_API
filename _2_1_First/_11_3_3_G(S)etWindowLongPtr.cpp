#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	G(S)etWindowLongPtr에 대한 내용입니다.

	추후 _11_5, _12_3_2 에도 나오는데, G(S)etWindowLongPtr은 윈도우 의 특정 속성값을 설정/읽을 때에도 사용되며,
	WndClass.cbWndExtra > 0 일 때, 여유 공간을 thread_local 처럼 사용할 때에도 사용되는 함수입니다.
----------------------------------------------------------------------------------------------------*/


#if 1 // 주석
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
	const TCHAR* Mes = TEXT("마우스 좌우 버튼으로 최대화 버튼 토글");
	
	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
	{
		{
			LONG style = GetWindowLongPtr(hWnd, GWL_STYLE);
			style |= WS_MAXIMIZEBOX;
			SetWindowLongPtr(hWnd, GWL_STYLE, style);
			SendMessage(hWnd, WM_NCPAINT, 0, 0); // ※ WM_NCPAINT : 윈도우의 비클라이언트 영역을 다시 그리라는 요청
			
		}

		
		return 0;

	case WM_RBUTTONDOWN:
	{
		{
			LONG style = GetWindowLongPtr(hWnd, GWL_STYLE);
			style &= ~WS_MAXIMIZEBOX;
			SetWindowLongPtr(hWnd, GWL_STYLE, style);
			SendMessage(hWnd, WM_NCPAINT, 0, 0);
		}


		return 0;
	}


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 10, 10, Mes, lstrlen(Mes));
		EndPaint(hWnd, &ps);
		
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석



#endif // Total