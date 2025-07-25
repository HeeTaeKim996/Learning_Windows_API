#if 0 // Total
/*----------------------------------------------
    WM_CHAR�� ���� ���ڿ��� �Է¹ް�,
	�Էµ� ���ڿ����� ȭ�鿡 ����ϴ� �ڵ��Դϴ�.
----------------------------------------------*/
#if 0 // �ּ�
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Key");

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
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		/* �� TranslateMessage
		    - TranslateMesage�� ����� �����ϴ�. WN_KEYDOWN�� ������, �ش� �Է°��� �������� Ȯ���Ѵ�.
			  ���ڶ��, wParam���� �Էµ� ���ڸ� ���ڷ� �־� WM_CHAR �� �޼��� ť�� �ִ´�.
			- �׿ܿ��� ����� ����. ���� ���α׷��� ���ڿ��� �Է��ϴ� ��ɾ��� left, up, right, down Arrow ����
			  �̵� ��ɸ� �����ϴ� ���α׷��̶��, TranslateMessage �Լ��� �����ص� �ȴ�.
			- ���� ���, A�� �����ٰ� ���� ��, WM_KEYDOWN���� A�� ���ȴ��� Ȯ����, WM_CHAR�� �޼��� ť�� �ִ´�. 
			  WM_KEYUP�� ȣ��ɽ�, WM_CHAR�� �޼��� ť�� �ִ� ���� ����
		*/

		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static TCHAR str[256];
	int len;

	switch (iMessage)
	{
	case WM_CHAR:
		len = lstrlen(str);
		str[len] = (TCHAR)wParam;
		str[len + 1] = 0; // = 0 ���� �ϸ�, = '\0'; �� ����
		InvalidateRect(hWnd, NULL, FALSE);
		/* �� InvalidateRect 
		    - �����츦 ��ȿȭ�ؼ�, WM_PAINT�� ȣ��ǵ��� ��
			- (2) : ��ȿȭ�� ���� ����. NULL�Ͻ� ������ ��ȿȭ (��� �ٽ� �׸�). 
			- (3) : ��ȿȭ�ϱ� ����, ����� ��� ����� �ٽ� �׸��ٸ� FALSE, ���� ����� ������ �ʰ�, �׸��ٸ� TRUE
			 �� Ÿ���ο��� ����� ��ɵ� �ִ´ٸ�, (3)���� TRUE�� �ؾ���

			==>> Unity�� Input.GetAxis�� WM_CHAR�� �ƴ� �ٸ� ������� �Է��� �����ϳ�����
		*/
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 20, 20, str, lstrlen(str));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
#endif // �ּ�


#if 1 // �ڵ常
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Key");

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
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
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
	static TCHAR str[256];
	int len;

	switch (iMessage)
	{
	case WM_CHAR:
		len = lstrlen(str);
		str[len] = wParam;
		str[len + 1] = 0;
		InvalidateRect(hWnd, NULL, FALSE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 20, 20, str, lstrlen(str));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // �ڵ常


#endif // Total

