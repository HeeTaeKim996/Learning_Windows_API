#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	윈도우가 하나의 DC 를 생성 때 할당하고, WM_DESTROY 때 파괴하는 방법입니다.
	WndClass.style 에서 CS_OWNDC 를 추가해야 합니다.

	그림 칠할 때마다 GetDC 를 하지 않아도 되므로 이점도 있지만, 
	화면의 그림이 전체적으로 자주 바뀌는 경우 지우는 비용도 크기 때문에 단점도 많습니다.

	현대에는 커먼 DC (아래내용), 프라이빗 DC (이전까지 했던 방식) 두 방법이 대부분 사용됩니다.
----------------------------------------------------------------------------------------------------*/


#if 1 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Sample_2");
HDC hdc;

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
	WndClass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC; // ※ CS_OWNDC
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
	PAINTSTRUCT ps;
	static HPEN hPen, OldPen;

	switch (iMessage)
	{
	case WM_CREATE:
		hdc = GetDC(hWnd); // 생성
		hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
		OldPen = (HPEN)SelectObject(hdc, hPen);
		return 0;


	case WM_PAINT:
		BeginPaint(hWnd, &ps);
		Rectangle(hdc, 10, 10, 200, 200);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		DeleteObject(SelectObject(hdc, OldPen)); // 삭제
		PostQuitMessage(0);
		return 0;


	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석


#endif // Total