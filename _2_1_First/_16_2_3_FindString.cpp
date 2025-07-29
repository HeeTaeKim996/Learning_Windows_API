#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	■ LB_FINDSTRING, LB_FINDEXACT, LB_SELECTSTRING 에 대한 코드입니다

	 - LB_FINDSTRING	: 해당 문자열의 앞부분과 일치하는 문자를 검색하여, 인덱스 반환
	 - LB_FINDEXACT		: 정확히 해당 문자열인 문자를 검색하여, 인덱스 반환
	 - LB_SELECTSTRING	: 해당 문자열의 앞부분과 일치하는 문자를 검색하여, 해당 인덱스로 SetCursel 처리
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




const TCHAR* Items[] = { TEXT("Harry"), TEXT("Hack"), TEXT("Bori") };

INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[128];

	switch (iMessage)
	{
	case WM_INITDIALOG:
		for (int i = 0; i < sizeof(Items) / sizeof(Items[0]); i++)
		{
			SendDlgItemMessage(hDlg, IDC_LIST_16_3_1, LB_ADDSTRING, 0, (LPARAM)Items[i]);
		}
		return TRUE;


	case WM_COMMAND:
		GetWindowText(GetDlgItem(hDlg, IDC_EDIT_16_3_1), str, 128);
		int idx = SendDlgItemMessage(hDlg, IDC_LIST_16_3_1, LB_GETCURSEL, 0, 0);

		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;

		case IDC_BUTTON_Find:
			idx = SendDlgItemMessage(hDlg, IDC_LIST_16_3_1, LB_FINDSTRING, idx, (LPARAM)str);
			SendDlgItemMessage(hDlg, IDC_LIST_16_3_1, LB_SETCURSEL, idx, 0); // WPARAM 에 idx 넣으면, 해당 idx 이후부터 검색
			return TRUE;

		case IDC_BUTTON_FindExact:
			idx = SendDlgItemMessage(hDlg, IDC_LIST_16_3_1, LB_FINDSTRINGEXACT, idx, (LPARAM)str);
			SendDlgItemMessage(hDlg, IDC_LIST_16_3_1, LB_SETCURSEL, idx, 0);
			return TRUE;

		case IDC_BUTTON_Select:
			idx = SendDlgItemMessage(hDlg, IDC_LIST_16_3_1, LB_SELECTSTRING, idx, (LPARAM)str);
			return TRUE;
		}

		break;
	}

	return FALSE;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG_16_3_1), hWnd, MainDlgProc);
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석



#endif // Total