#if 1 // Total
/*----------------------------------------------------------------------------------------------------
	WM_PAINT �� ���� �����, UpdateWindow �� ���� �����Դϴ�.
	WM_PAINT �� ���� �޼��� ť�� ��ť�ƴ� �ϴ���, ������ �޼������� ��� ó���� �Ŀ� ó���˴ϴ�.

	�����찡 �۾� ó����, WM_PAINT�� �� �ִ� ��Ȳ����, ���ο� WM_PAINT�� ������,
	�� InvalidateRect �� rect ������ ��ģ ��, �������� ó���Ͽ�, ȿ���� ���̱� �����Դϴ�.

	UpdateWindow �� �ﰢ WM_PAINT�� �����ϵ��� �ϴ� �ڵ��Դϴ�.
	��ġ SendMessage(WM_PAINT).. �� �ſ� �����ѵ�, 
	�� �ϳ��� �������� UpdateWindow �� InvalidateRect �� ������ ���� ���, ������ ���� �ʴ´ٶ��
	�������� �ϳ� �ֽ��ϴ�.

	�Ʒ��� �� ������� �����ִ� �ڵ��Դϴ�. ���� ���� ���� �ʿ�� ����, �� ���븸 �����ϸ� �˴ϴ�.
----------------------------------------------------------------------------------------------------*/


#if 1 // �ּ�
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
	static BOOL isEllipse;

	switch (iMessage)
	{
	case WM_CREATE:
		isEllipse = TRUE;
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		if (isEllipse)
		{
			Ellipse(hdc, 10, 10, 100, 100);
		}
		else
		{
			Rectangle(hdc, 10, 10, 100, 100);
		}
		return 0;


	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		isEllipse = !isEllipse;
		
		hdc = GetDC(hWnd);

		InvalidateRect(hWnd, NULL, TRUE);
		if (iMessage == WM_RBUTTONDOWN)
		{
			UpdateWindow(hWnd);
		}
		Sleep(1'000);

		ReleaseDC(hWnd, hdc);
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // �ּ�


#endif // Total