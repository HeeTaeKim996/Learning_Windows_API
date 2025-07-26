#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	앞선 장의 서브에딧과 비슷하지만, GWLP 가 아닌 GCLP_WNDPROC 입니다.
	GCLP 로 하면, 해당 WND 가 교체되는 게 아니라, 해당 WND와 동일한 클래스 의 WND가 지정한 함수로 교체됩니다.
	( !! 해당 WND 의 WNDPROC은 교체되지 않습니다. 앞.으.로. 만들어질 동일한 클래스의 WND 의 WNDPROC이 
	  자동으로 교체됩니다 )

	※ 만들면서 위 적은 내용 외에 원리를 모르겠음. OldProc은 정의한 WND의 WNDPROC일텐데, 교체하는 함수의 
	  리턴값은 OldProc임. 그렇다면 hEdit2의 타이핑 내용이 hEdit1 으로 가야하는 게 아닌가 라고 생각했는데
	  돌려보면 hEdit2에 잘 적혀짐. 타이핑 하는 내용은, WNDPROC 에서 처리하는 게 아닌건가 싶음
	
----------------------------------------------------------------------------------------------------*/


#if 1 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_GCLP_WNDPROC");

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


#define ID_EDIT1 100
#define ID_EDIT2 101
#define ID_EDIT3 102

HWND hEdit1, hEdit2, hEdit3;
WNDPROC OldEditProc;

LRESULT CALLBACK EditSubProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			MessageBox(hWnd, TEXT("서브에딧 클래스"), TEXT("알림"), MB_OK);
			break;
		}
	}

	return CallWindowProc(OldEditProc, hWnd, iMessage, wParam, lParam);
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	

	switch (iMessage)
	{
	case WM_CREATE:
		hEdit1 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 10, 200, 25,
			hWnd, (HMENU)ID_EDIT1, g_hInst, NULL);

		OldEditProc = (WNDPROC)SetClassLongPtr(hEdit1, GCLP_WNDPROC, (LONG_PTR)EditSubProc);

		hEdit2 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 50, 200, 25,
			hWnd, (HMENU)ID_EDIT2, g_hInst, NULL);
		
		hEdit3 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 90, 200, 25,
			hWnd, (HMENU)ID_EDIT3, g_hInst, NULL);

		SetFocus(hEdit1);

		return 0;

	case WM_DESTROY:
		SetClassLongPtr(hEdit1, GCLP_WNDPROC, (LONG_PTR)OldEditProc);
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석


#endif // Total