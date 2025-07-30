#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	DialogBox ���� �޺��ڽ��� ����ϴ� ���� �⺻���� �ڵ��Դϴ�. 
	���̾Ʒα� �ڽ����� �޺��ڽ��� ����� �� ������ ����, rc ���� �������� ����, �޺��ڽ��� ��Ӵٿ� �� ����
	ũ�� ���� ���̸� ����� �巡�׷� �����ؾ�, ��Ҵٿ� �� ��ҵ��� �����ż� ���δٴ� ���Դϴ�.

	����Ʈ�� �ҽ�, ��Ӵٿ� �� ��Ұ� 1���ۿ� ������ �ʽ��ϴ�.

	
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



const TCHAR* arItem[3] = { TEXT("���"), TEXT("������"), TEXT("Ƣ��") };

INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		for (int i = 0; i < 3; i++)
		{
			SendDlgItemMessage(hDlg, IDC_COMBO_16_5_1, CB_ADDSTRING, 0, (LPARAM)arItem[i]);
			SendDlgItemMessage(hDlg, IDC_COMBO_16_5_2, CB_ADDSTRING, 0, (LPARAM)arItem[i]);
			SendDlgItemMessage(hDlg, IDC_COMBO_16_5_3, CB_ADDSTRING, 0, (LPARAM)arItem[i]);
		}

		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}

		return FALSE;

	}

	return FALSE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	

	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG_16_5_1), hWnd, MainDlgProc);
		
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;


	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // �ּ�



#endif // Total