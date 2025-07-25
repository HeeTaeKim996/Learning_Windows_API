#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	WndRgn 에 대한 코드입니다. 윈도우의 영역이 기본적으로 사각형인데, RGN을 수동으로 할당하면,
	사각형 외에 타원형 등 윈도우 영역을 커스텀할 수 있습니다

	○ HRGN	: RGN 영역
	○ SetWindowRgn
	 - (1) : 할당될 윈도우
	 - (2) : 할당할 RGN
	 - (3) : 적용후 다시 그릴지 여부
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
	UINT nHit;
	HRGN hWndRgn;

	switch (iMessage)
	{
	case WM_CREATE:
		hWndRgn = CreateEllipticRgn(0, 0, 200, 200); // ※ RGN 영역 할당
		SetWindowRgn(hWnd, hWndRgn, FALSE); // ※ HWND 에 RGN 영역 적용 
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		Ellipse(hdc, 0, 0, 199, 199);
		Rectangle(hdc, 40, 50, 160, 150);
		TextOut(hdc, 45, 90, TEXT("스페이스 종료"), 13);
		EndPaint(hWnd, &ps);

		return 0;

	case WM_NCHITTEST:
		nHit = DefWindowProc(hWnd, iMessage, wParam, lParam);
		if (nHit == HTCLIENT)
		{
			nHit = HTCAPTION;
		}
		return nHit;

	case WM_KEYDOWN:
		if (wParam == VK_SPACE)
		{
			DestroyWindow(hWnd);
		}
		return TRUE;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석


#endif // Total