#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	���������� DialogBox�� Ȱ���ϴ� �����Դϴ�.
	LBUTTONDOWN ���� Edit �� ��� �ִ� ���̾Ʒα� �ڽ��� ����ϴ� ������ �ְ�,
	RBUTTONDOWN ���� üũ �ڽ�, ���� �ڽ� ��  ��� �ִ� ������ �ֽ��ϴ�.

	�ռ� Edit, CheckBox, RadioBox�ʹ� ������ ��������, ���̾Ʒα� �ڽ� ���� ��ü �Լ��� ����
	�����쿡�� ���� �� �����ϴ�.
----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_DialogBoxes_Edit_Check_RadioBox");
HWND hWndMain;

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


int x, y;
TCHAR stringStr[128];
INT_PTR CALLBACK EditDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		SetDlgItemText(hDlg, IDC_EDIT4, stringStr);
		SetDlgItemInt(hDlg, IDC_EDIT2, x, FALSE); // �� (4) : IS_SIGNED ? 
		SetDlgItemInt(hDlg, IDC_EDIT3, y, FALSE);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			GetDlgItemText(hDlg, IDC_EDIT4, stringStr, 128);
			x = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE); // �� (3) : ��ȯ ���� ���θ� �����ϴ� BOOL ������ 
			y = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, FALSE);
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


BOOL bMale;
enum tag_Major { MANAGE, KOREAN, ENGLISH, LAW } Major;
const TCHAR* arMajor[] = { TEXT("�濵�а�"), TEXT("�����а�"), TEXT("�����а�"), TEXT("���а�") };
TCHAR isMaleStr[64];
TCHAR majorStr[64];
INT_PTR CALLBACK DlgCheckRadioBox(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		CheckDlgButton(hDlg, IDC_CHECK2, bMale ? BST_CHECKED : BST_UNCHECKED);
		CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO4, IDC_RADIO1 + Major);

		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			bMale = IsDlgButtonChecked(hDlg, IDC_CHECK2) == BST_CHECKED;

			if (IsDlgButtonChecked(hDlg, IDC_RADIO1) == BST_CHECKED) Major = MANAGE;
			else if (IsDlgButtonChecked(hDlg, IDC_RADIO2) == BST_CHECKED) Major = KOREAN;
			else if (IsDlgButtonChecked(hDlg, IDC_RADIO3) == BST_CHECKED) Major = ENGLISH;
			else if (IsDlgButtonChecked(hDlg, IDC_RADIO4) == BST_CHECKED) Major = LAW;

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

		hWndMain = hWnd;
		x = y = 100;
		lstrcpy(stringStr, TEXT("String"));


		bMale = TRUE;
		Major = KOREAN;

		return 0;

	case WM_PAINT:


		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc, x, y, stringStr, lstrlen(stringStr));

		wsprintf(isMaleStr, TEXT("���� = %s"), bMale ? TEXT("����") : TEXT("����"));
		TextOut(hdc, 20, 20, isMaleStr, lstrlen(isMaleStr));

		wsprintf(majorStr, TEXT("���� = %s"), arMajor[Major]);
		TextOut(hdc, 20, 50, majorStr, lstrlen(majorStr));

		EndPaint(hWnd, &ps);

		return 0;

	case WM_LBUTTONDOWN:
		if (DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG6), hWnd, EditDlgProc) == IDOK)
		{
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;

	case WM_RBUTTONDOWN:
		if (DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG7), hWnd, DlgCheckRadioBox) == IDOK)
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



#endif // �ּ�


#if 1 // �ڵ常
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_DialogBoxes_Edit_Check_RadioBox");
HWND hWndMain;

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



int x, y;
TCHAR stringStr[128];
INT_PTR CALLBACK EditDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		SetDlgItemText(hDlg, IDC_EDIT4, stringStr);
		SetDlgItemInt(hDlg, IDC_EDIT2, x, FALSE);
		SetDlgItemInt(hDlg, IDC_EDIT3, y, FALSE);
		
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			GetDlgItemText(hDlg, IDC_EDIT4, stringStr, 128);
			x = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE);
			y = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, FALSE);

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


BOOL bMale;
enum tag_Major { MANAGE, KOREAN, ENGLISH, LAW } Major;
const TCHAR* arMajor[] = { TEXT("�濵�а�"), TEXT("�����а�"), TEXT("�����а�"), TEXT("���а�") };
TCHAR isMaleStr[64];
TCHAR majorStr[64];

INT_PTR CALLBACK DlgCheckRadioBox(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		CheckDlgButton(hDlg, IDC_CHECK2, bMale ? BST_CHECKED : BST_UNCHECKED);
		CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO4, IDC_RADIO1 + Major);

		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			bMale = IsDlgButtonChecked(hDlg, IDC_CHECK2) == BST_CHECKED;

			if (IsDlgButtonChecked(hDlg, IDC_RADIO1) == BST_CHECKED) Major = MANAGE;
			else if (IsDlgButtonChecked(hDlg, IDC_RADIO2) == BST_CHECKED) Major = KOREAN;
			else if (IsDlgButtonChecked(hDlg, IDC_RADIO3) == BST_CHECKED) Major = ENGLISH;
			else if (IsDlgButtonChecked(hDlg, IDC_RADIO4) == BST_CHECKED) Major = LAW;

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
		hWndMain = hWnd;
		
		x = y = 100;
		lstrcpy(stringStr, TEXT("String"));

		bMale = TRUE;
		Major = KOREAN;

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc, x, y, stringStr, lstrlen(stringStr));

		wsprintf(isMaleStr, TEXT("���� = %s"), bMale ? TEXT("����") : TEXT("����"));
		TextOut(hdc, 20, 20, isMaleStr, lstrlen(isMaleStr));

		wsprintf(majorStr, TEXT("���� = %s"), arMajor[Major]);
		TextOut(hdc, 20, 50, majorStr, lstrlen(majorStr));

		EndPaint(hWnd, &ps);

		return 0;

	case WM_LBUTTONDOWN:
		if (DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG6), hWnd, EditDlgProc) == IDOK)
		{
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;

	case WM_RBUTTONDOWN:
		if (DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG7), hWnd, DlgCheckRadioBox) == IDOK)
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

#endif // �ڵ常


#endif // Total