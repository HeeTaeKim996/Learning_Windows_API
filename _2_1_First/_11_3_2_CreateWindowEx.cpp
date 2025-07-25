#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	CreateWindowEx �� ���� �ڵ��Դϴ�. ������ ���� �����ϴ�. 
----------------------------------------------------------------------------------------------------*/


#if 1 // �ּ�
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Sample_2");

HWND hWndMain;


/* �� CreateWindowEx 
    - CreateWindow �� �ٸ� ���� �� �ϳ��ε�, (1) �׿� ��Ÿ�� �÷��� �߰�
	- (1) �׿� �Է��� �÷��״� ��� WS_EX �� ����
	   - WS_EX_DLGMODALFRAME
	   - WS_EX_TOPMOST ... ��
	- �׿ܿ��� ��� ����


*/


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

	hWnd = CreateWindowEx(WS_EX_WINDOWEDGE, lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
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
	switch (iMessage)
	{
	case WM_CREATE:
		hWndMain = hWnd;

		CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE,
			10, 10, 90, 90,
			hWnd, (HMENU)0, g_hInst, NULL);
		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE,
			110, 10, 90, 90,
			hWnd, (HMENU)1, g_hInst, NULL);
		CreateWindowEx(WS_EX_STATICEDGE, TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE,
			210, 10, 90, 90,
			hWnd, (HMENU)2, g_hInst, NULL);
		CreateWindowEx(WS_EX_STATICEDGE, TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE,
			310, 10, 90, 90, hWnd, (HMENU)3, g_hInst, NULL);

		CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 110, 90, 90,
			hWnd, (HMENU)4, g_hInst, NULL);
		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
			110, 110, 90, 90,
			hWnd, (HMENU)5, g_hInst, NULL);
		CreateWindowEx(WS_EX_STATICEDGE, TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
			210, 110, 90, 90,
			hWnd, (HMENU)6, g_hInst, NULL);
		CreateWindowEx(WS_EX_WINDOWEDGE, TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
			310, 110, 90, 90,
			hWnd, (HMENU)7, g_hInst, NULL);

		return 0;

		
	case WM_DESTROY:
		PostQuitMessage(0);
		
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // �ּ�



#endif // Total