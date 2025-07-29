#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	�� LB_FINDSTRING, LB_FINDEXACT, LB_SELECTSTRING �� ���� �ڵ��Դϴ�

	 - LB_FINDSTRING	: �ش� ���ڿ��� �պκа� ��ġ�ϴ� ���ڸ� �˻��Ͽ�, �ε��� ��ȯ
	 - LB_FINDEXACT		: ��Ȯ�� �ش� ���ڿ��� ���ڸ� �˻��Ͽ�, �ε��� ��ȯ
	 - LB_SELECTSTRING	: �ش� ���ڿ��� �պκа� ��ġ�ϴ� ���ڸ� �˻��Ͽ�, �ش� �ε����� SetCursel ó��
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
			SendDlgItemMessage(hDlg, IDC_LIST_16_3_1, LB_SETCURSEL, idx, 0); // WPARAM �� idx ������, �ش� idx ���ĺ��� �˻�
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





#endif // �ּ�



#endif // Total