#if 1 // Total
/*----------------------------------------------------------------------------------------------------
	■ 디렉터리 검색 및 string 반환 코드	
	 - 확장자가 파일이 아닌, 디렉터리 폴더를 선택하고, 해당 주소를 문자열로 반환하는 코드입니다.
	 - 생소한 타입, 함수가 많아서, 완전하게 이해하지는 못했고, 지피티의 도움으로 대략적으로 어떻게 돌아가는 구나
	   정도만 이해했고, 이해한 내용을 기록했습니다.
	 - 작동 순서대로, 코드를 설명합니다.

	○ SHBrowseForFolder
	 - 사용자가 폴더를 선택할 수 있는 탐색기 창을 띄워주는 함수
	 - 리턴값으로 선택한 폴더를 나타내는 LPITEMIDLIST 를 반환

	○ BROWSEINFO
	 - SHBrowseForFolder 에 전달되는 매개변수로, 폴더 선택 대화상자의 설정을 담음
	 - hwndOwner		: 대화상자의 부모 윈도우
	 - pidlRoot			: 대화상자 폴더트리의 최상위 디렉터리
	 - pszDisplayName	: 선택한 폴더의 폴더이름 을 반환할 버퍼 ( 전체 경로가 아닌 마지막 경로인 폴더명 만을 버퍼에 반환 )
	 - lpszTitle		: 상단에 표시할 타이틀
	 - uFlags			: 대화상자의 동작 옵션
	 - lpfn				: 콜백함수의 포인터. SHBrowseForFolder 는 BROWSEINFO 의 lpfn 이 할당될시, SHBroweForFolder
						  호출 초기인, 대화상자 초기화 때 lpfn 에 할당된 함수를 호출. 호출하는 함수의 (4)항에는,
						  바로 밑에 설명하는 lParam 을 인자로 넣어 호출.
	 - lParam			: 콜백함수의 (4)항에 입력될 인자
	 
	 ○ BroweCallbackProc
	  - 위에 BrowseInfo의 lpfn 에서 설명했듯, SHBorwseForFolder 에서 대화상자 초기화 때 호출되도록 하는 함수
	  - 아래 코드에서는 BROWSEINFO 의 lParam 인자로 받은 StartPath (TCHAR[]) 를 대화상자의 초기 경로로 설정하는 역할
	  - BrowseCallbackProc 의 (1) 인 HWND 에 들어오는 HWND 는, 프로그램 시행시 main HWND 가 아닌, 폴더 선택 대화상자 내부의 WND로,
	    Shell 이 내부적으로 만든 WND. SendMessage(.., BFFM_SETSELECTION ...) 을 보내면, 해당 WND 가 처리하여, 대화상자의 초기 경로를 설정

	 ○ SHGetPathFromIDList
	  - SHBrowseForFolder 로 반환된 LPITEMIDLIST 를, 실제 경로 문자열로 반환하는 함수
	   
	 ○ SHGetMalloc
	  - SHBrowseForFolder 는 WND 가 아닌 시스템/프로세스 차원에서의 shell 자원을 사용하여 검색한다. 
	  - 이 때 사용한 메모리를 SHGetMalloc 을 통해 할당한 Shell 메모리를 해제해야 한다

----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Sample_2");
HWND hWndMain;

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


#include <Shlobj.h>
BOOL BrowseFolder(HWND hParent, LPCTSTR szTitle, LPCTSTR StartPath, TCHAR* szFolder);


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR* Mes = TEXT("왼쪽 마우스 버튼을 눌러 폴더를 선택하시오.");
	static TCHAR StartPath[MAX_PATH];
	TCHAR Folder[MAX_PATH];


	switch (iMessage)
	{
	case WM_CREATE:
		hWndMain = hWnd;
		return 0;

	case WM_LBUTTONDOWN:
		if (BrowseFolder(hWnd, TEXT("폴더를 선택하시오"), StartPath, Folder))
		{
			MessageBox(hWnd, Folder, TEXT("선택한 폴더"), MB_OK);
			lstrcpy(StartPath, Folder);
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

int CALLBACK BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch (uMsg)
	{
	case BFFM_INITIALIZED:
		if (lpData != NULL)
		{
			SendMessage(hWnd, BFFM_SETSELECTION, TRUE, (LPARAM)lpData);
		}
		break;
	}
	return 0;
}

BOOL BrowseFolder(HWND hParent, LPCTSTR szTitle, LPCTSTR StartPath, TCHAR* szFolder)
{
	LPMALLOC pMalloc;
	LPITEMIDLIST pidl;
	BROWSEINFO bi;

	bi.hwndOwner = hParent;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = NULL;
	bi.lpszTitle = szTitle;
	bi.ulFlags = 0;
	bi.lpfn = BrowseCallbackProc;
	bi.lParam = (LPARAM)StartPath;

	pidl = SHBrowseForFolder(&bi);

	if (pidl == NULL)
	{
		return FALSE;
	}

	SHGetPathFromIDList(pidl, szFolder);

	if (SHGetMalloc(&pMalloc) != NOERROR)
	{
		return FALSE;
	}

	pMalloc->Free(pidl);
	pMalloc->Release();
	return TRUE;
}



#endif // 주석


#if 0 // 코드만
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Sample_2");
HWND hWndMain;

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

#include <ShlObj.h>

BOOL BrowseFolder(HWND hParent, LPCTSTR szTitle, LPCTSTR StartPath, TCHAR* szFolder);

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR* Mes = TEXT("마우스 왼쪽 버튼을 눌러 폴더를 선택하세요");
	static TCHAR StartPath[MAX_PATH];
	TCHAR Folder[MAX_PATH];


	switch (iMessage)
	{
	case WM_CREATE:
		hWndMain = hWnd;
		return 0;

	case WM_LBUTTONDOWN:
		if (BrowseFolder(hWnd, TEXT("폴더를 선택하시오"), StartPath, Folder))
		{
			MessageBox(hWnd, Folder, TEXT("선택한 폴더"), MB_OK);
			lstrcpy(StartPath, Folder);
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

int CALLBACK BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch (uMsg)
	{
	case BFFM_INITIALIZED:
		if (lpData != NULL)
		{
			SendMessage(hWnd, BFFM_SETSELECTION, TRUE, (LPARAM)lpData);
		}
		break;
	}
	return 0;
}

BOOL BrowseFolder(HWND hParent, LPCTSTR szTitle, LPCTSTR StartPath, TCHAR* szFolder)
{
	LPMALLOC pMalloc;
	LPITEMIDLIST pidl;
	BROWSEINFO bi;

	bi.hwndOwner = hParent;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = NULL;
	bi.lpszTitle = szTitle;
	bi.ulFlags = 0;
	bi.lpfn = BrowseCallbackProc;
	bi.lParam = (LPARAM)StartPath;

	pidl = SHBrowseForFolder(&bi);

	if (pidl == NULL)
	{
		return FALSE;
	}

	SHGetPathFromIDList(pidl, szFolder);

	if (SHGetMalloc(&pMalloc) != NOERROR)
	{
		return FALSE;
	}

	pMalloc->Free(pidl);
	pMalloc->Release();
	return TRUE;
}


#endif // 코드만


#endif // Total