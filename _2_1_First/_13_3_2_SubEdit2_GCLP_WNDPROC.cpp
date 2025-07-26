#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	�ռ� ���� ���꿡���� ���������, GWLP �� �ƴ� GCLP_WNDPROC �Դϴ�.
	GCLP �� �ϸ�, �ش� WND �� ��ü�Ǵ� �� �ƴ϶�, �ش� WND�� ������ Ŭ���� �� WND�� ������ �Լ��� ��ü�˴ϴ�.
	( !! �ش� WND �� WNDPROC�� ��ü���� �ʽ��ϴ�. ��.��.��. ������� ������ Ŭ������ WND �� WNDPROC�� 
	  �ڵ����� ��ü�˴ϴ� )

	�� ����鼭 �� ���� ���� �ܿ� ������ �𸣰���. OldProc�� ������ WND�� WNDPROC���ٵ�, ��ü�ϴ� �Լ��� 
	  ���ϰ��� OldProc��. �׷��ٸ� hEdit2�� Ÿ���� ������ hEdit1 ���� �����ϴ� �� �ƴѰ� ��� �����ߴµ�
	  �������� hEdit2�� �� ������. Ÿ���� �ϴ� ������, WNDPROC ���� ó���ϴ� �� �ƴѰǰ� ����
	
----------------------------------------------------------------------------------------------------*/


#if 1 // �ּ�
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_GCLP_WNDPROC");

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
#define ID_EDIT3 102

HWND hEdit1, hEdit2, hEdit3;
WNDPROC OldEditProc;

LRESULT CALLBACK EditSubProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			MessageBox(hWnd, TEXT("���꿡�� Ŭ����"), TEXT("�˸�"), MB_OK);
			break;
		}
	}

	return CallWindowProc(OldEditProc, hWnd, iMessage, wParam, lParam);
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	

	switch (iMessage)
	{
	case WM_CREATE:
		hEdit1 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 10, 200, 25,
			hWnd, (HMENU)ID_EDIT1, g_hInst, NULL);

		OldEditProc = (WNDPROC)SetClassLongPtr(hEdit1, GCLP_WNDPROC, (LONG_PTR)EditSubProc);

		hEdit2 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 50, 200, 25,
			hWnd, (HMENU)ID_EDIT2, g_hInst, NULL);
		
		hEdit3 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 90, 200, 25,
			hWnd, (HMENU)ID_EDIT3, g_hInst, NULL);

		SetFocus(hEdit1);

		return 0;

	case WM_DESTROY:
		SetClassLongPtr(hEdit1, GCLP_WNDPROC, (LONG_PTR)OldEditProc);
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // �ּ�


#endif // Total