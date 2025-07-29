#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	LBS 다중선택 관련 코드입니다.

	LBS_GETSELCOUNT, LBS_GETSELITEMS  가 새로 사용됐습니다.
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



#define ID_LISTBOX 100
#define ID_BTNADD 101
#define ID_BTNDELETE 102
HWND hList, hBtnAdd, hBtnDelete;

const TCHAR* data[] = { TEXT("하나"), TEXT("둘"), TEXT("셋"), TEXT("넷"), TEXT("다섯") };


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int buffer[100];

	switch (iMessage)
	{
	case WM_CREATE:
		hList = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_MULTIPLESEL,
			10, 10, 200, 300,
			hWnd, (HMENU)ID_LISTBOX, g_hInst, NULL);
		hBtnAdd = CreateWindow(TEXT("button"), TEXT("Reset"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			220, 50, 100, 25,
			hWnd, (HMENU)ID_BTNADD, g_hInst, NULL);
		hBtnDelete = CreateWindow(TEXT("button"), TEXT("Remove Strings"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			220, 80, 100, 25,
			hWnd, (HMENU)ID_BTNDELETE, g_hInst, NULL);

		return 0;


	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_BTNADD:
			SendMessage(hList, LB_RESETCONTENT, 0, 0);
			for (int i = 0; i < 5; i++)
			{
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)data[i]);
			}
			break;

		case ID_BTNDELETE:
			int num = SendMessage(hList, LB_GETSELCOUNT, 0, 0);
			if (num != 0)
			{
				SendMessage(hList, LB_GETSELITEMS, 100, (LPARAM)buffer);
				for (int i = num - 1; i > -1; i--)
				{
					SendMessage(hList, LB_DELETESTRING, buffer[i], 0);
				}
			}
			break;
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