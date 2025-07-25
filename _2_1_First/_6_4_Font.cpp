#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	 ��Ʈ ���� ( HFONT ) �� ���� �ڵ��Դϴ�
----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
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

	{ // ������ ������ ������ �� �ְ�, �Լ� ȣ�� �� ���� ������ �� ����� ���� ������, ���� ���� ��Ʈ��� �� ȿ����
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
		lstrcpy(lf.lfFaceName, TEXT("�ü�"));
	}

	return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		{
			hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN,
				TEXT("�ü�"));
			/* �� CreateFont
				- (1) ũ��� ���������� (14) �۾�ü �� ����ص� �ȴ�. ������ 12 ���ڴ� ���� ���� ���� ����..

				�� �׷��� ����� ��������ϴ�, ��ɵ� ������
				- (1)	: �۾�ü ũ��
				- (2)	: �ڰ�
				- (3)	: x�� ���� ��ü ����
				- (4)	: x�� ���� ���� ���� ����
				- (5)	: ��Ʈ �β�
				- (6)	: �����ü.	Ÿ���� DWORD���� TRUE FALSE
				- (7)	: ����.		Ÿ���� DWORD���� TRUE FALSE
				- (8)	: ���뼱.		Ÿ���� DWORD���� TRUE FALSE
				- (9)	: (��������𸣰���. �߿����� ����)
				- (10)	: (��������𸣰���. �߿����� ����)
				- (11)	: (��������𸣰���. �߿����� ����)
				- (12)	: (��������𸣰���. �߿����� ����)
				- (13)	: (��������𸣰���. �߿����� ����)
				- (14)  : �۲�
			*/

			OldFont = (HFONT)SelectObject(hdc, hFont);

			lstrcpy(st, TEXT("��Ʈ Test 1234"));
			TextOut(hdc, 100, 100, st, lstrlen(st));

			DeleteObject(SelectObject(hdc, OldFont));
		}


		{ // �� WM_CREATE ���� ���� ��Ʈ ���
			hFont = CreateFontIndirect(&lf);
			OldFont = (HFONT)SelectObject(hdc, hFont);

			SetTextColor(hdc, RGB(255, 0, 0)); // �� ���ڻ� ����
			SetBkColor(hdc, RGB(0, 0, 255)); // �� ���� ���� ���� 
			SetBkMode(hdc, OPAQUE); // �� �������� ����� ��� ����. OPAQUE vs TRANSPARENT


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





#endif // �ּ�


#if 1 // �ڵ常
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
		lstrcpy(lf.lfFaceName, TEXT("�ü�"));

		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		{
			hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN,
				TEXT("�ü�"));
			OldFont = (HFONT)SelectObject(hdc, hFont);

			lstrcpy(st, TEXT("��Ʈ Test 1234"));
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

#endif // �ڵ常


#endif // Total