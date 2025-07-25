#if 0 // Total
/*----------------------------------------------------------------------------------------------------

----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_CreateStruct");


struct tag_Param
{
	int x;
	int y;
	TCHAR Mes[128];
};

tag_Param Param = { 100, 100, TEXT("Create Parameter") };


/*	�� CREATESTRUCT �� LPVOID
    
	�� LP 
	 - ������ API�� Ÿ�Կ��� LP.. �� �տ� ���� Ÿ���� ������, �̴� ������ �� �ǹ�
	   -> LPCREATESTRUCT �� CREATESTRUCT �� ������ Ÿ��
	 - LPVOID �� LP VOID �� �ǹ̰� �ߺ��ź��̴µ�, ���״�� ������ API�� ����� �� ���� ����ϴ�, void* �� 
	   ������ ���� ������ Ÿ��

	�� CREATESTRUCT
	 - WM_CREATE �� ��, LPARAM �� CREATESTRUCT ����ü�� ������ ���� LP �� ���޵�
	 - WM_CREATE ���� �̸� ����� ��, CREATESTRUCT (instance) = *(LPCREATESTRUCT)lParam; �������� ���
	 - CreateWindow �� �������׿�, (LPVOID) (Any Address) �� �Ҵ��ϸ�, CREATESTRUCT�� �ʵ���
	   lpCreateParams �� �Ҵ��. -> WM_CREATE ���� CREATESTRUCT ���� �̾� ��� ����

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

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, (LPVOID)&Param);
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
	CREATESTRUCT cs;
	static tag_Param WndParam;


	switch (iMessage)
	{
	case WM_CREATE:
		cs = *(LPCREATESTRUCT)lParam;
		WndParam = *((tag_Param*)(cs.lpCreateParams));

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, WndParam.x, WndParam.y, WndParam.Mes, lstrlen(WndParam.Mes));
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
LPCTSTR lpszClass = TEXT("Learning_CreateStruct");


struct tag_Param
{
	int x;
	int y;
	TCHAR Mes[128];
};

tag_Param Param = { 100, 100, TEXT("Create Parameter") };

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
		NULL, (HMENU)NULL, hInstance, (LPVOID)&Param);
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
	CREATESTRUCT cs;
	static tag_Param WndParam;

	switch (iMessage)
	{
	case WM_CREATE:
		cs = *(LPCREATESTRUCT)lParam;
		WndParam = *((tag_Param*)(cs.lpCreateParams));

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, WndParam.x, WndParam.y, WndParam.Mes, lstrlen(WndParam.Mes));
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