#if 0 // Total
/*----------------------------------------------------------------------------------------------------

----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
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

			/* ○ DrawMode
			    - R2_BLACK		: 항상 검은색으로
				- R2_WHITE		: 항상 흰색으로
				- R2_NOP		: 아무런 그리기도 하지 않는다
				- R2_NOT		: 원래의 그림을 반전시켜 그린다
				- R2_COPYPEN	: 원래의 그림을 덮어버리고, 새 그림을 그린다.
				- R2_NOTCOPYPEN	: 새 그림을 반전시켜 그린다
				- R2_NOTXORPEN	: XOR 결과의 반대값을 써 넣는다
				- R2_MERGEPEN	: OR 연산으로 두 그림을 합친다
				- R2_MASKPEN	: AND 연산으로 겹치는 부분만 그린다
				- R2_XORPEN		: XOR 연산으로 겹치는 부분만 반전시킨다.

				※ SetDROP2 로 설정한 건 ReleaseDC까지 적용. GetDC 시, 초기화되기 때문에, 
				  LUBTTONDOWN, LBUTTONUP 에서는 적용되지 않음
			*/


			SetROP2(hdc, R2_NOT);
			MoveToEx(hdc, sx, sy, NULL);
			LineTo(hdc, oldx, oldy);
			// => lParam으로 좌표를 업데이트하지 않은, 이전에 그렸던 선을 반전 (R2_NOT) 시켜, 흰색으로 지운다.
			
			//  ※ R2_WHITE 로 바꾼다면 선 자체가 보이지 않는다. 하단의 MoveToEx 위에 R2_BLACK 처리한다 해도,
			//     기능이 완전치 않고, 마우스를 누른 채로 왔다 갔다 하면, 기존 선이 지워진다.

			oldx = LOWORD(lParam);
			oldy = HIWORD(lParam);
			MoveToEx(hdc, sx, sy, NULL);
			LineTo(hdc, oldx, oldy);
			
			ReleaseDC(hWnd, hdc);


/*---------------------------------------------------------------------------------------------

      위처럼 기존 것들을 지우는 방법은, 0 1 로구성된 흑백화면에서는 R2_NOT 이 적합하고,
	  컬러 화면에서는 NOTXORPEN 을 사용해야 한다.

	  예를 들어, 
	  0 0 0
	  R R R
	  0 0 0 
	  에, 
	  0 B 0
	  0 B 0
	  0 B 0 
	  을 오버라이드 한다 하자.
	  
	  그렇다면, 위 2차원 화면에서 (0, 1) 인덱스는, 
	  0x00'00'00 XOR 0XFF'00'00 == 0XFF'00'00 이고,
	  여기에 NOT을하니,
	  0X00'FF'FF 인, RG 가 된다.

	  위 2차원 화면에서 (1, 1,)인 인덱스는,
	  0X00'00'FF NORXOR 0XFF'00'00 == 0X00'FF'00 으로, G가 된다.

	  즉 오버라이드 결과는,
	  0 (RG) 0
	  R (G ) R
	  0 (RG) 0 

	  이 된다.


	  여기서 다시 
	  0 B 0
	  0 B 0
	  0 B 0 
	  을 해제하면,

	  (0, 1) 은
	  0X00'FF'FF NORXOR 0XFF'00'00 == 0X00'00'00 으로 다시 0 이 되고,
	  (1, 1) 은
	  OX00'FF'00 NORXOR 0XFF'00'00 == 0X00'00'FF 로 다시 R 이 되어,

	  0 0 0
	  R R R
	  0 0 0 

	  으로 복구된다.


	  따라서 컬러라면, 위 코드에서 R2_NOT 을 R2_NORXORPEN 으로 바꾼다면, 복구 에서는 같은 기능을 구현할 수 있다.
	  다만, 확정 컬러는 B 인데, 마우스를 드래그 할 때 사용자 눈에 보여지는 컬러는 (RG), (G) 의 조합으로 보여진다.
	  드래그중에도 확정 컬러와 같은 색의 B로만 오버라이드 되어 보여지게 하는 방법은 없으려나..

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





#endif // 주석


#if 1 // 코드만
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

#endif // 코드만


#endif // Total