#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	파일 열기 실습 2번째 입니다.
	첫장 _15_3_1 과 내용은 유사하고, 조금 더 확장된 버전입니다.
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
	TCHAR str[300];
	TCHAR lpstrFile[MAX_PATH] = TEXT("");
	TCHAR szFileTile[MAX_PATH];
	TCHAR InitDir[MAX_PATH];
	TCHAR CustFilter[40] = TEXT("사운드 파일");

	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = hWnd;
		OFN.lpstrFilter = TEXT(
			"모든 파일(*.*)\0*.*\0"
			"텍스트 파일 (*.txt)\0*.txt\0"
			"c 소스 파일 (*.c; *.h)\0*.c;*.h\0");
		/*	○ lpstrFilter
			 - 검색 때 사용될 필터를 문자열 \0 ... \0 이렇게 ... 로 지정. \0 밖은, 실제로 보여지는 문자열.
			 - \0 사이의 ... 는 검색 패턴

			 ※ \0 사이의 필터링 문자열은, Regex 패턴과 무관.
			  - * 는 최소 1개 이상의 CHAR 를 의미
			  - ; 는 OR 과 비슷한 의미
		*/
		OFN.nFilterIndex = 2; // ※ 위에 지정한 lpstrFilter 중 디펄트 인덱스
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = MAX_PATH;
		OFN.lpstrTitle = TEXT("파일을 선택해 주십시오"); // ※ 타이틀바명 지정. 디펄트는 '열기'
		OFN.lpstrFileTitle = szFileTile; // ※ 우측부터 검색해서 맨처음 발견되는 \ 를 피벗으로, 파일명 A.x 리턴
		OFN.nMaxFileTitle = MAX_PATH;
		OFN.lpstrDefExt = TEXT("abc"); 
		// 파일명을 사용자가 타이핑했을 때, 만약 확장자 ( . 우측) 가 지정되지 않다면, 디펄트로 할당한 lpstDefExt 로 지정
		// Ex) A\B -> A\B.abc
		GetWindowsDirectory(InitDir, MAX_PATH); // ※ C:\Windows  를 InitDir 에 입력
		OFN.lpstrInitialDir = InitDir; // ※ 처음 파일열기 를 했을 때에 나오는 디펄트 경로

		if (GetOpenFileName(&OFN) != 0)
		{
			wsprintf(str, TEXT("%s 파일을 선택했습니다. 파일명은 %s 입니다. 파일명 오프셋 %d, 확장자 오프셋 %d"),
				lpstrFile, szFileTile, OFN.nFileOffset, OFN.nFileExtension);
			/*
				○ nFileOffset
				 - lpstrFile 에서, 파일이름 이 시작되는 인덱스
				
				○ nFileExtension
				 - lpstrFile 에서, 확장자 가 시작되는 인덱스
			
			*/
			MessageBox(hWnd, str, TEXT("파일 열기 성공"), MB_OK);
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
	PAINTSTRUCT ps;
	const TCHAR* Mes = TEXT("마우스 왼쪽 버튼을 누르십시오");
	OPENFILENAME OFN;
	TCHAR str[300];
	TCHAR lpstrFile[MAX_PATH] = TEXT("");
	TCHAR szFileTitle[MAX_PATH];
	TCHAR InitDir[MAX_PATH];


	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = hWnd;
		OFN.lpstrFilter = TEXT(
			"모든 파일(*.*)\0*.*\0"
			"텍스트 파일 (*.txt)\0*.txt\0"
			"c 소스 파일 (*.c; *.h)\0*.c;*.h\0");
		OFN.nFilterIndex = 2;
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = MAX_PATH;
		OFN.lpstrTitle = TEXT("파일을 선택해 주십시오");
		OFN.lpstrFileTitle = szFileTitle;
		OFN.nMaxFileTitle = MAX_PATH;
		OFN.lpstrDefExt = TEXT("abc");
		GetWindowsDirectory(InitDir, MAX_PATH);
		OFN.lpstrInitialDir = InitDir;

		if (GetOpenFileName(&OFN) != 0)
		{
			wsprintf(str, TEXT("%s 파일을 선택했습니다. 파일명은 %s 입니다. 파일명 오프셋 %d, 확장자 오프셋 %d"),
				lpstrFile, szFileTitle, OFN.nFileOffset, OFN.nFileExtension);
			MessageBox(hWnd, str, TEXT("파일 열기 성공"), MB_OK);
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

#endif // 코드만


#endif // Total