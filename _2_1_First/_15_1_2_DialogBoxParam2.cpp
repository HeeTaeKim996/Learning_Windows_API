#if 1 // Total
/*----------------------------------------------------------------------------------------------------
	DialogBoxParam 을 사용하는 다른 예시입니다. 특별한 내용 없이 전장의 내용과 동일합니다
----------------------------------------------------------------------------------------------------*/


#if 1 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Sample_1");

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

struct tag_Str
{
	int x;
	int y;
	TCHAR str[128];
};
tag_Str Str[2];

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static tag_Str* str;

	switch (iMessage)
	{
	case WM_INITDIALOG:
		str = (tag_Str*)lParam;
		SetDlgItemText(hDlg, IDC_EDIT_15_1_2_3, str->str);
		SetDlgItemInt(hDlg, IDC_EDIT_15_1_2_1, str->x, FALSE);
		SetDlgItemInt(hDlg, IDC_EDIT_15_1_2_2, str->y, FALSE);
		return TRUE;

	case WM_COMMAND:

		switch (wParam)
		{
		case IDOK:
			GetDlgItemText(hDlg, IDC_EDIT_15_1_2_3, str->str, 128);
			str->x = GetDlgItemInt(hDlg, IDC_EDIT_15_1_2_1, NULL, FALSE);
			str->y = GetDlgItemInt(hDlg, IDC_EDIT_15_1_2_2, NULL, FALSE);

			EndDialog(hDlg, IDOK);
			return TRUE;

		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
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
		Str[0].x = 100;
		Str[0].y = 100;
		lstrcpy(Str[0].str, TEXT("String"));

		Str[1].x = 400;
		Str[1].y = 400;
		lstrcpy(Str[1].str, TEXT("문자열"));

		return 0;


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		for (int i = 0; i < sizeof(Str) / sizeof(Str[0]); i++)
		{
			TextOut(hdc, Str[i].x, Str[i].y, Str[i].str, lstrlen(Str[i].str));
		}

		EndPaint(hWnd, &ps);
		return 0;


	case WM_LBUTTONDOWN:
		if (DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_DIALOG_15_1_2), hWnd, DlgProc, (LPARAM)&Str[0]) == IDOK)
		{
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;


	case WM_RBUTTONDOWN:
		if (DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_DIALOG_15_1_2), hWnd, DlgProc, (LPARAM)&Str[1]) == IDOK)
		{
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));

}





#endif // 주석


#if 1 // 코드만


#endif // 코드만


#endif // Total