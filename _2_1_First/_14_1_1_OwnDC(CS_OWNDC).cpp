#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	�����찡 �ϳ��� DC �� ���� �� �Ҵ��ϰ�, WM_DESTROY �� �ı��ϴ� ����Դϴ�.
	WndClass.style ���� CS_OWNDC �� �߰��ؾ� �մϴ�.

	�׸� ĥ�� ������ GetDC �� ���� �ʾƵ� �ǹǷ� ������ ������, 
	ȭ���� �׸��� ��ü������ ���� �ٲ�� ��� ����� ��뵵 ũ�� ������ ������ �����ϴ�.

	���뿡�� Ŀ�� DC (�Ʒ�����), �����̺� DC (�������� �ߴ� ���) �� ����� ��κ� ���˴ϴ�.
----------------------------------------------------------------------------------------------------*/


#if 1 // �ּ�
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Sample_2");
HDC hdc;

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
	WndClass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC; // �� CS_OWNDC
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
	PAINTSTRUCT ps;
	static HPEN hPen, OldPen;

	switch (iMessage)
	{
	case WM_CREATE:
		hdc = GetDC(hWnd); // ����
		hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
		OldPen = (HPEN)SelectObject(hdc, hPen);
		return 0;


	case WM_PAINT:
		BeginPaint(hWnd, &ps);
		Rectangle(hdc, 10, 10, 200, 200);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		DeleteObject(SelectObject(hdc, OldPen)); // ����
		PostQuitMessage(0);
		return 0;


	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // �ּ�


#endif // Total