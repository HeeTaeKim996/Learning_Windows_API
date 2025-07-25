#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	�ռ� �޼��� ������� ������ �߰� �ڵ��Դϴ�.
	�ռ� �忡�� �� ó���Ϸ� �ߴµ�, ���� �ڵ� ������ ���� �� ���� ���� �������ϴ�.

	���� ������ �ξ� �߿��ϴ�, �װ͸� ���� ����� �� �����ϴ�. PostMessage�� ������ �ذ���� ������ �ͽ��ϴ�
----------------------------------------------------------------------------------------------------*/


#if 1 // �ּ�
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LockProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;

LPCTSTR lpszClass = TEXT("Learning_SendMEssgaeCallback");
LPCTSTR lockClass = TEXT("LockClass");

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
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_VREDRAW | CS_HREDRAW;


	int inputNumber = atoi(lpszCmdParam);
	LPCTSTR registerClass;
	int xPos, yPos;
	switch (inputNumber)
	{
	case 1:
		WndClass.lpfnWndProc = WndProc;
		WndClass.lpszClassName = lpszClass;
		registerClass = lpszClass;
		xPos = yPos = 100;

		break;

	case 2:
		WndClass.lpfnWndProc = LockProc;
		WndClass.lpszClassName = lockClass;
		registerClass = lockClass;
		xPos = 600;
		yPos = 100;

		break;

	default:
		MessageBox(NULL, TEXT("CMD ���� ���� 1 �Ǵ� 2�� �Է��Ͽ� �����ϼ���"), TEXT("�˸�"), MB_OK);
		return 0;
	}


	RegisterClass(&WndClass);

	hWnd = CreateWindow(registerClass, registerClass, WS_OVERLAPPEDWINDOW,
		xPos, yPos, 400, 300,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}


VOID CALLBACK SendAsyncProc(HWND, UINT uMessage, ULONG_PTR dwData, LRESULT lParam)
{
	MessageBox(hWndMain, TEXT("�ٸ� �����쿡�� �۾��� �Ϸ��߽��ϴ�"), TEXT("sEND1"), MB_OK);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HWND hSend2;
	TCHAR Mes[128];
	static int time;

	switch (iMessage)
	{
	case WM_CREATE:
		time = 0;
		SetTimer(hWnd, 0, 1'000, NULL);
		return 0;

	case WM_TIMER:
		hdc = GetDC(hWnd);
		
		wsprintf(Mes, TEXT("%d �� �������ϴ�"), ++time);
		TextOut(hdc, 100, 100, Mes, lstrlen(Mes));

		ReleaseDC(hWnd, hdc);

		return 0;

	case WM_LBUTTONDOWN:
		hSend2 = FindWindow(lockClass, NULL);
		if (hSend2)
		{
			SendMessageCallback(hSend2, WM_USER + 1, 0, 0, SendAsyncProc, NULL);
		}
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}



LRESULT CALLBACK LockProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_USER + 1:
		MessageBox(hWnd, TEXT("OK�� ������, �۾��� ���� ó�� �˴ϴ�"), TEXT("�˸�"), MB_OK);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}


#endif // �ּ�




#endif // Total