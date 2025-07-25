#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	본격적으로 DialogBox를 활용하는 예제입니다.
	LBUTTONDOWN 에는 Edit 을 담고 있는 다이아로그 박스를 사용하는 예제가 있고,
	RBUTTONDOWN 에는 체크 박스, 라디오 박스 를  담고 있는 예제가 있습니다.

	앞선 Edit, CheckBox, RadioBox와는 별개의 내용으로, 다이아로그 박스 내에 자체 함수를 따로
	윈도우에서 만든 것 같습니다.
----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
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
		SetDlgItemInt(hDlg, IDC_EDIT2, x, FALSE); // ※ (4) : IS_SIGNED ? 
		SetDlgItemInt(hDlg, IDC_EDIT3, y, FALSE);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			GetDlgItemText(hDlg, IDC_EDIT4, stringStr, 128);
			x = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE); // ※ (3) : 반환 성공 여부를 전달하는 BOOL 포인터 
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
const TCHAR* arMajor[] = { TEXT("경영학과"), TEXT("국문학과"), TEXT("영문학과"), TEXT("법학과") };
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

		wsprintf(isMaleStr, TEXT("성별 = %s"), bMale ? TEXT("남자") : TEXT("여자"));
		TextOut(hdc, 20, 20, isMaleStr, lstrlen(isMaleStr));

		wsprintf(majorStr, TEXT("전공 = %s"), arMajor[Major]);
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



#endif // 주석


#if 1 // 코드만
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
const TCHAR* arMajor[] = { TEXT("경영학과"), TEXT("국문학과"), TEXT("영문학과"), TEXT("법학과") };
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

		wsprintf(isMaleStr, TEXT("성별 = %s"), bMale ? TEXT("남자") : TEXT("여자"));
		TextOut(hdc, 20, 20, isMaleStr, lstrlen(isMaleStr));

		wsprintf(majorStr, TEXT("전공 = %s"), arMajor[Major]);
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

#endif // 코드만


#endif // Total