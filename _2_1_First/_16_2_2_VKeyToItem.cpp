#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	�� LBS_WANTKEYBOARDINPUT 
	 - .rc ��  DialogBox �� ListBox �׸�, LBS_WANTKEYBOARDINPUT �� �߰��ϸ�, �ش� ����Ʈ�ڽ� �� ��Ŀ���� �� ä�� Ű���� �Է½�,
	   MainDlgProc ( DialogBox�� WNDPROC ) �� WM_VKEYTOITEM �� �ߵ���
	 - WM_VKEYTOITEM �� �ߵ��� ��, (BOOL) - 2 �� �����ϸ�, �ش� ����Ʈ�ڽ��� �ƹ��� ������ ���� ����� ����.
	 - WM_VKEYTOITEM �� �ߵ��� ��, (BOOL) - 1 �� �����ϸ�, ����Ʈ�ڽ��� ����Ʈ ���� ó�� ����
	 - WM_VKEYTOITEM �� �ߵ��� ��, ���       �� �����ϸ�, ����Ʈ�ڽ��� ����Ʈ ���� ó�� ����
	 
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


const TCHAR* Items[] = { TEXT("Apple"), TEXT("Orange"), TEXT("Melon"), TEXT("Grape"), TEXT("Great"), TEXT("Strawberry") };

INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		for (int i = 0; i < sizeof(Items) / sizeof(Items[0]); i++)
		{
			SendDlgItemMessage(hDlg, IDC_LIST_16_2_1, LB_ADDSTRING, 0, (LPARAM)Items[i]);
		}
		return TRUE;

	case WM_VKEYTOITEM: // ����Ʈ�ڽ��� �ٷ� ���޵� �� �����. ���� ����Ʈ�ڽ��� ������. rc �� LBS_WANTKEYBOARDINPUT �߰� �ʿ�
		if (LOWORD(wParam) == 'D')
		{
			int i = SendDlgItemMessage(hDlg, IDC_LIST_16_2_1, LB_GETCURSEL, 0, 0);
			if (i != LB_ERR)
			{
				SendDlgItemMessage(hDlg, IDC_LIST_16_2_1, LB_DELETESTRING, i, 0);

				return (BOOL)-2; // ����Ʈ�ڽ� �ƹ��͵� ���� ����
			}
		}

		return (BOOL)-1; // ����Ʈ�ڽ� ����Ʈ ���� �ϱ�

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}

		break;
	}

	return FALSE;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;


	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG_16_2_1), hWnd, MainDlgProc);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // �ּ�


#endif // Total