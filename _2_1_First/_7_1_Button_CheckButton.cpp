#if 0 // Total
/*----------------------------------------------------------------------------------------------------
     윈도우 기본 제공 버튼, 체크 버튼( Check, Uncheck, Indeterminate ) 에 관한 코드입니다.
----------------------------------------------------------------------------------------------------*/


#if 0 // 주석

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
		/* ○ CreateWindow - TEXT("button")
		    - (1) 항에 윈도우에서 지정한 클래스 TEXT("button") 또는 TEXT("BUTTON") (대소문자 구분 없음) 를 입력하면,
			  윈도우에서 미리 정의한 클래스 버튼이 생성됨.
			  ※ 이전에 윈도우 프로그램 이름을 수정했을 때 오류가 해결됐었는데, 미리 지정된 클래스 이름으로
			     생성하려 해서 그랬던 건가

			- (2) : 버튼 위에 텍스트 지정. NULL 이면 텍스트 없음.
			
			- (3) : 버튼 설정
				- WS_CHILD				: 윈도우 프로그램 자식
				- WS_VISIBLE			: ShowWindow 안하고 보여지도록 함

				- BS_PUSHBUTTON			: 푸시 버튼
				- BS_DEFPUSHBUTTON		: 디폴트 푸시 버튼
				- BS_CHECKBOX			: 체크박스
				- BS_3STATE				: 3가지 상태를 가지는 체크 박스
				- BS_AUTOCHECKBOX		: 자동 체크 박스
				- BS_AUTO3STATE			: 3가지 상태를 가지는 자동 체크 박스
				- BS_RADIOBUTTON		: 라디오 버튼
				- BS_AUTORADIOBUTTON	: 자동 라디오 버튼
				- BS_GROUPBOX			: 그룹 박스

			- (4),(5),(6),(7) : 기존 내용과 동일. posX, posY, width, height

			- (8) : (3)에서 WS_CHILD 이므로, 반드시 부모 지정해야 함

			- (9) : WM_COMMAND 의 LOWORD(wParam) 에 호출될 정수



		    ○ 부모와의 통신 방법
			 - TEXT("button") 은 버튼 클릭시, 부모에 메세지큐 WM_CMMAND를 스택에 넣는다.
			 - LOWORD(wParam)	: ID (위 CreateWindow의 (9) 항 입력값
			 - HIWORD(wParam)	: 통지 코드 (버튼은 볼 필요 없음)
			 - lParam			: 메세지를 보낸 차일드 윈도우의 윈도우 핸들 
			                      [ g_hInst (윈도우 인스턴스 핸들) 이 아닌, 버튼의 HWND (윈도우 핸들) ]

			○ WM_COMMAND 
			 - 메뉴 항목, 엑셀러레이터, 버튼 은 모두 LOWORD(wParam) 으로 ID 를 WM_COMMAND 에 전달하므로,
			   위 세 개의 ID를 0 ~ 66535 사이의 정수로, 반드시 중복되지 않게, 입력해야 한다
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
				/* ○  BM_GETCHECK의 리턴값은 총 3개로,
					1) BST_CHECKED
					2) BST_UNCHECKED
					3) BST_INDETERMINATE

				   ○ (3), (4)항은 고정 0, 0 ( wParam, lParam인데 아무 의미 없음 )
				*/

			{
				SendMessage(c1, BM_SETCHECK, BST_CHECKED, 0); 
				// ※ 위 주석과 마찬가지로 (4)항도 고정 0. lParam인데 아무 의미 없음
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


#endif // 주석


#if 1 // 코드만
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

#endif // 코드만


#endif // Total