#if 0 // Total
/*---------------------------------------------------------------------------------
	���ݱ��� ������ ������ Ȱ���ؼ�, ������ ������ ����� �ڵ��Դϴ�. 
---------------------------------------------------------------------------------*/

#if 0 // �ּ�
#include <windows.h>
#include "resource.h"

// �� �Ҹ� ����� ���� h, lib
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

	/* �� ��Ʈ �ʵ�
		-  C, Cpp (C#������) ������, �ʵ����� ����Ʈ ������ �ƴ� ��Ʈ ������ �ɰ� �� �� �ִ�.
		- �� �ڵ�ó�� �ʵ��� ������, : 3, : 3, : 2 ó�� ����ϸ�, dx���� 3��Ʈ, dy���� 3��Ʈ, bWithPack����
		  2��Ʈ �� ����Ͽ� �� 8��Ʈ (1����Ʈ) �� ũ���� ����ü�� ����� �� �ִ�
		- ��Ʈ �ʵ�� ����� �� �ִ� Ÿ����, char, unsigned char, short, unsighed short, int, unsigned int,
		  long, unsigned long ��, ���� Ÿ���̴�.  (float �� �Ұ�)
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
		/* �� AdjustWindowRect
			- ������ ũ�� ����. x, y, w, h �ܿ�, (2)��ó�� �� �����? (3)ó�� �޴��� �� �ִ��� ���ε� �ľ�
			- ��, Ȯ��(���) �� �Ѵ�. ������ ���������� ������. ���� ������ �ϴ��� SetWindowPos ���� ��
			- (1) : CreateWidnow�� 4 5 6 7
			- (2) : CreateWindow�� 3)
			- (3) : �޴��ٰ� �ִ��� �ľ��ϴ� BOOL
		*/
		SetWindowPos(hWnd, NULL, 0, 0, crt.right - crt.left, crt.bottom - crt.top,
			SWP_NOMOVE | SWP_NOZORDER);
		/* �� SetWindowPos
			- ���� ������ ũ�� ���� �����ϴ� �Լ�.
			- (2) : Z ���� ����. (Z���� : ��Ƽ�½�ŷ����, ���� ���̴� ������ ���α׷��� Z ���� �� ���� �� )
					NULL �̸�, ���� Z ���� ����
			- (7) : �ɼ� �÷��׵�
					 - SWP_NOMOVE		: ��ġ(X,Y) ���� ����
					 - SW_NOSIZE		: ũ��(H,W) ���� ����
					 - SWP_NOZORDER		: Z ���� ���� ����
					 - SWP_SHOWWINDOW	: â�� ǥ��
					 - SWP_HIDEWINDOW	: â ����
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
				wsprintf(Message, TEXT("%d ���������� Ǯ�����ϴ�.")TEXT("���� ���������� �̵��մϴ�"),
					nStage + 1);
				MessageBox(hWnd, Message, TEXT("�˸�"), MB_OK);
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
	wsprintf(Message, TEXT("Q:����, R:�ٽý���"));
	TextOut(hdc, 700, 30, Message, lstrlen(Message));
	wsprintf(Message, TEXT("N:����, P:����"));
	TextOut(hdc, 700, 50, Message, lstrlen(Message));
	wsprintf(Message, TEXT("Z:���, Y:�����"));
	TextOut(hdc, 700, 70, Message, lstrlen(Message));
	wsprintf(Message, TEXT("�������� : %d"), nStage + 1);
	TextOut(hdc, 700, 90, Message, lstrlen(Message));
	wsprintf(Message, TEXT("�̵� ȸ�� : %d"), nMove);
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
		/* �� PlaySound
		    -  �⺻���� ��� �Լ�. mmsystem �� ���̺귯�� �ʿ�
			- (1) : ��� ���� ��� �Ǵ� ���ҽ� �̸�
			- (2) : ���尡 ���ҽ��� ���, ���ҽ��� ���Ե� ��� �ڵ�
			- (3) : ��� �ɼ� �÷���.
			         - SND_ASYNC : �Ҹ��� �񵿱�� ���. �� �÷��װ� ���ٸ�, �Ҹ��� ��� ����� �Ŀ�, 
					               �ϴ� InvalidateRect �����


			�� rc �� WAVE �� ���� �������� �ʱ� ������, ���ҽ��� �������� �������� rc, resource.h �����ؾ� �Ǵ� �� ����
			  ���ŷο���, �׳� �ּҿ��� �������� ������� ��.

		    �� PlaySound �Լ��� �Ѱ谡 ������, Ư�� �Ҹ��� ��ø ������� ���ϰ�, ���� ����Ǵ� ���带 �ߴ��ϰ�
			  �����. ���ο����� ����ϵ�, ���� �ٸ� api ����ҵ�
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
		MoveInfo[i].dx = -2; // dx == -2 �̸�, �̵� ����� ���� ������ ����
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



#endif // �ּ�























               


































#if 1 // �ڵ常
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
				wsprintf(Message, TEXT("%d ���������� Ǯ�����ϴ�. ���� ���������� �̵��մϴ�."), nStage + 1);
				MessageBox(hWnd, Message, TEXT("�˸�"), MB_OK);
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
	wsprintf(Message, TEXT("Q:����, R:�ٽý���"));
	TextOut(hdc, 700, 30, Message, lstrlen(Message));
	wsprintf(Message, TEXT("N:����, P:����"));
	TextOut(hdc, 700, 50, Message, lstrlen(Message));
	wsprintf(Message, TEXT("Z:���, Y:�����"));
	TextOut(hdc, 700, 70, Message, lstrlen(Message));
	wsprintf(Message, TEXT("�������� : %d"), nStage + 1);
	TextOut(hdc, 700, 90, Message, lstrlen(Message));
	wsprintf(Message, TEXT("�̵� ȸ�� : %d"), nMove);
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


#endif // �ڵ常

#endif // Total