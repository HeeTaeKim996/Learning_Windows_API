#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	서브에딧 (GWLP 를 사용한) 에 대한 코드입니다.
	이미 만들어진 클래스 button, edit 등의 WNDPROC을 건들 수 없는데,
	WND들의 WNDPROC 처리전 가로채서, 검출 등을 하고, 기존 WNDPROC에 다시 메세지를 넘기는 방법입니다.

	아래 코드는 edit1, edit2 에 서브에딧 함수를 추가해서, Tab을 할시, WNDPROC 처리 전에, 
	사용자 정의 동작 (다른 WND 에 SetFocus 하기) 을 하도록 조작했습니다.

	○ GWLP_WNDPROC	: SetWindowLong의 플래그로, (1)항 WND 의 WNDPROC을 (3)항 함수로 바꾼다. 
					  리턴값이 OLD WNDPROC 이다.
					  -> (3)항 함수가 마지막에 리턴값으로 OldProc을 호출하여, 기존 WNDPROC 도 작동하도록 처리함
						
	※ WM_DESTROY 때 다시 SetWindowLong...( ..., GWL_WNDPROC, OldProc); 으로 WND의 기존 WNDPROC으로
	   다시 돌려주는데, 돌려주는 이유는 모르겠음.. 안정성 때문에 그러는듯
----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_SubEdit_SetWindowLongPtr");

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

HWND hEdit1;
WNDPROC OldEditProc1;

HWND hEdit2;
WNDPROC OldEditProc2;

LRESULT CALLBACK EditSubProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			MessageBox(hWnd, TEXT("Enter is Pressed"), TEXT("Edit"), MB_OK);
			SetFocus(hWnd);
			break;

		case VK_TAB:
			SetFocus(hEdit2);
			break;

		}
	}
	return CallWindowProc(OldEditProc1, hWnd, iMessage, wParam, lParam);
}

LRESULT CALLBACK EditSubProc2(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_TAB:
			SetFocus(hEdit1);
			break;

		}
	}
	return CallWindowProc(OldEditProc2, hWnd, iMessage, wParam, lParam);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR* Mes = TEXT("에디트의 Enter 키 입력을 검출합니다. Tab 키 도 검출합니다");

	switch (iMessage)
	{
	case WM_CREATE:
		hEdit1 = CreateWindow(TEXT("edit"), NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 10, 200, 25,
			hWnd, (HMENU)ID_EDIT1, g_hInst, NULL);
		hEdit2 = CreateWindow(TEXT("edit"), NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 50, 200, 25,
			hWnd, (HMENU)ID_EDIT2, g_hInst, NULL);
		SetFocus(hEdit1);

		OldEditProc1 = (WNDPROC)SetWindowLongPtr(hEdit1, GWLP_WNDPROC, (LONG_PTR)EditSubProc);
		OldEditProc2 = (WNDPROC)SetWindowLongPtr(hEdit2, GWLP_WNDPROC, (LONG_PTR)EditSubProc2);

		return 0;


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc, 10, 100, Mes, lstrlen(Mes));

		EndPaint(hWnd, &ps);

		return 0;

	case WM_DESTROY:
		SetWindowLongPtr(hEdit1, GWLP_WNDPROC, (LONG_PTR)OldEditProc1);
		SetWindowLongPtr(hEdit2, GWLP_WNDPROC, (LONG_PTR)OldEditProc2);
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석


#if 1 // 코드만
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_SubEdit_SetWindowLongPtr");

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

HWND hEdit1;
WNDPROC OldEditProc1;

HWND hEdit2;
WNDPROC OldEditProc2;


LRESULT CALLBACK EditSubProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			MessageBox(hWnd, TEXT("Enter is Pressed"), TEXT("Edit"), MB_OK);
			SetFocus(hWnd);
			break;
			
		case VK_TAB:
			SetFocus(hEdit2);
			break;
		}
	}

	return CallWindowProc(OldEditProc1, hWnd, iMessage, wParam, lParam);
}

LRESULT CALLBACK EditSubProc2(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_TAB:
			SetFocus(hEdit1);
			break;
		}	
	}
	return CallWindowProc(OldEditProc2, hWnd, iMessage, wParam, lParam);
}




LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR* Mes = TEXT("에디트의 Enter 키 입력을 검출합니다. Tab 키 도 검출합니다");


	switch (iMessage)
	{
	case WM_CREATE:
		hEdit1 = CreateWindow(TEXT("edit"), NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 10, 200, 25,
			hWnd, (HMENU)ID_EDIT1, g_hInst, NULL);
		hEdit2 = CreateWindow(TEXT("edit"), NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 50, 200, 25,
			hWnd, (HMENU)ID_EDIT2, g_hInst, NULL);
		SetFocus(hEdit1);

		OldEditProc1 = (WNDPROC)SetWindowLongPtr(hEdit1, GWLP_WNDPROC, (LONG_PTR)EditSubProc);
		OldEditProc2 = (WNDPROC)SetWindowLongPtr(hEdit2, GWLP_WNDPROC, (LONG_PTR)EditSubProc2);

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc, 10, 100, Mes, lstrlen(Mes));

		EndPaint(hWnd, &ps);

		return 0;

	case WM_DESTROY:
		SetWindowLongPtr(hEdit1, GWLP_WNDPROC, (LONG_PTR)OldEditProc1);
		SetWindowLongPtr(hEdit2, GWLP_WNDPROC, (LONG_PTR)OldEditProc2);
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // 코드만


#endif // Total