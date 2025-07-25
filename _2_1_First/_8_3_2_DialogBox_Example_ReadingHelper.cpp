#if 0 // Total
/*----------------------------------------------------------------------------------------------------

----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
#include <Windows.h>
#include "resource.h"

INT_PTR CALLBACK ReadingDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
HINSTANCE g_hInst;
HWND hDlgMain;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	g_hInst = hInstance;
	DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG8), HWND_DESKTOP, ReadingDlgProc);
	return 0;
}

int PageStart, PageEnd, NowPage;
int PageSec, NowSec;
enum tag_Status{WAIT, RUN, PAUSE};
tag_Status Status;

INT_PTR CALLBACK ReadingDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR Mes[256];

	switch (iMessage)
	{
	case WM_INITDIALOG:
		hDlgMain = hDlg;
		Status = WAIT;
		return TRUE;

	case WM_TIMER:
		NowSec--;
		if (NowSec <= 0)
		{
			if (IsDlgButtonChecked(hDlg, IDC_CHECK1) == BST_CHECKED)
			{
				MessageBeep(0);
			}

			NowPage++;
			NowSec = PageSec;
			if (NowPage > PageEnd)
			{
				SetDlgItemText(hDlg, IDC_MY_TEXT, TEXT("�� �о����ϴ�"));
				// �� DlgBox �� STATIC_TEXT�� �⺻�����δ� ���� ID �� �������� ����.
				//    STATIC_TEXT ���� -> F4 -> ID�� �������� �����ϸ�, ...rc �� Resource.h ���� �ڵ� �����
				KillTimer(hDlg, 1);
				Status = WAIT;
				return TRUE;
			}
		}

		wsprintf(Mes, TEXT("%d ������ �д� �� : %d �� ����"), NowPage,  NowSec);
		SetDlgItemText(hDlg, IDC_MY_TEXT, Mes);

		return TRUE;


	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:
			PageStart = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE);
			PageEnd = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE);
			if (PageStart == 0 || PageEnd == 0 || PageStart >= PageEnd)
			{
				MessageBox(hDlg, TEXT("�ð��� �ٽ� �Է��Ͻÿ�."), TEXT("�˸�"), MB_OK);
				return TRUE;
			}

			NowPage = PageStart;
			PageSec = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, FALSE);
			if (PageSec <= 0)
			{
				MessageBox(hDlg, TEXT("�ð��� �ٽ� �Է��ϼ���"), TEXT("�˸�"), MB_OK);
				return TRUE;
			}

			NowSec = PageSec;
			SetTimer(hDlg, 1, 1'000, NULL);
			SendMessage(hDlg, WM_TIMER, 1, 0);
			Status = RUN;
			
			return TRUE;

		case IDC_BUTTON2:
			if (Status == PAUSE)
			{
				SetTimer(hDlg, 1, 1'000, NULL);
				Status = RUN;
				SetDlgItemText(hDlg, IDC_BUTTON2, TEXT("�Ͻ�����")); 
				// �� ��ư�� string �� SetDlgItemText �� ���� ����
			}
			else if (Status == RUN)
			{
				KillTimer(hDlg, 1);
				Status = PAUSE;
				SetDlgItemText(hDlg, IDC_BUTTON2, TEXT("�簳"));
			}

			return TRUE;

		case IDC_BUTTON3:
			SendMessage(hDlgMain, WM_COMMAND, IDCANCEL, 0);

		case IDCANCEL:
			KillTimer(hDlg, 1);
			EndDialog(hDlg, IDCANCEL);

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

INT_PTR CALLBACK ReadingDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
HINSTANCE g_hInst;
HWND hDlgMain;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	g_hInst = hInstance;
	DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG8), HWND_DESKTOP, ReadingDlgProc);
	return 0;
}

int PageStart, PageEnd, NowPage;
int PageSec, NowSec;
enum tag_Status{WAIT, RUN, PAUSE};
tag_Status Status;

INT_PTR CALLBACK ReadingDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR Mes[256];

	switch (iMessage)
	{
	case WM_INITDIALOG:
		hDlgMain = hDlg;
		Status = WAIT;
		return TRUE;

	case WM_TIMER:
		NowSec--;
		if (NowSec <= 0)
		{
			if (IsDlgButtonChecked(hDlg, IDC_CHECK1) == BST_CHECKED)
			{
				MessageBeep(0);
			}

			NowPage++;
			NowSec = PageSec;
			if (NowPage > PageEnd)
			{
				SetDlgItemText(hDlg, IDC_MY_TEXT, TEXT("�� �о����ϴ�"));
				KillTimer(hDlg, 1);
				Status = WAIT;

				return TRUE;
			}
		}
		wsprintf(Mes, TEXT("%d ������ �д� �� : %d �� ����"), NowPage, NowSec);
		SetDlgItemText(hDlg, IDC_MY_TEXT, Mes);

		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:
			PageStart = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE);
			PageEnd = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE);
			if (PageStart == 0 || PageEnd == 0 || PageStart >= PageEnd)
			{
				MessageBox(hDlg, TEXT("�ð��� �ٽ� �Է��Ͻÿ�."), TEXT("�˸�"), MB_OK);
				return TRUE;
			}

			NowPage = PageStart;
			PageSec = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, FALSE);
			if (PageSec <= 0)
			{
				MessageBox(hDlg, TEXT("�ð��� �ٽ� �Է��ϼ���"), TEXT("�˸�"), MB_OK);
				return TRUE;
			}

			NowSec = PageSec;
			SetTimer(hDlg, 1, 1'000, NULL);
			SendMessage(hDlg, WM_TIMER, 1, 0);
			Status = RUN;

			return TRUE;

		case IDC_BUTTON2:
			if (Status == PAUSE)
			{
				SetTimer(hDlg, 1, 1'000, NULL);
				Status = RUN;
				SetDlgItemText(hDlg, IDC_BUTTON2, TEXT("�Ͻ�����"));
			}
			else if (Status == RUN)
			{
				KillTimer(hDlg, 1);
				Status = PAUSE;
				SetDlgItemText(hDlg, IDC_BUTTON2, TEXT("�簳"));
			}

			return TRUE;

		case IDC_BUTTON3:
			SendMessage(hDlgMain, WM_COMMAND, IDCANCEL, 0);


		case IDCANCEL:
			KillTimer(hDlg, 1);
			EndDialog(hDlg, IDCANCEL);

			return TRUE;
		}

		return FALSE;
	}

	return FALSE;
}


#endif // �ڵ常


#endif // Total