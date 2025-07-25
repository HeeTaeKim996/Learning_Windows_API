#if 0 // Total
/*-------------------------------------------------
     가장 기본적인 그래픽 (점, 선, 사각형, 원)을
	 그려보는 코드입니다.
-------------------------------------------------*/

#if 0 // 주석
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("GraphOut");

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
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		

		SetPixel(hdc, 10, 10, RGB(255, 0, 0, ));
		// ○ SetPixel : (2), (3) 좌표에 (4)로 지정한 컬러의 점을 그림


		MoveToEx(hdc, 50, 50, NULL);
		LineTo(hdc, 300, 90);
		/*
		 ○ LineTo
		  - 기존 CP를 원점으로, (2) - (3) 좌표로 선을 그림
		 ○ MoveToEx
		  - CP 좌표를 (2), (3) 으로 이동함. (4)에는 주로 NULL을 넣는데, 만약 이전 CP좌표를 저장하고 싶다면, 
		    (4)에 입력하면 됨 (입력 방법은 모르겠음.. 웬만함 NULL쓴다 하니)

		==> 연속 된 도형(선의 집합)을 그리고 싶다면, MoveToEx로 원점 잡고, LineTo를 연속으로 사용하는 방법으로 그림
		*/


		Rectangle(hdc, 50, 100, 200, 180);
		// ○ Recntangle : (2)-(3)-(4)-(5) : 좌 - 탑 - 우 - 바텀

		Ellipse(hdc, 220, 100, 400, 200);
		// Ellipse : (2)-(3)-(4)-(5) : 좌 - 탑 - 우 - 바텀 을 접하는 원을 그림 [ (원점, r) 사용하지 않고, 4인자 사용]

		EndPaint(hWnd, &ps);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // 주석

#if 1 // 코드만
#include <CoreWindow.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("GraphOut");

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
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		SetPixel(hdc, 10, 10, RGB(255, 0, 0,));

		MoveToEx(hdc, 50, 50, NULL);
		LineTo(hdc, 100, 100);


		Rectangle(hdc, 50, 100, 200, 180);

		Ellipse(hdc, 220, 180, 400, 200);

		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 코드만


#endif // Total
