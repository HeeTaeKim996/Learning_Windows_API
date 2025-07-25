#if 0 // Total
/*--------------------------------------------------------------------------
      CHAR가 아닌 특수문자 (LEFT,RIGHT,UP,DOWN ) ARROW 등.. 을 사용할 때
	  필요한 WM_KEYDOWN 에 대한 코드입니다
--------------------------------------------------------------------------*/
#if 1 // 주석
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("WM_KEYDOWN");

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
	static int x = 100;
	static int y = 100;

	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			x -= 8;
			break;
		case VK_UP:
			y -= 8;
			break;
		case VK_RIGHT:
			x += 8;
			break;
		case VK_DOWN:
			y += 8;
			break;
		}
		/*
			  ※ 우측을 누른 상태에서, 위키를 눌러도 우측 계속 이동. 위키를 누른 상태에서 우측을 눌러도 위쪽 계속 이동
				 코드를 보면 VK_UP: ... break; 가 있기 때문에, 우측 누른 상태에서 위쪽 누르면, 위쪽으로 이동하지 않을까
				 하는데, 그렇지 않다.
				- 이유는 WM_KEYDOWN은 하나의 키만 인식. 그리고 눌렀던 키가 계속 눌려있으면, 그 키만 인식되도록함
		*/



		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		Ellipse(hdc, x - 3, y - 3, x + 3, y + 3);

		EndPaint(hWnd, &ps);
		break;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}



#endif // 주석


#if 1// 코드만



#endif // 코드만


#endif // Total