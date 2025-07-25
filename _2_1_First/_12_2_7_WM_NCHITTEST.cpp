#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	WM_NCHITTEST 에 대한 코드입니다.


	○ WM_NCHITTEST
	 - 클릭, 이동, 드래그 등 커서 작업시 발동
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
	RECT crt;
	const TCHAR* Mes = TEXT("WM_NCHITTEST 메세지를 활용하는 예제입니다");

	switch (iMessage)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &crt);
		for (int i = 50; i > 0; i -= 5)
		{
			MoveToEx(hdc, crt.right, crt.bottom - i, NULL);
			LineTo(hdc, crt.right - i, crt.bottom);
		}
		TextOut(hdc, 10, 10, Mes, lstrlen(Mes));
		EndPaint(hWnd, &ps);

		return 0;

	case WM_NCHITTEST:
		GetClientRect(hWnd, &crt);
		
		POINT mpt;
		mpt.x = LOWORD(lParam);
		mpt.y = HIWORD(lParam);
		
		ScreenToClient(hWnd, &mpt);

		int nHit;
		if (mpt.y > -mpt.x - 50 + crt.right + crt.bottom) // ※ Y의 음양이 반대이므로, X축 반전 그래프 생각
		{
			nHit = HTBOTTOMRIGHT; 
			// ※ 위 MoveToEx - LineTo 로 표시한 영역 클릭시, HTBOTTOMRIGHT 로 간주하여 크기 조절 가능하게 함
		}
		else
		{
			nHit = DefWindowProc(hWnd, iMessage, wParam, lParam);
		}

		return nHit;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석


#endif // Total