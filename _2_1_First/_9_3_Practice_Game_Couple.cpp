#if 0 // Total
/*-----------------------------------------------------------------------------------------------------
	게임 제작 실습 게임 마지막 내용입니다. 가장 간단한 코드네요.
-----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>
#include "resource.h"
#define random(n) (rand() % n);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("Practice_Game_Couple");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = 0;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, 0, 0,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

enum Status { HIDDEN, FLIP, TEMPFLIP };
struct tag_Cell
{
	int Num;
	Status St;
};
tag_Cell arCell[4][4];
int count;
HBITMAP hShape[9];
enum { RUN, HINT, VIEW } GameStatus;

void InitGame();
void DrawScreen(HDC hdc);
void GetTempFlip(int* tx, int* ty);
int GetRemain();
void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit);

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
	{
		hWndMain = hWnd;

		RECT crt;
		SetRect(&crt, 0, 0, 64 * 4 + 250, 64 * 4);
		AdjustWindowRect(&crt, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);
		SetWindowPos(hWnd, NULL, 0, 0, crt.right - crt.left, crt.bottom - crt.top,
			SWP_NOMOVE | SWP_NOZORDER);
		
		for (int i = 0; i < sizeof(hShape) / sizeof(hShape[0]); i++)
		{
			hShape[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_Couple_0 + i));
		}
		srand(GetTickCount());
		InitGame();
		
		return 0;
	}

	case WM_LBUTTONDOWN:
	{
		int nx = LOWORD(lParam) / 64;
		int ny = HIWORD(lParam) / 64;
		if (GameStatus != RUN || nx > 3 || ny > 3 || arCell[nx][ny].St != HIDDEN)
		{
			return 0;
		}

		int tx, ty;
		GetTempFlip(&tx, &ty);
		if (tx == -1)
		{
			arCell[nx][ny].St = TEMPFLIP;
			InvalidateRect(hWnd, NULL, FALSE);
		}
		else
		{
			count++;
			if (arCell[tx][ty].Num == arCell[nx][ny].Num)
			{
				MessageBeep(0);
				arCell[tx][ty].St = FLIP;
				arCell[nx][ny].St = FLIP;
				InvalidateRect(hWnd, NULL, FALSE);
				if (GetRemain() == 0)
				{
					MessageBox(hWnd, TEXT("축하합니다. 다시 시작합니다."), TEXT("알림"), MB_OK);
					InitGame();
				}
			}
			else
			{
				arCell[nx][ny].St = TEMPFLIP;
				InvalidateRect(hWnd, NULL, FALSE);
				GameStatus = VIEW;
				SetTimer(hWnd, 1, 1'000, NULL);
			}
		}
		
		return 0;
	}

	case WM_TIMER:
		switch (wParam)
		{
		case 0:
		{
			KillTimer(hWnd, 0);
			GameStatus = RUN;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case 1:
		{
			KillTimer(hWnd, 1);
			GameStatus = RUN;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (arCell[i][j].St == TEMPFLIP)
					{
						arCell[i][j].St = HIDDEN;
					}
				}
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		}
		return 0;


	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		DrawScreen(hdc);
		EndPaint(hWnd, &ps);
		return 0;
	}
		

	case WM_DESTROY:
	{
		for (int i = 0; i < sizeof(hShape) / sizeof(hShape[0]); i++)
		{
			DeleteObject(hShape[i]);
		}
		PostQuitMessage(0);
		return 0;
	}
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void InitGame()
{
	count = 0;
	memset(arCell, 0, sizeof(arCell));

	for (int i = 1; i <= 8; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			int x, y;
			do
			{
				x = random(4);
				y = random(4);
			} while (arCell[x][y].Num != 0);
			arCell[x][y].Num = i;
		}
	}

	GameStatus = HINT;
	InvalidateRect(hWndMain, NULL, TRUE);
	SetTimer(hWndMain, 0, 2'000, NULL);
}

void DrawScreen(HDC hdc)
{
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			int image;
			if (GameStatus == HINT || arCell[x][y].St != HIDDEN)
			{
				image = arCell[x][y].Num - 1;
			}
			else
			{
				image = 8;
			}

			DrawBitmap(hdc, x * 64, y * 64, hShape[image]);
		}
	}

	TCHAR Mes[128];
	lstrcpy(Mes, TEXT("짝맞추기 게임 Ver 1.2"));
	TextOut(hdc, 300, 10, Mes, lstrlen(Mes));
	wsprintf(Mes, TEXT("총 시도 회수 : %d"), count);
	TextOut(hdc, 300, 50, Mes, lstrlen(Mes));
	wsprintf(Mes, TEXT("아직 못 찾은 것 : %d"), GetRemain());
	TextOut(hdc, 300, 70, Mes, lstrlen(Mes));
}

void GetTempFlip(int* tx, int* ty)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (arCell[i][j].St == TEMPFLIP)
			{
				*tx = i;
				*ty = j;
				return;
			}
		}
	}

	*tx = -1;
}

int GetRemain()
{
	int remain = 16;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (arCell[i][j].St == FLIP)
			{
				remain--;
			}
		}
	}

	return remain;
}

void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	BITMAP bit;

	MemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

	GetObject(hBit, sizeof(BITMAP), &bit);
	
	StretchBlt(hdc, x, y, 64, 64, MemDC, 0, 0, bit.bmWidth, bit.bmHeight, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	DeleteObject(MemDC);
}











#endif // 주석

































































#if 1 // 코드만
#include <Windows.h>
#include "resource.h"
#define random(n) (rand() % n);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("Practice_Game_Couple");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = 0;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, 0, 0,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

enum Status { HIDDEN, FLIP, TEMPFLIP };
struct tag_Cell
{
	int Num;
	Status St;
};
tag_Cell arCell[4][4];
int count;
HBITMAP hShape[9];
enum { RUN, HINT, VIEW } GameStatus;

void InitGame();
void DrawScreen(HDC hdc);
void GetTempFlip(int* tx, int* ty);
int GetRemain();
void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit);


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
	{
		hWndMain = hWnd;

		RECT crt;
		SetRect(&crt, 0, 0, 64 * 4 + 250, 64 * 4);
		AdjustWindowRect(&crt, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);
		SetWindowPos(hWnd, NULL, 0, 0, crt.right - crt.left, crt.bottom - crt.top,
			SWP_NOMOVE | SWP_NOZORDER);

		for (int i = 0; i < sizeof(hShape) / sizeof(hShape[0]); i++)
		{
			hShape[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_Couple_0 + i));
		}
		srand(GetTickCount());
		InitGame();

		return 0;
	}



	case WM_LBUTTONDOWN:
	{
		int nx = LOWORD(lParam) / 64;
		int ny = HIWORD(lParam) / 64;
		if (GameStatus != RUN || nx > 3 || ny > 3 || arCell[nx][ny].St != HIDDEN)
		{
			return 0;
		}

		int tx, ty;
		GetTempFlip(&tx, &ty);
		if (tx == -1)
		{
			arCell[nx][ny].St = TEMPFLIP;
			InvalidateRect(hWnd, NULL, FALSE);
		}
		else
		{
			count++;
			if (arCell[tx][ty].Num == arCell[nx][ny].Num)
			{
				MessageBeep(0);
				arCell[tx][ty].St = FLIP;
				arCell[nx][ny].St = FLIP;
				InvalidateRect(hWnd, NULL, FALSE);
				if (GetRemain() == 0)
				{
					MessageBox(hWnd, TEXT("축하합니다. 다시 시작합니다."), TEXT("알림"), MB_OK);
					InitGame();
				}
			}
			else
			{
				arCell[nx][ny].St = TEMPFLIP;
				InvalidateRect(hWnd, NULL, FALSE);
				GameStatus = VIEW;
				SetTimer(hWnd, 1, 1'000, NULL);
			}
		}

		return 0;
	}

	case WM_TIMER:
		switch (wParam)
		{
		case 0:
		{
			KillTimer(hWnd, 0);
			GameStatus = RUN;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case 1:
		{
			KillTimer(hWnd, 1);
			GameStatus = RUN;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (arCell[i][j].St == TEMPFLIP)
					{
						arCell[i][j].St = HIDDEN;
					}
				}
			}

			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		}

		return 0;


	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		DrawScreen(hdc);
		EndPaint(hWnd, &ps);
		
		return 0;
	}

	case WM_DESTROY:
	{
		for (int i = 0; i < sizeof(hShape) / sizeof(hShape[0]); i++)
		{
			DeleteObject(hShape[i]);
		}
		PostQuitMessage(0);
		return 0;
	}

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}


void InitGame()
{
	count = 0;
	memset(arCell, 0, sizeof(arCell));

	for (int i = 1; i <= 8; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			int x, y;
			do
			{
				x = random(4);
				y = random(4);
			} while (arCell[x][y].Num != 0);

			arCell[x][y].Num = i;
		}
	}

	

	GameStatus = HINT;
	InvalidateRect(hWndMain, NULL, TRUE);
	SetTimer(hWndMain, 0, 2'000, NULL);
}

void DrawScreen(HDC hdc)
{
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			int image;
			if (GameStatus == HINT || arCell[x][y].St != HIDDEN)
			{
				image = arCell[x][y].Num - 1;
			}
			else
			{
				image = 8;
			}

			DrawBitmap(hdc, x * 64, y * 64, hShape[image]);
		}
	}


	TCHAR Mes[128];
	lstrcpy(Mes, TEXT("짝 맞추기 게임 Ver 1.2"));
	TextOut(hdc, 300, 10, Mes, lstrlen(Mes));
	wsprintf(Mes, TEXT("총 시도 회수 : %d"), count);
	TextOut(hdc, 300, 50, Mes, lstrlen(Mes));
	wsprintf(Mes, TEXT("아직 못찾은 것 : %d"), GetRemain());
	TextOut(hdc, 300, 70, Mes, lstrlen(Mes));
}

void GetTempFlip(int* tx, int* ty)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (arCell[i][j].St == TEMPFLIP)
			{
				*tx = i;
				*ty = j;
				return;
			}
		}
	}

	*tx = -1;
}

int GetRemain()
{
	int remain = 16;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (arCell[i][j].St == FLIP)
			{
				remain--;
			}
		}
	}

	return remain;
}


void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit)
{
	HDC MemDC = CreateCompatibleDC(hdc);
	HBITMAP OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);
	BITMAP bit;
	GetObject(hBit, sizeof(BITMAP), &bit);

	StretchBlt(hdc, x, y, 64, 64, MemDC, 0, 0, bit.bmWidth, bit.bmHeight, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}

#endif // 코드만



#endif // Total