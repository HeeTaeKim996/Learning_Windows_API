#if 0 // Total
/*----------------------------------------------------------------------------------------------------
        GDI Objectd, SelectObject, DeleteObject에 관한 내용입니다.
		추가로 COLORREF의 4바이트(1바NULL'BB'GG'RR ) 로 구성됨도 적어놓은 코드입니다.
----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("GdiObject");

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

	HBRUSH myBrush, oldBrush;
	HPEN myPen, oldPen;

	switch (iMessage)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		COLORREF brushColor = 0xFF'00'00; 
		/* ○ COLORREF
		    - COLORREF는 unsigned 4바이트 정수
			- 16진수로 RGB( R, G, B) 를 처리하는데, ox'공란1바이트'BB'GG'RR' ; 이다
			- 따라서 위 0xFF'00'00; 은 푸른색
			- 위 우항을 RGB(0, 0, 255); 로 입력해도 됨
		*/
		myBrush = CreateSolidBrush(brushColor); 
		// (HBRUSH)GetSTockOBject(COLORNAME).. 은 윈도우에서 지정한 색상 할당이나 종류가 적음
		oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
		/* ○ SelectObject 
		    - SelectObject는 GDI Object ( 브러시, 펜 등..) 를 (2) 인자로 변경하고, 
			  같은 항목의 이전 Selected OBject를 리턴
			- 따라서 위 코드에서 myBrush에 할당되는 값은 위 brushColor 가 아닌, Select 전에 사용됐던 컬러 
		*/

		
		COLORREF penColor = RGB(255, 0, 0);
		myPen = CreatePen(PS_SOLID, 5, penColor);
		/* ○ CreatePen
			- (1) : 폰트 스타일
			- (2) : 펜 굵기
			- (3) : 펜 색상
		*/
		oldPen = (HPEN)SelectObject(hdc, myPen);

		Rectangle(hdc, 50, 50, 300, 200);


		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(myPen);

		/* GDI OBJECT 삭제
		  - GDI OBJECT는 메모리에 할당되므로, 메모리 누수를 방지하기 위해 DeleteObject로 메모리 해제해야 한다.
		  - 이 때 안전 규칙으로 현재 사용중인 GDI OBJECT는 삭제가 안되기 때문에, 위처럼
		    사용전에 OldPen,Brush를 할당하고, 사용후에 SelectObject로 old Pen,Brush를 SelectObject후, 사용했던 my..
			를 삭제하는 방법을 위 코드에서 사용했다.
		*/


		myPen = CreatePen(PS_SOLID, 3, 0x00'FF'00);
		oldPen = (HPEN)SelectObject(hdc, myPen);
		
		myBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(127, 127, 127));
		oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

		Rectangle(hdc, 400, 300, 600, 350);

		DeleteObject(SelectObject(hdc, oldPen));
		DeleteObject(SelectObject(hdc, oldBrush));

		/*
		  - 이전에 COLORREF를 직접 할당했고, SelectObject의 리턴값이 Select 이전의 값들이었으므로,
		    리턴값은 사용했던 hPen, hBrush가 된다. 따라서 위처럼 축약할 수 있다.
		*/


		EndPaint(hWnd, &ps);
	}

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
LPCTSTR lpszClass = TEXT("GdiObject");

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

	HBRUSH hBrush, oBrush;

	HPEN hPen, oPen;


	switch (iMessage)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		oBrush = (HBRUSH)SelectObject(hdc, hBrush);

		hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
		oPen = (HPEN)SelectObject(hdc, hPen);
		
		Rectangle(hdc, 50, 50, 600, 400);

		DeleteObject(SelectObject(hdc, oBrush));
		DeleteObject(SelectObject(hdc, oPen));

		EndPaint(hWnd, &ps);

		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // 코드만

#endif // Total