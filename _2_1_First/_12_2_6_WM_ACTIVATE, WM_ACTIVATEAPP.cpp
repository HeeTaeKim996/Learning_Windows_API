#if 1 // Total
/*----------------------------------------------------------------------------------------------------
	WM_ACTIVAGTE, WM_ACTIVATEAPP �� ���� �ڵ��Դϴ�.
	���������� �����찡 Ȱ��ȭ/��Ȱ��ȭ�� �� �ߵ��˴ϴ�.

	���� ������ WM_SETFOCUS (17��, 28�� ����) �͵� �����غ��̴µ�,
	WM_ACTIVATE �� �����찡 Ȱ��ȭ/��Ȱ��ȭ�� �� �ߵ�,
	WM_SETFOCUS �� Ű���� �Է� ���� �� ��(��)�� �� �� �ߵ�
	�� ���̰� �ֽ��ϴ�.
	�� ��� ���������� �θ� �����쿡�� �켱������ �ߵ��մϴ�.
----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK PopupProc(HWND, UINT, WPARAM, LPARAM);

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

	WndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	WndClass.lpfnWndProc = PopupProc;
	WndClass.lpszClassName = TEXT("PopupClass");
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
	static TCHAR Mes[128];
	static HWND hPopup;

	switch (iMessage)
	{
	case WM_CREATE:
		hPopup = CreateWindow(TEXT("PopupClass"), TEXT("�˾�_������"), 
			WS_POPUPWINDOW | WS_CAPTION | WS_VISIBLE,
			410, 100, 300, 300,
			hWnd, (HMENU)0, g_hInst, NULL);
		return 0;

	case WM_ACTIVATEAPP: 
		// �� ���ø�ĳ�̼�(���ߺθ� ������ �Ǵ� �ڽ� �� �ϳ����̶�..) �� Ȱ��ȭ/��Ȱ��ȭ �� �� �ߵ�
		if (wParam == TRUE)
		{
			ShowWindow(hPopup, SW_SHOWNOACTIVATE);
			// �� SW_SHOWNOACTIVATE : â�� ��������(�ּ�ȭ�ȵ�����), INACTIVATE ���·� ó��
		}
		else
		{
			ShowWindow(hPopup, SW_HIDE);
		}
		return 0;

	case WM_ACTIVATE: // �� �ش� �����찡 Ȱ��ȭ/��Ȱ��ȭ �� �� �ߵ�
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			lstrcpy(Mes, TEXT("��Ȱ��ȭ �����Դϴ�"));
		}
		else
		{
			lstrcpy(Mes, TEXT("���� ���� Ȱ��ȭ�Ǿ��ֽ��ϴ�"));
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 10, Mes, lstrlen(Mes));
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}


LRESULT CALLBACK PopupProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static TCHAR Mes[128];

	switch (iMessage)
	{
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			lstrcpy(Mes, TEXT("��Ȱ��ȭ �����Դϴ�"));
		}
		else
		{
			lstrcpy(Mes, TEXT("���� ���� Ȱ��ȭ�Ǿ��ֽ��ϴ�"));
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 10, 10, Mes, lstrlen(Mes));
		EndPaint(hWnd, &ps);

		return 0;

	case WM_CLOSE:
		ShowWindow(hWnd, SW_HIDE);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}




#endif // �ּ�



#endif // Total