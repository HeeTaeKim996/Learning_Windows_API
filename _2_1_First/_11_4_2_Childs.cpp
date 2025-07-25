#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	자식 (list, edit, button 등의 자식을 두고 있는) 이 셋 있는 HWND 입니다
----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildLeftProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildTopProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildBottomProc(HWND, UINT, WPARAM, LPARAM);



HINSTANCE g_hInst;
HWND hWndMain, hc1, hc2, hc3;
LPCTSTR lpszClass = TEXT("Learning_Childs");


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	
	static HBRUSH hRedBrush, hGreenBrush, hBlueBrush;

	hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
	hGreenBrush = CreateSolidBrush(RGB(0, 255, 0));
	hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));

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


	WndClass.hbrBackground = hRedBrush;
	WndClass.lpfnWndProc = ChildLeftProc;
	WndClass.lpszClassName = TEXT("ChildLeft");
	RegisterClass(&WndClass);

	WndClass.hbrBackground = hGreenBrush;
	WndClass.lpfnWndProc = ChildTopProc;
	WndClass.lpszClassName = TEXT("ChildTop");
	RegisterClass(&WndClass);

	WndClass.hbrBackground = hBlueBrush;
	WndClass.lpfnWndProc = ChildBottomProc;
	WndClass.lpszClassName = TEXT("ChildBottom");
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


	DeleteObject(hRedBrush);
	DeleteObject(hGreenBrush);
	DeleteObject(hBlueBrush);


	return (int)Message.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	
	switch (iMessage)
	{
	case WM_CREATE:
		hc1 = CreateWindow(TEXT("ChildLeft"), NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
			0, 0, 0, 0,
			hWnd, (HMENU)0, g_hInst, NULL);
		/* WS_CLIPCHILDREN
		   - 부모 영역의 WM_PAINT에서, 해당 자식의 영역은 그리지 않도록 처리. (오버라이드 방지)
		*/

		hc2 = CreateWindow(TEXT("ChildTop"), NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
			0, 0, 0, 0,
			hWnd, (HMENU)0, g_hInst, NULL);
		hc3 = CreateWindow(TEXT("ChildBottom"), NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
			0, 0, 0, 0,
			hWnd, (HMENU)0, g_hInst, NULL);

		return 0;

	case WM_SIZE:
		if (wParam != SIZE_MINIMIZED)
		{
			RECT crt;
			GetClientRect(hWnd, &crt);
			MoveWindow(hc1, 0, 0, 300, crt.bottom, TRUE);
			MoveWindow(hc2, 300, 0, crt.right - 300, 150, TRUE);
			MoveWindow(hc3, 300, 150, crt.right - 300, crt.bottom - 150, TRUE);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK ChildLeftProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static HWND hList, hEdit, hBtn;

	TCHAR str[256];

	switch (iMessage)
	{
	case WM_CREATE:
		hList = CreateWindow(TEXT("listbox"), NULL, 
			WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT,
			0, 0, 0, 0,
			hWnd, (HMENU)0, g_hInst, NULL);
		hEdit = CreateWindow(TEXT("edit"), NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			210, 10, 85, 25,
			hWnd, (HMENU)1, g_hInst, NULL);

		hBtn = CreateWindow(TEXT("button"), TEXT("add"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			210, 50, 80, 25,
			hWnd, (HMENU)2, g_hInst, NULL);
		
		return 0;

	case WM_SIZE:
		MoveWindow(hList, 10, 10, 190, HIWORD(lParam) - 20, TRUE);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 2:
			GetWindowText(hEdit, str, 256);
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)str);
		}
			
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK ChildTopProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR* Mes = TEXT("이 윈도우는 차일드를 가지고 있지 않습니다");

	switch (iMessage)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 10, 50, Mes, lstrlen(Mes));
		EndPaint(hWnd, &ps);

		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK ChildBottomProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit;

	switch (iMessage)
	{
	case WM_CREATE:
		hEdit = CreateWindow(TEXT("edit"), NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | WS_VSCROLL,
			0, 0, 0, 0,
			hWnd, (HMENU)0, g_hInst, NULL);
		SetWindowText(hEdit, TEXT("에디트 윈도우입니다"));
		
		return 0;

	case WM_SIZE:
		MoveWindow(hEdit, 50, 50, LOWORD(lParam) - 100, HIWORD(lParam) - 100, TRUE);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));

}




#endif // 주석


#if 1// 코드만
#include <Windows.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildLeftProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildTopProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildBottomProc(HWND, UINT, WPARAM, LPARAM);




HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_Childs");
HWND hWndMain, hc1, hc2, hc3;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	static HBRUSH hRedBrush, hGreenBrush, hBlueBrush;
	hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
	hGreenBrush = CreateSolidBrush(RGB(0, 255, 0));
	hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
	

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


	WndClass.hbrBackground = hRedBrush;
	WndClass.lpfnWndProc = ChildLeftProc;
	WndClass.lpszClassName = TEXT("ChildLeft");
	RegisterClass(&WndClass);

	WndClass.hbrBackground = hGreenBrush;
	WndClass.lpfnWndProc = ChildTopProc;
	WndClass.lpszClassName = TEXT("ChildTop");
	RegisterClass(&WndClass);

	WndClass.hbrBackground = hBlueBrush;
	WndClass.lpfnWndProc = ChildBottomProc;
	WndClass.lpszClassName = TEXT("ChildBottom");
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

	DeleteObject(hRedBrush);
	DeleteObject(hGreenBrush);
	DeleteObject(hBlueBrush);

	return (int)Message.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		hc1 = CreateWindow(TEXT("ChildLeft"), NULL,
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
			0, 0, 0, 0,
			hWnd, (HMENU)0, g_hInst, NULL);
		hc2 = CreateWindow(TEXT("ChildTop"), NULL,
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
			0, 0, 0, 0,
			hWnd, (HMENU)0, g_hInst, NULL);
		hc3 = CreateWindow(TEXT("ChildBottom"), NULL,
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
			0, 0, 0, 0,
			hWnd, (HMENU)0, g_hInst, NULL);

		return 0;

	case WM_SIZE:
		if (wParam != SIZE_MINIMIZED)
		{
			RECT crt;
			GetClientRect(hWnd, &crt);
			MoveWindow(hc1, 0, 0, 300, crt.bottom, TRUE);
			MoveWindow(hc2, 300, 0, crt.right - 300, 150, TRUE);
			MoveWindow(hc3, 300, 150, crt.right - 300, crt.bottom - 150, TRUE);
		}
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}


LRESULT CALLBACK ChildLeftProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static HWND hList, hEdit, hBtn;

	TCHAR str[256];

	switch (iMessage)
	{
	case WM_CREATE:
		hList = CreateWindow(TEXT("listbox"), NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT,
			0, 0, 0, 0,
			hWnd, (HMENU)0, g_hInst, NULL);
		hEdit = CreateWindow(TEXT("edit"), NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			210, 10, 85, 25,
			hWnd, (HMENU)1, g_hInst, NULL);

		hBtn = CreateWindow(TEXT("button"), TEXT("add"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			210, 50, 80, 25,
			hWnd, (HMENU)2, g_hInst, NULL);

		return 0;

	case WM_SIZE:
		MoveWindow(hList, 10, 10, 190, HIWORD(lParam) - 20, TRUE);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 2:
			GetWindowText(hEdit, str, 256);
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)str);
		}

		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK ChildTopProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR* Mes = TEXT("이 윈도우는 차일드르 가지고 있지 않습니다");

	switch (iMessage)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 10, 50, Mes, lstrlen(Mes));
		EndPaint(hWnd, &ps);

		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK ChildBottomProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit;

	switch (iMessage)
	{
	case WM_CREATE:
		hEdit = CreateWindow(TEXT("edit"), NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | WS_VSCROLL,
			0, 0, 0, 0,
			hWnd, (HMENU)0, g_hInst, NULL);
		SetWindowText(hEdit, TEXT("에디트 윈도우입니다"));

		return 0;

	case WM_SIZE:
		MoveWindow(hEdit, 50, 50, LOWORD(lParam) - 100, HIWORD(lParam) - 100, TRUE);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // 코드만


#endif // Total