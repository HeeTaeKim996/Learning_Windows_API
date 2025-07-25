#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	G(S)etWindowLongPtr�� ���� �����Դϴ�.

	���� _11_5, _12_3_2 ���� �����µ�, G(S)etWindowLongPtr�� ������ �� Ư�� �Ӽ����� ����/���� ������ ���Ǹ�,
	WndClass.cbWndExtra > 0 �� ��, ���� ������ thread_local ó�� ����� ������ ���Ǵ� �Լ��Դϴ�.
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
	const TCHAR* Mes = TEXT("���콺 �¿� ��ư���� �ִ�ȭ ��ư ���");
	
	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
	{
		{
			LONG style = GetWindowLongPtr(hWnd, GWL_STYLE);
			style |= WS_MAXIMIZEBOX;
			SetWindowLongPtr(hWnd, GWL_STYLE, style);
			SendMessage(hWnd, WM_NCPAINT, 0, 0); // �� WM_NCPAINT : �������� ��Ŭ���̾�Ʈ ������ �ٽ� �׸���� ��û
			
		}

		
		return 0;

	case WM_RBUTTONDOWN:
	{
		{
			LONG style = GetWindowLongPtr(hWnd, GWL_STYLE);
			style &= ~WS_MAXIMIZEBOX;
			SetWindowLongPtr(hWnd, GWL_STYLE, style);
			SendMessage(hWnd, WM_NCPAINT, 0, 0);
		}


		return 0;
	}


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 10, 10, Mes, lstrlen(Mes));
		EndPaint(hWnd, &ps);
		
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // �ּ�



#endif // Total