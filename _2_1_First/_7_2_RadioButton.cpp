#if 0 // Total
/*----------------------------------------------------------------------------------------------------
     n개로 구성된 그룹 중 하나만 선택이 가능한, 라디오 버튼에 관한 코드입니다.
----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("RadioButton");

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

/*----------------------------------------------------------------------------------------------
   □ 라디오 버튼
	- 라디오 버튼은, 그룹으로 묶은 라디오 버튼들 사이에서, 단 하나만 선택되도록 하는 버튼.
	○ WS_GROUP
	 - 라디오 버튼의 시작 버튼에는 WS_GROUP을 추가한다. 윈도우는 CreateWindow 선언순서와, WS_GROUP 을 통해
	   라디오 그룹을 구분한다.
	 - 아래 코드에서는, r1, r4에 WS_GROUP이 입력됐고, r1_r6순서로 CreateWindow 가 선언됐으므로,
	   r1_r3이 같은 라디오 그룹, r4_r6이 같은 라디오 그룹이다.
	 - 따라서 WS_GROUP 선언 위치, CreateWindow의 선언 순서에 주의해야 한다
	○ CheckRadioButton
	 - 라디오 버튼의 기본 로직은 위 WS_GROUP과 CreateWindow의 선언 순서에 의해서만 결정된다.
	 - CheckRadioButton 이 하는 일은, 초기화 때 체크되는 라디오 버튼을 처리하는 것
	 - 주의할 점은, 실질 로직은 WS_GROUP, CreateWindow의 선언 순서를 기준으로 작동하지만,
	   CheckRadioButton은 ID_Rn 의 정수의 오름차순으로 구분한다는 것이다.
	 - 만약 CheckRadioButton에 정수가 속하지 않는 라디어 버튼이 있다면, 해당 버튼은 Unchecked 된다.

	○ BS_GROUPBOX
	 - BS_GROUPBOX 를 입력하면, 해당 버튼은 실질적으로 버튼이 아닌, 라디오 버튼들의 배경? 처럼 처리됨

	○ 라디오 버튼 처리 방법
	 - 아래 코드처럼, 라디오 버튼 중 하나를 누른다면,
	 WM_COMMAND 의 HIWORD(wParam) == BN_CLICKED, LOWORD(wParam) == 각 라디오 버튼에 할당한 ID_Rn 이 입력된다.
	 이를 통해
	 1) WM_COMMAND 내 분기별로 로직 처리
	 하거나,
	 WM_PAINT 내에서 처럼,
	 2)SendMessage(라디오버튼핸들인서튼스, BM_GETCHECK, 0, 0) == .... ) 로
	   선택된 라디오 버튼이 무엇인지 확인 후 처리
	 하는, 2가지 방법으로 라디오 버튼을 처리할 수 있다.

----------------------------------------------------------------------------------------------*/

enum
{
	ID_R1 = 101, ID_R2, ID_R3, ID_R4, ID_R5, ID_R6
};
HWND r1, r2, r3, r4, r5, r6;
int Graph = 0;
COLORREF Color = RGB(0, 0, 0);

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	HBRUSH hBrush, OldBrush;

	switch (iMessage)
	{
	case WM_CREATE:
		CreateWindow(TEXT("button"), TEXT("Graph"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			5, 5, 120, 110,
			hWnd, (HMENU)0, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Color"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			145, 5, 120, 110,
			hWnd, (HMENU)1, g_hInst, NULL);
		r1 = CreateWindow(TEXT("button"), TEXT("Rectangle"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
			10, 20, 100, 30,
			hWnd, (HMENU)ID_R1, g_hInst, NULL);
		r2 = CreateWindow(TEXT("button"), TEXT("Ellipse"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			10, 50, 100, 30,
			hWnd, (HMENU)ID_R2, g_hInst, NULL);
		r3 = CreateWindow(TEXT("button"), TEXT("Line"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			10, 80, 100, 30,
			hWnd, (HMENU)ID_R3, g_hInst, NULL);
		r4 = CreateWindow(TEXT("button"), TEXT("Black"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
			150, 20, 100, 30,
			hWnd, (HMENU)ID_R4, g_hInst, NULL);
		r5 = CreateWindow(TEXT("button"), TEXT("Red"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			150, 50, 100, 30,
			hWnd, (HMENU)ID_R5, g_hInst, NULL);
		r6 = CreateWindow(TEXT("button"), TEXT("Blue"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			150, 80, 100, 30,
			hWnd, (HMENU)ID_R6, g_hInst, NULL);

		CheckRadioButton(hWnd, ID_R1, ID_R3, ID_R1);
		CheckRadioButton(hWnd, ID_R4, ID_R6, ID_R6);
		return 0;

	case WM_COMMAND:

		if (HIWORD(wParam) == BN_CLICKED)
		{
			switch (LOWORD(wParam))
			{
			case ID_R1:
				Graph = 0;
				break;
			case ID_R2:
				Graph = 1;
				break;
			case ID_R3:
				Graph = 2;
				break;
			}
		}

		InvalidateRect(hWnd, NULL, TRUE);
		return 0;


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);


		if (SendMessage(r4, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
			Color = RGB(0, 0, 0);
		}
		else if (SendMessage(r5, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
			Color = RGB(255, 0, 0);
		}
		else if (SendMessage(r6, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
			Color = RGB(0, 0, 255);
		}
		hBrush = CreateSolidBrush(Color);
		OldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		switch (Graph)
		{
		case 0:
			Rectangle(hdc, 10, 200, 200, 300);
			break;
		case 1:
			Ellipse(hdc, 10, 200, 200, 300);
			break;
		case 2:
			MoveToEx(hdc, 10, 200, NULL);
			LineTo(hdc, 200, 300);
			break;
		}

		DeleteObject(SelectObject(hdc, OldBrush));

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
LPCTSTR lpszClass = TEXT("RadioButton");

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


enum
{
	ID_R1 = 101, ID_R2, ID_R3, ID_R4, ID_R5, ID_R6
};
HWND r1, r2, r3, r4, r5, r6;
int Graph = 0;
COLORREF Color = RGB(0, 0, 0);

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	HBRUSH hBrush, OldBrush;

	switch (iMessage)
	{
	case WM_CREATE:
		CreateWindow(TEXT("button"), TEXT("Graph"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			5, 5, 120, 110,
			hWnd, (HMENU)0, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Color"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			145, 5, 120, 110,
			hWnd, (HMENU)1, g_hInst, NULL);
		r1 = CreateWindow(TEXT("button"), TEXT("Recntangle"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
			10, 20, 100, 30,
			hWnd, (HMENU)ID_R1, g_hInst, NULL);
		r2 = CreateWindow(TEXT("button"), TEXT("Ellipse"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			10, 50, 100, 30,
			hWnd, (HMENU)ID_R2, g_hInst, NULL);
		r3 = CreateWindow(TEXT("button"), TEXT("Line"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			10, 80, 100, 30,
			hWnd, (HMENU)ID_R3, g_hInst, NULL);
		r4 = CreateWindow(TEXT("button"), TEXT("Black"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
			150, 20, 100, 30,
			hWnd, (HMENU)ID_R4, g_hInst, NULL);
		r5 = CreateWindow(TEXT("button"), TEXT("Red"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			150, 50, 100, 30,
			hWnd, (HMENU)ID_R5, g_hInst, NULL);
		r6 = CreateWindow(TEXT("button"), TEXT("Blue"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			150, 80, 100, 30,
			hWnd, (HMENU)ID_R6, g_hInst, NULL);

		CheckRadioButton(hWnd, ID_R1, ID_R3, ID_R1);
		CheckRadioButton(hWnd, ID_R4, ID_R6, ID_R4);
		return 0;

	case WM_COMMAND:
		if (HIWORD(wParam) == BN_CLICKED)
		{
			switch (LOWORD(wParam))
			{
			case ID_R1:
				Graph = 0;
				break;
			case ID_R2:
				Graph = 1;
				break;
			case ID_R3:
				Graph = 2;
				break;
			}
		}

		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		if (SendMessage(r4, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
			Color = RGB(0, 0, 0);
		}
		else if (SendMessage(r5, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
			Color = RGB(255, 0, 0);
		}
		else
		{
			Color = RGB(0, 0, 255);
		}

		hBrush = CreateSolidBrush(Color);
		OldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		switch (Graph)
		{
		case 0:
			Rectangle(hdc, 10, 200, 200, 300);
			break;
		case 1:
			Ellipse(hdc, 10, 200, 200, 300);
			break;
		case 2:
			MoveToEx(hdc, 10, 200, NULL);
			LineTo(hdc, 200, 300);
			break;
		}

		DeleteObject(SelectObject(hdc, OldBrush));

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