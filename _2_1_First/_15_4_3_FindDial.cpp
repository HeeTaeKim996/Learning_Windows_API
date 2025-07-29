#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	단어 검색 Dial 입니다. 쓸모 없습니다. 교재 내용대로 따라 적긴 했지만, 실용성 없는 코드입니다.
	단어 검색 기능이 필요한 프로그램도 드물 뿐더러, 검색 기능이 필요하다 하더라도 직접 만드는 추새이기 때문에,
	실용성이 1도 없는 코드입니다. 
	
	내용 무시해도 좋습니다.
----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Sample_2");
HWND hWndMain;
UINT FRMsg;
HWND hDlgFR = NULL;
FINDREPLACE FR;
TCHAR szFindWhat[256];


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


	hWndMain = hWnd; // ※ hWndMain 여기서 할당
	while (GetMessage(&Message, NULL, 0, 0))
	{
		if (!IsWindow(hDlgFR) || !IsDialogMessage(hDlgFR, &Message)) // ◁
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
	return (int)Message.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR* Mes = TEXT("찾기 대화상자를 보여줍니다");
	FINDREPLACE* pFR;
	static int Count = 1;
	static TCHAR str[10'000];
	TCHAR sTmp[256];
	RECT crt;


	if (iMessage == FRMsg)
	{
		pFR = (FINDREPLACE*)lParam;

		if (pFR->Flags & FR_DIALOGTERM)
		{
			hDlgFR = NULL;
			return 0;
		}

		if (pFR->Flags & FR_FINDNEXT)
		{
			wsprintf(sTmp, TEXT("%s 문자열을 %s 방향으로 대소문자 구분 %s %s 검색합니다.\r\n"),
				szFindWhat,
				(pFR->Flags & FR_DOWN ? TEXT("아래쪽") : TEXT("위쪽")),
				(pFR->Flags & FR_MATCHCASE ? TEXT("하여") : TEXT("없이")),
				(pFR->Flags & FR_WHOLEWORD ? TEXT("단어단위로") : TEXT("")));

			lstrcat(str, sTmp);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;
	}



	switch (iMessage)
	{
	case WM_CREATE:
		FRMsg = RegisterWindowMessage(FINDMSGSTRING);
		return 0;

	case WM_LBUTTONDOWN:
		if (hDlgFR == NULL)
		{
			memset(&FR, 0, sizeof(FINDREPLACE));
			FR.lStructSize = sizeof(FINDREPLACE);
			FR.hwndOwner = hWnd;
			FR.lpstrFindWhat = szFindWhat;
			FR.wFindWhatLen = 256;

			hDlgFR = FindText(&FR);
		}
		return 0;

		
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		GetClientRect(hWnd, &crt);
		crt.left = 10;
		crt.top = 30;

		TextOut(hdc, 10, 10, Mes, lstrlen(Mes));
		DrawText(hdc, str, -1, &crt, 0);
		EndPaint(hWnd, &ps);

		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석


#endif // Total