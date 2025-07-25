#if 0 // Total
/*---------------------------------------------------------------------------------------------------
	�ǽ� ��Ʈ���� ���� ������Դϴ�.
	1) ���� 9���ε�, 11�忡�� �����츦 �ϳ� �߰��� ����� ����� ��� ��, 
	 291p_293p �������� ���� ���� ǥ�� �����츦 ����� ����� �����߽��ϴ�.
	2) Ÿ���� �ٴڿ� ���� ��, 0.5�������� �� �� �̵��� �� �ְ� �ϴ� ����� ����� �;��µ�,
	   �ð������ �����߽��ϴ�.

	 �� �� ����� ���� �ð��� ���� �� �غ��� �͵� ���� �� �����ϴ�
---------------------------------------------------------------------------------------------------*/



#if 0 // �ּ�
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
	/* �� hWndMain�� �ٷ� �����ϰ�, hWnd�� ����ϴ� ����.
	   - ���� hWnd�� ������� �ʰ�, hWndMain = CreateWindow... �� hWndMain ���� ��ü�� ����ϸ�, ������ �����.
	   - ��ó�� �ϸ�, hWndMain = CreateWindow.. �̹Ƿ�, CreateWindow �� WM_CREATE �� ����� �� hWndMain �� �Ҵ���� �ʴ´�
	     ����, �� ���¿��� WM_CREATE���� �ܺ� �Լ��� hWndMain �� �ʿ�� �ϴ� �Լ��� ȣ��ȴٸ� 
		 (���� �ڵ忡���� AdjustMainWindow ) ���� hWndMain �� �Ҵ���� �ʾ� ������ �����.
	   - ���� WM_CREATE ���� HwNDmAIN �� �ʿ�� �ϴ� ��Ȳ�� ����Ͽ�, WM_CREATE ���� hWndMain = hWnd ; �� ó���ϴ� ����
	     �������� ����ε�
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
/* �� ������ �迭���� �߰�ȣ ���� ����
	- Point �� 2���� ������ ������ �������ε�, Shape[][4][4] �� ��ó�� �����Ѵ�. ������ [4] ��,
	  ������ ���� 8���� ������ �����ǰ� ó���ߴµ�,
	  �̴� C, Cpp �� �������� �迭�� ������ ����, �߰�ȣ�� �����ص� �����Ϸ��� ������
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

		/* �� WM_INITMENU
		    - �޴��� ������ ������ ȣ��
		   �� CheckMenuItem
		    - (1) : ���� �޴� �ڵ�
			- (2) : üũ/���� �� ID
			- (3)
			   - MF_BYCOMMAND	: (2) �ĺ��� ID�� ��������
			   - MF_CHECKED		: üũǥ����
			   - MF_UNCHECKED	: üũǥ�þ���
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
	wsprintf(str, TEXT("���� : %d"), score);
	TextOut(hdc, (BW + 4) * TS, 60, str, lstrlen(str));
	wsprintf(str, TEXT("���� : %d ��   "), bricknum);
	TextOut(hdc, (BW + 4) * TS, 80, str, lstrlen(str));
}

void MakeNewBrick()
{
	bricknum++;
	brick = nbrick;
	nbrick = random(sizeof(Shape) / sizeof(Shape[0]));
	nx = BW / 2;
	ny = 3; // @@@ TS * 0.2f ; �̷� ���� ���� ��������
	rot = 0;

	InvalidateRect(hWndMain, NULL, FALSE);
	if (GetAround(nx, ny, brick, rot) != EMPTY)
	{
		KillTimer(hWndMain, 1);
		GameStatus = GAMEOVER;
		MessageBox(hWndMain, TEXT("������ �������ϴ�. �ٽ� �����Ϸ��� ���ӽ��� �׸��� �������ֽʽÿ�."), TEXT("�˸�"),
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
	/* �� UpdateWindow
	    - �����찡 ��ȿȭ�ƴٸ�(InvalidateRect), WM_PAINT �Ѵ�
		- �����찡 ��ȿȭ���� �ʾҴٸ�, �ƹ� �ϵ� ���� �ʴ´�
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

	brick = -1; // �̵����� ������ ��� ���� ����


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


			Sleep(150); // �� WinAPI. ms ��ŭ ������ ����
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




#endif // �ּ�











































































#if 1 // �ڵ常
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
	wsprintf(str, TEXT("���� : %d"), score);
	TextOut(hdc, (BW + 4) * TS, 60, str, lstrlen(str));
	wsprintf(str, TEXT("���� : %d��"), bricknum);
	TextOut(hdc, (BW + 4) * TS, 80, str, lstrlen(str));
}


void MakeNewBrick()
{
	bricknum++;
	brick = nbrick;
	nbrick = random(sizeof(Shape) / sizeof(Shape[0]));
	nx = BW / 2;
	ny = 3; // �� �����ϰ� �ʹ�. �ð��� ��� ���ߴ�
	rot = 0;

	InvalidateRect(hWndMain, NULL, FALSE);
	if (GetAround(nx, ny, brick, rot) != EMPTY)
	{
		KillTimer(hWndMain, 1);
		GameStatus = GAMEOVER;
		MessageBox(hWndMain, TEXT("������ �������ϴ�. �ٽ� �����Ϸ��� ���ӽ��� �׸��� �������ֽʽÿ�."), TEXT("�˸�"),
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

#endif // �ڵ常


#endif // Total