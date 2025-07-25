#if 0 // Total
/*----------------------------------------------------------------------------------------------------
     텍스트 입력 윈도우인 Edit에 대한 코드입니다. 쓰임새가 아주 많을 것 같습니다.
	 추가로, Edit의 기능 외에, 지금까지 배운 Button, Edit 은 모두 윈도우이기 때문에,
	 Edit를 MoveWindow, HideWindow 가 가능함을 코드로 보입니다.

	 Buttom, Edit은 윈도우이기 때문에, 자체로 WinMain, WndProc, SendMessage 를 자체로 처리합니다
----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_Edit");

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
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
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

#define ID_EDIT 100
HWND hEdit;
int nTop = 10;
BOOL bShow = TRUE;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[128];

	const TCHAR* Mes = TEXT("Up_DownArrow : 에디트위아래이동. Space : 보임/숨김");

	switch (iMessage)
	{
	case WM_CREATE:
		hEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 10, 200, 25,
			hWnd, (HMENU)ID_EDIT, g_hInst, NULL);
		/* ○ 3항 ES ENUM
			- ES_AUTOHSCROLL	: 수평 스크롤을 지원
			- ES_AUTOVSCROLL	: 여러 줄 편집시 수직 스크롤을 지원
			- ES_LEFT			: 왼쪽 정렬
			- ES_CENTER			: 중앙 정렬
			- ES_RIGHT			: 오른쪽 정렬
			- ES_LOWERCASE		: 소문자로 변환하여 표시
			- ES_UPPDERCASE		: 대문자로 변환하여 표시
			- ES_MULTILINE		: 여러 줄을 편집 가능
			- ES_NOHIDESEEL		: 포커스를 잃더라도 선택된 영역을 표시
			- ES_READONLY		: 읽기 전용으로 만들어 편집을 금지
		*/
		SetWindowText(hEdit, TEXT("에디트도 윈도우다. 여기 클릭하면 텍스트 수정 가능"));

		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_EDIT:
			switch (HIWORD(wParam))
			{
				/* ○ EN ENUM
					- EN_CHANGE		: 문자열이 변경됨
					- EN_ERRSPACE	: 메모리가 부족
					- EN_HSCROLL	: 사용자가 수평 스크롤 바를 클릭
					- EN_VSCROLL	: 사용자가 수직 스크롤 바를 클릭
					- EN_KILLFOCUS	: 포커스를 잃었다
					- EN_SETFOCUS	: 포커스를 얻었다
					- EN_MAXTEXT	: 지정한 문자열 길이를 초과하였다
					- EN_UPDATE		: 문자열이 변경되기 직전이다
					 ※ EN_CHANGE 와 EN_UPDATE의 차이는,
					   EN_CHANGE 는 문자열이 화면에서 변경된 직후,
					   EN_UPDATE 는 문자열이 화면에서 변경되기 직전
					   -> 둘 기능이 거의 같기 때문에, 보통 둘 중 하나 사용. 주로 EN_CHAGE 사용
				*/
			case EN_CHANGE:
				GetWindowText(hEdit, str, 128); // ※ Get에서 str 수정. str이 배열 또는 포인터일테니.. &생략 가능.
				SetWindowText(hWnd, str); // ※ (1)의 HWND의 lpWindowName 을 변경된 str로 교체한다
				break;
			}

			break;
		}

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			nTop -= 10;
			MoveWindow(hEdit, 10, nTop, 220, 25, TRUE);
			break;
		case VK_DOWN:
			nTop += 10;
			MoveWindow(hEdit, 10, nTop, 220, 25, TRUE);
			break;

		case VK_SPACE:
			if (bShow)
			{
				bShow = FALSE;
				ShowWindow(hEdit, SW_HIDE);
			}
			else
			{
				bShow = TRUE;
				ShowWindow(hEdit, SW_SHOW);
			}
			break;
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

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_Edit");

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
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
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

#define ID_EDIT 100
HWND hEdit;
int nTop = 10;
BOOL bShow = TRUE;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[128];

	const TCHAR* Mes = TEXT("Up_DownArrow : 에디터위아래 이동. Space : 보임/숨김");

	switch (iMessage)
	{
	case WM_CREATE:
		hEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 10, 200, 25,
			hWnd, (HMENU)ID_EDIT, g_hInst, NULL);
		SetWindowText(hEdit, TEXT("에디트도 윈도우다. 여기 클릭하면 텍스트 수정 가능"));

		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_EDIT:
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
				GetWindowText(hEdit, str, 128);
				SetWindowText(hWnd, str);
				break;
			}

			break;
		}

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			nTop -= 10;
			MoveWindow(hEdit, 10, nTop, 220, 25, TRUE);
			break;
		case VK_DOWN:
			nTop += 10;
			MoveWindow(hEdit, 10, nTop, 220, 25, TRUE);
			break;
		case VK_SPACE:
			if (bShow)
			{
				bShow = FALSE;
				ShowWindow(hEdit, SW_HIDE);
			}
			else
			{
				bShow = TRUE;
				ShowWindow(hEdit, SW_SHOW);
			}
			break;
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