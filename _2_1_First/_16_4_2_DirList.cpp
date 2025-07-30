#if 0 // Total
/*-------------------------------------------------------------------------------------------------------------------
	LB_DIR 로 특정 주소 + 패턴의 특정 속성의 파일+디렉터리를 리스트 요소로 사용하는 코드입니다.
	
	■ LB_DIR
	 - (3)인 WPARAM 에 검색 대상 조건, (4)인 LPARAM 에 [ 주소 + 패턴 ] 입력시, 해당 주소의 패턴을 리스트 요소로 입력
	  ※ (3)항 WPARAM 플래그 일부 정리
	      - DDL_ARCHIVE		: 파일에서 아카이브 속성이 있는 파일들만 검색. 대부분 아카이브 속성을 지니니, 대부분 파일을 검색한다 라보면됨
		  - DDL_DIRECTORY	: 디렉토리를 검색
		  - DDL_DRIVE		: 드라이브 가 있을시, -C-, -D- 형식으로 표기
		  - DDL_READWRITE	: 파일의 읽기-쓰기 속성이 있는 파일을 검색. 대부분이 읽기-쓰기 속성을 지니니, 대부분 파일을 검색한다 보면됨


	 ○ DlgDirSelectEx
	  - (4) HMENU 인 리스트위 요소를, (2) 인  TCHAR* 에 할당.만약 (2) 가 디렉터리 로 판단될시, BOOL TRUE 리턴. 아닐시, FALSE 리턴

-------------------------------------------------------------------------------------------------------------------*/


#if 0 // 주석
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


#define ID_LISTBOX 100
HWND hList;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR File[MAX_PATH];
	TCHAR Mes[256];
	BOOL dir;


	switch (iMessage)
	{
	case WM_CREATE:
		hList = CreateWindow(TEXT("listbox"), NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_NOTIFY,
			10, 10, 300, 200,
			hWnd, (HMENU)ID_LISTBOX, g_hInst, NULL);
		SendMessage(hList, LB_DIR, (WPARAM)(DDL_ARCHIVE | DDL_DIRECTORY | DDL_DRIVES | DDL_READWRITE), (LPARAM)TEXT("c:\\Windows\\*.*"));
		
		return 0;
		

	case WM_LBUTTONDOWN:
		dir = DlgDirSelectEx(hWnd, File, MAX_PATH, ID_LISTBOX);
		if (lstrlen(File) != 0)
		{
			if (dir)
			{
				wsprintf(Mes, TEXT("%s 디렉토리를 선택했습니다."), File);
			}
			else
			{
				wsprintf(Mes, TEXT("%s 파일을 선택했습니다."), File);
			}

			MessageBox(hWnd, Mes, TEXT("알림"), MB_OK);
		}
		return 0;



	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석


#if 1 // 코드만
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



#define ID_LISTBOX 100

HWND hList;


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR File[MAX_PATH];
	TCHAR Mes[256];
	BOOL dir;

	switch (iMessage)
	{
	case WM_CREATE:
		hList = CreateWindow(TEXT("listbox"), NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_NOTIFY,
			10, 10, 300, 200,
			hWnd, (HMENU)ID_LISTBOX, g_hInst, NULL);

		SendMessage(hList, LB_DIR, (WPARAM)(DDL_ARCHIVE | DDL_DIRECTORY | DDL_DRIVES | DDL_READWRITE),
			(LPARAM)TEXT("C:\\Windows\\*.*"));

		return 0;
		

	case WM_LBUTTONDOWN:
		dir = DlgDirSelectEx(hWnd, File, MAX_PATH, ID_LISTBOX);
		if (lstrlen(File) != 0)
		{
			if (dir)
			{
				wsprintf(Mes, TEXT("%s 디렉터리를 선택했습니다."), File);
			}
			else
			{
				wsprintf(Mes, TEXT("%s 파일을 선택했습니다"), File);
			}
			
			MessageBox(hWnd, Mes, TEXT("알림"), MB_OK);
		}
		
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // 코드만


#endif // Total