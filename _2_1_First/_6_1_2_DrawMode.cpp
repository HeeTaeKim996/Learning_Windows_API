#if 0 // Total
/*----------------------------------------------------------------------------------------------------

----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("DrawMode");

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

	static int sx, sy, oldx, oldy;static bool bNowDraw = FALSE;
	
	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		oldx = sx;
		oldy = sy;
		bNowDraw = TRUE;
		return 0;

	case WM_MOUSEMOVE:
		if (bNowDraw)
		{
			hdc = GetDC(hWnd);

			/* �� DrawMode
			    - R2_BLACK		: �׻� ����������
				- R2_WHITE		: �׻� �������
				- R2_NOP		: �ƹ��� �׸��⵵ ���� �ʴ´�
				- R2_NOT		: ������ �׸��� �������� �׸���
				- R2_COPYPEN	: ������ �׸��� ���������, �� �׸��� �׸���.
				- R2_NOTCOPYPEN	: �� �׸��� �������� �׸���
				- R2_NOTXORPEN	: XOR ����� �ݴ밪�� �� �ִ´�
				- R2_MERGEPEN	: OR �������� �� �׸��� ��ģ��
				- R2_MASKPEN	: AND �������� ��ġ�� �κи� �׸���
				- R2_XORPEN		: XOR �������� ��ġ�� �κи� ������Ų��.

				�� SetDROP2 �� ������ �� ReleaseDC���� ����. GetDC ��, �ʱ�ȭ�Ǳ� ������, 
				  LUBTTONDOWN, LBUTTONUP ������ ������� ����
			*/


			SetROP2(hdc, R2_NOT);
			MoveToEx(hdc, sx, sy, NULL);
			LineTo(hdc, oldx, oldy);
			// => lParam���� ��ǥ�� ������Ʈ���� ����, ������ �׷ȴ� ���� ���� (R2_NOT) ����, ������� �����.
			
			//  �� R2_WHITE �� �ٲ۴ٸ� �� ��ü�� ������ �ʴ´�. �ϴ��� MoveToEx ���� R2_BLACK ó���Ѵ� �ص�,
			//     ����� ����ġ �ʰ�, ���콺�� ���� ä�� �Դ� ���� �ϸ�, ���� ���� ��������.

			oldx = LOWORD(lParam);
			oldy = HIWORD(lParam);
			MoveToEx(hdc, sx, sy, NULL);
			LineTo(hdc, oldx, oldy);
			
			ReleaseDC(hWnd, hdc);


/*---------------------------------------------------------------------------------------------

      ��ó�� ���� �͵��� ����� �����, 0 1 �α����� ���ȭ�鿡���� R2_NOT �� �����ϰ�,
	  �÷� ȭ�鿡���� NOTXORPEN �� ����ؾ� �Ѵ�.

	  ���� ���, 
	  0 0 0
	  R R R
	  0 0 0 
	  ��, 
	  0 B 0
	  0 B 0
	  0 B 0 
	  �� �������̵� �Ѵ� ����.
	  
	  �׷��ٸ�, �� 2���� ȭ�鿡�� (0, 1) �ε�����, 
	  0x00'00'00 XOR 0XFF'00'00 == 0XFF'00'00 �̰�,
	  ���⿡ NOT���ϴ�,
	  0X00'FF'FF ��, RG �� �ȴ�.

	  �� 2���� ȭ�鿡�� (1, 1,)�� �ε�����,
	  0X00'00'FF NORXOR 0XFF'00'00 == 0X00'FF'00 ����, G�� �ȴ�.

	  �� �������̵� �����,
	  0 (RG) 0
	  R (G ) R
	  0 (RG) 0 

	  �� �ȴ�.


	  ���⼭ �ٽ� 
	  0 B 0
	  0 B 0
	  0 B 0 
	  �� �����ϸ�,

	  (0, 1) ��
	  0X00'FF'FF NORXOR 0XFF'00'00 == 0X00'00'00 ���� �ٽ� 0 �� �ǰ�,
	  (1, 1) ��
	  OX00'FF'00 NORXOR 0XFF'00'00 == 0X00'00'FF �� �ٽ� R �� �Ǿ�,

	  0 0 0
	  R R R
	  0 0 0 

	  ���� �����ȴ�.


	  ���� �÷����, �� �ڵ忡�� R2_NOT �� R2_NORXORPEN ���� �ٲ۴ٸ�, ���� ������ ���� ����� ������ �� �ִ�.
	  �ٸ�, Ȯ�� �÷��� B �ε�, ���콺�� �巡�� �� �� ����� ���� �������� �÷��� (RG), (G) �� �������� ��������.
	  �巡���߿��� Ȯ�� �÷��� ���� ���� B�θ� �������̵� �Ǿ� �������� �ϴ� ����� ��������..

---------------------------------------------------------------------------------------------*/
		}

		return 0;
	case WM_LBUTTONUP:
		bNowDraw = FALSE;
		hdc = GetDC(hWnd);
		MoveToEx(hdc, sx, sy, NULL);
		LineTo(hdc, oldx, oldy);
		ReleaseDC(hWnd, hdc);
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
LPCTSTR lpszClass = TEXT("DrawMode");

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

	static int sx, sy, oldx, oldy;
	static bool bNowDraw = FALSE;


	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		oldx = sx;
		oldy = sy;
		bNowDraw = TRUE;
		return 0;
	
	case WM_MOUSEMOVE:
		
		if (bNowDraw)
		{
			hdc = GetDC(hWnd);

			SetROP2(hdc, R2_NOT);
			MoveToEx(hdc, sx, sy, NULL);
			LineTo(hdc, oldx, oldy);

			oldx = LOWORD(lParam);
			oldy = HIWORD(lParam);
			MoveToEx(hdc, sx, sy, NULL);
			LineTo(hdc, oldx, oldy);

			ReleaseDC(hWnd, hdc);
		}

		return 0;

	case WM_LBUTTONUP:
		bNowDraw = false;
		hdc = GetDC(hWnd);
		MoveToEx(hdc, sx, sy, NULL);
		LineTo(hdc, oldx, oldy);
		ReleaseDC(hWnd, hdc);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // �ڵ常


#endif // Total