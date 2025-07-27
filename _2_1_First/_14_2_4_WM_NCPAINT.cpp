#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	WM_NCPAINT �� ���� �ڵ��Դϴ�.
	�ռ� �忡�� �����ߵ�, BeginPaint�� 5�۾���, ������ �۾��� WM_NCPAINT �� ȣ��˴ϴ�.
	WM_NCPAINT�� ���۾�����(Ÿ��Ʋ��, �׵θ� ��) �� �׸��ϴ�.
	
	�Ʒ� �ڵ�� ���۾������� �������� �׸��� �ڵ��ε�, ���翡���� �׵θ��� �β��� ���������� ĥ���� �ݸ�,
	�����غ��� ���� ���� ������ �׵θ��� ĥ�����ϴ�.
	(������ ��)

	WM_NCPAINT�� ������ ����� ���ɼ��� ����, ������ �˾� ������ ��� + �����̳ʰ� �׸� �̹��� ���
	���� ��κ� ó���մϴ�. 


	����������, ' BeginPaint�� ������ �۾� ��  WM_NCPAINT�� ȣ��Ǿ�, ���۾������� �׸��� '
	��� �͸� �����ϸ� �˴ϴ�.
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
	RECT wrt;
	HPEN hPen, OldPen;


	switch (iMessage)
	{
	case WM_NCPAINT:
		DefWindowProc(hWnd, iMessage, wParam, lParam);
		hdc = GetWindowDC(hWnd);


		GetWindowRect(hWnd, &wrt);
		hPen = CreatePen(PS_INSIDEFRAME, 1500, RGB(255, 0, 0));
		OldPen = (HPEN)SelectObject(hdc, hPen);
		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		Rectangle(hdc, 0, 0, wrt.right - wrt.left, wrt.bottom - wrt.top);
		DeleteObject(SelectObject(hdc, OldPen));
		
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