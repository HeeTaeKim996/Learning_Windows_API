#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	FindWin, FindWinEx에 대한 코드입니다.

	○ FindWin	: 최상위 부모 HWND 만 검색. (1) 은 WndClass.lpszClassName 을 기준으로 검색
				  (2) 는 CreateWindow의 (2)항인 캡션 (윈도우 텍스트) 을 기준으로 검색

	○ FindWinEx	: 지정한 HWND (1) 의 자식들 만 검색. HWND (2)를 지정시, 그 HWND 다음 순서부터 Z순서 
	              기준으로 검색함. 그외에는 FindWin 과 동일
----------------------------------------------------------------------------------------------------*/


#if 1 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_FindWin");

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
	HWND hFirst;
	static HWND h1, h2, h3;
	

	switch (iMessage)
	{
	case WM_CREATE:
		h1 = CreateWindow(TEXT("button"), TEXT("버튼"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20, 20, 100, 25,
			hWnd, (HMENU)0, g_hInst, NULL);
		h2 = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
			20, 50, 100, 50,
			hWnd, (HMENU)1, g_hInst, NULL);
		h3 = CreateWindow(TEXT("edit"), TEXT("에디트"), WS_CHILD | WS_VISIBLE | WS_BORDER,
			20, 110, 100, 25,
			hWnd, (HMENU)2, g_hInst, NULL);
		return 0;


	case WM_LBUTTONDOWN:
		hFirst = FindWindow(NULL, TEXT("Learning_FindWin"));
		if (hFirst == NULL)
		{
			MessageBox(hWnd, TEXT("예제를 찾을 수 없습니다."), TEXT("알림"), MB_OK);
		}
		else
		{
			MessageBox(hWnd, TEXT("예제가 실행중입니다."), TEXT("알림"), MB_OK);
		}
		return 0;


	case WM_RBUTTONDOWN:
		hFirst = FindWindowEx(hWnd, NULL, TEXT("edit"), NULL);
		if (hFirst == NULL)
		{
			MessageBox(hWnd, TEXT("차일드 컨트롤이 없습니다."), TEXT("알림"), MB_OK);
		}
		else
		{
			MessageBox(hWnd, TEXT("차일드 컨트롤을 찾았습니다"), TEXT("알림"), MB_OK);
		}
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석



#endif // Total