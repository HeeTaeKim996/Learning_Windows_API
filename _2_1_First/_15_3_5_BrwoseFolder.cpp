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
	 - pidlRoot			: ?
	 - pszDisplayName	: ?
	 - lpszTitle		: 상단에 표시할 타이틀
	 - uFlags			: 대화상자의 동작 옵션
	 - lpfn				: 콜백함수의 포인터. SHBrowseForFolder 는 BROWSEINFO 의 lfpn 이 할당될시, SHBroweForFolder
						  호출 초기인, 대화상자 초기화 때 lpfn 에 할당된 함수를 호출. 호출하는 함수의 (4)항에는,
						  바로 밑에 설명하는 lParam 을 인자로 넣어 호출.
	 - lParam			: 콜백함수의 (4)항에 입력될 인자
	 
	 ○ BroweCallbackProc
	  - 위에 BrowseInfo의 lpfn 에서 설명했듯, SHBorwseForFolder 에서 대화상자 초기화 때 호출되도록 하는 함수
	  - 아래 코드에서는 BROWSEINFO 의 lParam 인자로 받은 StartPath (TCHAR[]) 를 대화상자의 초기 경로로 설정하는 역할

	 ○ SHGetPathFromIDList
	  - SHBrowseForFolder 로 반환된 LPITEMIDLIST 를, 실제 경로 문자열로 반환하는 함수
	   
	 ○ SHGetMalloc
	  - ??? 이부분을 이해못함.. @@@@@@@@ 추후 추가정리!!!

	  ※ 지피티 추가 질문 예정 내용!! @@@@@@@@@@@@@@@@@
	  1) SH 는 WND에 하나만 할당되나? 어떻게 SHBrowseForFolder 를 했는데, 
		  SHGetMalloc 으로 유효? 했었는지를 판단할 수 있는지.

	  2) BROWSEINFO 의 pidlRoot, pszDisplayName

	  3) BFFM_INITAILIZED 가 호출되는 타임은 대충 이해하겠음 ( 대화상자가 초기화 될 때 ) 그렇다면, hWnd (부모 WND)  에 
	     SendMEssage로  BFFM_SETSELECTION 을 호출시, lpData 로 StartPath
	     (TCHAR[] ) 를 인자로, SendMessage 하면, 어떻게 대화상자가 StartPath를 초기값을 갖는 상태로 시작할 수 있는 건지? 
		 BFFM_SETSELECTION 을 처리하는 코드가 어디에 있나? #include <SHlob.h> 에 있는건가?

----------------------------------------------------------------------------------------------------*/


#if 1 // 주석
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