#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	
	- SaveDC, RestoreDC �� ���� �����Դϴ�.
	  �Ʒ� ������ �� �䵥, ª�� �����ϸ�,
	  SaveDC �� '���ڷ� ���� HDC�� ���� ������ ���纻�� ���� ����ü�� �����, �ش� ����ü�� ID �� int�� ��ȯ�ϴ� �Լ�'
	  �Դϴ�.
	  RestoreDC �� �ݴ�� ��ȯ�� int������, �ش� HDC�� �ʵ����� ���纻 �������� ��ü�ϴ� �Լ��Դϴ�.
	  �� SaveDC �� ���� Ű�� int ��, ReleaseDC ( EndPaint ) ���� ����ؾ� ��ȿ�մϴ�. ���Ŀ��� �������ϴ�





	�� �Ʒ� ������ ������ ����Ƽ�κ��� ��� ������ �����̴�, ��Ȯ���� ���� ������ �� ����.
	�� �Ʒ� ������ SaveDC �� ��ȯ���� int�ε�, �� int�� HBRUSH, HPEN, HBITMAP �� hdc�� ��� �ִ� ������ ������
	  ��� �������� int�� ������ �� �ִ��� �� ���� �������� �����Ͽ�, ������ ������
	�� �̸� �����ϱ� ����, ������ API ���� H�� �����ϴ� HANDLE Ÿ���� �ǹ̿�, LP �� �ǹ̿� ���� ���� �� �켱 ����
	   ( �� ���� ���� ����Ƽ�κ��� ���� �����̱� ������, ��Ȯ���� ���� )

	�� H (HANDLE)
	 - �ڵ��� ID�� �ǹ�. WINDOW API ������, ����ü �� �����͸� �����ϰ�, ó���ϴ� GDI ���� ��? �� �� �ִµ�,
	   �̵��� �����͸� ���̺� ���� �ڷᱸ���� ������.
	   �׸��� GDI ���� ���� ���� ���� �� �ڷᱸ�� �� �з� �� ������ ID�� ���� ������
	 - H �� �� ID �� �ǹ�

	�� LP �� H �� ����
	 - LP �� �ռ� �����ߵ�, ������ �� �ǹ�. �ݸ� H�� ���̺�(�ڷᱸ��) �� �����ϱ� ���� ID �� �ǹ�

	�� HDC �� GDI_DC 
	 - HDC �� GDI_DC �� ID. 
	 - GDI_DC�� HPEN, HBRUSH, HBITMAP ���� �ʵ����� ������ ����ü�̸�,
	   GDI_DC ���纻 ( �� SaveData ���� �������� ����, GDI_DC �� �ʵ������� ������ ���纻���� ���� ����ü) 
	   ��� ������ ���� ���� �ʵ� ����� GDI_DC �� ���� ����

	�� SaveDC ��, �ش� HDC �� GDI_DC �� GDI_DC ���纻 �� ID ������ ���� int��
	  ��ȯ�� 
	  ( ������غôµ�, ó�� SaveDC�� ��ȯ���� 1, �������� �ι�°�� SaveDC�� ��ȯ���� 2 ����..
	    1���� �����ϴ� ������ �ε����� ��ȯ�ϴ� �� ���� )



	�� RestoreDC �� �� int�� ��������, ������ GDI_DC �� GDIC_���纻 �� ������ �μ� HDC �� �ش� ���纻�� ����

	�� SaveDC�� ��ȯ����, GDI_DC �� �ʵ��� ���纻 GDI_DC�� ���� �ε��� ��ȣ�� �ǹ��ϸ�,
	  GDI_DC �� ReleaseDC �� �޸� �����Ǳ� ������, SaveDC �� ��ȯ���� ReleaseDC( EndPaint ) ������ ��ȿ��




----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
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





#endif // �ּ�


#if 1 // �ڵ常
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

#endif // �ڵ常


#endif // Total