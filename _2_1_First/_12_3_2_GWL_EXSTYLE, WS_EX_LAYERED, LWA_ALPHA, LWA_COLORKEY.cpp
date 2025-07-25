#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	GWL_EXSTYLE, WS_EX_LAYERED ����,
	LWA_ALPHA �� ä���� alpha ���� �����ϰ�,
	LWA_COLORKEY �� Ư�� ������ ������ ����ó�� 
	�ϴ� �ڵ��Դϴ�

	�� GWL_EXSTYLE	: �����쿡�� Ȯ�� ��Ÿ��(����, �������� ä�� ���) �� ������ �� ����ϴ� �÷��װ�
	�� WS_EX_LAYERED	: GWL_EXSTYLE Ű������ ������ �� ����� �� �ִ� �÷��׷�, â�� ���̾� �����
	                  �ο��Ͽ�, ���� ���� �߰� ó�� ����
	
	�� SetLayerWindowAttribute
	 - ������â�� ���̾� �Ӽ� ���� �Լ�
	 - (2) : Ű �÷� [ (4) �� LWA_COLORKEY �� ���� ��� ���� ]
	 - (3) : ALPHA��. [ (4) �� LWA_ALPHA �� ���� ��� ���� ]
	 - LWA_ALPHA	: (3)�� �Էµ� ���� ����, ���İ� ����
	 - LWA_COLORKEY	: (2)�� �Էµ� ���� �÷���, ������ �����ϰ� ó��
					  [ ex) 0x888888 �� 2�� �Է½�, �����쿡 0x888888 ������ ���� ���, �� ���� �κ��� ������
					       �����ϰ� ó�� ]
----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
#include <Windows.h>
#include "resource.h"


LRESULT CALLBACK MainDlgProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_Translucent");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG10), HWND_DESKTOP, MainDlgProc);

	return 0;
}



LRESULT CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH hBrush, OldBrush;
	static int iOpa = 200;

	switch (iMessage)
	{
	case WM_INITDIALOG:
		SetWindowLong(hDlg, GWL_EXSTYLE, GetWindowLong(hDlg, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(hDlg, RGB(0, 0, 255), iOpa, LWA_ALPHA | LWA_COLORKEY);

		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCLOSE:
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;

		case IDC_BUTTON1:
			iOpa += 25;
			if (iOpa > 255)
			{
				iOpa = 255;
			}
			SetLayeredWindowAttributes(hDlg, RGB(0, 0, 255), iOpa, LWA_ALPHA |  LWA_COLORKEY);

			return TRUE;

		case IDC_BUTTON2:
			iOpa -= 25;
			if (iOpa < 50)
			{
				iOpa = 50;
			}
			SetLayeredWindowAttributes(hDlg, RGB(0, 0, 255), iOpa, LWA_ALPHA | LWA_COLORKEY);

			return TRUE;
		}

		return FALSE;

	case WM_PAINT:
		hdc = BeginPaint(hDlg, &ps);
		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		OldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		Rectangle(hdc, 10, 10, 300, 80);
		
		DeleteObject(SelectObject(hdc, OldBrush));

		EndPaint(hDlg, &ps);

		return TRUE;
	}
	return FALSE;
}





#endif // �ּ�


#if 1 // �ڵ常
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK MainDlgProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Sample_2");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG10), HWND_DESKTOP, MainDlgProc);

	return 0;
}


LRESULT CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH hBrush, OldBrush;
	static int iOpa = 200;

	switch (iMessage)
	{
	case WM_INITDIALOG:
		SetWindowLong(hDlg, GWL_EXSTYLE, GetWindowLong(hDlg, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(hDlg, RGB(0, 0, 255), iOpa, LWA_ALPHA | LWA_COLORKEY);

		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCLOSE:
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;

		case IDC_BUTTON1:
			iOpa += 25;
			if (iOpa > 255)
			{
				iOpa = 255;
			}
			SetLayeredWindowAttributes(hDlg, RGB(0, 0, 255), iOpa, LWA_ALPHA | LWA_COLORKEY);

			return TRUE;

		case IDC_BUTTON2:
			iOpa -= 25;
			if (iOpa < 50)
			{
				iOpa = 50;
			}
			SetLayeredWindowAttributes(hDlg, RGB(0, 0, 255), iOpa, LWA_ALPHA | LWA_COLORKEY);

			return TRUE;
		}

		return FALSE;

	case WM_PAINT:
		hdc = BeginPaint(hDlg, &ps);
		
		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		OldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		Rectangle(hdc, 10, 10, 300, 80);

		DeleteObject(SelectObject(hdc, OldBrush));

		EndPaint(hDlg, &ps);

		return TRUE;
	}
	return FALSE;
}

#endif // �ڵ常


#endif // Total