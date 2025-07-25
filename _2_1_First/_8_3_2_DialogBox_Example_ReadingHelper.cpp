#if 0 // Total
/*----------------------------------------------------------------------------------------------------

----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
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
				SetDlgItemText(hDlg, IDC_MY_TEXT, TEXT("다 읽었습니다"));
				// ※ DlgBox 의 STATIC_TEXT는 기본적으로는 고유 ID 가 지정되지 않음.
				//    STATIC_TEXT 선택 -> F4 -> ID를 수동으로 수정하면, ...rc 와 Resource.h 에서 자동 변경됨
				KillTimer(hDlg, 1);
				Status = WAIT;
				return TRUE;
			}
		}

		wsprintf(Mes, TEXT("%d 페이지 읽는 중 : %d 초 남음"), NowPage,  NowSec);
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
				MessageBox(hDlg, TEXT("시간을 다시 입력하시오."), TEXT("알림"), MB_OK);
				return TRUE;
			}

			NowPage = PageStart;
			PageSec = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, FALSE);
			if (PageSec <= 0)
			{
				MessageBox(hDlg, TEXT("시간을 다시 입력하세요"), TEXT("알림"), MB_OK);
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
				SetDlgItemText(hDlg, IDC_BUTTON2, TEXT("일시중지")); 
				// ※ 버튼의 string 도 SetDlgItemText 로 변경 가능
			}
			else if (Status == RUN)
			{
				KillTimer(hDlg, 1);
				Status = PAUSE;
				SetDlgItemText(hDlg, IDC_BUTTON2, TEXT("재개"));
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



#endif // 주석


#if 1 // 코드만
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
				SetDlgItemText(hDlg, IDC_MY_TEXT, TEXT("다 읽었습니다"));
				KillTimer(hDlg, 1);
				Status = WAIT;

				return TRUE;
			}
		}
		wsprintf(Mes, TEXT("%d 페이지 읽는 중 : %d 초 남음"), NowPage, NowSec);
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
				MessageBox(hDlg, TEXT("시간을 다시 입력하시오."), TEXT("알림"), MB_OK);
				return TRUE;
			}

			NowPage = PageStart;
			PageSec = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, FALSE);
			if (PageSec <= 0)
			{
				MessageBox(hDlg, TEXT("시간을 다시 입력하세요"), TEXT("알림"), MB_OK);
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
				SetDlgItemText(hDlg, IDC_BUTTON2, TEXT("일시중지"));
			}
			else if (Status == RUN)
			{
				KillTimer(hDlg, 1);
				Status = PAUSE;
				SetDlgItemText(hDlg, IDC_BUTTON2, TEXT("재개"));
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


#endif // 코드만


#endif // Total