#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	DlgProc �� ���� WNdProc ó�� ���Ǵ� ��츦 �����ϴ� ������ �ڵ��Դϴ�. 
----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
#include <Windows.h>
#include "resource.h"


/* �� DlgBox�� ���� HWND ó�� ���
    - ������ ���� ���� ���, ����� �Է��� �������� ó���ϱ� ������, 
	  WndProc �� ���� ������� �ʰ�, DlgProc�� ��ġ WndProc ó�� �������� ����Ѵ�.
	- �� �� DlgBox�� Main HWND �� ���ȴ�.
*/



INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);

HWND hDlgMain;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdshow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG4), HWND_DESKTOP, MainDlgProc);
	/* �� HWND_DESKTOP : HWND_DESKTOP ���� �θ� HWND�� �Ҵ��ϸ�, NULL �� �Ҵ��ϴ� �Ͱ� �����ϴ�.
		-> DlgBox�� ���� HWND�� �Ǿ�, DlgProc �����, ���α׷��� ����ȴ�
	*/
	return 0;
}


INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		hDlgMain = hDlg;
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, IDOK);
			return TRUE;
		}

		return FALSE;
	}

	return FALSE;
}



#endif // �ּ�


#if 1 // �ڵ常
#include <Windows.h>
#include "resource.h"


INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);

HWND hDlgMain;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG4), HWND_DESKTOP, MainDlgProc);

	return 0;
}

INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		hDlgMain = hDlg;
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, IDOK);
			return TRUE;
		}

		return FALSE;
	}
	
	return FALSE;
}


#endif // �ڵ常


#endif // Total