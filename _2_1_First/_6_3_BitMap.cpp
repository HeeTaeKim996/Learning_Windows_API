#if 0 // Total
/*----------------------------------------------------------------------------------------------------
      Bitmap���� 2������ �׸��� ȭ�鿡 ����ϴ� �ڵ��Դϴ�.
----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("BitMap");

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


void DrawBitBlt(HDC hdc, int x, int y, HBITMAP hBit)
{
	HDC MemDC = CreateCompatibleDC(hdc);
	/* �� CreateCompatibleDC
		- ȭ����� DC�� ���� Bitmap ������ �������� �ʴ´�. ȭ�� DC�� ȣȯ�Ǵ� DC(�ҽ���Ʈ��)��
		CreateCompatiable�� �Ҵ��� ��, �� DC�� �켱 Bitmap�� �ε��� (�ϴ��� LoadBotmap�� SelectObject��)
		BitBlt ���� �Լ��� ȭ�� DC�� �̸� �غ��� DC ������ �����Ѵ�
	*/

	HBITMAP OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

	BITMAP bit;
	GetObject(hBit, sizeof(BITMAP), &bit);
	/* �� GetObject : GDI Object �� ���� ���� ���� 
		- (1) : HBITMAP, HBRUSH, HPEN, HFONT, HPLATTE �� ������ ������ GDI Object �Է�
		- (2) : ������ �޾ƿ� ������ ũ��
		- (3) : ������ ���� �ּ�
	*/

	BitBlt(hdc, x, y, bit.bmWidth, bit.bmHeight, MemDC, 0, 0, SRCCOPY);
	/* �� BitBlt
	- BitBlt�� �Ҵ�� Bitmap�� width, Height�� Ȯ��, ��� ���� �ʰ� �״�� ����
	- (1) : ����޴� ȭ�� DC
	- (2) : ���� x
	- (3) : ���� y
	- (4) : width
	- (5) : height
	- (6) : �����ϴ� �غ�� DC
	- (7) : ������� DC �� x
	- (8) : ������� DC �� y
	- (9) : ������ SRCCOPY�� �������.
			�� SetDROP2 ó��, �׸�����ó�� �׸��� ��� ����
			 - BLACKNESS	: ��󿵿��� ���������� ä��
			 - DSTINVERT	: ȭ���� ������Ų��
			 - MERGECOPY	: �ҽ� ��Ʈ�ʰ� ȭ���� AND �����Ѵ�
			 - MERGEPAINT	: �ҽ� ��Ʈ�ʰ� ��� ȭ���� OR �����Ѵ�
			 - SCROPPY		: �ҽ� ������ ��� ������ ���� (�⺻)
			 - WHITENESS	: ��󿵿��� ������� ä���
	*/
	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}

void DrawStretchBlt(HDC hdc, int x, int y, int width, int height, HBITMAP hBit)
{
	HDC MemDC;
	HBITMAP OldBitmap;

	BITMAP bit;

	MemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

	GetObject(hBit, sizeof(BITMAP), &bit);

	StretchBlt(hdc, x, y, width, height, MemDC, 0, 0, bit.bmWidth, bit.bmHeight, SRCCOPY);
	// �� StretchBlt : BitBlt�� �ٸ���, ��Ʈ�� ���/Ȯ�� ����. (4), (5) �� ����, (9), (10) �� ���/Ȯ��
	
	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);

}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	HDC MemDC;

	PAINTSTRUCT ps;

	static HBITMAP MyBitmap;

	switch (iMessage)
	{
	case WM_CREATE:
		MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		DrawBitBlt(hdc, 0, 0, MyBitmap);
		DrawStretchBlt(hdc, 0, 0, 400, 300, MyBitmap);
		
		return 0;
	
	case WM_DESTROY:
		DeleteObject(MyBitmap);
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}


#endif // �ּ�


#if 1 // �ڵ常
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("BitMap");

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

void DrawBitBlt(HDC hdc, int x, int y, HBITMAP hBit)
{
	HDC MemDC = CreateCompatibleDC(hdc);

	HBITMAP OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

	BITMAP bit;
	GetObject(hBit, sizeof(BITMAP), &bit);

	BitBlt(hdc, x, y, bit.bmWidth, bit.bmHeight, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}

void DrawStretchBlt(HDC hdc, int x, int y, int width, int height, HBITMAP hBit)
{
	HDC MemDC = CreateCompatibleDC(hdc);

	HBITMAP OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

	BITMAP bit;
	GetObject(hBit, sizeof(BITMAP), &bit);

	StretchBlt(hdc, x, y, width, height, MemDC, 0, 0, bit.bmWidth, bit.bmHeight, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static HBITMAP storedBit;
	static RECT resolutionRect;

	switch (iMessage)
	{
	case WM_CREATE:
		storedBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		GetClientRect(hWnd, &resolutionRect);
		return 0;
	case WM_SIZE:
		resolutionRect.right = LOWORD(lParam);
		resolutionRect.bottom = HIWORD(lParam);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		DrawBitBlt(hdc, 0, 0, storedBit);

		DrawStretchBlt(hdc, 0, 0, resolutionRect.right / 3, resolutionRect.bottom / 3, storedBit);
		
		EndPaint(hWnd, &ps);

		return 0;
	case WM_DESTROY:
		DeleteObject(storedBit);
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // �ڵ常


#endif // Total