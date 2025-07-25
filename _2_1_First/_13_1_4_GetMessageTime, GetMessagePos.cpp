#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	GetMessageTime, GetMessagePos,
	GetDoubleClickTime, SM_CXDOUBLECLK, SM_CYDOUBLECLK �� ���� �ڵ��Դϴ�.
----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_TripleClick");


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



DWORD ct[5];
DWORD cp[5];

BOOL TestClicks(int n)
{
	if (n < 2 || n > 5) return FALSE;


	static DWORD dt = GetDoubleClickTime();
	static int dx = GetSystemMetrics(SM_CXDOUBLECLK);
	static int dy = GetSystemMetrics(SM_CYDOUBLECLK);
	/*	
		�� GetDoubleClickTime
		 - ���긦������ ������, Ŭ������ ���� ���Ѱ��� ��ȯ
	
	
		�� SM_CXDOUBLECLK vs SM_CYDOUBLECLK
		 - ����Ŭ������ ������, (X, Y) ������ �� Ŭ�� ���� ���Ѱ��� ��ȯ�ϴ� �÷���
	*/


	for (int i = 0; i < n - 1; i++)
	{
		if (ct[4 - i] - ct[4 - i - 1] > dt)							return FALSE;
		if(abs(LOWORD(cp[4 - i] - LOWORD(cp[4 - i - 1]))) > dx)		return FALSE;
		if (abs(HIWORD(cp[4 - i]) - HIWORD(cp[4 - i - 1])) > dy)	return FALSE;
	}

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR* Mes = TEXT("Ʈ���� Ŭ�� ���� �׽�Ʈ ���α׷�");

	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		for (int i = 0; i < 4; i++)
		{
			ct[i] = ct[i + 1];
			cp[i] = cp[i + 1];
		}
		ct[4] = GetMessageTime(); // �޼����� �߻����� ���� �ð� ( unsigned long)
		cp[4] = GetMessagePos(); // �� �޼����� �߻����� ���� Ŀ�� Pos (unsigned long)

		if (TestClicks(3))
		{
			MessageBox(hWnd, TEXT("Ʈ���� Ŭ���� ����Ǿ����ϴ�"), TEXT("�˸�"), MB_OK);
		}

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 10, Mes, lstrlen(Mes));
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
LPCTSTR lpszClass = TEXT("Learning_TripleClick");

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


DWORD ct[5];
DWORD cp[5];

BOOL TestClicks(int n)
{
	if (n < 2 || n > 5) return FALSE;

	static DWORD dt = GetDoubleClickTime();
	static int dx = GetSystemMetrics(SM_CXDOUBLECLK);
	static int dy = GetSystemMetrics(SM_CYDOUBLECLK);

	for (int i = 4; i > 4 - n + 1; i--)
	{
		if (ct[i] - ct[i - 1] > dt)							return FALSE;
		if (abs(LOWORD(cp[i]) - LOWORD(cp[i - 1])) > dx)	return FALSE;
		if (abs(HIWORD(cp[i]) - HIWORD(cp[i - 1])) > dy)		return FALSE;
	}

	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR* Mes = TEXT("Ʈ���� Ŭ�� ���� �׽�Ʈ ���α׷�");

	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		for (int i = 0; i < 4; i++)
		{
			ct[i] = ct[i + 1];
			cp[i] = cp[i + 1];
		}
		ct[4] = GetMessageTime();
		cp[4] = GetMessagePos();

		if (TestClicks(3))
		{
			MessageBox(hWnd, TEXT("Ʈ���� Ŭ���� ����ƽ��ϴ�"), TEXT("�˸�"), MB_OK);
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 10, Mes, lstrlen(Mes));
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