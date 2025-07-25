#if 0 // Total
/*----------------------------------------------------------------------------------------------------

----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
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
			// �� 1) hMdlg�� ��ȿ���� �ʰų�, 2) hMdlg�� ��ȿ�ص�, hMdlg�� �޼����� �ƴϸ�, �Ʒ� ������ ó��
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
		if (!IsWindow(hMdlg)) // �� ���� (1) �� NULL �̸�, FALSE, NULL �� �ƴϸ� TRUE
		{
			hMdlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG9), hWnd, MlessDlgProc);
			ShowWindow(hMdlg, SW_SHOW); 
			// �� SW_SHOW : nCmdShow �� �ϳ���, ���� ũ��, ��ġ �״�� ������
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





#endif // �ּ�


#if 1 // �ڵ常
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

#endif // �ڵ常


#endif // Total