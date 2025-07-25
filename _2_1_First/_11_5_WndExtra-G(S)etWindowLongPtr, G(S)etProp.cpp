#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	WndExtra - G(S)etWindowLong, G(S)etProp 에 대한 내용입니다. 간략히 thread_local 의 윈도우 버전이라 보면 됩니다.
	
	G(S)etWindowLong, G(S)etProp 모두 4바이트로 데이터를 저장합니다.
	둘의 차이점으로,
	G(S)etWindowLong 은  저장공간을 메모리위치 로 식별하고, 윈도우를 생성할 때 메모리를 WndClass.cbWndExtra로 동적 할당하고
	사용하여 무의미하게 후자보다 빠르며,
	G(S)etProp 은 동적으로 메모리를 할당하여 사용할 수 있기 때문에, 활용 빈도가 높습니다.
----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);



HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_WndExtra");

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


	WndClass.cbWndExtra = 4; // 해당 윈도우 생성시 4바이트 메모리 추가 할당
	WndClass.hCursor = LoadCursor(NULL, IDC_CROSS);
	WndClass.lpfnWndProc = ChildProc;
	WndClass.lpszClassName = TEXT("ChildCls");
	WndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
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
	switch (iMessage)
	{
	case WM_CREATE:
	{
		for (int x = 0; x < 300; x += 100)
		{
			for (int y = 0; y < 300; y += 100)
			{
				HWND child = CreateWindow(TEXT("ChildCls"), NULL, WS_CHILD | WS_VISIBLE,
					x, y, 100, 100,
					hWnd, (HMENU)NULL, g_hInst, NULL);

				int num = (x << 8) + y;
				SendMessage(child, WM_COMMAND, 0, num);
			}
		}
		return 0;

	}
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK ChildProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMessage)
	{
	case WM_CREATE:
		SetWindowLong(hWnd, 0, TRUE); // ※ cWndExtra 의 메모리 공간 0 에, TRUE (1) 을 signed long 으로 입력
		return 0;

	case WM_LBUTTONDOWN:
		SetWindowLong(hWnd, 0, !GetWindowLong(hWnd, 0)); 
		// ※ GetWindowLong : cWndExtra의 0번 공간의 signed long 값을 가져옴
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		if (GetWindowLong(hWnd, 0))
		{
			Ellipse(hdc, 10, 10, 90, 90);
		}
		else
		{
			MoveToEx(hdc, 10, 10, NULL); LineTo(hdc, 90, 90);
			MoveToEx(hdc, 10, 90, NULL); LineTo(hdc, 90, 10);
		}

		EndPaint(hWnd, &ps);
		
		return 0;


	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 0:
			int prop = SetProp(hWnd, TEXT("prop"), (HANDLE)lParam); 
			// ※ SetProp : lpsClassName + (2) - TEXT... 2개의 조합으로, 2차원으로 데이터를 구분하여 저장
			//             위의 SetWindowLong 처럼 고정 4바이트로 데이터 저장
			break;
			
		}
		return 0;

	case WM_RBUTTONDOWN:
		int prop = (int)GetProp(hWnd, TEXT("prop"));

		TCHAR Mes[64];
		wsprintf(Mes, TEXT("%d, %d"), prop >> 8 , prop & 0xFF);
		MessageBox(hWnd, Mes, TEXT("알림"), MB_OK);

		return 0;
	}
	


	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}




#endif // 주석


#if 1 // 코드만
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_WndExtra");

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


	WndClass.cbWndExtra = 4;
	WndClass.hCursor = LoadCursor(NULL, IDC_CROSS);
	WndClass.lpfnWndProc = ChildProc;
	WndClass.lpszClassName = TEXT("ChildCls");
	WndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
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
	switch (iMessage)
	{
	case WM_CREATE:
		for (int x = 0; x < 300; x += 100)
		{
			for (int y = 0; y < 300; y += 100)
			{
				HWND child = CreateWindow(TEXT("ChildCls"), NULL, WS_CHILD | WS_VISIBLE,
					x, y, 100, 100,
					hWnd, (HMENU)NULL, g_hInst, NULL);

				int num = (x << 8) + y;
				SendMessage(child, WM_COMMAND, 0, num);
				
			}
		}
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}



LRESULT CALLBACK ChildProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMessage)
	{
	case WM_CREATE:
		SetWindowLong(hWnd, 0, 1);
		return 0;


	case WM_LBUTTONDOWN:
		SetWindowLong(hWnd, 0, !GetWindowLong(hWnd, 0));
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		if (GetWindowLong(hWnd, 0))
		{
			Ellipse(hdc, 10, 10, 90, 90);
		}
		else
		{
			MoveToEx(hdc, 10, 10, NULL); LineTo(hdc, 90, 90);
			MoveToEx(hdc, 10, 90, NULL); LineTo(hdc, 90, 10);
		}

		EndPaint(hWnd, &ps);

		return 0;


	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 0:
			int prop = SetProp(hWnd, TEXT("prop"), (HANDLE)lParam);
			break;
		}
		
		return 0;

	case WM_RBUTTONDOWN:
		int prop = (int)GetProp(hWnd, TEXT("prop"));

		TCHAR Mes[64];
		wsprintf(Mes, TEXT("%d, %d"), prop >> 8, prop & 0xFF);
		MessageBox(hWnd, Mes, TEXT("알림"), MB_OK);

		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}



#endif // 코드만


#endif // Total