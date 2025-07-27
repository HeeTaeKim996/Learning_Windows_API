#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	WM_NCPAINT 에 대한 코드입니다.
	앞선 장에서 설명했듯, BeginPaint의 5작업중, 마지막 작업에 WM_NCPAINT 가 호출됩니다.
	WM_NCPAINT로 비작업영역(타이틀바, 테두리 등) 을 그립니다.
	
	아래 코드는 비작업영역을 수동으로 그리는 코드인데, 교재에서는 테두리가 두껍게 빨간색으로 칠해진 반면,
	시행해보면 아주 얇은 빨간색 테두리가 칠해집니다.
	(원인은 모름)

	WM_NCPAINT를 실제로 사용할 가능성은 없고, 요즘은 팝업 윈도우 사용 + 디자이너가 그린 이미지 사용
	으로 대부분 처리합니다. 


	개념적으로, ' BeginPaint의 마지막 작업 때  WM_NCPAINT가 호출되어, 비작업영역을 그린다 '
	라는 것만 이해하면 됩니다.
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
	RECT wrt;
	HPEN hPen, OldPen;


	switch (iMessage)
	{
	case WM_NCPAINT:
		DefWindowProc(hWnd, iMessage, wParam, lParam);
		hdc = GetWindowDC(hWnd);


		GetWindowRect(hWnd, &wrt);
		hPen = CreatePen(PS_INSIDEFRAME, 1500, RGB(255, 0, 0));
		OldPen = (HPEN)SelectObject(hdc, hPen);
		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		Rectangle(hdc, 0, 0, wrt.right - wrt.left, wrt.bottom - wrt.top);
		DeleteObject(SelectObject(hdc, OldPen));
		
		ReleaseDC(hWnd, hdc);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석



#endif // Total