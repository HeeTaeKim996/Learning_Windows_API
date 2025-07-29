#if 1 // Total
/*----------------------------------------------------------------------------------------------------
	리스트 박스의 일부 플래그에 대한 내용입니다. 이외에 내용은 이전에 공부한 ListBox 코드와 같습니다.

	- LBS_MULTICOLUMN		: 여러 열 사용
	- LB_SETCOLUMNWIDTH		: 열간격 설정

----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
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
const TCHAR* Items[] = { TEXT("Apple"), TEXT("Orange"), TEXT("Melon"), TEXT("Grape"), TEXT("Strawberry") };
HWND hList;


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[128];


	switch (iMessage)
	{
	case WM_CREATE:
		hList = CreateWindow(TEXT("listbox"), NULL, 
			WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_NOTIFY | LBS_MULTICOLUMN,
			10, 10, 800, 20,
			hWnd, (HMENU)ID_LISTBOX, g_hInst, NULL);
		SendMessage(hList, LB_SETCOLUMNWIDTH, 150, 0);
		for (int i = 0; i < sizeof(Items) / sizeof(Items[0]); i++)
		{
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)Items[i]);
		}
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_LISTBOX:

			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
			{
				{
					int i = SendMessage(hList, LB_GETCURSEL, 0, 0);
					SendMessage(hList, LB_GETTEXT, i, (LPARAM)str);

					SetWindowText(hWnd, str);
					break;
				}
			}

			}

			return 0;
		}

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));

}


#endif // 주석




#endif // Total