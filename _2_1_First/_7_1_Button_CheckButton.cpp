#if 0 // Total
/*----------------------------------------------------------------------------------------------------
     ������ �⺻ ���� ��ư, üũ ��ư( Check, Uncheck, Indeterminate ) �� ���� �ڵ��Դϴ�.
----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�

#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("LearningButton");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	//WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
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

	static HWND c0, c1, c2, c3, c4;
	static BOOL bEllipse = FALSE;
	
	switch (iMessage)
	{
	case WM_CREATE:
		c0 = CreateWindow(TEXT("button"), TEXT("Push Button"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20, 20, 100, 25,
			hWnd, (HMENU)0, g_hInst, NULL);
		/* �� CreateWindow - TEXT("button")
		    - (1) �׿� �����쿡�� ������ Ŭ���� TEXT("button") �Ǵ� TEXT("BUTTON") (��ҹ��� ���� ����) �� �Է��ϸ�,
			  �����쿡�� �̸� ������ Ŭ���� ��ư�� ������.
			  �� ������ ������ ���α׷� �̸��� �������� �� ������ �ذ�ƾ��µ�, �̸� ������ Ŭ���� �̸�����
			     �����Ϸ� �ؼ� �׷��� �ǰ�

			- (2) : ��ư ���� �ؽ�Ʈ ����. NULL �̸� �ؽ�Ʈ ����.
			
			- (3) : ��ư ����
				- WS_CHILD				: ������ ���α׷� �ڽ�
				- WS_VISIBLE			: ShowWindow ���ϰ� ���������� ��

				- BS_PUSHBUTTON			: Ǫ�� ��ư
				- BS_DEFPUSHBUTTON		: ����Ʈ Ǫ�� ��ư
				- BS_CHECKBOX			: üũ�ڽ�
				- BS_3STATE				: 3���� ���¸� ������ üũ �ڽ�
				- BS_AUTOCHECKBOX		: �ڵ� üũ �ڽ�
				- BS_AUTO3STATE			: 3���� ���¸� ������ �ڵ� üũ �ڽ�
				- BS_RADIOBUTTON		: ���� ��ư
				- BS_AUTORADIOBUTTON	: �ڵ� ���� ��ư
				- BS_GROUPBOX			: �׷� �ڽ�

			- (4),(5),(6),(7) : ���� ����� ����. posX, posY, width, height

			- (8) : (3)���� WS_CHILD �̹Ƿ�, �ݵ�� �θ� �����ؾ� ��

			- (9) : WM_COMMAND �� LOWORD(wParam) �� ȣ��� ����



		    �� �θ���� ��� ���
			 - TEXT("button") �� ��ư Ŭ����, �θ� �޼���ť WM_CMMAND�� ���ÿ� �ִ´�.
			 - LOWORD(wParam)	: ID (�� CreateWindow�� (9) �� �Է°�
			 - HIWORD(wParam)	: ���� �ڵ� (��ư�� �� �ʿ� ����)
			 - lParam			: �޼����� ���� ���ϵ� �������� ������ �ڵ� 
			                      [ g_hInst (������ �ν��Ͻ� �ڵ�) �� �ƴ�, ��ư�� HWND (������ �ڵ�) ]

			�� WM_COMMAND 
			 - �޴� �׸�, ������������, ��ư �� ��� LOWORD(wParam) ���� ID �� WM_COMMAND �� �����ϹǷ�,
			   �� �� ���� ID�� 0 ~ 66535 ������ ������, �ݵ�� �ߺ����� �ʰ�, �Է��ؾ� �Ѵ�
		*/

		c1 = CreateWindow(TEXT("button"), TEXT("Draw Ellipse?"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			20, 40, 160, 25, 
			hWnd, (HMENU)1, g_hInst, NULL);
		c2 = CreateWindow(TEXT("button"), TEXT("GoodBye Message?"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
			20, 70, 160, 25,
			hWnd, (HMENU)2, g_hInst, NULL);
		c3 = CreateWindow(TEXT("button"), TEXT("3State"), WS_CHILD | WS_VISIBLE | BS_3STATE,
			20, 100, 160, 25,
			hWnd, (HMENU)3, g_hInst, NULL);
		c4 = CreateWindow(TEXT("button"), TEXT("Auto 3State"), WS_CHILD | WS_VISIBLE | BS_AUTO3STATE,
			20, 130, 160, 25,
			hWnd, (HMENU)4, g_hInst, NULL);

		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 0:
			MessageBox(hWnd, TEXT("Push Button Clicked"), TEXT("Button"), MB_OK);
			break;
		case 1:
			if (SendMessage(c1, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
				/* ��  BM_GETCHECK�� ���ϰ��� �� 3����,
					1) BST_CHECKED
					2) BST_UNCHECKED
					3) BST_INDETERMINATE

				   �� (3), (4)���� ���� 0, 0 ( wParam, lParam�ε� �ƹ� �ǹ� ���� )
				*/

			{
				SendMessage(c1, BM_SETCHECK, BST_CHECKED, 0); 
				// �� �� �ּ��� ���������� (4)�׵� ���� 0. lParam�ε� �ƹ� �ǹ� ����
				bEllipse = TRUE;
			}
			else
			{
				SendMessage(c1, BM_SETCHECK, BST_UNCHECKED, 0);
				bEllipse = FALSE;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 3:
			switch (SendMessage(c3, BM_GETCHECK, 0, 0))
			{
			case BST_UNCHECKED:
				SendMessage(c3, BM_SETCHECK, BST_CHECKED, 0);
				break;
			case BST_CHECKED:
				SendMessage(c3, BM_SETCHECK, BST_INDETERMINATE, 0);
				break;
			case BST_INDETERMINATE:
				SendMessage(c3, BM_SETCHECK, BST_UNCHECKED, 0);
				break;
			}

			break;
		}

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		if (bEllipse == TRUE)
		{
			Ellipse(hdc, 200, 100, 400, 200);
		}
		else
		{
			Rectangle(hdc, 200, 100, 400, 200);
		}
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:

		TCHAR str[128] = TEXT("");

		if (SendMessage(c2, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
			lstrcat(str, TEXT("c2_Goodbye\n"));
		}
		else
		{
			lstrcat(str, TEXT("c2_NotGoodbye\n"));
		}
		switch (SendMessage(c4, BM_GETCHECK, 0, 0))
		{
		case BST_CHECKED:
			lstrcat(str, TEXT("c4_check"));
			break;
		case BST_UNCHECKED:
			lstrcat(str, TEXT("c4_uncheck"));
			break;
		case BST_INDETERMINATE:
			lstrcat(str, TEXT("c4_indeterminated"));
			break;
		}
		MessageBox(hWnd, str, TEXT("check"), MB_OK);

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
LPCTSTR lpszClass = TEXT("LearningButton");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
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

	static HWND c0, c1, c2, c3, c4;
	static BOOL bEllipse = FALSE;

	switch (iMessage)
	{
	case WM_CREATE:
		c0 = CreateWindow(TEXT("button"), TEXT("Push Button"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20, 20, 100, 25,
			hWnd, (HMENU)0, g_hInst, NULL);
		c1 = CreateWindow(TEXT("button"), TEXT("Draw Ellipse?"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			20, 40, 160, 25,
			hWnd, (HMENU)1, g_hInst, NULL);
		c2 = CreateWindow(TEXT("button"), TEXT("GoodBye Message?"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
			20, 70, 160, 25,
			hWnd, (HMENU)2, g_hInst, NULL);
		c3 = CreateWindow(TEXT("button"), TEXT("3State"), WS_CHILD | WS_VISIBLE | BS_3STATE,
			20, 100, 160, 25,
			hWnd, (HMENU)3, g_hInst, NULL);
		c4 = CreateWindow(TEXT("button"), TEXT("Auto 3State"), WS_CHILD | WS_VISIBLE | BS_AUTO3STATE,
			20, 130, 160, 25,
			hWnd, (HMENU)4, g_hInst, NULL);
		
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 0:
			MessageBox(hWnd, TEXT("Push Button Clicked"), TEXT("Button"), MB_OK);
			break;
		case 1:
			if (SendMessage(c1, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
			{
				SendMessage(c1, BM_SETCHECK, BST_CHECKED, 0);
				bEllipse = TRUE;
			}
			else
			{
				SendMessage(c1, BM_SETCHECK, BST_UNCHECKED, 0);
				bEllipse = FALSE;
			}

			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 3:
			switch (SendMessage(c3, BM_GETCHECK, 0, 0))
			{
			case BST_UNCHECKED:
				SendMessage(c3, BM_SETCHECK, BST_CHECKED, 0);
				break;
			case BST_CHECKED:
				SendMessage(c3, BM_SETCHECK, BST_INDETERMINATE, 0);
				break;
			case BST_INDETERMINATE:
				SendMessage(c3, BM_SETCHECK, BST_UNCHECKED, 0);
				break;
			}
			break;
		}

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		if (bEllipse)
		{
			Ellipse(hdc, 200, 100, 400, 200);
		}
		else
		{
			Rectangle(hdc, 200, 100, 400, 200);
		}

		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		TCHAR str[128] = TEXT("");

		if (SendMessage(c2, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
			lstrcat(str, TEXT("c2_checked\n"));
		}
		else
		{
			lstrcat(str, TEXT("c2_unchecked\n"));
		}

		switch (SendMessage(c4, BM_GETCHECK, 0, 0))
		{
		case BST_CHECKED:
			lstrcat(str, TEXT("c4_checked"));
			break;
		case BST_UNCHECKED:
			lstrcat(str, TEXT("c4_unchecked"));
			break;
		case BST_INDETERMINATE:
			lstrcat(str, TEXT("c4_indeterminate"));
			break;
		}

		MessageBox(hWnd, str, TEXT("check"), MB_OK);

		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // �ڵ常


#endif // Total