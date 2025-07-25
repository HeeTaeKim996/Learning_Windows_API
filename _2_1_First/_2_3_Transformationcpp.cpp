#if 0 // WinMain

/* _2_1 코드 기반으로, 일부 커스터마이징하는 내용입니다 */

#if 0 // 주석 vs 코드만

/*-----------
	 주석
-----------*/

#include <stdio.h>
#include <stdlib.h>
#include "Windows.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("_2_3_Transformation");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;


	if (0)
	{
		WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	}
	else if (0)
	{
		WndClass.hbrBackground = CreateSolidBrush(RGB(0, 0, 255));
	}
	else if(1)
	{
		WndClass.hbrBackground = CreateHatchBrush(HS_CROSS, RGB(54, 88, 37));
	}
	/*
	- GetStockObject	: 윈도우 기본 제공 펜, 브러시 (  WHITE_BRUSH, BLACK_BRUSH, LTGRAY_BRUSH .. )
	- CreateSolidBrush	: RGB 값을 수동 지정
	- CreateHatchBrush	: 여러 무늬 가능. (1) : 무늬지정 enum , (2) : 색상
	*/
	
	
	if (0)
	{
		WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	}
	else if (0)
	{
		WndClass.hCursor = LoadCursor(NULL, IDC_CROSS);
	}
	else if (1)
	{
		WndClass.hCursor = LoadCursor(NULL, IDC_HAND);
	}
	else if (0)
	{
		WndClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(999)); // 5장에서 배운다 한다. 이 내용은 지피티 기반
	}
	/* ○ WndClass.hCursor
	    - (1) : NULL 일시, 윈도우 기본 제공 커서 사용. hInstance일시, 프로그램의 리소스 파일에서 커서 가져올 수 있ㅇ므
		 ※ hInstance는 프로그램의 핸들러로 식별자 역할 뿐만 아니라, 프로그램의 리소스 파일 접근에도 키로 필요하다 함
		- (2) : 커서 enum 
	*/
	
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);

	if (0)
	{
		hWnd = CreateWindow(lpszClass, TEXT("안녕해리야"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 
			CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
		// - (2)항을 lpszClass로 하지 않고, 직접 TEXT를 할당했다
	}
	else if (0)
	{
		hWnd = CreateWindow(lpszClass, TEXT("안녕해리야"), WS_OVERLAPPEDWINDOW, 0, 0, 1700,
			1000, NULL, (HMENU)NULL, hInstance, NULL);
		// - (4),(5), (6),(7) 을 CW_USEDEFAULT가 아닌 수동 할당했다. 대부분 CW_USEDEFAULT 를 사용한다 한다
	}
	else if (0)
	{
		hWnd = CreateWindow(lpszClass, TEXT("안녕보리야"), 
			(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX),
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
		/* ○ (3)항 - dwStyle
		    - WS_OVERLAPPED		: 제목 표시줄과 경계선 표시
			- WS_CAPTION		: 타이틀 바를 가진다
			- WS_SYSMENU		: 시스템 메뉴를 가진다
			- WS_THICKFRAME		: 크기를 조절할 수 있는 경계선을 가진다
			- WS_MINIMIZEBOX	: 최소화 버튼을 가진다
			- WS_MAXIMIZEBOX	: 최대화 버튼을 가진다
		*/
	}
	else if (1)
	{
		hWnd = CreateWindow(lpszClass, TEXT("안녕보리야"),
			(WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL),
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
		/* ○ (3)항 - dwStype +
		    - WS_OVERLAPPEDWINDOW 
			 == WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIZEBOX | WS_MAXIMIZEBOX
			- WS_VSCROLL : 수직 스크롤바
			- WS_HSCROLL : 횡축 스크롤바
		*/
	}




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
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		MessageBeep(0);
		return 0;
		// 마우스 좌클릭시, 삡 소리가 나도록 함
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}



 #else
/*----------------
	  코드만
-----------------*/
#include <stdio.h>
#include <stdlib.h>
#include "Windows.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("_2_3_Transformation");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;

	if (0)
	{
		WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	}
	else if (1)
	{
		WndClass.hbrBackground = CreateSolidBrush(RGB(0, 0, 30));
	}
	else if (0)
	{
		WndClass.hbrBackground = CreateHatchBrush(HS_CROSS, RGB(54, 88, 37));
	}


	if (0)
	{
		WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	}
	else if (0)
	{
		WndClass.hCursor = LoadCursor(NULL, IDC_CROSS);
	}
	else if (1)
	{
		WndClass.hCursor = LoadCursor(NULL, IDC_HAND);
	}
	else if (0)
	{
		WndClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(999));
	}


	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);


	if (0)
	{
		hWnd = CreateWindow(lpszClass, TEXT("수동입력"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	}
	else if (0)
	{
		hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
			0, 0, 1700, 1000,
			NULL, (HMENU)NULL, hInstance, NULL);
	}
	else if (0)
	{
		hWnd = CreateWindow(lpszClass, lpszClass,
			(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX),
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	}
	else if (1)
	{
		hWnd = CreateWindow(lpszClass, lpszClass, 
			( WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL ),
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			NULL, (HMENU)NULL, hInstance, NULL);
	}


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
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		MessageBeep(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}




#endif // 주석 vs 코드만


#endif // WinMain