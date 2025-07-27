#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	WM_ERASEBKGND �� ���� �ڵ��Դϴ�.
	�ռ� _14_2_3 ���� ������, BeginPaint �Լ��� ������ �۾����� WM_ERASEBKGND �� ȣ��Ǿ�,
	Ŭ���� ������ ��� WndClass.hbrBackground �� ��� ĥ�ϴ� �۾��Դϴ�.

	�Ʒ� �ڵ�� WM_ERASEBKGND �� ���� �ڵ��, Ÿ�� ����� ��׶��带 ������ �ڵ��Դϴ�.


	���ȭ���� �׸��� �� �ʿ��� �ڵ��̹Ƿ� �߿��մϴ�.
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
	RECT rt;

	switch (iMessage)
	{
	case WM_ERASEBKGND:
		hdc = (HDC)wParam;
		GetClientRect(hWnd, &rt);
		for (int i = 0; i < rt.right; i += 50)
		{
			for (int j = 0; j < rt.bottom; j += 50)
			{
				Rectangle(hdc, i, j, i + 50, j + 50);
				Ellipse(hdc, i, j, i + 50, j + 50);
			}
		}

		return TRUE;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;


	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // �ּ�



#endif // Total