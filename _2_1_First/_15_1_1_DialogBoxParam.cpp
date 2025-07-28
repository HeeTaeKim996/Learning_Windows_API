#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	DialogBoxParam �� ���� �ڵ��Դϴ�. 
	������ _8_1_1 ___ 8_3_2 ���� DialogBox �� ����߾��µ�,
	DialogBox �� �������� �����ϰ�, �Ű������� LPARAM �� ���� �� �ְ�, DlgProc ���� LPARAM ���ڸ� ����� ��
	�ִٴ� �������� �ֽ��ϴ�.

	�׿ܿ� DlgProc �� ���ϰ��� �ش� �Լ��� ���ϰ��� �� ���� �����մϴ�.
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


INT_PTR CALLBACK DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static TCHAR* Param;

	switch (iMessage)
	{
	case WM_INITDIALOG:
		Param = (TCHAR*)lParam;
		SetDlgItemText(hDlg, IDC_STATIC_TEXT123, Param);
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
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
	const TCHAR* Mes = TEXT("���콺 ���� ��ư�� ������ ��ȭ���ڰ� ȣ��˴ϴ�");


	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_DIALOG_15_1_1), hWnd, DlgProc, 
			(LPARAM)TEXT("���� ������ �Է��� �ֽʽÿ�."));
		
		return TRUE;

	case WM_RBUTTONDOWN:
		DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_DIALOG_15_1_1), hWnd, DlgProc,
			(LPARAM)TEXT("������ ���ϸ��� �Է��� �ֽʽÿ�"));
		return TRUE;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 50, 50, Mes, lstrlen(Mes));
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // �ּ�


#endif // Total