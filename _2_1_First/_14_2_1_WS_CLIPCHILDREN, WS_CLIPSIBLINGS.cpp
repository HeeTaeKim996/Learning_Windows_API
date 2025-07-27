#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	○ 클리핑 영역
	WM_PAINT 의 영역은, InvalidateRect 로 무효화한 영역이 아니라,
	무효화 영역 & 갸새 영역(사용자 눈에 윈도우가 보이는 영역. 다른 윈도우에 가려질시, 가시영역이 아님)
	입니다. 무효영역 & 가시영역 을 클리핑 영역 이라 합니다

	○ WS_CLIPCHILDREN
	 - CreateWindow 에서 설정. WS_CLIPCHILDREN 시, 자식윈도우들을 클리핑영역에서 제외하여, WM_PAINT 때
	   자식 영역 부분은 WM_PAINT 에서 제외함
	   ( 아래 코드는 이와 관련된 코드 )
	
	○ WS_CLIPSIBLINGS
	 - WS_CLIPCHILDREN 만큼 사용되지는 않지만, 있다는 것만 알아두면 됨. 이름 그대로 형제 윈도우를
	   클리핑 영역에서 제외
----------------------------------------------------------------------------------------------------*/


#if 1 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Sample_2");
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
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_VREDRAW | CS_HREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, // ※ WS_CLIPCHILDREN
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
	HPEN hPen, OldPen;
	HBRUSH OldBrush;

	switch (iMessage)
	{
	case WM_CREATE:
		CreateWindow(TEXT("button"), TEXT("ChildButton"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			50, 50, 200, 100,
			hWnd, (HMENU)0, g_hInst, NULL);
		CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,
			50, 200, 200, 100,
			hWnd, (HMENU)1, g_hInst, NULL);
		CreateWindow(TEXT("edit"), TEXT("에디트 컨트롤입니다"), WS_CHILD | WS_VISIBLE | WS_BORDER,
			300, 120, 200, 80,
			hWnd, (HMENU)2, g_hInst, NULL);
		
		hWndMain = hWnd;
		
		return 0;

	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);
		OldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
		
		hPen = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
		OldPen = (HPEN)SelectObject(hdc, hPen);

		Ellipse(hdc, LOWORD(lParam) - 50, HIWORD(lParam) - 40, LOWORD(lParam) + 50, HIWORD(lParam) + 40);

		DeleteObject(SelectObject(hdc, OldPen));
		SelectObject(hdc, OldPen);

		SelectObject(hdc, OldBrush);

		ReleaseDC(hWnd, hdc);

		return 0;


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

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