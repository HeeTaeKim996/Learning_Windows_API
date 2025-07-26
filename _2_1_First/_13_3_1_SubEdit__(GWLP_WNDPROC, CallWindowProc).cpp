#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	���꿡�� (GWLP �� �����) �� ���� �ڵ��Դϴ�.
	�̹� ������� Ŭ���� button, edit ���� WNDPROC�� �ǵ� �� ���µ�,
	WND���� WNDPROC ó���� ����ä��, ���� ���� �ϰ�, ���� WNDPROC�� �ٽ� �޼����� �ѱ�� ����Դϴ�.

	�Ʒ� �ڵ�� edit1, edit2 �� ���꿡�� �Լ��� �߰��ؼ�, Tab�� �ҽ�, WNDPROC ó�� ����, 
	����� ���� ���� (�ٸ� WND �� SetFocus �ϱ�) �� �ϵ��� �����߽��ϴ�.

	�� GWLP_WNDPROC	: SetWindowLong�� �÷��׷�, (1)�� WND �� WNDPROC�� (3)�� �Լ��� �ٲ۴�. 
					  ���ϰ��� OLD WNDPROC �̴�.
					  -> (3)�� �Լ��� �������� ���ϰ����� OldProc�� ȣ���Ͽ�, ���� WNDPROC �� �۵��ϵ��� ó����
						
	�� WM_DESTROY �� �ٽ� SetWindowLong...( ..., GWL_WNDPROC, OldProc); ���� WND�� ���� WNDPROC����
	   �ٽ� �����ִµ�, �����ִ� ������ �𸣰���.. ������ ������ �׷��µ�
----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_SubEdit_SetWindowLongPtr");

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




#define ID_EDIT1 100
#define ID_EDIT2 101

HWND hEdit1;
WNDPROC OldEditProc1;

HWND hEdit2;
WNDPROC OldEditProc2;

LRESULT CALLBACK EditSubProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			MessageBox(hWnd, TEXT("Enter is Pressed"), TEXT("Edit"), MB_OK);
			SetFocus(hWnd);
			break;

		case VK_TAB:
			SetFocus(hEdit2);
			break;

		}
	}
	return CallWindowProc(OldEditProc1, hWnd, iMessage, wParam, lParam);
}

LRESULT CALLBACK EditSubProc2(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_TAB:
			SetFocus(hEdit1);
			break;

		}
	}
	return CallWindowProc(OldEditProc2, hWnd, iMessage, wParam, lParam);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR* Mes = TEXT("����Ʈ�� Enter Ű �Է��� �����մϴ�. Tab Ű �� �����մϴ�");

	switch (iMessage)
	{
	case WM_CREATE:
		hEdit1 = CreateWindow(TEXT("edit"), NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 10, 200, 25,
			hWnd, (HMENU)ID_EDIT1, g_hInst, NULL);
		hEdit2 = CreateWindow(TEXT("edit"), NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 50, 200, 25,
			hWnd, (HMENU)ID_EDIT2, g_hInst, NULL);
		SetFocus(hEdit1);

		OldEditProc1 = (WNDPROC)SetWindowLongPtr(hEdit1, GWLP_WNDPROC, (LONG_PTR)EditSubProc);
		OldEditProc2 = (WNDPROC)SetWindowLongPtr(hEdit2, GWLP_WNDPROC, (LONG_PTR)EditSubProc2);

		return 0;


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc, 10, 100, Mes, lstrlen(Mes));

		EndPaint(hWnd, &ps);

		return 0;

	case WM_DESTROY:
		SetWindowLongPtr(hEdit1, GWLP_WNDPROC, (LONG_PTR)OldEditProc1);
		SetWindowLongPtr(hEdit2, GWLP_WNDPROC, (LONG_PTR)OldEditProc2);
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
LPCTSTR lpszClass = TEXT("Learning_SubEdit_SetWindowLongPtr");

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


#define ID_EDIT1 100
#define ID_EDIT2 101

HWND hEdit1;
WNDPROC OldEditProc1;

HWND hEdit2;
WNDPROC OldEditProc2;


LRESULT CALLBACK EditSubProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			MessageBox(hWnd, TEXT("Enter is Pressed"), TEXT("Edit"), MB_OK);
			SetFocus(hWnd);
			break;
			
		case VK_TAB:
			SetFocus(hEdit2);
			break;
		}
	}

	return CallWindowProc(OldEditProc1, hWnd, iMessage, wParam, lParam);
}

LRESULT CALLBACK EditSubProc2(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_TAB:
			SetFocus(hEdit1);
			break;
		}	
	}
	return CallWindowProc(OldEditProc2, hWnd, iMessage, wParam, lParam);
}




LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR* Mes = TEXT("����Ʈ�� Enter Ű �Է��� �����մϴ�. Tab Ű �� �����մϴ�");


	switch (iMessage)
	{
	case WM_CREATE:
		hEdit1 = CreateWindow(TEXT("edit"), NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 10, 200, 25,
			hWnd, (HMENU)ID_EDIT1, g_hInst, NULL);
		hEdit2 = CreateWindow(TEXT("edit"), NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 50, 200, 25,
			hWnd, (HMENU)ID_EDIT2, g_hInst, NULL);
		SetFocus(hEdit1);

		OldEditProc1 = (WNDPROC)SetWindowLongPtr(hEdit1, GWLP_WNDPROC, (LONG_PTR)EditSubProc);
		OldEditProc2 = (WNDPROC)SetWindowLongPtr(hEdit2, GWLP_WNDPROC, (LONG_PTR)EditSubProc2);

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc, 10, 100, Mes, lstrlen(Mes));

		EndPaint(hWnd, &ps);

		return 0;

	case WM_DESTROY:
		SetWindowLongPtr(hEdit1, GWLP_WNDPROC, (LONG_PTR)OldEditProc1);
		SetWindowLongPtr(hEdit2, GWLP_WNDPROC, (LONG_PTR)OldEditProc2);
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // �ڵ常


#endif // Total