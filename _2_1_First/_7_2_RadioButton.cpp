#if 0 // Total
/*----------------------------------------------------------------------------------------------------
     n���� ������ �׷� �� �ϳ��� ������ ������, ���� ��ư�� ���� �ڵ��Դϴ�.
----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
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
   �� ���� ��ư
	- ���� ��ư��, �׷����� ���� ���� ��ư�� ���̿���, �� �ϳ��� ���õǵ��� �ϴ� ��ư.
	�� WS_GROUP
	 - ���� ��ư�� ���� ��ư���� WS_GROUP�� �߰��Ѵ�. ������� CreateWindow ���������, WS_GROUP �� ����
	   ���� �׷��� �����Ѵ�.
	 - �Ʒ� �ڵ忡����, r1, r4�� WS_GROUP�� �Էµư�, r1_r6������ CreateWindow �� ��������Ƿ�,
	   r1_r3�� ���� ���� �׷�, r4_r6�� ���� ���� �׷��̴�.
	 - ���� WS_GROUP ���� ��ġ, CreateWindow�� ���� ������ �����ؾ� �Ѵ�
	�� CheckRadioButton
	 - ���� ��ư�� �⺻ ������ �� WS_GROUP�� CreateWindow�� ���� ������ ���ؼ��� �����ȴ�.
	 - CheckRadioButton �� �ϴ� ����, �ʱ�ȭ �� üũ�Ǵ� ���� ��ư�� ó���ϴ� ��
	 - ������ ����, ���� ������ WS_GROUP, CreateWindow�� ���� ������ �������� �۵�������,
	   CheckRadioButton�� ID_Rn �� ������ ������������ �����Ѵٴ� ���̴�.
	 - ���� CheckRadioButton�� ������ ������ �ʴ� ���� ��ư�� �ִٸ�, �ش� ��ư�� Unchecked �ȴ�.

	�� BS_GROUPBOX
	 - BS_GROUPBOX �� �Է��ϸ�, �ش� ��ư�� ���������� ��ư�� �ƴ�, ���� ��ư���� ���? ó�� ó����

	�� ���� ��ư ó�� ���
	 - �Ʒ� �ڵ�ó��, ���� ��ư �� �ϳ��� �����ٸ�,
	 WM_COMMAND �� HIWORD(wParam) == BN_CLICKED, LOWORD(wParam) == �� ���� ��ư�� �Ҵ��� ID_Rn �� �Էµȴ�.
	 �̸� ����
	 1) WM_COMMAND �� �б⺰�� ���� ó��
	 �ϰų�,
	 WM_PAINT ������ ó��,
	 2)SendMessage(������ư�ڵ��μ�ư��, BM_GETCHECK, 0, 0) == .... ) ��
	   ���õ� ���� ��ư�� �������� Ȯ�� �� ó��
	 �ϴ�, 2���� ������� ���� ��ư�� ó���� �� �ִ�.

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





#endif // �ּ�


#if 1 // �ڵ常
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

#endif // �ڵ常


#endif // Total