#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	펜으로 그리기 버전 2 입니다.
	WM_PAINT에서 그릴 데이터를 어떻게 저장할 지 에 대한 원초적인 코드입니다.
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




struct
{
	int x, y;
	BOOL Move;
} Line[10'000];

int index = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static BOOL bNowDraw = FALSE;


	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		bNowDraw = TRUE;
		Line[index].x = LOWORD(lParam);
		Line[index].y = HIWORD(lParam);
		Line[index].Move = TRUE;
		index++;

		return 0;

	case WM_MOUSEMOVE:
		if (bNowDraw == TRUE)
		{
			hdc = GetDC(hWnd);

			MoveToEx(hdc, Line[index - 1].x, Line[index - 1].y, NULL);
			Line[index].x = LOWORD(lParam);
			Line[index].y = HIWORD(lParam);
			Line[index].Move = FALSE;
			LineTo(hdc, Line[index].x, Line[index].y);
			index++;
			
			ReleaseDC(hWnd, hdc);
		}
		return 0;


	case WM_LBUTTONUP:
		bNowDraw = FALSE;
		return 0;

	case WM_RBUTTONDOWN:
		index = 0;
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		for (int i = 0; i < index; i++)
		{
			if (Line[i].Move == TRUE)
			{
				MoveToEx(hdc, Line[i].x, Line[i].y, NULL);
			}
			else
			{
				LineTo(hdc, Line[i].x, Line[i].y);
			}
		}

		EndPaint(hWnd, &ps);
		return 0;

		
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석




#endif // Total