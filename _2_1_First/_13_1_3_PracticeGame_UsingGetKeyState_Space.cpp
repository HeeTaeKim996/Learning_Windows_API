#if 0 // Total

#include <Windows.h>
#include "resource.h"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_GetKeyState");
HWND hWndMain;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
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



void StartGame();
void RunGame();
void DrawGame(HDC hdc);
void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit);

struct tag_Mete
{
	float x, y;
	float dx, dy;
};

tag_Mete arMete[1000];
int Num;
double sx = 200, sy = 150;
DWORD st;
HBITMAP Ship;
BOOL bStart;
TCHAR sEllapse[32];


#define moveMaxSpeed  4.f

short prevLeftKey;
short prevRightKey;
short prevUpKey;
short prevDownKey;

enum VertState
{
	Ver_None, Ver_Down, Ver_Up
}verState;
enum HorzState
{
	Hor_None, Hor_Left, Hor_Right
}horzState;

float speed;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt;

	switch (iMessage)
	{
	case WM_CREATE:
		hWndMain = hWnd;
		
		SetRect(&rt, 0, 0, 400, 300);
		AdjustWindowRect(&rt, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
		MoveWindow(hWnd, 100, 100, rt.right - rt.left, rt.bottom - rt.top, FALSE);

		srand(GetTickCount());
		Ship = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_SpacePlane));
		bStart = FALSE;
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			if (!bStart)
			{
				StartGame();
			}

			break;
		}
		return 0;

	case WM_TIMER:
		RunGame();
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		DrawGame(hdc);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		DeleteObject(Ship);
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void StartGame()
{
	Num = 50;
	for (int i = 0; i < Num; i++)
	{
		int t = rand() % 1400;
		if (t < 400)
		{
			arMete[i].x = t;
			arMete[i].y = 5;
		}
		else if (t < 700)
		{
			arMete[i].x = 395;
			arMete[i].y = t - 400;
		}
		else if (t < 1100)
		{
			arMete[i].x = t - 700;
			arMete[i].y = 295;
		}
		else
		{
			arMete[i].x = 5;
			arMete[i].y = t - 1100;
		}

		arMete[i].dx = rand() % 51 / 10.0 - 2.5;
		arMete[i].dy = rand() % 51 / 10.0 - 2.5;
	}

	sx = 200;
	sy = 150;

	bStart = TRUE;

	st = GetTickCount();


	prevLeftKey = prevRightKey = prevUpKey = prevDownKey = 0;
	verState = Ver_None;
	horzState = Hor_None;
	speed = 0.f;

	SetTimer(hWndMain, 1, 20, NULL);
}





void RunGame()
{
	RECT srt;
	POINT pt;

	
	short leftCur = GetKeyState(VK_LEFT) & 0x8000;
	if (leftCur != prevLeftKey)
	{
		if (leftCur) // GetKeyDown?
		{
			horzState = Hor_Left;
		}
		else // == GetKeyUp ??
		{
			if (!prevRightKey)
			{
				horzState = Hor_None;
			}
		}
		
		prevLeftKey = leftCur;
	}

	short rightCur = GetKeyState(VK_RIGHT) & 0x8000;
	if (rightCur != prevRightKey)
	{
		if (rightCur) 
		{
			horzState = Hor_Right;
		}
		else
		{
			if (!prevLeftKey)
			{
				horzState = Hor_None;
			}
		}

		prevRightKey = rightCur;
	}

	short upCur = GetKeyState(VK_UP) & 0x8000;
	if (upCur != prevUpKey)
	{
		if (upCur)
		{
			verState = Ver_Up;
		}
		else
		{
			if (!prevDownKey)
			{
				verState = Ver_None;
			}
		}

		prevUpKey = upCur;
	}

	short downCur = GetKeyState(VK_DOWN) & 0x8000;
	if (downCur != prevDownKey)
	{
		if (downCur)
		{
			verState = Ver_Down;
		}
		else
		{
			if (!prevUpKey)
			{
				verState = Ver_None;
			}
		}

		prevDownKey = downCur;
	}


	if (verState != Ver_None || horzState != Hor_None)
	{
		speed += 0.3f;
		if (speed > moveMaxSpeed)
		{
			speed = moveMaxSpeed;
		}

		if (horzState != Hor_None && verState == Ver_None)
		{
			if (horzState == Hor_Right)
			{
				sx += speed;
			}
			else
			{
				sx -= speed;
			}
		}
		else if (horzState == Hor_None && verState != Ver_None)
		{
			if (verState == Ver_Up)
			{
				sy -= speed;
			}
			else
			{
				sy += speed;
			}
		}
		else
		{
			float move = speed / 1.4142135623730951;

			if (horzState == Hor_Right)
			{
				sx += move;
			}
			else
			{
				sx -= move;
			}

			if (verState == Ver_Up)
			{
				sy -= move;
			}
			else
			{
				sy += move;
			}
		}

		if (horzState == Hor_Right)
		{
			if (sx > 400)
			{
				sx = 400;
			}
		}
		else if (horzState == Hor_Left)
		{
			if (sx < 0)
			{
				sx = 0;
			}
		}

		if (verState == Ver_Up)
		{
			if (sy < 0)
			{
				sy = 0;
			}
		}
		else if (verState == Ver_Down)
		{
			if (sy > 300)
			{
				sy = 300;
			}
		}
	}
	else
	{
		speed -= 0.4f;
		if (speed < 0)
		{
			speed = 0;
		}
	}




	SetRect(&srt, (int)sx + 2, int(sy) + 2, (int)sx + 10, (int)sy + 10);

	for (int i = 0; i < Num; i++)
	{
		arMete[i].x += arMete[i].dx;
		arMete[i].y += arMete[i].dy;

		if (arMete[i].x > 400) arMete[i].x = 0;
		if (arMete[i].x < 0) arMete[i].x = 400;
		if (arMete[i].y > 300) arMete[i].y = 0;
		if (arMete[i].y < 0) arMete[i].y = 300;

		pt.x = int(arMete[i].x);
		pt.y = int(arMete[i].y);

		if(PtInRect(&srt, pt))
		{
			KillTimer(hWndMain, 1);
			bStart = FALSE;
		}
	}

	wsprintf(sEllapse, TEXT("%dÃÊ"), (GetTickCount() - st) / 1'000);
	InvalidateRect(hWndMain, NULL, TRUE);
}

void DrawGame(HDC hdc)
{
	for (int i = 0; i < Num; i++)
	{
		SetPixel(hdc, int(arMete[i].x), int(arMete[i].y), RGB(255, 255, 0));
		SetPixel(hdc, int(arMete[i].x + 1), int(arMete[i].y), RGB(255, 255, 0));
		SetPixel(hdc, int(arMete[i].x), int(arMete[i].y + 1), RGB(255, 255, 0));
		SetPixel(hdc, int(arMete[i].x) + 1, int(arMete[i].y + 1), RGB(255, 255, 0));
		SetPixel(hdc, int(arMete[i].x) - 1, int(arMete[i].y), RGB(255, 255, 0));
	}

	DrawBitmap(hdc, (int)sx, (int)sy, Ship);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, 350, 5, sEllapse, lstrlen(sEllapse));
}

void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit)
{
	HDC MemDC = CreateCompatibleDC(hdc);
	HBITMAP OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);
	BITMAP bit;
	GetObject(hBit, sizeof(BITMAP), &bit);

	StretchBlt(hdc, x, y, 8, 8, MemDC, 0, 0, bit.bmWidth, bit.bmHeight, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);

}


#endif // Total