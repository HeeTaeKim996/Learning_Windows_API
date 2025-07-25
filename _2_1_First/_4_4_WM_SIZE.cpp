#if 0 // Total
/*----------------------------------------------------------------------------
		WM_SIZE 에 대한 코드로, 화면의 크기가 조정되거나, 최소화, 최대화 
		등이 되는 상황에 발동되는 메세지입니다.
----------------------------------------------------------------------------*/

#if 0 // 주석
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("_4_4");

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

	static RECT workingRect;
	static TCHAR rectStr[128];

	switch (iMessage)
	{
	case WM_SIZE:
		//GetClientRect(hWnd, &workingRect); // 이 함수를 사용해도 되지만, lParam에서 직접 받아오기 가능

		workingRect.right = LOWORD(lParam);
		workingRect.bottom = HIWORD(lParam);
		wsprintf(rectStr, TEXT("Width : %d,    Height : %d   ///     "), workingRect.right, workingRect.bottom);
		
		TCHAR tempStr[64];
		switch (wParam)
		{
		case SIZE_MAXHIDE:
			lstrcat(rectStr, TEXT("YOU_WONT_SEE_ME"));
			break;
		case SIZE_MAXSHOW:
			lstrcat(rectStr, TEXT("YOU_MAY_SEE_ME"));
		case SIZE_MAXIMIZED:
			lstrcat(rectStr, TEXT("YOU_SEE_ME"));
			break;
		case SIZE_MINIMIZED:
			lstrcat(rectStr, TEXT("YOU_WONT_SEE_ME"));
			break;
		case SIZE_RESTORED:
			lstrcat(rectStr, TEXT("SIZE_REVISED"));
			break;
		}
		/* ○ WM_SIZE에서 wParam
		   - wParam은 사이즈 변동 사유
		   - SIZE_MAXHIDE	: 다른 프로그램이 최대화되어, 현프로그램이 보이지 않게 됨
		   - SIZE_MAXSHOW	: 다르 프로그램의 최대화가 되지 않게 되어, 현프로그램이 보일 수 있게 됨
		   - SIZE_MAXIMIZED : 현 프로그램의 크기가 최대화됨
		   - size_minized	: 현 프로그램의 크기가 최소화됨
		   - SIZE_RESTORED	: 현 프로그램의 크기가 조정됨
		*/

		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetTextAlign(hdc, TA_CENTER);
		TextOut(hdc, workingRect.right / 2, workingRect.bottom / 2, rectStr, lstrlen(rectStr));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // 주석

#if 1 // 코드만
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("WM_SIZE");

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

	static RECT sizeRect;
	static TCHAR sizeStr[64];

	switch (iMessage)
	{
	case WM_SIZE:
		sizeRect.right = LOWORD(lParam);
		sizeRect.bottom = HIWORD(lParam);
		wsprintf(sizeStr, TEXT("WIDTH : %d,   HEIGHT : %d      ///      "), sizeRect.right, sizeRect.bottom);


		switch (wParam)
		{
		case SIZE_MAXHIDE:
			lstrcat(sizeStr, TEXT("SIZE_MAXHIDE"));
			break;
		case SIZE_MAXSHOW:
			lstrcat(sizeStr, TEXT("SIZE_MAXSHOW"));
			break;
		case SIZE_MAXIMIZED:
			lstrcat(sizeStr, TEXT("SIZE_MAXIMIZED"));
			break;
		case SIZE_MINIMIZED:
			lstrcat(sizeStr, TEXT("SIZE_MINIMIZED"));
			break;
		case SIZE_RESTORED:
			lstrcat(sizeStr, TEXT("SIZE_RESTORED"));
			break;
		}


		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetTextAlign(hdc, TA_CENTER);
		TextOut(hdc, sizeRect.right / 2, sizeRect.bottom / 2, sizeStr, lstrlen(sizeStr));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}


#endif // 코드만

#endif // Total