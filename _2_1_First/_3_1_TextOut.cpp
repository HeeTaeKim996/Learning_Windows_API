#if 0 // Total

/*--------------------------------------------
    마우스 좌클릭시, 지정된 텍스트를 출력하는
	코드입니다.
--------------------------------------------*/

# if 0 // 주석
/*--------------
      주석
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
	case WM_LBUTTONDOWN: // 마우스 좌클릭시
		hdc = GetDC(hWnd);
		TextOut(hdc, 100, 100, TEXT("Cute Harry"), 10); // (5) : 문자열 길이. 주로 lstrlen 사용
		ReleaseDC(hWnd, hdc);
		return 0;
		// ※ 1) GetDC -> ReleaseDC : 쌍으로 사용 (DC할당시 메모리 차지)

	case WM_PAINT: // 1) 윈도우 처음 시작 때, 2) 윈도우 일부가 무효화될 때(다른 윈도우에 가려지거나, 윈도우 크기를 조정할 때)
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 100, 100, TEXT("Cute Bori"), 9);
		EndPaint(hWnd, &ps);
		return 0;
	/* ○ WM_PAINT
	    - 윈도우, 리눅스, IOS 모두 멀티태스킹 운영체제로, 다른 프로그램 시행시, 기존 프로그램의 DC 결과들이 사라질 수 있다.
		- 따라서, 항상 WM_PAINT로 이부분을 코드로 보완해야 한다. 교재에는 다른 방법은 없다 함.. 수기로 모두 처리 필요
	
	  ○ BeginPaint -> EndPaint
	    - 위 쌍은, WM_PAINT 호출시에만 사용할 수 있다. 그외에 메세지에서는 사용할 수 없다

	   ==>> 일반적인 상황에서는 GetDC -> ReleaseDC 사용. WM_PAINT 에서만 BeginPaint -> EndPaint 사용
	*/

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // 주석

#if 1 // 코드만
/*----------------------
         코드만
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



#endif // 코드만

#endif // Total