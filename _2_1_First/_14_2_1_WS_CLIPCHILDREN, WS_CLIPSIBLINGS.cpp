#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	�� Ŭ���� ����
	WM_PAINT �� ������, InvalidateRect �� ��ȿȭ�� ������ �ƴ϶�,
	��ȿȭ ���� & ���� ����(����� ���� �����찡 ���̴� ����. �ٸ� �����쿡 ��������, ���ÿ����� �ƴ�)
	�Դϴ�. ��ȿ���� & ���ÿ��� �� Ŭ���� ���� �̶� �մϴ�

	�� WS_CLIPCHILDREN
	 - CreateWindow ���� ����. WS_CLIPCHILDREN ��, �ڽ���������� Ŭ���ο������� �����Ͽ�, WM_PAINT ��
	   �ڽ� ���� �κ��� WM_PAINT ���� ������
	   ( �Ʒ� �ڵ�� �̿� ���õ� �ڵ� )
	
	�� WS_CLIPSIBLINGS
	 - WS_CLIPCHILDREN ��ŭ �������� ������, �ִٴ� �͸� �˾Ƶθ� ��. �̸� �״�� ���� �����츦
	   Ŭ���� �������� ����
----------------------------------------------------------------------------------------------------*/


#if 1 // �ּ�
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Sample_2");
HWND hWndMain;

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

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, // �� WS_CLIPCHILDREN
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
	HPEN hPen, OldPen;
	HBRUSH OldBrush;

	switch (iMessage)
	{
	case WM_CREATE:
		CreateWindow(TEXT("button"), TEXT("ChildButton"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			50, 50, 200, 100,
			hWnd, (HMENU)0, g_hInst, NULL);
		CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,
			50, 200, 200, 100,
			hWnd, (HMENU)1, g_hInst, NULL);
		CreateWindow(TEXT("edit"), TEXT("����Ʈ ��Ʈ���Դϴ�"), WS_CHILD | WS_VISIBLE | WS_BORDER,
			300, 120, 200, 80,
			hWnd, (HMENU)2, g_hInst, NULL);
		
		hWndMain = hWnd;
		
		return 0;

	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);
		OldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
		
		hPen = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
		OldPen = (HPEN)SelectObject(hdc, hPen);

		Ellipse(hdc, LOWORD(lParam) - 50, HIWORD(lParam) - 40, LOWORD(lParam) + 50, HIWORD(lParam) + 40);

		DeleteObject(SelectObject(hdc, OldPen));
		SelectObject(hdc, OldPen);

		SelectObject(hdc, OldBrush);

		ReleaseDC(hWnd, hdc);

		return 0;


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);

		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // �ּ�



#endif // Total