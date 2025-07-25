#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	DlgProc 이 메인 WNdProc 처럼 사용되는 경우를 설명하는 간략한 코드입니다. 
----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>
#include "resource.h"


/* ○ DlgBox를 메인 HWND 처럼 사용
    - 윈도우 계산기 같은 경우, 사용자 입력을 메인으로 처리하기 때문에, 
	  WndProc 을 거의 사용하지 않고, DlgProc을 마치 WndProc 처럼 메인으로 사용한다.
	- 이 때 DlgBox가 Main HWND 로 사용된다.
*/



INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);

HWND hDlgMain;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdshow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG4), HWND_DESKTOP, MainDlgProc);
	/* ○ HWND_DESKTOP : HWND_DESKTOP 으로 부모 HWND를 할당하면, NULL 을 할당하는 것과 유사하다.
		-> DlgBox가 메인 HWND가 되어, DlgProc 종료시, 프로그램이 종료된다
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



#endif // 주석


#if 1 // 코드만
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


#endif // 코드만


#endif // Total