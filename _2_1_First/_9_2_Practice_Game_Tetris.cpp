#if 0 // Total
/*---------------------------------------------------------------------------------------------------
	실습 테트리스 게임 만들기입니다.
	1) 현재 9장인데, 11장에서 윈도우를 하나 추가로 만드는 기능을 배운 후, 
	 291p_293p 내용으로 게임 중지 표시 윈도우를 만드는 기능은 생략했습니다.
	2) 타일이 바닥에 닿은 후, 0.5초정도는 좌 우 이동할 수 있게 하는 기능을 만들고 싶었는데,
	   시간관계상 생략했습니다.

	 위 두 기능은 추후 시간이 남을 때 해보는 것도 좋을 것 같습니다
---------------------------------------------------------------------------------------------------*/



#if 0 // 주석
#include<Windows.h>
#include "resource.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Practice_Game_Tetris");
HWND hWndMain;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	MSG Message;
	WNDCLASS WndClass;
	HWND hWnd; 
	/* ○ hWndMain을 바로 사용안하고, hWnd를 사용하는 이유.
	   - 만약 hWnd를 사용하지 않고, hWndMain = CreateWindow... 로 hWndMain 으로 대체항 사용하면, 문제가 생긴다.
	   - 위처럼 하면, hWndMain = CreateWindow.. 이므로, CreateWindow 의 WM_CREATE 이 시행될 때 hWndMain 이 할당되지 않는다
	     만약, 이 상태에서 WM_CREATE에서 외부 함수로 hWndMain 이 필요로 하는 함수가 호출된다면 
		 (여기 코드에서는 AdjustMainWindow ) 아직 hWndMain 이 할당되지 않아 문제가 생긴다.
	   - 따라서 WM_CREATE 에서 HwNDmAIN 이 필요로 하는 상황을 고려하여, WM_CREATE 에서 hWndMain = hWnd ; 를 처리하는 것이
	     정석적인 방법인듯
	*/


	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU3);
	WndClass.style = 0;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, 0, 0,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR_Tetris));
	while (GetMessage(&Message, NULL, 0, 0))
	{
		if (!TranslateAccelerator(hWnd, hAccel, &Message))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
	return (int)Message.wParam;
}


void AdjustMainWindow();
void DrawScreen(HDC hdc);
void MakeNewBrick();
int GetAround(int x, int y, int b, int r);
BOOL MoveDown();
void TestFull();
void PrintTile(HDC hdc, int x, int y, int c);
void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit);
void UpdateBoard();
BOOL isMovingBrick(int x, int y);

int arBW[] = { 8, 10, 12, 15, 20 };
int arBH[] = { 15, 20, 25, 30, 32 };
int BW = 10;
int BH = 20;
#define random(n) (rand() % n)
#define TS 24
struct Point
{
	int x, y;
};

Point Shape[][4][4] =
{
	{ {0, 0,		1, 0,		2, 0,		-1, 0}, {0, 0,		0, 1,		0, -1,		0, -2},
	{0, 0,		1, 0,		2, 0,		-1, 0}, {0, 0,		0, 1,		0, -1,		0, -2} },

	{ {0, 0,		1, 0,		0, 1,		1, 1}, {0, 0,		1, 0,		0, 1,		1, 1},
	{0, 0,		1, 0,		0, 1,		1, 1}, {0, 0,		1, 0,		0, 1,		1, 1} },

	{ {0, 0,		-1, 0,		0, -1,		1, -1}, {0, 0,		0, 1,		-1, 0,		-1, -1},
	{0, 0,		-1, 0,		0, -1,		1, -1}, {0, 0,		0, 1,		-1, 0,		-1, -1} },

	{ {0, 0,		-1, -1,		0, -1,		1, 0}, {0, 0,		-1,0,		-1, 1,		0, -1},
	{0, 0,		-1, -1,		0, -1,		1, 0}, {0, 0,		-1, 0,		-1, 1,		0, -1} },






	{ {0, 0,		1, 0,		2, 0,		-1, 0}, {0, 0,		0, 1,		0, -1,		0, -2},
	{0, 0,		1, 0,		2, 0,		-1, 0}, {0, 0,		0, 1,		0, -1,		0, -2} },

	{ {0, 0,		1, 0,		0, 1,		1, 1}, {0, 0,		1, 0,		0, 1,		1, 1},
	{0, 0,		1, 0,		0, 1,		1, 1}, {0, 0,		1, 0,		0, 1,		1, 1} },

	{ {0, 0,		-1, 0,		0, -1,		1, -1}, {0, 0,		0, 1,		-1, 0,		-1, -1},
	{0, 0,		-1, 0,		0, -1,		1, -1}, {0, 0,		0, 1,		-1, 0,		-1, -1} },

	{ {0, 0,		-1, -1,		0, -1,		1, 0}, {0, 0,		-1,0,		-1, 1,		0, -1},
	{0, 0,		-1, -1,		0, -1,		1, 0}, {0, 0,		-1, 0,		-1, 1,		0, -1} },






	{ {0, 0,		1, 0,		2, 0,		-1, 0}, {0, 0,		0, 1,		0, -1,		0, -2},
	{0, 0,		1, 0,		2, 0,		-1, 0}, {0, 0,		0, 1,		0, -1,		0, -2} },



};
/* ○ 다차원 배열에서 중괄호 생략 가능
	- Point 는 2개의 정수로 구성된 포인터인데, Shape[][4][4] 를 위처럼 선언한다. 마지막 [4] 를,
	  스코프 내에 8개의 정수로 구성되게 처리했는데,
	  이는 C, Cpp 가 다차원의 배열을 선언할 때에, 중괄호를 생략해도 컴파일러가 이해함
*/

enum { EMPTY, BRICK, WALL = sizeof(Shape) / sizeof(Shape[0]) + 1};

int board[22][34];
int nx, ny;
int brick, rot;
int nbrick;
int score;
int bricknum;
enum tag_Status{GAMEOVER, RUNNING, PAUSE};
tag_Status GameStatus;
int Interval;
HBITMAP hBit[11];

BOOL bShowSpace = FALSE;
BOOL bQuiet = FALSE;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	
	switch (iMessage)
	{
	case WM_CREATE:
		hWndMain = hWnd;
		AdjustMainWindow();

		

		GameStatus = GAMEOVER;

		srand(GetTickCount());
		for (int i = 0; i < 11; i++)
		{
			hBit[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_Tetris_0 + i));
		}

		return 0;

	case WM_COMMAND:


		switch (LOWORD(wParam))
		{
		case ID_Tetris_Start_Game:
			if (GameStatus != GAMEOVER)
			{
				break;
			}

			for (int x = 0; x < BW + 2; x++)
			{
				for (int y = 0; y < BH + 2; y++)
				{
					board[x][y] = (y == 0 || y == BH + 1 || x == 0 || x == BW + 1) ? WALL : EMPTY;
				}
			}

			score = 0;
			bricknum = 0;
			GameStatus = RUNNING;

			nbrick = random(sizeof(Shape) / sizeof(Shape[0]));
			MakeNewBrick();

			Interval = 1'000;
			SetTimer(hWnd, 1, Interval, NULL);
			
			break;

		case ID_Tetris_Pause_Game:
			if (GameStatus == RUNNING)
			{
				GameStatus = PAUSE;
				KillTimer(hWnd, 1);
			}
			else if (GameStatus == PAUSE)
			{
				GameStatus = RUNNING;
				SetTimer(hWnd, 1, Interval, NULL);
			}
			break;

		case ID_Tetris_Exit_Game:
			DestroyWindow(hWnd);
			break;

		case ID_Tetris_ViewSpace:
			bShowSpace = !bShowSpace;
			InvalidateRect(hWnd, NULL, FALSE);
			break;

		}



		if (LOWORD(wParam) >= ID_Tetris_Size_8_10 && LOWORD(wParam) <= ID_Tetris_Size_20_32)
		{
			if (GameStatus != GAMEOVER)
			{
				return 0;
			}

			BW = arBW[LOWORD(wParam) - ID_Tetris_Size_8_10];
			BH = arBH[LOWORD(wParam) - ID_Tetris_Size_8_10];

			AdjustMainWindow();
			memset(board, 0, sizeof(board));
			InvalidateRect(hWnd, NULL, TRUE);
		}



		return 0;


	case WM_INITMENU:
		CheckMenuItem((HMENU)wParam, ID_Tetris_ViewSpace, MF_BYCOMMAND | (bShowSpace ? MF_CHECKED : MF_UNCHECKED));

		/* ○ WM_INITMENU
		    - 메뉴가 열리기 직전에 호출
		   ○ CheckMenuItem
		    - (1) : 열릴 메뉴 핸들
			- (2) : 체크/해제 할 ID
			- (3)
			   - MF_BYCOMMAND	: (2) 식별을 ID를 기준으로
			   - MF_CHECKED		: 체크표시함
			   - MF_UNCHECKED	: 체크표시안함
		*/



		return 0;
		
	case WM_TIMER:
		if (MoveDown() == TRUE)
		{
			MakeNewBrick();
		}

		return 0;

	case WM_KEYDOWN:
		if (GameStatus != RUNNING || brick == -1)
		{
			return 0;
		}

		switch (wParam)
		{
		case VK_LEFT:
			if (GetAround(nx - 1, ny, brick, rot) == EMPTY)
			{
				nx--;
				UpdateBoard();
			}
			break;
		case VK_RIGHT:
			if (GetAround(nx + 1, ny, brick, rot) == EMPTY)
			{
				nx++;
				UpdateBoard();
			}
			break;
		case VK_UP:
			{
			int trot = (rot == 3 ? 0 : rot + 1);
			if (GetAround(nx, ny, brick, trot) == EMPTY)
			{
				rot = trot;
				UpdateBoard();
			}
			break;
			}

		case VK_DOWN:
			if (MoveDown() == TRUE)
			{
				MakeNewBrick();
			}
			break;

		case VK_SPACE:
			while (MoveDown() == FALSE) {}
			MakeNewBrick();
			break;
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
		KillTimer(hWndMain, 1);
		for (int i = 0; i < 11; i++)
		{
			DeleteObject(hBit[i]);
		}
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}



void AdjustMainWindow()
{
	RECT crt;

	SetRect(&crt, 0, 0, (BW + 12) * TS, (BH + 2) * TS);
	AdjustWindowRect(&crt, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, TRUE);

	



	SetWindowPos(hWndMain, NULL, 0, 0,
		crt.right - crt.left, crt.bottom - crt.top,
		SWP_NOMOVE | SWP_NOZORDER);
}

void DrawScreen(HDC hdc)
{
	for (int x = 0; x < BW + 1; x++)
	{
		PrintTile(hdc, x, 0, WALL);
		PrintTile(hdc, x, BH + 1, WALL);
	}
	for (int y = 0; y < BH + 2; y++)
	{
		PrintTile(hdc, 0, y, WALL);
		PrintTile(hdc, BW + 1, y, WALL);
	}


	for (int x = 1; x < BW + 1; x++)
	{
		for (int y = 1; y < BH + 1; y++)
		{
			if (isMovingBrick(x, y))
			{
				PrintTile(hdc, x, y, brick + 1);
			}
			else
			{
				PrintTile(hdc, x, y, board[x][y]);
			}
		}
	}


	for (int x = BW + 3; x < BW + 11; x++)
	{
		for (int y = BH - 5; y <= BH + 1; y++)
		{
			if (x == BW + 3 || x == BW + 10 || y == BH - 5 || y == BH + 1)
			{
				PrintTile(hdc, x, y, WALL);
			}
			else
			{
				PrintTile(hdc, x, y, 0);
			}
		}
	}

	if (GameStatus != GAMEOVER)
	{
		for (int i = 0; i < 4; i++)
		{
			PrintTile(hdc, BW + 7 + Shape[nbrick][0][i].x, BH - 2 + Shape[nbrick][0][i].y, nbrick + 1);
		}
	}

	TCHAR str[128];
	lstrcpy(str, TEXT("Tetris Ver 1.3"));
	TextOut(hdc, (BW + 4) * TS, 30, str, lstrlen(str));
	wsprintf(str, TEXT("점수 : %d"), score);
	TextOut(hdc, (BW + 4) * TS, 60, str, lstrlen(str));
	wsprintf(str, TEXT("벽돌 : %d 개   "), bricknum);
	TextOut(hdc, (BW + 4) * TS, 80, str, lstrlen(str));
}

void MakeNewBrick()
{
	bricknum++;
	brick = nbrick;
	nbrick = random(sizeof(Shape) / sizeof(Shape[0]));
	nx = BW / 2;
	ny = 3; // @@@ TS * 0.2f ; 이런 식이 낫지 않으려나
	rot = 0;

	InvalidateRect(hWndMain, NULL, FALSE);
	if (GetAround(nx, ny, brick, rot) != EMPTY)
	{
		KillTimer(hWndMain, 1);
		GameStatus = GAMEOVER;
		MessageBox(hWndMain, TEXT("게임이 끝났습니다. 다시 시작하려면 게임시작 항목을 선택해주십시오."), TEXT("알림"),
			MB_OK);
	}
}

int GetAround(int x, int y, int b, int r)
{
	int k = EMPTY;

	for (int i = 0; i < 4; i++)
	{
		k = max(k, board[x + Shape[b][r][i].x][y + Shape[b][r][i].y]);
	}

	return k;
}

BOOL MoveDown()
{
	if (GetAround(nx, ny + 1, brick, rot) != EMPTY)
	{
		TestFull();
		return TRUE;
	}

	ny++;
	UpdateBoard();
	UpdateWindow(hWndMain); 
	/* ○ UpdateWindow
	    - 윈도우가 무효화됐다면(InvalidateRect), WM_PAINT 한다
		- 윈도우가 무효화되지 않았다면, 아무 일도 하지 않는다
	*/
	return FALSE;
}

void TestFull()
{
	int count = 0;
	static int arSCoreInc[] = { 0, 1, 3, 8, 20 };
	
	for (int i = 0; i < 4; i++)
	{
		board[nx + Shape[brick][rot][i].x][ny + Shape[brick][rot][i].y] = brick + 1;
	}

	brick = -1; // 이동중인 벽돌이 잠시 없는 상태


	for (int y = 1; y < BH + 1; y++)
	{
		int x = 1;
		for (; x < BW + 1; x++)
		{
			if (board[x][y] == EMPTY)
			{
				break;
			}
		}

		if (x == BW + 1)
		{
			count++;
			for (int ty = y; ty > 1; ty--)
			{
				for (x = 1; x < BW + 1; x++)
				{
					board[x][ty] = board[x][ty - 1];
				}
			}


			UpdateBoard();
			UpdateWindow(hWndMain);

			PlaySound(TEXT("C:\\Users\\Heetae\\source\\repos\\Learning_WindowsAPI\\OtherFiles\\FootStepSound.wav"),
				NULL, SND_ASYNC);


			Sleep(150); // ※ WinAPI. ms 만큼 스레드 슬립
		}
	}

	score += arSCoreInc[count];
	if (bricknum % 10 == 0 && Interval > 200)
	{
		Interval -= 50;
		SetTimer(hWndMain, 1, Interval, NULL);
	}
}

void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	BITMAP bit;

	MemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

	GetObject(hBit, sizeof(BITMAP), &bit);

	StretchBlt(hdc, x, y, TS, TS, MemDC, 0, 0, bit.bmWidth, bit.bmHeight, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}

void PrintTile(HDC hdc, int x, int y, int c)
{
	DrawBitmap(hdc, x * TS, y * TS, hBit[c]);
	if (c == EMPTY && bShowSpace)
	{
		Rectangle(hdc, x * TS + TS / 2 - 1, y * TS + TS / 2 - 1, x * TS + TS / 2 + 1, y * TS + TS / 2 + 1);
	}
	return;
}

void UpdateBoard()
{
	RECT rt;

	SetRect(&rt, TS, TS, (BW + 1) * TS, (BH + 1) * TS);
	InvalidateRect(hWndMain, &rt, FALSE);
}

BOOL isMovingBrick(int x, int y)
{
	if (GameStatus == GAMEOVER || brick == -1)
	{
		return FALSE;
	}

	for (int i = 0; i < 4; i++)
	{
		if (x == nx + Shape[brick][rot][i].x && y == ny + Shape[brick][rot][i].y)
		{
			return TRUE;
		}
	}

	return FALSE;
}




#endif // 주석











































































#if 1 // 코드만
#include <Windows.h>
#include "resource.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Practice_Game_Tetris");
HWND hWndMain;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	MSG Message;
	WNDCLASS WndClass;
	HWND hWnd;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU3);
	WndClass.style = 0;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, 0, 0,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR_Tetris));
	while (GetMessage(&Message, NULL, 0, 0))
	{
		if (!TranslateAccelerator(hWnd, hAccel, &Message))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
	return (int)Message.wParam;
}

void AdjustMainWindow();
void DrawScreen(HDC hdc);
void MakeNewBrick();
int GetAround(int x, int y, int b, int r);
BOOL MoveDown();
void TestFull();
void PrintTile(HDC hdc, int x, int y, int c);
void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit);
void UpdateBoard();
BOOL isMovingBrick(int x, int y);

int arBW[] = { 8, 10, 12, 15, 20 };
int arBH[] = { 15, 20, 25, 30, 32 };
int BW = 10;
int BH = 20;
#define random(n) (rand() % n)
#define TS 24

struct Point
{
	int x, y;
};

Point Shape[][4][4] =
{
	{ {0, 0,		1, 0,		2, 0,		-1, 0}, {0, 0,		0, 1,		0, -1,		0, -2},
	{0, 0,		1, 0,		2, 0,		-1, 0}, {0, 0,		0, 1,		0, -1,		0, -2} },

	{ {0, 0,		1, 0,		0, 1,		1, 1}, {0, 0,		1, 0,		0, 1,		1, 1},
	{0, 0,		1, 0,		0, 1,		1, 1}, {0, 0,		1, 0,		0, 1,		1, 1} },

	{ {0, 0,		-1, 0,		0, -1,		1, -1}, {0, 0,		0, 1,		-1, 0,		-1, -1},
	{0, 0,		-1, 0,		0, -1,		1, -1}, {0, 0,		0, 1,		-1, 0,		-1, -1} },

	{ {0, 0,		-1, -1,		0, -1,		1, 0}, {0, 0,		-1,0,		-1, 1,		0, -1},
	{0, 0,		-1, -1,		0, -1,		1, 0}, {0, 0,		-1, 0,		-1, 1,		0, -1} },






	{ {0, 0,		1, 0,		2, 0,		-1, 0}, {0, 0,		0, 1,		0, -1,		0, -2},
	{0, 0,		1, 0,		2, 0,		-1, 0}, {0, 0,		0, 1,		0, -1,		0, -2} },

	{ {0, 0,		1, 0,		0, 1,		1, 1}, {0, 0,		1, 0,		0, 1,		1, 1},
	{0, 0,		1, 0,		0, 1,		1, 1}, {0, 0,		1, 0,		0, 1,		1, 1} },

	{ {0, 0,		-1, 0,		0, -1,		1, -1}, {0, 0,		0, 1,		-1, 0,		-1, -1},
	{0, 0,		-1, 0,		0, -1,		1, -1}, {0, 0,		0, 1,		-1, 0,		-1, -1} },

	{ {0, 0,		-1, -1,		0, -1,		1, 0}, {0, 0,		-1,0,		-1, 1,		0, -1},
	{0, 0,		-1, -1,		0, -1,		1, 0}, {0, 0,		-1, 0,		-1, 1,		0, -1} },






	{ {0, 0,		1, 0,		2, 0,		-1, 0}, {0, 0,		0, 1,		0, -1,		0, -2},
	{0, 0,		1, 0,		2, 0,		-1, 0}, {0, 0,		0, 1,		0, -1,		0, -2} },



};

enum {EMPTY, BRICK, WALL = sizeof(Shape) / sizeof(Shape[0]) + 1};

int board[22][34];
int nx, ny;
int brick, rot;
int nbrick;
int score;
int bricknum;
enum tag_Status{GAMEOVER, RUNNING, PAUSE};
tag_Status GameStatus;
int Interval;
HBITMAP hBit[11];

BOOL bShowSpace = FALSE;
BOOL bQuiet = FALSE;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		hWndMain = hWnd;
		AdjustMainWindow();

		GameStatus = GAMEOVER;

		srand(GetTickCount());
		for (int i = 0; i < 11; i++)
		{
			hBit[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_Tetris_0 + i));
		}

		return 0;


	case WM_COMMAND:
		
		switch (LOWORD(wParam))
		{
		case ID_Tetris_Start_Game:
			if (GameStatus != GAMEOVER)
			{
				break;
			}

			for (int x = 0; x < BW + 2; x++)
			{
				for (int y = 0; y < BH + 2; y++)
				{
					board[x][y] = (y == 0 || y == BH + 1 || x == 0 || x == BW + 1) ? WALL : EMPTY;
				}
			}

			score = 0;
			bricknum = 0;
			GameStatus = RUNNING;
			
			nbrick = random(sizeof(Shape) / sizeof(Shape[0]));
			MakeNewBrick();

			Interval = 1'000;
			SetTimer(hWnd, 1, Interval, NULL);

			break;


		case ID_Tetris_Pause_Game:
			if (GameStatus == RUNNING)
			{
				GameStatus = PAUSE;
				KillTimer(hWnd, 1);
			}
			else if (GameStatus == PAUSE)
			{
				GameStatus = RUNNING;
				SetTimer(hWnd, 1, Interval, NULL);
			}
			break;

		case ID_Tetris_Exit_Game:
			DestroyWindow(hWnd);
			break;

		case ID_Tetris_ViewSpace:
			bShowSpace = !bShowSpace;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}

		if (LOWORD(wParam) >= ID_Tetris_Size_8_10 && LOWORD(wParam) <= ID_Tetris_Size_20_32)
		{
			if (GameStatus != GAMEOVER)
			{
				return 0;
			}

			BW = arBW[LOWORD(wParam) - ID_Tetris_Size_8_10];
			BH = arBH[LOWORD(wParam) - ID_Tetris_Size_8_10];

			AdjustMainWindow();
			memset(board, 0, sizeof(board));
			InvalidateRect(hWnd, NULL, TRUE);
		}

		return 0;


	case WM_INITMENU:
		CheckMenuItem((HMENU)wParam, ID_Tetris_ViewSpace, MF_BYCOMMAND | (bShowSpace ? MF_CHECKED : MF_UNCHECKED));

		return 0;

	case WM_TIMER:
		if (MoveDown() == TRUE)
		{
			MakeNewBrick();
		}

		return 0;

	case WM_KEYDOWN:
		if (GameStatus != RUNNING || brick == -1)
		{
			return 0;
		}

		switch (wParam)
		{
		case VK_LEFT:
			if (GetAround(nx - 1, ny, brick, rot) == EMPTY)
			{
				nx--;
				UpdateBoard();
			}
			break;
		case VK_RIGHT:
			if (GetAround(nx + 1, ny, brick, rot) == EMPTY)
			{
				nx++;
				UpdateBoard();
			}
			break;
		case VK_UP:
			{
			int trot = (rot == 3 ? 0 : rot + 1);
			if (GetAround(nx, ny, brick, trot) == EMPTY)
			{
				rot = trot;
				UpdateBoard();
			}
			break;
			}

		case VK_DOWN:
			if (MoveDown() == TRUE)
			{
				MakeNewBrick();
			}
			break;

		case VK_SPACE:
			while(MoveDown() == FALSE){}
			MakeNewBrick();
			break;
		}
		return 0;


	case WM_PAINT:
		{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		DrawScreen(hdc);
		EndPaint(hWnd, &ps);
		}
		return 0;
	
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void AdjustMainWindow()
{
	RECT crt;

	SetRect(&crt, 0, 0, (BW + 12) * TS, (BH + 2) * TS);
	AdjustWindowRect(&crt, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, TRUE);

	SetWindowPos(hWndMain, NULL,
		0, 0, crt.right - crt.left, crt.bottom - crt.top,
		SWP_NOMOVE | SWP_NOZORDER);
}

void DrawScreen(HDC hdc)
{
	for (int x = 0; x < BW + 1; x++)
	{
		PrintTile(hdc, x, 0, WALL);
		PrintTile(hdc, x, BH + 1, WALL);
	}
	for (int y = 0; y < BH + 2; y++)
	{
		PrintTile(hdc, 0, y, WALL);
		PrintTile(hdc, BW + 1, y, WALL);
	}

	for (int x = 1; x < BW + 1; x++)
	{
		for (int y = 1; y < BH + 1; y++)
		{
			if (isMovingBrick(x, y))
			{
				PrintTile(hdc, x, y, brick + 1);
			}
			else
			{
				PrintTile(hdc, x, y, board[x][y]);
			}
		}
	}


	for (int x = BW + 3; x < BW + 11; x++)
	{
		for (int y = BH - 5; y <= BH + 1; y++)
		{
			if (x == BW + 3 || x == BW + 10 || y == BH - 5 || y == BH + 1)
			{
				PrintTile(hdc, x, y, WALL);
			}
			else
			{
				PrintTile(hdc, x, y, 0);
			}
		}
	}


	if (GameStatus != GAMEOVER)
	{
		for (int i = 0; i < 4; i++)
		{
			PrintTile(hdc, BW + 7 + Shape[nbrick][0][i].x, BH - 2 + Shape[nbrick][0][i].y, nbrick + 1);
		}
	}

	TCHAR str[128];
	lstrcpy(str, TEXT("Tetris Ver 1.3"));
	TextOut(hdc, (BW + 4) * TS, 30, str, lstrlen(str));
	wsprintf(str, TEXT("점수 : %d"), score);
	TextOut(hdc, (BW + 4) * TS, 60, str, lstrlen(str));
	wsprintf(str, TEXT("벽돌 : %d개"), bricknum);
	TextOut(hdc, (BW + 4) * TS, 80, str, lstrlen(str));
}


void MakeNewBrick()
{
	bricknum++;
	brick = nbrick;
	nbrick = random(sizeof(Shape) / sizeof(Shape[0]));
	nx = BW / 2;
	ny = 3; // ※ 수정하고 싶다. 시간이 없어서 못했다
	rot = 0;

	InvalidateRect(hWndMain, NULL, FALSE);
	if (GetAround(nx, ny, brick, rot) != EMPTY)
	{
		KillTimer(hWndMain, 1);
		GameStatus = GAMEOVER;
		MessageBox(hWndMain, TEXT("게임이 끝났습니다. 다시 시작하려면 게임시작 항목을 선택해주십시오."), TEXT("알림"),
			MB_OK);
	}
}

int GetAround(int x, int y, int b, int r)
{
	int k = EMPTY;

	for (int i = 0; i < 4; i++)
	{
		k = max(k, board[x + Shape[b][r][i].x][y + Shape[b][r][i].y]);
	}

	return k;
}

BOOL MoveDown()
{
	if (GetAround(nx, ny + 1, brick, rot) != EMPTY)
	{
		TestFull();
		return TRUE;
	}

	ny++;
	UpdateBoard();
	UpdateWindow(hWndMain);

	return FALSE;
}

void TestFull()
{
	int count = 0;
	static int arScoreInt[] = { 0, 1, 3, 8, 20 };

	for (int i = 0; i < 4; i++)
	{
		board[nx + Shape[brick][rot][i].x][ny + Shape[brick][rot][i].y] = brick + 1;
	}

	brick = -1;

	for (int y = 1; y < BH + 1; y++)
	{
		int x = 1;
		for (; x < BW + 1; x++)
		{
			if (board[x][y] == EMPTY)
			{
				break;
			}
		}

		if (x == BW + 1)
		{
			count++;
			for (int ty = y; ty > 1; ty--)
			{
				for (x = 1; x < BW + 1; x++)
				{
					board[x][ty] = board[x][ty - 1];
				}
			}

			UpdateBoard();
			UpdateWindow(hWndMain);

			PlaySound(TEXT("C:\\Users\\Heetae\\source\\repos\\Learning_WindowsAPI\\OtherFiles\\FootStepSound.wav"),
				NULL, SND_ASYNC);

			Sleep(150);
		}
	}

	score += arScoreInt[count];
	if (bricknum % 10 && Interval > 200)
	{
		Interval -= 50;
		SetTimer(hWndMain, 1, Interval, NULL);
	}
}

void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	BITMAP bit;

	MemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

	GetObject(hBit, sizeof(BITMAP), &bit);

	StretchBlt(hdc, x, y, TS, TS, MemDC, 0, 0, bit.bmWidth, bit.bmHeight, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}

void PrintTile(HDC hdc, int x, int y, int c)
{
	DrawBitmap(hdc, x * TS, y * TS, hBit[c]);
	if (c == EMPTY && bShowSpace)
	{
		Rectangle(hdc, x * TS + TS / 2 - 1, y * TS + TS / 2 - 1, x * TS + TS / 2 + 1, y * TS + TS / 2 + 1);
	}
	return;
}

void UpdateBoard()
{
	RECT rt;

	SetRect(&rt, TS, TS, (BW + 1) * TS, (BH + 1) * TS);
	InvalidateRect(hWndMain, &rt, FALSE);
}

BOOL isMovingBrick(int x, int y)
{
	if (GameStatus == GAMEOVER || brick == -1)
	{
		return FALSE;
	}

	for (int i = 0; i < 4; i++)
	{
		if (x == nx + Shape[brick][rot][i].x && y == ny + Shape[brick][rot][i].y)
		{
			return TRUE;
		}
	}

	return FALSE;
}

#endif // 코드만


#endif // Total