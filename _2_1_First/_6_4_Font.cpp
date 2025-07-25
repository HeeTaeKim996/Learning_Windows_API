#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	 폰트 설정 ( HFONT ) 에 관한 코드입니다
----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Font");

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


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HFONT hFont, OldFont;
	TCHAR st[64];

	static LOGFONT lf;


	switch (iMessage)
	{
	case WM_CREATE:

	{ // 설정을 변수로 저장할 수 있고, 함수 호출 때 인자 전달이 위 방법에 비해 적으니, 자주 쓰는 폰트라면 더 효율적
		lf.lfHeight = 50;
		lf.lfWidth = 0;
		lf.lfEscapement = 0;
		lf.lfOrientation = 0;
		lf.lfWeight = 0;
		lf.lfItalic = 0;
		lf.lfUnderline = 0;
		lf.lfStrikeOut = 0;
		lf.lfCharSet = HANGEUL_CHARSET;
		lf.lfOutPrecision = 0;
		lf.lfClipPrecision = 0;
		lf.lfQuality = 0;
		lf.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
		lstrcpy(lf.lfFaceName, TEXT("궁서"));
	}

	return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		{
			hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN,
				TEXT("궁서"));
			/* ○ CreateFont
				- (1) 크기와 마지막항인 (14) 글씨체 만 기억해도 된다. 나머지 12 인자는 만질 일이 많이 없음..

				○ 그래도 기능은 적어놔야하니, 기능들 나열함
				- (1)	: 글씨체 크기
				- (2)	: 자간
				- (3)	: x축 기준 전체 기울기
				- (4)	: x축 기준 문자 개별 기울기
				- (5)	: 폰트 두께
				- (6)	: 기울임체.	타입은 DWORD지만 TRUE FALSE
				- (7)	: 밑줄.		타입은 DWORD지만 TRUE FALSE
				- (8)	: 관통선.		타이은 DWORD지만 TRUE FALSE
				- (9)	: (설명봐도모르겠음. 중요하진 않음)
				- (10)	: (설명봐도모르겠음. 중요하진 않음)
				- (11)	: (설명봐도모르겠음. 중요하진 않음)
				- (12)	: (설명봐도모르겠음. 중요하진 않음)
				- (13)	: (설명봐도모르겠음. 중요하진 않음)
				- (14)  : 글꼴
			*/

			OldFont = (HFONT)SelectObject(hdc, hFont);

			lstrcpy(st, TEXT("폰트 Test 1234"));
			TextOut(hdc, 100, 100, st, lstrlen(st));

			DeleteObject(SelectObject(hdc, OldFont));
		}


		{ // ※ WM_CREATE 에서 만든 폰트 사용
			hFont = CreateFontIndirect(&lf);
			OldFont = (HFONT)SelectObject(hdc, hFont);

			SetTextColor(hdc, RGB(255, 0, 0)); // ※ 글자색 설정
			SetBkColor(hdc, RGB(0, 0, 255)); // ※ 글자 배경색 설정 
			SetBkMode(hdc, OPAQUE); // ※ 배경색상을 사용할 방법 설정. OPAQUE vs TRANSPARENT


			TextOut(hdc, 100, 200, st, lstrlen(st));

			DeleteObject(SelectObject(hdc, OldFont));
		}

		{
			lf.lfHeight = 40;
			lstrcpy(st, TEXT("     Cute Harry"));
			SetTextColor(hdc, RGB(0, 0, 0, ));
			SetBkMode(hdc, TRANSPARENT);

			for (int i = 0; i <= 800; i += 200)
			{
				lf.lfEscapement = i;
				hFont = CreateFontIndirect(&lf);
				OldFont = (HFONT)SelectObject(hdc, hFont);
				TextOut(hdc, 0, 600, st, lstrlen(st));

				DeleteObject(SelectObject(hdc, OldFont));
			}

		}


		EndPaint(hWnd, &ps);
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
LPCTSTR lpszClass = TEXT("Font");

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


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	HFONT hFont, OldFont;

	TCHAR st[64];
	static LOGFONT lf;



	switch (iMessage)
	{
	case WM_CREATE:

		lf.lfHeight = 50;
		lf.lfWidth = 0;
		lf.lfEscapement = 0;
		lf.lfOrientation = 0;
		lf.lfWeight = 0;
		lf.lfItalic = 0;
		lf.lfUnderline = 0;
		lf.lfStrikeOut = 0;
		lf.lfCharSet = HANGUL_CHARSET;
		lf.lfOutPrecision = 0;
		lf.lfClipPrecision = 0;
		lf.lfQuality = 0;
		lf.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
		lstrcpy(lf.lfFaceName, TEXT("궁서"));

		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		{
			hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN,
				TEXT("궁서"));
			OldFont = (HFONT)SelectObject(hdc, hFont);

			lstrcpy(st, TEXT("폰트 Test 1234"));
			TextOut(hdc, 100, 100, st, lstrlen(st));

			DeleteObject(SelectObject(hdc, OldFont));
		}


		{
			hFont = CreateFontIndirect(&lf);
			OldFont = (HFONT)SelectObject(hdc, hFont);

			SetTextColor(hdc, RGB(255, 0, 0));
			SetBkColor(hdc, RGB(0, 0, 255));
			SetBkMode(hdc, OPAQUE);

			TextOut(hdc, 100, 200, st, lstrlen(st));

			DeleteObject(SelectObject(hdc, OldFont));
		}

		{
			lf.lfHeight = 40;
			lstrcpy(st, TEXT("    Cute Bori"));
			SetTextColor(hdc, RGB(0, 0, 0, ));
			SetBkMode(hdc, TRANSPARENT);

			for (int i = 0; i <= 800; i += 200)
			{
				lf.lfEscapement = i;
				hFont = CreateFontIndirect(&lf);
				OldFont = (HFONT)SelectObject(hdc, hFont);
				TextOut(hdc, 0, 600, st, lstrlen(st));

				DeleteObject(SelectObject(hdc, OldFont));
			}
		}

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