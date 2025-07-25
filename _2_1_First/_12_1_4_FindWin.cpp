#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	FindWin, FindWinEx�� ���� �ڵ��Դϴ�.

	�� FindWin	: �ֻ��� �θ� HWND �� �˻�. (1) �� WndClass.lpszClassName �� �������� �˻�
				  (2) �� CreateWindow�� (2)���� ĸ�� (������ �ؽ�Ʈ) �� �������� �˻�

	�� FindWinEx	: ������ HWND (1) �� �ڽĵ� �� �˻�. HWND (2)�� ������, �� HWND ���� �������� Z���� 
	              �������� �˻���. �׿ܿ��� FindWin �� ����
----------------------------------------------------------------------------------------------------*/


#if 1 // �ּ�
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_FindWin");

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
	HWND hFirst;
	static HWND h1, h2, h3;
	

	switch (iMessage)
	{
	case WM_CREATE:
		h1 = CreateWindow(TEXT("button"), TEXT("��ư"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20, 20, 100, 25,
			hWnd, (HMENU)0, g_hInst, NULL);
		h2 = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
			20, 50, 100, 50,
			hWnd, (HMENU)1, g_hInst, NULL);
		h3 = CreateWindow(TEXT("edit"), TEXT("����Ʈ"), WS_CHILD | WS_VISIBLE | WS_BORDER,
			20, 110, 100, 25,
			hWnd, (HMENU)2, g_hInst, NULL);
		return 0;


	case WM_LBUTTONDOWN:
		hFirst = FindWindow(NULL, TEXT("Learning_FindWin"));
		if (hFirst == NULL)
		{
			MessageBox(hWnd, TEXT("������ ã�� �� �����ϴ�."), TEXT("�˸�"), MB_OK);
		}
		else
		{
			MessageBox(hWnd, TEXT("������ �������Դϴ�."), TEXT("�˸�"), MB_OK);
		}
		return 0;


	case WM_RBUTTONDOWN:
		hFirst = FindWindowEx(hWnd, NULL, TEXT("edit"), NULL);
		if (hFirst == NULL)
		{
			MessageBox(hWnd, TEXT("���ϵ� ��Ʈ���� �����ϴ�."), TEXT("�˸�"), MB_OK);
		}
		else
		{
			MessageBox(hWnd, TEXT("���ϵ� ��Ʈ���� ã�ҽ��ϴ�"), TEXT("�˸�"), MB_OK);
		}
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // �ּ�



#endif // Total