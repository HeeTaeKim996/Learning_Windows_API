#if 0 // Total
/*----------------------------------------------------------------------------------------------------
      Bitmap으로 2차원의 그림을 화면에 출력하는 코드입니다.
----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
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
	/* ○ CreateCompatibleDC
		- 화면출력 DC에 직접 Bitmap 파일을 복사하지 않는다. 화면 DC에 호환되는 DC(소스비트맵)를
		CreateCompatiable에 할당한 후, 그 DC에 우선 Bitmap을 로드후 (하단의 LoadBotmap과 SelectObject로)
		BitBlt 등의 함수로 화면 DC에 미리 준비한 DC 내용을 복사한다
	*/

	HBITMAP OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

	BITMAP bit;
	GetObject(hBit, sizeof(BITMAP), &bit);
	/* ○ GetObject : GDI Object 에 관한 정보 추출 
		- (1) : HBITMAP, HBRUSH, HPEN, HFONT, HPLATTE 등 정보를 가져올 GDI Object 입력
		- (2) : 정보를 받아올 데이터 크기
		- (3) : 정보를 받을 주소
	*/

	BitBlt(hdc, x, y, bit.bmWidth, bit.bmHeight, MemDC, 0, 0, SRCCOPY);
	/* ○ BitBlt
	- BitBlt는 할당된 Bitmap의 width, Height를 확장, 축소 하지 않고 그대로 복붙
	- (1) : 복사받는 화면 DC
	- (2) : 시작 x
	- (3) : 시작 y
	- (4) : width
	- (5) : height
	- (6) : 복사하는 준비된 DC
	- (7) : 복사시작 DC 의 x
	- (8) : 복사시작 DC 의 y
	- (9) : 웬만함 SRCCOPY로 기억하자.
			※ SetDROP2 처럼, 그리기모드처럼 그리는 방법 지정
			 - BLACKNESS	: 대상영역을 검정색으로 채움
			 - DSTINVERT	: 화면을 반전시킨다
			 - MERGECOPY	: 소스 비트맵과 화면을 AND 연산한다
			 - MERGEPAINT	: 소스 비트맵과 대상 화면을 OR 연산한다
			 - SCROPPY		: 소스 영역을 대상 영역에 복사 (기본)
			 - WHITENESS	: 대상영역을 흰색으로 채운다
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
	// ※ StretchBlt : BitBlt와 다르게, 비트맵 축소/확대 가능. (4), (5) 에 맞춰, (9), (10) 을 축소/확대
	
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


#endif // 주석


#if 1 // 코드만
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

#endif // 코드만


#endif // Total