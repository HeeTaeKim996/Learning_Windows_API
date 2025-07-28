#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	
	- SaveDC, RestoreDC 에 대한 내용입니다.
	  아래 정리한 게 긴데, 짧게 정리하면,
	  SaveDC 는 '인자로 받은 HDC의 현재 정보의 복사본을 가진 구조체를 만들고, 해당 구조체의 ID 를 int로 반환하는 함수'
	  입니다.
	  RestoreDC 는 반대로 반환된 int값으로, 해당 HDC의 필드멤버를 복사본 내용으로 교체하는 함수입니다.
	  ※ SaveDC 로 받은 키인 int 는, ReleaseDC ( EndPaint ) 전에 사용해야 유효합니다. 이후에는 오류납니다





	※ 아래 정리한 내용은 지피티로부터 듣고 정리한 내용이니, 정확하지 않은 정보일 수 있음.
	※ 아래 내용은 SaveDC 의 반환값이 int인데, 이 int로 HBRUSH, HPEN, HBITMAP 등 hdc가 담고 있는 다차원 정보를
	  어떻게 일차원의 int에 저장할 수 있는지 에 대한 질문으로 시작하여, 정리한 내용임
	※ 이를 이해하기 위해, 윈도우 API 에서 H로 시작하는 HANDLE 타입의 의미와, LP 의 의미에 대한 정리 를 우선 시작
	   ( 위 정보 또한 지피티로부터 얻은 정보이기 때문에, 정확하지 않음 )

	○ H (HANDLE)
	 - 핸들은 ID를 의미. WINDOW API 에서는, 구조체 의 데이터를 관리하고, 처리하는 GDI 같은 것? 들 이 있는데,
	   이들은 데이터를 테이블 같은 자료구조에 저장함.
	   그리고 GDI 같은 통합 관리 들은 이 자료구조 를 분류 및 관리를 ID를 통해 관리함
	 - H 는 이 ID 를 의미

	○ LP 와 H 의 차이
	 - LP 는 앞서 정리했듯, 포인터 를 의미. 반면 H는 테이블(자료구조) 를 관리하기 위한 ID 를 의미

	○ HDC 와 GDI_DC 
	 - HDC 는 GDI_DC 의 ID. 
	 - GDI_DC는 HPEN, HBRUSH, HBITMAP 등의 필드멤버로 구성된 구조체이며,
	   GDI_DC 복사본 ( 위 SaveData 에서 가져오기 위한, GDI_DC 의 필드멤버들의 정보를 복사본으로 담은 구조체) 
	   들로 구성된 스택 또한 필드 멤버로 GDI_DC 가 갖고 있음

	○ SaveDC 는, 해당 HDC 의 GDI_DC 의 GDI_DC 복사본 의 ID 정보를 담은 int를
	  반환함 
	  ( 디버그해봤는데, 처음 SaveDC한 반환값은 1, 연속으로 두번째로 SaveDC한 반환값은 2 였음..
	    1부터 시작하는 스택의 인덱스를 반환하는 듯 싶음 )



	○ RestoreDC 는 위 int를 기준으로, 역으로 GDI_DC 의 GDIC_복사본 을 가져와 인수 HDC 에 해당 복사본을 복사

	※ SaveDC의 반환값은, GDI_DC 의 필드멤버 복사본 GDI_DC의 스택 인덱스 번호를 의미하며,
	  GDI_DC 는 ReleaseDC 시 메모리 해제되기 때문에, SaveDC 의 반환값은 ReleaseDC( EndPaint ) 전까지 유효함




----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>
#include "resource.h"

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


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int nSaveDC;


	switch (iMessage)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		SelectObject(hdc, GetStockObject(LTGRAY_BRUSH));
		Rectangle(hdc, 0, 0, 300, 200);

		nSaveDC = SaveDC(hdc);

		SelectObject(hdc, GetStockObject(BLACK_BRUSH));
		Ellipse(hdc, 0, 0, 300, 200);

		RestoreDC(hdc, nSaveDC);
		Rectangle(hdc, 50, 50, 250, 150);
		
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
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


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int nSaveDC;


	switch (iMessage)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		SelectObject(hdc, GetStockObject(LTGRAY_BRUSH));
		Rectangle(hdc, 0, 0, 300, 200);

		nSaveDC = SaveDC(hdc);

		SelectObject(hdc, GetStockObject(BLACK_BRUSH));
		Ellipse(hdc, 0, 0, 300, 200);

		RestoreDC(hdc, nSaveDC);
		Rectangle(hdc, 50, 50, 250, 150);

		EndPaint(hWnd, &ps);
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // 코드만


#endif // Total