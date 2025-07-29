#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	LBS_ADDSTRING, LBS_DELETESTRING �� ���� �ڵ��Դϴ�. ������ �����ߴ� ���� �ݺ��Դϴ�. 
----------------------------------------------------------------------------------------------------*/


#if 1 // �ּ�
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
#define ID_EDIT 101
#define ID_BTNADD 102
#define ID_BTNDELETE 103

HWND hList, hEdit, hBtnAdd, hBtnDelete;


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int index;
	TCHAR str[128];
	

	switch (iMessage)
	{
	case WM_CREATE:
		hList = CreateWindow(TEXT("listbox"), NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_SORT | LBS_NOTIFY,
			10, 10, 100, 200,
			hWnd, (HMENU)ID_LISTBOX, g_hInst, NULL);
		hEdit = CreateWindow(TEXT("edit"), NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			120, 10, 100, 25,
			hWnd, (HMENU)ID_EDIT, g_hInst, NULL);
		hBtnAdd = CreateWindow(TEXT("button"), TEXT("Add String"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			120, 50, 100, 25,
			hWnd, (HMENU)ID_BTNADD, g_hInst, NULL);
		hBtnDelete = CreateWindow(TEXT("button"), TEXT("Delete String"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			120, 80, 100, 25,
			hWnd, (HMENU)ID_BTNDELETE, g_hInst, NULL);
		
		return 0;


	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_BTNADD:
			SendMessage(hEdit, WM_GETTEXT, (WPARAM)128, (LPARAM)str);
			if (lstrlen(str))
			{
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)str);
			}
			break;

		case ID_BTNDELETE:
			index = SendMessage(hList, LB_GETCURSEL, 0, 0);
			if (index == LB_ERR)
			{
				MessageBox(hWnd, TEXT("���õ� �׸��� �����ϴ�"), TEXT("����"), MB_OK);
			}
			else
			{
				SendMessage(hList, LB_DELETESTRING, (WPARAM)index, 0);
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





#endif // �ּ�


#endif // Total