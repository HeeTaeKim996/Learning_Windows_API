#if 0 // WinMain

/* _2_1 �ڵ� �������, �Ϻ� Ŀ���͸���¡�ϴ� �����Դϴ� */

#if 0 // �ּ� vs �ڵ常

/*-----------
	 �ּ�
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
	- GetStockObject	: ������ �⺻ ���� ��, �귯�� (  WHITE_BRUSH, BLACK_BRUSH, LTGRAY_BRUSH .. )
	- CreateSolidBrush	: RGB ���� ���� ����
	- CreateHatchBrush	: ���� ���� ����. (1) : �������� enum , (2) : ����
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
		WndClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(999)); // 5�忡�� ���� �Ѵ�. �� ������ ����Ƽ ���
	}
	/* �� WndClass.hCursor
	    - (1) : NULL �Ͻ�, ������ �⺻ ���� Ŀ�� ���. hInstance�Ͻ�, ���α׷��� ���ҽ� ���Ͽ��� Ŀ�� ������ �� �֤���
		 �� hInstance�� ���α׷��� �ڵ鷯�� �ĺ��� ���� �Ӹ� �ƴ϶�, ���α׷��� ���ҽ� ���� ���ٿ��� Ű�� �ʿ��ϴ� ��
		- (2) : Ŀ�� enum 
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
		hWnd = CreateWindow(lpszClass, TEXT("�ȳ��ظ���"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 
			CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
		// - (2)���� lpszClass�� ���� �ʰ�, ���� TEXT�� �Ҵ��ߴ�
	}
	else if (0)
	{
		hWnd = CreateWindow(lpszClass, TEXT("�ȳ��ظ���"), WS_OVERLAPPEDWINDOW, 0, 0, 1700,
			1000, NULL, (HMENU)NULL, hInstance, NULL);
		// - (4),(5), (6),(7) �� CW_USEDEFAULT�� �ƴ� ���� �Ҵ��ߴ�. ��κ� CW_USEDEFAULT �� ����Ѵ� �Ѵ�
	}
	else if (0)
	{
		hWnd = CreateWindow(lpszClass, TEXT("�ȳ纸����"), 
			(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX),
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
		/* �� (3)�� - dwStyle
		    - WS_OVERLAPPED		: ���� ǥ���ٰ� ��輱 ǥ��
			- WS_CAPTION		: Ÿ��Ʋ �ٸ� ������
			- WS_SYSMENU		: �ý��� �޴��� ������
			- WS_THICKFRAME		: ũ�⸦ ������ �� �ִ� ��輱�� ������
			- WS_MINIMIZEBOX	: �ּ�ȭ ��ư�� ������
			- WS_MAXIMIZEBOX	: �ִ�ȭ ��ư�� ������
		*/
	}
	else if (1)
	{
		hWnd = CreateWindow(lpszClass, TEXT("�ȳ纸����"),
			(WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL),
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
		/* �� (3)�� - dwStype +
		    - WS_OVERLAPPEDWINDOW 
			 == WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIZEBOX | WS_MAXIMIZEBOX
			- WS_VSCROLL : ���� ��ũ�ѹ�
			- WS_HSCROLL : Ⱦ�� ��ũ�ѹ�
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
		// ���콺 ��Ŭ����, �� �Ҹ��� ������ ��
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}



 #else
/*----------------
	  �ڵ常
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
		hWnd = CreateWindow(lpszClass, TEXT("�����Է�"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
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




#endif // �ּ� vs �ڵ常


#endif // WinMain