#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	스크롤바에 대한 코드입니다.
	스크롤 바 자체를 HWND 로 하는 3개의 스크롤바로, R G B 를 조정하는 코드와,
	메인 윈도우 HWND 에 부속으로 HSCROLL, VSCROLL 을 추가하여, Background를 이동하는 코드 입니다.
----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_ScrollBar");

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

	hWnd = CreateWindow(lpszClass, lpszClass,
		WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL, // ※ WS_HSCROLL | WS_VSCROLL 추가
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




enum
{
	ID_SCRRED = 100, ID_SCRGREEN = 101, ID_SCRBLUE = 102
};

enum
{
	sb_min = 0, sb_max = 255
};
HWND hRed, hGreen, hBlue;
int Red, Green, Blue;


enum
{
	VIRTUAL_WIDTH = 1'000,
	VIRTUAL_HEIGHT = 800
};
int backXPos = 0;
int backYPos = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	HBRUSH hBrush, OldBrush;
	int TempPos;



	switch (iMessage)
	{
	case WM_CREATE:
	{
		{ // ScrollBars

			hRed = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
				10, 10, 400, 20,
				hWnd, (HMENU)ID_SCRRED, g_hInst, NULL);
			/* ○ SBS
				- SBS_HORZ : 수평 컨트롤바
				- SBS_VERT : 수직 컨트롤바

			   ○ WS
				- WS_HSCROLL : 수평 컨트롤 (윈도우 내에 컨트롤바)
				- WS_VSCROLL : 수직 컨트롤 (윈도우 내에 컨트롤바)
			*/

			SetScrollRange(hRed, SB_CTL, sb_min, sb_max, TRUE);
			/* □ SetScrollRange
				○ (2)
				 - SB_CTL	: HWND가 스크롤바 자체 . CreateWindow 를 TEXT("scrollbar") 로 만든 HWND에 고정 사용
				 - SB_HORZ	: 윈도우 내에 스크롤바일 때, HORZ 용도로 사용
				 - SB_VERT	: 윈도우 내에 스크롤바일 때, VERT 용도로 사용

				○ (5) : TRUE시, 스크롤바 수정시, 해당 hWnd 화면 자동 갱신, FALSE시, InvalidateRect로 수동 조정 필요
			*/


			SetScrollPos(hRed, SB_CTL, sb_min, TRUE); // (3) 항 값으로 스크롤바 Value 설정

			hGreen = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
				10, 40, 400, 20,
				hWnd, (HMENU)ID_SCRGREEN, g_hInst, NULL);
			SetScrollRange(hGreen, SB_CTL, sb_min, sb_max, TRUE);
			SetScrollPos(hGreen, SB_CTL, sb_min, TRUE);

			hBlue = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
				10, 70, 400, 20,
				hWnd, (HMENU)ID_SCRBLUE, g_hInst, NULL);
			SetScrollRange(hBlue, SB_CTL, sb_min, sb_max, TRUE);
			SetScrollPos(hBlue, SB_CTL, sb_min, TRUE);

		}


		{ // WndScrollBars
			SCROLLINFO si;
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_RANGE | SIF_PAGE;
			si.nMin = 0;

			si.nMax = VIRTUAL_WIDTH;
			si.nPage = VIRTUAL_WIDTH / 5;
			SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);

			si.nMax = VIRTUAL_HEIGHT;
			si.nPage = VIRTUAL_HEIGHT / 5;
			SetScrollInfo(hWnd, SB_VERT, &si, TRUE);


			/* □ SetScrollInfo / GetScrollInfo 와 SCROLLINFO
				- SB_CTL 스크롤바와 다르게, SB_HORZ, SB_VERT로 만들어지는 윈도우 내에 사용되는 스크롤바는
				  WPARAM, LPARAM으로 정보 전달하기에는 공간이 부족해서,
				  SCROLLINFO 구조체를 사용함
				- SB_CTL의 SetScrollRange - SetScrolllPos 의 기능도, SetScrollInfo 함수로 통합하여 사용

			   ○ SCROLLINFO
				- cbSize	: 구조체 크기
				- fMask		: 어떤 멤버를 사용하거나, 갱신할 것인지 지정
				- nMin		: 스크롤 범위의 최소값
				- nMax		: 스크롤 범위의 최대값
				- nPage		: 한번에 표시가능한 페이지의 크기
				- nPos		: 현재 스크롤 위치
				- nTrackPos	: 드래그중인 스크롤 위치

				※ cbSize
				 - &SCROLLINFO(instance) 로 받은 구조체를, SetScrollInfo, GetScrollInfo 에서
				   memcpy로 복사하는데, 버전마다 SCROLLINFO의 크기가 다를 수 있다 한다.
				   안전히 복사하기 위해, cbSize로 설정 필요


				※ fMask
				 - GetScrollInfo, SetScrollInfo 로 정보를 주고받을 때, fMask에 설정한 값에 따라,
				  SCROLLINFO의 특정 멤버만 함수에 전달, 함수에 받아온다.
				 - SIF_RANGE			: nMin, nMax 사용
				 - SIF_PAGE				: nPage
				 - SIF_POS				: nPos
				 - SIF_TRACKPOS			: nTrackPos
				 - SIF_ALL				: SIF_RANGE | SIF_PAGE | SIF_POS | SIF_TRACKPOS

				  ==> SIF_RANGE만 하면, SCROLLINFO의 nPos는 SetSCroll.. 로 설정, GetScroll..로 정보 받아오기 불가

			*/
		}


		return 0;
	}

	case WM_HSCROLL:

		if ((HWND)lParam != 0) // ScrollBars    ※ 윈도우 자체 스크롤바일 경우, (HWND)lParam == hWnd 가 아닌, (HWND)lParam == 0이다.
		{
			if ((HWND)lParam == hRed)
			{
				TempPos = Red;
			}
			else if ((HWND)lParam == hGreen)
			{
				TempPos = Green;
			}
			else if ((HWND)lParam == hBlue)
			{
				TempPos = Blue;
			}

			switch (LOWORD(wParam))
			{
			case SB_LINELEFT:
				TempPos = max(sb_min, TempPos - 1);
				break;
			case SB_LINERIGHT:
				TempPos = min(sb_max, TempPos + 1);
				break;
			case SB_PAGELEFT:
				TempPos = max(sb_min, TempPos - 10);
				break;
			case SB_PAGERIGHT:
				TempPos = min(sb_max, TempPos + 10);
				break;
			case SB_THUMBTRACK: // ※ SB_THUMBTRACK : 스크롤바를 드래그 중일 때 호출
				TempPos = HIWORD(wParam);
				break;
			}

			if ((HWND)lParam == hRed)
			{
				Red = TempPos;
			}
			else if ((HWND)lParam == hGreen)
			{
				Green = TempPos;
			}
			else if ((HWND)lParam == hBlue)
			{
				Blue = TempPos;
			}

			SetScrollPos((HWND)lParam, SB_CTL, TempPos, TRUE);
			InvalidateRect(hWnd, NULL, FALSE);
		}
		else // WndScrollBar
		{
			SCROLLINFO si;
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_ALL;
			GetScrollInfo(hWnd, SB_HORZ, &si);

			switch (LOWORD(wParam))
			{
			case SB_LINELEFT: backXPos -= 10; break;
			case SB_LINERIGHT: backXPos += 10; break;
			case SB_PAGELEFT: backXPos -= si.nPage; break;
			case SB_PAGERIGHT: backXPos += si.nPage; break;
			case SB_THUMBTRACK: backXPos = si.nTrackPos; break;
			}

			backXPos = max(0, min(backXPos, si.nMax - (int)si.nPage));

			si.fMask = SIF_POS;
			si.nPos = backXPos;
			SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);

			InvalidateRect(hWnd, NULL, TRUE);
		}

		return 0;


	case WM_VSCROLL:
		SCROLLINFO si;

		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_ALL;
		GetScrollInfo(hWnd, SB_VERT, &si);

		switch (LOWORD(wParam))
		{
		case SB_LINELEFT: backYPos -= 10; break;
		case SB_LINERIGHT: backYPos += 10; break;
		case SB_PAGELEFT: backYPos -= si.nPage; break;
		case SB_PAGERIGHT: backYPos += si.nPage; break;
		case SB_THUMBTRACK: backYPos = si.nTrackPos; break;
		}

		backYPos = max(0, min(backYPos, si.nMax - (int)si.nPage));

		si.fMask = SIF_POS;
		si.nPos = backYPos;
		SetScrollInfo(hWnd, SB_VERT, &si, TRUE);

		InvalidateRect(hWnd, NULL, TRUE);

		return 0;


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);


		hBrush = CreateSolidBrush(RGB(Red, Green, Blue));
		OldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		Rectangle(hdc, 10 - backXPos, 100 - backYPos, 410 - backXPos, 300 - backYPos);

		DeleteObject(SelectObject(hdc, OldBrush));


		MoveWindow(hRed, 10 - backXPos, 10 - backYPos, 400, 20, TRUE);
		MoveWindow(hGreen, 10 - backXPos, 40 - backYPos, 400, 20, TRUE);
		MoveWindow(hBlue, 10 - backXPos, 70 - backYPos, 400, 20, TRUE);




		EndPaint(hWnd, &ps);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석


#if 1 // 코드만
#include <Windows.h>

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
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_VREDRAW | CS_HREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
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




enum
{
	ID_SCRRED = 100, ID_SCRGREEN = 101, ID_SCRBLUE = 102
};
enum
{
	sb_min = 0, sb_max = 255
};
HWND hRed, hGreen, hBlue;
int Red, Green, Blue;

enum
{
	VIRTUAL_WIDTH = 1'000,
	VIRTUAL_HEIGHT = 800
};
int backXPos = 0;
int backYPos = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	HBRUSH hBrush, OldBrush;
	int TemPos;


	switch (iMessage)
	{
	case WM_CREATE:

	{ // ScrollBars

		hRed = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
			10, 10, 400, 20,
			hWnd, (HMENU)ID_SCRRED, g_hInst, NULL);
		SetScrollRange(hRed, SB_CTL, sb_min, sb_max, TRUE);
		SetScrollPos(hRed, SB_CTL, sb_min, TRUE);

		hGreen = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
			10, 40, 400, 20,
			hWnd, (HMENU)ID_SCRGREEN, g_hInst, NULL);
		SetScrollRange(hGreen, SB_CTL, sb_min, sb_max, TRUE);
		SetScrollPos(hGreen, SB_CTL, sb_min, TRUE);

		hBlue = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
			10, 70, 400, 20,
			hWnd, (HMENU)ID_SCRBLUE, g_hInst, NULL);
		SetScrollRange(hBlue, SB_CTL, sb_min, sb_max, TRUE);
		SetScrollPos(hBlue, SB_CTL, sb_min, TRUE);
	}


	{ // WndScrollBars

		SCROLLINFO si;
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_RANGE | SIF_PAGE;
		si.nMin = 0;

		si.nMax = VIRTUAL_WIDTH;
		si.nPage = VIRTUAL_WIDTH / 5;
		SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);

		si.nMax = VIRTUAL_HEIGHT;
		si.nPage = VIRTUAL_HEIGHT / 5;
		SetScrollInfo(hWnd, SB_VERT, &si, TRUE);

	}

	return 0;

	case WM_HSCROLL:
	{
		if ((HWND)lParam != 0) // ScrollBars
		{
			if ((HWND)lParam == hRed)
			{
				TemPos = Red;
			}
			else if ((HWND)lParam == hGreen)
			{
				TemPos = Green;
			}
			else if ((HWND)lParam == hBlue)
			{
				TemPos = Blue;
			}

			switch (LOWORD(wParam))
			{
			case SB_LINELEFT:
				TemPos = max(sb_min, TemPos - 1);
				break;
			case SB_LINERIGHT:
				TemPos = min(sb_max, TemPos + 1);
				break;
			case SB_PAGELEFT:
				TemPos = max(sb_min, TemPos - 10);
				break;
			case SB_PAGERIGHT:
				TemPos = min(sb_max, TemPos + 10);
				break;
			case SB_THUMBTRACK:
				TemPos = HIWORD(wParam);
				break;
			}

			if ((HWND)lParam == hRed)
			{
				Red = TemPos;
			}
			else if ((HWND)lParam == hGreen)
			{
				Green = TemPos;
			}
			else if ((HWND)lParam == hBlue)
			{
				Blue = TemPos;
			}

			SetScrollPos((HWND)lParam, SB_CTL, TemPos, TRUE);
			InvalidateRect(hWnd, NULL, FALSE);
		}
		else // WndScrollBar
		{
			SCROLLINFO si;
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_ALL;
			GetScrollInfo(hWnd, SB_HORZ, &si);

			switch (LOWORD(wParam))
			{
			case SB_LINELEFT: backXPos -= 10; break;
			case SB_LINERIGHT: backXPos += 10; break;
			case SB_PAGELEFT: backXPos -= si.nPage; break;
			case SB_PAGERIGHT: backXPos += si.nPage; break;
			case SB_THUMBTRACK: backXPos = si.nTrackPos; break;
			}

			backXPos = max(0, min(backXPos, si.nMax - (int)si.nPage));

			si.fMask = SIF_POS;
			si.nPos = backXPos;
			SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);

			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;
	}

	case WM_VSCROLL:
		SCROLLINFO si;

		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_ALL;
		GetScrollInfo(hWnd, SB_VERT, &si);

		switch (LOWORD(wParam))
		{
		case SB_LINELEFT: backYPos -= 10; break;
		case SB_LINERIGHT: backYPos += 10; break;
		case SB_PAGELEFT: backYPos -= si.nPage; break;
		case SB_PAGERIGHT: backYPos += si.nPage; break;
		case SB_THUMBTRACK: backYPos = si.nTrackPos; break;
		}

		backYPos = max(0, min(backYPos, si.nMax - (int)si.nPage));

		si.fMask = SIF_POS;
		si.nPos = backYPos;
		SetScrollInfo(hWnd, SB_VERT, &si, TRUE);

		InvalidateRect(hWnd, NULL, TRUE);

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);


		hBrush = CreateSolidBrush(RGB(Red, Green, Blue));
		OldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		Rectangle(hdc, 10 - backXPos, 100 - backYPos, 410 - backXPos, 300 - backYPos);

		DeleteObject(SelectObject(hdc, OldBrush));

		MoveWindow(hRed, 10 - backXPos, 10 - backYPos, 400, 20, TRUE);
		MoveWindow(hGreen, 10 - backXPos, 40 - backYPos, 400, 20, TRUE);
		MoveWindow(hBlue, 10 - backXPos, 70 - backYPos, 400, 20, TRUE);

		EndPaint(hWnd, &ps);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // 코드만


#endif // Total