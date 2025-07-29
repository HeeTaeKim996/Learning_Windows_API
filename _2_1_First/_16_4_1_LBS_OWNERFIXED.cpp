#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	�� LBS_OWNERDRAWFIXED
	 - ����Ʈ�ڽ��� ��Ҹ�, ���ڿ��� �ƴ� �׸� ���� �׸��� ���

	�� LBS_OWNERDRAWFIXED �̸�, LB_ADDSTRING ��, WM_MEASUREITEM, WM_DRAWITEM �� ȣ���

	�� WM_MEASUREITEM
	 - LB_ADDSTRING �� �ѹ� ȣ��ǰ� ȣ����� ����.
	 - LPMEASUREITEMSTRUCT �� itemHeight ��, ����Ʈ�ڽ� ����� ���� �� ����

	�� WM_DRAWITEM
	 - ����Ʈ ��Ҹ� �׸� ������ ȣ��
	 - LPARAM ���� �Ҵ��  LPDRAWITEMSTRUCT �� rcItem ����, �׸� ��ġ ������ ���� (�׿ܿ� ������ �ڵ� ����)
----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
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
HWND hList;
HBITMAP hbmp1, hbmp2, hbmp3;


void DrawBitmap(HDC hdc, int x, int y, int width, int height, HBITMAP hBit);

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	LPMEASUREITEMSTRUCT lpmis;
	LPDRAWITEMSTRUCT lpdis;
	HBITMAP hBmp;
	HBRUSH bkBrush;

	switch (iMessage)
	{
	case WM_CREATE:
		hList = CreateWindow(TEXT("listbox"), NULL, 
			WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_NOTIFY | LBS_OWNERDRAWFIXED,
			10, 10, 110, 200,
			hWnd, (HMENU)ID_LISTBOX, g_hInst, NULL);

		hbmp1 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_16_4_1));
		hbmp2 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_16_4_2));
		hbmp3 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_16_4_3));

		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)hbmp1);
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)hbmp2);
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)hbmp3);

		return 0;


	case WM_MEASUREITEM:
		lpmis = (LPMEASUREITEMSTRUCT)lParam;
		lpmis->itemHeight = 24;
		return TRUE;

	case WM_DRAWITEM:
		lpdis = (LPDRAWITEMSTRUCT)lParam;

		// ���� ��Ȳ�� ���� �Ķ��� ����� ����Ѵ�
		if (lpdis->itemState & ODS_SELECTED)
		{
			bkBrush = GetSysColorBrush(COLOR_HIGHLIGHT);
		}
		else
		{
			bkBrush = GetSysColorBrush(COLOR_WINDOW);
		}
		FillRect(lpdis->hDC, &lpdis->rcItem, bkBrush);


		// �׸� �����ͷκ��� ��Ʈ�� �ڵ��� �о� ����Ѵ�
		hBmp = (HBITMAP)lpdis->itemData;
		DrawBitmap(lpdis->hDC, lpdis->rcItem.left + 5, lpdis->rcItem.top + 2, lpdis->rcItem.right - lpdis->rcItem.left,
			lpdis->rcItem.bottom - lpdis->rcItem.top, hBmp);
		return TRUE;

	case WM_DESTROY:
		DeleteObject(hbmp1);
		DeleteObject(hbmp2);
		DeleteObject(hbmp3);
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}


void DrawBitmap(HDC hdc, int x, int y, int width, int height, HBITMAP hBit)
{
	HDC MemDC = CreateCompatibleDC(hdc);
	HBITMAP OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);
	BITMAP bit;
	GetObject(hBit, sizeof(BITMAP), &bit);

	StretchBlt(hdc, x, y, width, height, MemDC, 0, 0, bit.bmWidth, bit.bmHeight, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}


#endif // �ּ�


#if 1 // �ڵ常
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
HWND hList;
HBITMAP hbmp1, hbmp2, hbmp3;


void DrawBitmap(HDC hdc, int x, int y, int width, int height, HBITMAP hBit);


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	LPMEASUREITEMSTRUCT lpmis;
	LPDRAWITEMSTRUCT lpdis;
	HBITMAP hBmp;
	HBRUSH bkBrush;


	switch (iMessage)
	{
	case WM_CREATE:
		hList = CreateWindow(TEXT("listbox"), NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_NOTIFY | LBS_OWNERDRAWFIXED,
			10, 10, 110, 200,
			hWnd, (HMENU)ID_LISTBOX, g_hInst, NULL);

		hbmp1 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_16_4_1));
		hbmp2 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_16_4_2));
		hbmp3 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_16_4_3));

		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)hbmp1);
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)hbmp2);
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)hbmp3);

		return 0;




	case WM_MEASUREITEM:
		lpmis = (LPMEASUREITEMSTRUCT)lParam;
		lpmis->itemHeight = 24;
		return TRUE;

	case WM_DRAWITEM:
		lpdis = (LPDRAWITEMSTRUCT)lParam;

		if (lpdis->itemState & ODS_SELECTED)
		{
			bkBrush = GetSysColorBrush(COLOR_HIGHLIGHT);
		}
		else
		{
			bkBrush = GetSysColorBrush(COLOR_WINDOW);
		}
		FillRect(lpdis->hDC, &lpdis->rcItem, bkBrush);

		hBmp = (HBITMAP)lpdis->itemData;
		DrawBitmap(lpdis->hDC, lpdis->rcItem.left + 5, lpdis->rcItem.top + 2, lpdis->rcItem.right - lpdis->rcItem.left,
			lpdis->rcItem.bottom - lpdis->rcItem.top, hBmp);
		return TRUE;

	case WM_DESTROY:
		DeleteObject(hbmp1);
		DeleteObject(hbmp2);
		DeleteObject(hbmp3);
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void DrawBitmap(HDC hdc, int x, int y, int width, int height, HBITMAP hBit)
{
	HDC MemDC = CreateCompatibleDC(hdc);
	HBITMAP OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);
	BITMAP bit;
	GetObject(hBit, sizeof(BITMAP), &bit);

	StretchBlt(hdc, x, y, width, height, MemDC, 0, 0, bit.bmWidth, bit.bmHeight, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}

#endif // �ڵ常


#endif // Total