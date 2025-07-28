#if 1 // Total
/*----------------------------------------------------------------------------------------------------
	FileOpenDial1 에서 다중선택에 대한 코드입니다.
	아래 정리한 개념을 이해하지 못했다면, 아래 코드를 이해하기 어렵기 때문에, 정리합니다.

	○ lstrcpy
	 - (2)항을 (1)에 복사하는데, (2)에 \0 (종료문자)가 중간에 있다면, \0 전까지만 복사합니다.
	   
	 - 예를 들어, (2) 가 text("A\0BB\0CCC") 라면, (1)에 복사되는 건 A 뿐입니다. (2)에서 포인터를 우측으로 옮겨서
	   그다음 것을 복사한다면, BB 가 복사되고, CCC 는 (1)에 복사되지 않습니다.

	○ OFN.Flags 에 플래그 OFN_EXPLORER | OFN_ALLOWMULTISELECT 가 입력되면,
	  OFN.lpstrFile 에는, 경우에 따라 문자열이 다르게 할당

	  - 1) 파일 하나만 선택된 경우 - 기존 방법대로, C:/... .Exe 형식으로 문자열이 리턴
								EX) lpstrFile = 전체경로\0
								EX) lpstrFile = "C:\\Users\\Kim\\file.txt\0"

	  - 2) 파일이 2개 이상 선택된 경우 - 파일들의 부모 파일명이 \0 종료문자 까지 입력되고, 이후에 파일명들이 나열.
										  파일명들 또한 \0 로 구분되어 나열
								EX) lpstrFile = 폴더경로\0\첫번재파일명\0\두번째파일명\0\...\0
								EX) lpstrFile = "C:\\Users\\Kim\\0file1.txt\0file2.txt\0file3.txt\0\0"

----------------------------------------------------------------------------------------------------*/


#if 1 // 주석
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


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR* Mes = TEXT("마우스 왼쪽 버튼을 누르십시오");
	OPENFILENAME OFN;
	TCHAR str[32'000] = TEXT("");
	TCHAR lpstrFile[10'000] = TEXT("");
	TCHAR* p;
	TCHAR Name[MAX_PATH];
	TCHAR szTmp[MAX_PATH];
	int i = 1;


	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = hWnd;
		OFN.lpstrFilter = TEXT("모든 파일(*.)\0*.*\0");
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = 10'000;
		OFN.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT;  // ※ 두플래그는 고정되어 묶음으로 사용됨. 통째로 외우기
		if (GetOpenFileName(&OFN) != 0)
		{
			p = lpstrFile;
			lstrcpy(Name, p);
			if (*(p + lstrlen(Name) + 1) == 0)
			{
				wsprintf(str, TEXT("%s 파일 하나만 선택했습니다"), Name);
			}
			else
			{
				wsprintf(str, TEXT("%s 디렉토리에 있는 다음 파일들이 선택되었습니다\r\n\r\n"), Name);

				while (1)
				{
					p = p + lstrlen(Name) + 1;
					if (*p == 0)
					{
						break;
					}
					lstrcpy(Name, p);
					wsprintf(szTmp, TEXT("%d번째 파일 = %s \r\n"), i++, Name);
					lstrcat(str, szTmp);
				}
			}

			MessageBox(hWnd, str, TEXT("선택한 파일"), MB_OK);
		}
		else
		{
			if (CommDlgExtendedError() == FNERR_BUFFERTOOSMALL) // ※ 에러 구분. 초과시 메세지박스로 알림
			{
				MessageBox(hWnd, TEXT("버퍼 크기가 너무 작습니다"), TEXT("에러"), MB_OK);
			}
		}

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 10, Mes, lstrlen(Mes));
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석


#if 0 // 코드만
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


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;


	switch (iMessage)
	{


	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // 코드만


#endif // Total