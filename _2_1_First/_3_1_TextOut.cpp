#if 0 // Total

/*--------------------------------------------
    ���콺 ��Ŭ����, ������ �ؽ�Ʈ�� ����ϴ�
	�ڵ��Դϴ�.
--------------------------------------------*/

# if 0 // �ּ�
/*--------------
      �ּ�
--------------*/

#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("TextOut");

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

	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN: // ���콺 ��Ŭ����
		hdc = GetDC(hWnd);
		TextOut(hdc, 100, 100, TEXT("Cute Harry"), 10); // (5) : ���ڿ� ����. �ַ� lstrlen ���
		ReleaseDC(hWnd, hdc);
		return 0;
		// �� 1) GetDC -> ReleaseDC : ������ ��� (DC�Ҵ�� �޸� ����)

	case WM_PAINT: // 1) ������ ó�� ���� ��, 2) ������ �Ϻΰ� ��ȿȭ�� ��(�ٸ� �����쿡 �������ų�, ������ ũ�⸦ ������ ��)
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 100, 100, TEXT("Cute Bori"), 9);
		EndPaint(hWnd, &ps);
		return 0;
	/* �� WM_PAINT
	    - ������, ������, IOS ��� ��Ƽ�½�ŷ �ü����, �ٸ� ���α׷� �����, ���� ���α׷��� DC ������� ����� �� �ִ�.
		- ����, �׻� WM_PAINT�� �̺κ��� �ڵ�� �����ؾ� �Ѵ�. ���翡�� �ٸ� ����� ���� ��.. ����� ��� ó�� �ʿ�
	
	  �� BeginPaint -> EndPaint
	    - �� ����, WM_PAINT ȣ��ÿ��� ����� �� �ִ�. �׿ܿ� �޼��������� ����� �� ����

	   ==>> �Ϲ����� ��Ȳ������ GetDC -> ReleaseDC ���. WM_PAINT ������ BeginPaint -> EndPaint ���
	*/

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // �ּ�

#if 1 // �ڵ常
/*----------------------
         �ڵ常
----------------------*/
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("TextOut");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstnace, LPSTR lpszCmdParam, int nCmdShow)
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

	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);
		TextOut(hdc, 100, 100, TEXT("Cute Harry"), 10);
		ReleaseDC(hWnd, hdc);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 100, 100, TEXT("Cute Bori"), 9);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}



#endif // �ڵ常

#endif // Total