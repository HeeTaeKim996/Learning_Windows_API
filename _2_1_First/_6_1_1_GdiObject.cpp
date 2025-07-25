#if 0 // Total
/*----------------------------------------------------------------------------------------------------
        GDI Objectd, SelectObject, DeleteObject�� ���� �����Դϴ�.
		�߰��� COLORREF�� 4����Ʈ(1��NULL'BB'GG'RR ) �� �����ʵ� ������� �ڵ��Դϴ�.
----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
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
		/* �� COLORREF
		    - COLORREF�� unsigned 4����Ʈ ����
			- 16������ RGB( R, G, B) �� ó���ϴµ�, ox'����1����Ʈ'BB'GG'RR' ; �̴�
			- ���� �� 0xFF'00'00; �� Ǫ����
			- �� ������ RGB(0, 0, 255); �� �Է��ص� ��
		*/
		myBrush = CreateSolidBrush(brushColor); 
		// (HBRUSH)GetSTockOBject(COLORNAME).. �� �����쿡�� ������ ���� �Ҵ��̳� ������ ����
		oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
		/* �� SelectObject 
		    - SelectObject�� GDI Object ( �귯��, �� ��..) �� (2) ���ڷ� �����ϰ�, 
			  ���� �׸��� ���� Selected OBject�� ����
			- ���� �� �ڵ忡�� myBrush�� �Ҵ�Ǵ� ���� �� brushColor �� �ƴ�, Select ���� ���ƴ� �÷� 
		*/

		
		COLORREF penColor = RGB(255, 0, 0);
		myPen = CreatePen(PS_SOLID, 5, penColor);
		/* �� CreatePen
			- (1) : ��Ʈ ��Ÿ��
			- (2) : �� ����
			- (3) : �� ����
		*/
		oldPen = (HPEN)SelectObject(hdc, myPen);

		Rectangle(hdc, 50, 50, 300, 200);


		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(myPen);

		/* GDI OBJECT ����
		  - GDI OBJECT�� �޸𸮿� �Ҵ�ǹǷ�, �޸� ������ �����ϱ� ���� DeleteObject�� �޸� �����ؾ� �Ѵ�.
		  - �� �� ���� ��Ģ���� ���� ������� GDI OBJECT�� ������ �ȵǱ� ������, ��ó��
		    ������� OldPen,Brush�� �Ҵ��ϰ�, ����Ŀ� SelectObject�� old Pen,Brush�� SelectObject��, ����ߴ� my..
			�� �����ϴ� ����� �� �ڵ忡�� ����ߴ�.
		*/


		myPen = CreatePen(PS_SOLID, 3, 0x00'FF'00);
		oldPen = (HPEN)SelectObject(hdc, myPen);
		
		myBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(127, 127, 127));
		oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

		Rectangle(hdc, 400, 300, 600, 350);

		DeleteObject(SelectObject(hdc, oldPen));
		DeleteObject(SelectObject(hdc, oldBrush));

		/*
		  - ������ COLORREF�� ���� �Ҵ��߰�, SelectObject�� ���ϰ��� Select ������ �����̾����Ƿ�,
		    ���ϰ��� ����ߴ� hPen, hBrush�� �ȴ�. ���� ��ó�� ����� �� �ִ�.
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


#endif // �ּ�


#if 1 // �ڵ常
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

#endif // �ڵ常

#endif // Total