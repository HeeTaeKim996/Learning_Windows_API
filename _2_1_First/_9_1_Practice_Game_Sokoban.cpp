#if 0 // Total
/*---------------------------------------------------------------------------------
	지금까지 공부한 내용을 활용해서, 간단한 게임을 만드는 코드입니다. 
---------------------------------------------------------------------------------*/

#if 0 // 주석
#include <windows.h>
#include "resource.h"

// ※ 소리 재생을 위한 h, lib
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define MAXSTAGE 3
#define BW 32
#define BH 32

void DrawScreen(HDC hdc);

BOOL TestEnd();

void Move(int dir);
void InitStage();
void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit);

char ns[18][21];
int nStage;
int nx, ny;
int nMove;
HBITMAP hBit[9];

char arStage[MAXSTAGE][18][21] =
{
	{
		"###################",
		"###################",
		"###################",
		"#####  ############",
		"#####  ############",
		"#####    ###########",
		"###   O ##########",
		"### #  ####### ###",
		"##        @  ..###",
		"##  ### ##  .. ##",
		"#####     #########",
		"###################",
		"###################",
		"###################",
		"###################",
		"###################",
		"###################",
		"###################"
},
	{
		"###################",
		"###################",
		"###################",
		"#####  ############",
		"#####O ############",
		"#####  O###########",
		"### O O ##########",
		"### #  ####### ###",
		"##O  O    @  ..###",
		"##  ### ##  .. ##",
		"#####     #########",
		"###################",
		"###################",
		"###################",
		"###################",
		"###################",
		"###################",
		"###################"
},
	{
		"###################",
		"###################",
		"###################",
		"#####  ############",
		"#####O ############",
		"#####  O###########",
		"### O O ##########",
		"### #  ####### ###",
		"##O  O    @  ..###",
		"##  ### ##  .. ##",
		"#####     #########",
		"###################",
		"###################",
		"###################",
		"###################",
		"###################",
		"###################",
		"###################"
}

};


#define MAXUNDO 1'000
struct tag_MoveInfo
{
	char dx : 3;
	char dy : 3;
	char bWithPack : 2;

	/* ■ 비트 필드
		-  C, Cpp (C#미지원) 에서는, 필드멤버를 바이트 단위가 아닌 비트 단위로 쪼개 쓸 수 있다.
		- 위 코드처럼 필드멤버 우측에, : 3, : 3, : 2 처럼 사용하면, dx에는 3비트, dy에는 3비트, bWithPack에는
		  2비트 를 사용하여 총 8비트 (1바이트) 의 크기의 구조체로 사용할 수 있다
		- 비트 필드로 사용할 수 있는 타입은, char, unsigned char, short, unsighed short, int, unsigned int,
		  long, unsigned long 등, 정수 타입이다.  (float 등 불가)
	*/

};
tag_MoveInfo MoveInfo[MAXUNDO];
int UndoIdx;
int ManBit = 8;

void ErasePack(int x, int y);
void Undo();
void Redo();


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("Practice_Game_Sokoban");



int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
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

	hWndMain = CreateWindow(lpszClass, lpszClass, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, 0, 0,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWndMain, nCmdShow);
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


	switch (iMessage)
	{
	case WM_CREATE:
		RECT crt;
		SetRect(&crt, 0, 0, 900, BH * 18);
		AdjustWindowRect(&crt, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);
		/* ○ AdjustWindowRect
			- 윈도우 크기 조정. x, y, w, h 외에, (2)항처럼 위 제목바? (3)처럼 메뉴바 가 있는지 여부도 파악
			- 단, 확보(계산) 만 한다. 실제로 적용하지는 않은다. 실질 적용은 하단의 SetWindowPos 에서 함
			- (1) : CreateWidnow의 4 5 6 7
			- (2) : CreateWindow의 3)
			- (3) : 메뉴바가 있는지 파악하는 BOOL
		*/
		SetWindowPos(hWnd, NULL, 0, 0, crt.right - crt.left, crt.bottom - crt.top,
			SWP_NOMOVE | SWP_NOZORDER);
		/* ○ SetWindowPos
			- 실제 윈도우 크기 등을 조정하는 함수.
			- (2) : Z 순서 조정. (Z순서 : 멀티태스킹에서, 현재 보이는 윈도우 프로그램을 Z 에서 맨 위로 봄 )
					NULL 이면, 기존 Z 순서 적용
			- (7) : 옵션 플래그들
					 - SWP_NOMOVE		: 위치(X,Y) 변경 안함
					 - SW_NOSIZE		: 크기(H,W) 변경 안함
					 - SWP_NOZORDER		: Z 순서 변경 안함
					 - SWP_SHOWWINDOW	: 창을 표시
					 - SWP_HIDEWINDOW	: 창 숨김
		*/
		for (int i = 0; i < 9; i++)
		{
			hBit[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2 + i));
		}
		nStage = 0;
		InitStage();

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		DrawScreen(hdc);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
		case VK_RIGHT:
		case VK_UP:
		case VK_DOWN:
			Move(wParam);
			if (TestEnd())
			{
				TCHAR Message[256];
				wsprintf(Message, TEXT("%d 스테이지를 풀었습니다.")TEXT("다음 스테이지로 이동합니다"),
					nStage + 1);
				MessageBox(hWnd, Message, TEXT("알림"), MB_OK);
				if (nStage < MAXSTAGE - 1)
				{
					nStage++;
				}
				InitStage();
			}

			break;


		case 'Q':
			DestroyWindow(hWnd);
			break;
		case 'R':
			InitStage();
			break;
		case 'N':
			if (nStage < MAXSTAGE - 1)
			{
				nStage++;
				InitStage();
			}
			break;
		case 'P':
			if (nStage > 0)
			{
				nStage--;
				InitStage();
			}
			break;

		case 'Z':
			Undo();
			break;

		case 'Y':
			Redo();
			break;
		}
		return 0;

	case WM_DESTROY:
		for (int i = 0; i < 5; i++)
		{
			DeleteObject(hBit[i]);
		}
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void DrawScreen(HDC hdc)
{
	int iBit;

	for (int y = 0; y < 18; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			switch (ns[y][x])
			{
			case '#':
				iBit = 1;

				break;
			case 'O':
				iBit = 0;
				break;
			case '.':
				iBit = 4;
				break;
			case ' ':
				iBit = 3;
				break;
			}

			DrawBitmap(hdc, x * BW, y * BH, hBit[iBit]);
		}
	}

	DrawBitmap(hdc, nx * BW, ny * BH, hBit[ManBit]);


	TCHAR Message[256];
	wsprintf(Message, TEXT("SOKOBAN"));
	TextOut(hdc, 700, 10, Message, lstrlen(Message));
	wsprintf(Message, TEXT("Q:종료, R:다시시작"));
	TextOut(hdc, 700, 30, Message, lstrlen(Message));
	wsprintf(Message, TEXT("N:다음, P:이전"));
	TextOut(hdc, 700, 50, Message, lstrlen(Message));
	wsprintf(Message, TEXT("Z:취소, Y:재실행"));
	TextOut(hdc, 700, 70, Message, lstrlen(Message));
	wsprintf(Message, TEXT("스테이지 : %d"), nStage + 1);
	TextOut(hdc, 700, 90, Message, lstrlen(Message));
	wsprintf(Message, TEXT("이동 회수 : %d"), nMove);
	TextOut(hdc, 700, 110, Message, lstrlen(Message));
}

BOOL TestEnd()
{
	for (int y = 0; y < 18; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			if (ns[y][x] == 'O' && arStage[nStage][y][x] != '.')
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

void Move(int dir)
{
	int dx = 0, dy = 0;

	switch (dir)
	{
	case VK_LEFT:
		ManBit = 5;
		dx = -1;
		break;
	case VK_RIGHT:
		ManBit = 6;
		dx = 1;
		break;
	case VK_UP:
		ManBit = 7;
		dy = -1;
		break;
	case VK_DOWN:
		ManBit = 8;
		dy = 1;
		break;
	}


	char nextPos = ns[ny + dy][nx + dx];
	char farPos = ns[ny + dy * 2][nx + dx * 2];

	BOOL bWithPack = FALSE;
	
	if (nextPos != '#')
	{
		if (nextPos == 'O')
		{
			if (farPos == ' ' || farPos == '.')
			{
				ErasePack(nx + dx, ny + dy);

				ns[ny + dy * 2][nx + dx * 2] = 'O';

				bWithPack = TRUE;
			}
			else
			{
				return;
			}
		}


		nx += dx;
		ny += dy;
		nMove++;


		MoveInfo[UndoIdx].dx = dx;
		MoveInfo[UndoIdx].dy = dy;
		MoveInfo[UndoIdx].bWithPack = bWithPack;
		UndoIdx++;
		MoveInfo[UndoIdx].dx = -2;

		if (UndoIdx == MAXUNDO - 1)
		{
			memmove(MoveInfo, &MoveInfo[100], (MAXUNDO - 100) * sizeof(tag_MoveInfo));

			for (int i = MAXUNDO - 100; i < MAXUNDO; i++)
			{
				MoveInfo[i].dx = -2;
			}

			UndoIdx -= 100;
		}


		PlaySound(TEXT("C:\\Users\\Heetae\\source\\repos\\Learning_WindowsAPI\\OtherFiles\\FootStepSound.wav"),
			NULL, SND_ASYNC);
		/* ○ PlaySound
		    -  기본적인 재생 함수. mmsystem 등 라이브러리 필요
			- (1) : 재생 사운드 경로 또는 리소스 이름
			- (2) : 사운드가 리소스일 경우, 리소스가 포함된 모듈 핸들
			- (3) : 재생 옵션 플래그.
			         - SND_ASYNC : 소리를 비동기로 재생. 위 플래그가 없다면, 소리가 모두 재생된 후에, 
					               하단 InvalidateRect 시행됨


			※ rc 가 WAVE 를 직접 지원하지 않기 때문에, 리소스에 넣으려면 수동으로 rc, resource.h 관리해야 되는 것 같음
			  번거로워서, 그냥 주소에서 가져오는 방법으로 함.

		    ※ PlaySound 함수는 한계가 많은데, 특히 소리를 중첩 재생하지 못하고, 기존 재생되던 사운드를 중단하고
			  재생함. 공부용으로 사용하되, 추후 다른 api 사용할듯
		*/ 



		InvalidateRect(hWndMain, NULL, FALSE);
	}
}

void InitStage()
{
	memcpy(ns, arStage[nStage], sizeof(ns));

	for (int y = 0; y < 18; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			if (ns[y][x] == '@')
			{
				nx = x;
				ny = y;
				ns[y][x] = ' ';
			}
		}
	}

	UndoIdx = 0;
	for (int i = 0; i < MAXUNDO; i++)
	{
		MoveInfo[i].dx = -2; // dx == -2 이면, 이동 기록이 없는 것으로 간주
	}

	nMove = 0;
	InvalidateRect(hWndMain, NULL, TRUE);
}

void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	BITMAP bit;

	MemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

	GetObject(hBit, sizeof(BITMAP), &bit);

	StretchBlt(hdc, x, y, BW, BH, MemDC, 0, 0, bit.bmWidth, bit.bmHeight, SRCCOPY);
	//BitBlt(hdc, x, y, bit.bmWidth, bit.bmHeight, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}

void ErasePack(int x, int y)
{
	if (arStage[nStage][y][x] == '.')
	{
		ns[y][x] = '.';
	}
	else
	{
		ns[y][x] = ' ';
	}
}

void Undo()
{
	if (UndoIdx != 0)
	{
		if (MoveInfo[--UndoIdx].bWithPack)
		{
			ErasePack(nx + MoveInfo[UndoIdx].dx, ny + MoveInfo[UndoIdx].dy);
			ns[ny][nx] = 'O';
		}

		nx -= MoveInfo[UndoIdx].dx;
		ny -= MoveInfo[UndoIdx].dy;

		if (MoveInfo[UndoIdx].dy > 0)
		{
			ManBit = 8;
		}
		else if (MoveInfo[UndoIdx].dy < 0)
		{
			ManBit = 7;
		}
		else if (MoveInfo[UndoIdx].dx > 0)
		{
			ManBit = 6;
		}
		else
		{
			ManBit = 5;
		}

		InvalidateRect(hWndMain, NULL, FALSE);
	}
}

void Redo()
{
	if (MoveInfo[UndoIdx].dx != -2)
	{
		nx += MoveInfo[UndoIdx].dx;
		ny += MoveInfo[UndoIdx].dy;

		if (MoveInfo[UndoIdx].dy > 0)
		{
			ManBit = 8;
		}
		else if (MoveInfo[UndoIdx].dy < 0)
		{
			ManBit = 7;
		}
		else if (MoveInfo[UndoIdx].dx > 0)
		{
			ManBit = 6;
		}
		else
		{
			ManBit = 5;
		}



		if (MoveInfo[UndoIdx].bWithPack)
		{
			ErasePack(nx, ny);
			ns[ny + MoveInfo[UndoIdx].dy][nx + MoveInfo[UndoIdx].dx] = 'O';
		}
		InvalidateRect(hWndMain, NULL, FALSE);
		UndoIdx++;
	}
}



#endif // 주석























               


































#if 1 // 코드만
#include <Windows.h>
#include "resource.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define MAXSTAGE 3
#define BW 32
#define BH 32

void DrawScreen(HDC hdc);

BOOL TestEnd();

void Move(int dir);
void InitStage();
void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit);

char ns[18][21];
int nStage;
int nx, ny;
int nMove;
HBITMAP hBit[9];

char arStage[MAXSTAGE][18][21] = 
{
	{
		"###################",
		"###################",
		"###################",
		"#####  ############",
		"#####  ############",
		"#####    ###########",
		"###   O ##########",
		"### #  ####### ###",
		"##        @  ..###",
		"##  ### ##  .. ##",
		"#####     #########",
		"###################",
		"###################",
		"###################",
		"###################",
		"###################",
		"###################",
		"###################"
},
	{
		"###################",
		"###################",
		"###################",
		"#####  ############",
		"#####O ############",
		"#####  O###########",
		"### O O ##########",
		"### #  ####### ###",
		"##O  O    @  ..###",
		"##  ### ##  .. ##",
		"#####     #########",
		"###################",
		"###################",
		"###################",
		"###################",
		"###################",
		"###################",
		"###################"
},
	{
		"###################",
		"###################",
		"###################",
		"#####  ############",
		"#####O ############",
		"#####  O###########",
		"### O O ##########",
		"### #  ####### ###",
		"##O  O    @  ..###",
		"##  ### ##  .. ##",
		"#####     #########",
		"###################",
		"###################",
		"###################",
		"###################",
		"###################",
		"###################",
		"###################"
}

};


#define MAXUNDO 1'000
struct tag_MoveInfo
{
	char dx : 3;
	char dy : 3;
	char bWithPack : 2;
};

tag_MoveInfo MoveInfo[MAXUNDO];
int UndoIdx;
int ManBit = 8;

void ErasePack(int x, int y);
void Undo();
void Redo();

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("Practice_Game_Sokoban");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
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

	
	hWndMain = CreateWindow(lpszClass, lpszClass, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, 0, 0,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWndMain, nCmdShow);

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

	
	switch (iMessage)
	{
	case WM_CREATE:
		RECT crt;
		SetRect(&crt, 0, 0, 900, BH * 18);
		AdjustWindowRect(&crt, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);
		SetWindowPos(hWnd, NULL, 0, 0, crt.right - crt.left, crt.bottom - crt.top,
			SWP_NOMOVE | SWP_NOZORDER);
		for (int i = 0; i < 9; i++)
		{
			hBit[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2 + i));
		}
		nStage = 0;
		InitStage();

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		DrawScreen(hdc);
		EndPaint(hWnd, &ps);
		
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
		case VK_RIGHT:
		case VK_DOWN:
		case VK_UP:
			Move(wParam);
			if (TestEnd())
			{
				TCHAR Message[256];
				wsprintf(Message, TEXT("%d 스테이지를 풀었습니다. 다음 스테이지로 이동합니다."), nStage + 1);
				MessageBox(hWnd, Message, TEXT("알림"), MB_OK);
				if (nStage < MAXSTAGE - 1)
				{
					nStage++;
				}
				InitStage();
			}

			break;


		case 'Q':
			DestroyWindow(hWnd);
			break;
		case 'R':
			InitStage();
			break;
		case 'N':
			if (nStage < MAXSTAGE - 1)
			{
				nStage++;
				InitStage();
			}
			break;
		case 'P':
			if (nStage > 0)
			{
				nStage--;
				InitStage();
			}
			break;

		case 'Z':
			Undo();
			break;

		case 'Y':
			Redo();
			break;
		}



		return 0;

	case WM_DESTROY:
		for (int i = 0; i < 5; i++)
		{
			DeleteObject(hBit[i]);
		}
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void DrawScreen(HDC hdc)
{
	int iBit;

	for (int y = 0; y < 18; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			switch (ns[y][x])
			{
			case '#':
				iBit = 1;
				break;
			case 'O':
				iBit = 0;
				break;
			case '.':
				iBit = 4;
				break;
			case ' ':
				iBit = 3;
				break;
			}

			DrawBitmap(hdc, x * BW, y * BH, hBit[iBit]);
		}
	}

	DrawBitmap(hdc, nx * BW, ny * BH, hBit[ManBit]);

	TCHAR Message[256];
	wsprintf(Message, TEXT("SOKOBAN"));
	TextOut(hdc, 700, 10, Message, lstrlen(Message));
	wsprintf(Message, TEXT("Q:종료, R:다시시작"));
	TextOut(hdc, 700, 30, Message, lstrlen(Message));
	wsprintf(Message, TEXT("N:다음, P:이전"));
	TextOut(hdc, 700, 50, Message, lstrlen(Message));
	wsprintf(Message, TEXT("Z:취소, Y:재실행"));
	TextOut(hdc, 700, 70, Message, lstrlen(Message));
	wsprintf(Message, TEXT("스테이지 : %d"), nStage + 1);
	TextOut(hdc, 700, 90, Message, lstrlen(Message));
	wsprintf(Message, TEXT("이동 회수 : %d"), nMove);
	TextOut(hdc, 700, 110, Message, lstrlen(Message));
}

BOOL TestEnd()
{
	for (int y = 0; y < 18; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			if (ns[y][x] == 'O' && arStage[nStage][y][x] != '.')
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

void Move(int dir)
{
	int dx = 0, dy = 0;

	switch (dir)
	{
	case VK_LEFT:
		ManBit = 5;
		dx = -1;
		break;
	case VK_RIGHT:
		ManBit = 6;
		dx = 1;
		break;
	case VK_UP:
		ManBit = 7;
		dy = -1;
		break;
	case VK_DOWN:
		ManBit = 8;
		dy = 1;
		break;
	}


	char nextPos = ns[ny + dy][nx + dx];
	char farPos = ns[ny + dy * 2][nx + dx * 2];

	BOOL bWithPack = FALSE;
	
	if (nextPos != '#')
	{
		if (nextPos == 'O')
		{
			if (farPos == ' ' || farPos == '.')
			{
				ErasePack(nx + dx, ny + dy);
				
				ns[ny + dy * 2][nx + dx * 2] = 'O';

				bWithPack = TRUE;
			}
			else
			{
				return;
			}
		}

		nx += dx;
		ny += dy;
		nMove++;

		
		MoveInfo[UndoIdx].dx = dx;
		MoveInfo[UndoIdx].dy = dy;
		MoveInfo[UndoIdx].bWithPack = bWithPack;
		
		MoveInfo[++UndoIdx].dx = -2;

		if (UndoIdx >= MAXUNDO - 1)
		{
			memmove(MoveInfo, &MoveInfo[100], (MAXUNDO - 100) * sizeof(tag_MoveInfo));

			for (int i = MAXUNDO - 100; i < MAXUNDO; i++)
			{
				MoveInfo[i].dx = -2;
			}

			UndoIdx -= 100;
		}
		

		PlaySound(TEXT("C:\\Users\\Heetae\\source\\repos\\Learning_WindowsAPI\\OtherFiles\\FootStepSound.wav"),
			NULL, SND_ASYNC);

		InvalidateRect(hWndMain, NULL, FALSE);
	}
}

void InitStage()
{
	memcpy(ns, arStage[nStage], sizeof(ns));

	for (int y = 0; y < 18; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			if (ns[y][x] == '@')
			{
				nx = x;
				ny = y;
				ns[y][x] = ' ';
			}
		}
	}

	UndoIdx = 0;
	for (int i = 0; i < MAXUNDO; i++)
	{
		MoveInfo[i].dx = -2;
	}

	nMove = 0;
	InvalidateRect(hWndMain, NULL, TRUE);
}

void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	BITMAP bit;

	MemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

	GetObject(hBit, sizeof(BITMAP), &bit);

	StretchBlt(hdc, x, y, BW, BH, MemDC, 0, 0, bit.bmWidth, bit.bmHeight, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}

void ErasePack(int x, int y)
{
	if (arStage[nStage][y][x] == '.')
	{
		ns[y][x] = '.';
	}
	else
	{
		ns[y][x] = ' ';
	}
}

void Undo()
{
	if (UndoIdx != 0)
	{
		if (MoveInfo[--UndoIdx].bWithPack)
		{
			ErasePack(nx + MoveInfo[UndoIdx].dx, ny + MoveInfo[UndoIdx].dy);
			ns[ny][nx] = 'O';
		}

		nx -= MoveInfo[UndoIdx].dx;
		ny -= MoveInfo[UndoIdx].dy;

		if (MoveInfo[UndoIdx].dy > 0)
		{
			ManBit = 8;
		}
		else if (MoveInfo[UndoIdx].dy < 0)
		{
			ManBit = 7;
		}
		else if (MoveInfo[UndoIdx].dx > 0)
		{
			ManBit = 6;
		}
		else
		{
			ManBit = 5;
		}

		
		InvalidateRect(hWndMain, NULL, FALSE);
	}
}

void Redo()
{
	if (MoveInfo[UndoIdx].dx != 2)
	{
		nx += MoveInfo[UndoIdx].dx;
		ny += MoveInfo[UndoIdx].dy;

		if (MoveInfo[UndoIdx].dy > 0)
		{
			ManBit = 8;
		}
		else if (MoveInfo[UndoIdx].dy < 0)
		{
			ManBit = 7;
		}
		else if (MoveInfo[UndoIdx].dx > 0)
		{
			ManBit = 6;
		}
		else
		{
			ManBit = 5;
		}

		if (MoveInfo[UndoIdx].bWithPack)
		{
			ErasePack(nx, ny);
			ns[ny + MoveInfo[UndoIdx].dy][nx + MoveInfo[UndoIdx].dx] = 'O';
		}

		InvalidateRect(hWndMain, NULL, FALSE);
		UndoIdx++;
	}
}


#endif // 코드만

#endif // Total