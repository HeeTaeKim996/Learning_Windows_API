#if 0 // Total
/*----------------------------------------------------------------------------------------------------

----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_Modeless_Dialog_Box");

HWND hWndMain;
HWND hMdlg;


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
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

	hWndMain = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWndMain, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		if (!IsWindow(hMdlg) || !IsDialogMessage(hMdlg, &Message))
			// ※ 1) hMdlg가 유효하지 않거나, 2) hMdlg가 유효해도, hMdlg의 메세지가 아니면, 아래 스코프 처리
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
	return (int)Message.wParam;
}

TCHAR str[128];
int x, y;

INT_PTR CALLBACK MlessDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		SetDlgItemText(hDlg, IDC_EDIT3, str);
		SetDlgItemInt(hDlg, IDC_EDIT1, x, FALSE);
		SetDlgItemInt(hDlg, IDC_EDIT2, y, FALSE);

		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCHANGE:
			GetDlgItemText(hDlg, IDC_EDIT3, str, 128);
			x = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE);
			y = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE);

			InvalidateRect(hWndMain, NULL, TRUE);

			return TRUE;

		case IDCANCEL:
		case IDCLOSE:
			DestroyWindow(hMdlg);
			hMdlg = NULL;
			return TRUE;
		}

		break;
	}

	return FALSE;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		x = y = 100;
		lstrcpy(str, TEXT("HiHarry"));

		return 0;

	case WM_LBUTTONDOWN:
		if (!IsWindow(hMdlg)) // ※ 인자 (1) 이 NULL 이면, FALSE, NULL 이 아니면 TRUE
		{
			hMdlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG9), hWnd, MlessDlgProc);
			ShowWindow(hMdlg, SW_SHOW); 
			// ※ SW_SHOW : nCmdShow 중 하나로, 현재 크기, 위치 그대로 보여줌
		}

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc, x, y, str, lstrlen(str));

		EndPaint(hWnd, &ps);

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
LPCTSTR lpszClass = TEXT("Learning_Modeless_Dialog_Box");

HWND hWndMain;
HWND hMdlg;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
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

	hWndMain = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWndMain, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		if (!IsWindow(hMdlg) || !IsDialogMessage(hMdlg, &Message))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
	return (int)Message.wParam;
}

TCHAR str[128];
int x, y;

INT_PTR CALLBACK MLessDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		SetDlgItemText(hDlg, IDC_EDIT3, str);
		SetDlgItemInt(hDlg, IDC_EDIT1, x, FALSE);
		SetDlgItemInt(hDlg, IDC_EDIT2, y, FALSE);

		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCHANGE:
			GetDlgItemText(hDlg, IDC_EDIT3, str, 128);
			x = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE);
			y = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE);

			InvalidateRect(hWndMain, NULL, TRUE);

			return TRUE;

		case IDCANCEL:
		case IDCLOSE:
			DestroyWindow(hMdlg);
			hMdlg = NULL;
			return TRUE;
		}

		break;
	}

	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		x = y = 100;
		lstrcpy(str, TEXT("HiHarry"));

		return 0;

	case WM_LBUTTONDOWN:
		if (!IsWindow(hMdlg))
		{
			hMdlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG9), hWnd, MLessDlgProc);
			ShowWindow(hMdlg, SW_SHOW);
		}

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc, x, y, str, lstrlen(str));

		EndPaint(hWnd, &ps);

		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // 코드만


#endif // Total