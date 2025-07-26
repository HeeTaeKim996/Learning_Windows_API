#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	���� ���� �� ���� �ڵ��Դϴ�.
	�ռ� ���꿡���� ���, ������ WndClass �� �Լ��� ������� �Ŀ�, SetWindow(Class)LongPtr �� 
	WNDPROC �� ��ü�ϴ� ����� �ݸ�,
	���� ������ ���� ������� WndClass�� GetClassInfo �� �����Ͽ� ������ ��, ������ WndClass�� �����Ͽ�, 
	���ο� Ŭ������ ����Ͽ� ����ϴ� ����Դϴ�.
----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_SuperEdit");

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



LPCTSTR superClass = TEXT("SuperEditExam");
WNDPROC OldProc;
#define ID_EDIT1 100
HWND hEdit1;
LRESULT CALLBACK SuperProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		MessageBeep(0);
		break;
	}

	return CallWindowProc(OldProc, hWnd, iMessage, wParam, lParam);
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	WNDCLASS superWndClass;
	const TCHAR* Mes = TEXT("����Ʈ���� Ű���带 ���� ������ �Ҹ��� ���ϴ�");

	switch (iMessage)
	{
	case WM_CREATE:
		GetClassInfo(NULL, TEXT("edit"), &superWndClass);
		/* �� GetClassInfo �� (1)��
		    - �����Ϸ��� Ŭ������ �ý��� Ŭ���� (edit, button, combobox..) �� ���, NULL �� �Է�
			- �����Ϸ��� Ŭ������ ����� ���� Ŭ������ ���, ��κ� g_hInst �Է�
		*/

		superWndClass.hInstance = g_hInst;
		superWndClass.lpszClassName = superClass;
		superWndClass.hCursor = LoadCursor(NULL, IDC_WAIT);
		OldProc = superWndClass.lpfnWndProc;
		superWndClass.lpfnWndProc = SuperProc;
		RegisterClass(&superWndClass);

		hEdit1 = CreateWindow(superClass, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 10, 200, 25,
			hWnd, (HMENU)ID_EDIT1, g_hInst, NULL);
		SetFocus(hEdit1);

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 100, Mes, lstrlen(Mes));
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

LRESULT CALLBACK SendProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR SendClass = TEXT("Learning_SuperEdit");

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
	WndClass.lpfnWndProc = SendProc;
	WndClass.lpszClassName = SendClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_VREDRAW | CS_HREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(SendClass, SendClass, WS_OVERLAPPEDWINDOW,
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


LPCTSTR superClass = TEXT("SuperEditExam");
WNDPROC OldProc;
#define ID_EDIT1 100
HWND hEdit1;
LRESULT CALLBACK SuperProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		MessageBeep(0);
		break;
	}

	return CallWindowProc(OldProc, hWnd, iMessage, wParam, lParam);
}



LRESULT CALLBACK SendProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	WNDCLASS superWndClass;
	const TCHAR* Mes = TEXT("����Ʈ���� Ű���带 ���� ������ �Ҹ��� ���ϴ�");


	switch (iMessage)
	{
	case WM_CREATE:
		GetClassInfo(NULL, TEXT("edit"), &superWndClass);

		superWndClass.hInstance = g_hInst;
		superWndClass.lpszClassName = superClass;
		superWndClass.hCursor = LoadCursor(NULL, IDC_WAIT);
		OldProc = superWndClass.lpfnWndProc;
		superWndClass.lpfnWndProc = SuperProc;
		RegisterClass(&superWndClass);

		hEdit1 = CreateWindow(superClass, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 10, 200, 25,
			hWnd, (HMENU)ID_EDIT1, g_hInst, NULL);
		SetFocus(hEdit1);

		return 0;


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 100, Mes, lstrlen(Mes));
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