#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	��ũ�ѹٿ� ���� �ڵ��Դϴ�.
	��ũ�� �� ��ü�� HWND �� �ϴ� 3���� ��ũ�ѹٷ�, R G B �� �����ϴ� �ڵ��,
	���� ������ HWND �� �μ����� HSCROLL, VSCROLL �� �߰��Ͽ�, Background�� �̵��ϴ� �ڵ� �Դϴ�.
----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
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
		WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL, // �� WS_HSCROLL | WS_VSCROLL �߰�
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
			/* �� SBS
				- SBS_HORZ : ���� ��Ʈ�ѹ�
				- SBS_VERT : ���� ��Ʈ�ѹ�

			   �� WS
				- WS_HSCROLL : ���� ��Ʈ�� (������ ���� ��Ʈ�ѹ�)
				- WS_VSCROLL : ���� ��Ʈ�� (������ ���� ��Ʈ�ѹ�)
			*/

			SetScrollRange(hRed, SB_CTL, sb_min, sb_max, TRUE);
			/* �� SetScrollRange
				�� (2)
				 - SB_CTL	: HWND�� ��ũ�ѹ� ��ü . CreateWindow �� TEXT("scrollbar") �� ���� HWND�� ���� ���
				 - SB_HORZ	: ������ ���� ��ũ�ѹ��� ��, HORZ �뵵�� ���
				 - SB_VERT	: ������ ���� ��ũ�ѹ��� ��, VERT �뵵�� ���

				�� (5) : TRUE��, ��ũ�ѹ� ������, �ش� hWnd ȭ�� �ڵ� ����, FALSE��, InvalidateRect�� ���� ���� �ʿ�
			*/


			SetScrollPos(hRed, SB_CTL, sb_min, TRUE); // (3) �� ������ ��ũ�ѹ� Value ����

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


			/* �� SetScrollInfo / GetScrollInfo �� SCROLLINFO
				- SB_CTL ��ũ�ѹٿ� �ٸ���, SB_HORZ, SB_VERT�� ��������� ������ ���� ���Ǵ� ��ũ�ѹٴ�
				  WPARAM, LPARAM���� ���� �����ϱ⿡�� ������ �����ؼ�,
				  SCROLLINFO ����ü�� �����
				- SB_CTL�� SetScrollRange - SetScrolllPos �� ��ɵ�, SetScrollInfo �Լ��� �����Ͽ� ���

			   �� SCROLLINFO
				- cbSize	: ����ü ũ��
				- fMask		: � ����� ����ϰų�, ������ ������ ����
				- nMin		: ��ũ�� ������ �ּҰ�
				- nMax		: ��ũ�� ������ �ִ밪
				- nPage		: �ѹ��� ǥ�ð����� �������� ũ��
				- nPos		: ���� ��ũ�� ��ġ
				- nTrackPos	: �巡������ ��ũ�� ��ġ

				�� cbSize
				 - &SCROLLINFO(instance) �� ���� ����ü��, SetScrollInfo, GetScrollInfo ����
				   memcpy�� �����ϴµ�, �������� SCROLLINFO�� ũ�Ⱑ �ٸ� �� �ִ� �Ѵ�.
				   ������ �����ϱ� ����, cbSize�� ���� �ʿ�


				�� fMask
				 - GetScrollInfo, SetScrollInfo �� ������ �ְ���� ��, fMask�� ������ ���� ����,
				  SCROLLINFO�� Ư�� ����� �Լ��� ����, �Լ��� �޾ƿ´�.
				 - SIF_RANGE			: nMin, nMax ���
				 - SIF_PAGE				: nPage
				 - SIF_POS				: nPos
				 - SIF_TRACKPOS			: nTrackPos
				 - SIF_ALL				: SIF_RANGE | SIF_PAGE | SIF_POS | SIF_TRACKPOS

				  ==> SIF_RANGE�� �ϸ�, SCROLLINFO�� nPos�� SetSCroll.. �� ����, GetScroll..�� ���� �޾ƿ��� �Ұ�

			*/
		}


		return 0;
	}

	case WM_HSCROLL:

		if ((HWND)lParam != 0) // ScrollBars    �� ������ ��ü ��ũ�ѹ��� ���, (HWND)lParam == hWnd �� �ƴ�, (HWND)lParam == 0�̴�.
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
			case SB_THUMBTRACK: // �� SB_THUMBTRACK : ��ũ�ѹٸ� �巡�� ���� �� ȣ��
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





#endif // �ּ�


#if 1 // �ڵ常
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

#endif // �ڵ常


#endif // Total