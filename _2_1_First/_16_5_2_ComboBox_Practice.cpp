#if 1 // Total
/*----------------------------------------------------------------------------------------------------
	특별히 새로울 것 없는 콤보박스 연습용 코드입니다. 
	Dialog 가 아닌 콤보박스를 CreateWindow로 만든점, SetWindowLongPtr + GWLP_WNDPROC 으로 WndProc 가로채기? 등,
	기존에 배웠던 내용들을 재사용하는 코드입니다.

	새로운 건 하나 있는데, ChildWindowFromPoint로, 윈도우의 자식 윈도우를 좌표를 기준으로 리턴하는 함수입니다.

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







#define ID_COMBOBOX 100
WNDPROC OldEditProc;

LRESULT CALLBACK EditProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		if (wParam == VK_RETURN)
		{
			SendMessage(hWndMain, WM_USER + 1, 0, 0);
			return 0;
		}
		break;

	case WM_KEYUP:
	case WM_CHAR:
		if (wParam == VK_RETURN)
		{
			return 0;
		}
		break;

	}

	return CallWindowProc(OldEditProc, hWnd, iMessage, wParam, lParam);
}





LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR* Items[] = { TEXT("김치찌개"), TEXT("돈까스"), TEXT("감자탕"), TEXT("햄버거"), TEXT("빵") };

	static HWND hCombo;
	static HWND hEdit;
	static TCHAR str[128] = TEXT("메뉴를 선택해 주십시오");
	static TCHAR Food[128];

	POINT pt;


	switch (iMessage)
	{
	case WM_CREATE:
		hWndMain = hWnd;
		hCombo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,
			10, 10, 150, 200,
			hWnd, (HMENU)ID_COMBOBOX, g_hInst, NULL);
		for (int i = 0; i < 5; i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)Items[i]);
		}
		pt.x = pt.y = 5;

		hEdit = ChildWindowFromPoint(hCombo, pt); // ※ ChildWindowFromPoint : 좌표를 기준으로 해당되는 WND를 반환

		OldEditProc = (WNDPROC)SetWindowLongPtr(hEdit, GWLP_WNDPROC, (LONG_PTR)EditProc);

		return 0;


	case WM_USER + 1:
		GetWindowText(hCombo, Food, 128);
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_COMBOBOX:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				int i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
				SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)Food);
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			}
		}
		return 0;


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		wsprintf(str, TEXT("오늘 메뉴는 %s 입니다."), Food);
		TextOut(hdc, 10, 150, str, lstrlen(str));
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		SetWindowLongPtr(hEdit, GWLP_WNDPROC, (LONG_PTR)OldEditProc);
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석



#endif // Total