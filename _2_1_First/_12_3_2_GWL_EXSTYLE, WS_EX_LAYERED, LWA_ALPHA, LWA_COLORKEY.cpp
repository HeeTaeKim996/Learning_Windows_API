#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	GWL_EXSTYLE, WS_EX_LAYERED 에서,
	LWA_ALPHA 로 채색의 alpha 값을 조정하고,
	LWA_COLORKEY 로 특정 색상을 완전히 투명처리 
	하는 코드입니다

	○ GWL_EXSTYLE	: 윈도우에서 확장 스타일(투명, 완전투명 채색 기능) 을 설정할 때 사용하는 플래그값
	○ WS_EX_LAYERED	: GWL_EXSTYLE 키값으로 설정할 때 사용할 수 있는 플래그로, 창에 레이어 기능을
	                  부여하여, 투명도 관련 추가 처리 가능
	
	○ SetLayerWindowAttribute
	 - 윈도우창의 레이어 속성 설정 함수
	 - (2) : 키 컬러 [ (4) 의 LWA_COLORKEY 와 연계 사용 목적 ]
	 - (3) : ALPHA값. [ (4) 의 LWA_ALPHA 와 연계 사용 목적 ]
	 - LWA_ALPHA	: (3)에 입력된 값에 따라, 알파값 조정
	 - LWA_COLORKEY	: (2)에 입력된 값의 컬러를, 완전히 투명하게 처리
					  [ ex) 0x888888 을 2에 입력시, 윈도우에 0x888888 색상이 있을 경우, 그 색상 부분을 완전히
					       투명하게 처리 ]
----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
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





#endif // 주석


#if 1 // 코드만
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

#endif // 코드만


#endif // Total