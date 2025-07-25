#if 0 // Total
/*--------------------------------------------------------
	  TextOut에서 lstrlen, SetTextAlign, wsprintf를 통한 문자열 출력.
	  DrawText를 활용한 문자열 출력에 관한 내용입니다
--------------------------------------------------------*/

#if 0 // 주석
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("DrawText");

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
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
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


//#define UsingTextOut
//#define UsingDrawText
#define Using_wsprintf

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

#ifdef UsingTextOut
	const TCHAR* st1 = TEXT("Hary is Cute");
	const TCHAR* st2 = TEXT("bori is Also Cute");
	const TCHAR* st3 = TEXT("need to Clean Teeth");
#endif



#ifdef UsingDrawText
	RECT rt = { 20, 20, 300, 200 };
	const TCHAR* st = TEXT("님은 갔습니다. 아아 사랑하는 나의 님은 갔습니다. 푸른 산빛을 "
		"깨치고 단풍나무 숲을 향하여 난 작은 길을 걸어서 차마 떨치고 갔습니다."
		"황금의 꽃같이 굳고 빛나던 옛 맹세는 차디찬 티끝이 되어 한숨의 미풍에 "
		"날아갔습니다.");
#endif

#ifdef Using_wsprintf
	TCHAR st[200];
	wsprintf(st, TEXT("%d 입니다"), 10);
	/* ○ wsprintf
	    - 문자열 외에 변수들을 문자열로 출력하려면, wsprintf로 문자열에 정수값을 입력 후 문자열 추력
		- 버퍼 TCHAR instnace[n] 에서 버퍼의 최대값은 1024가 상한. 
	*/
#endif


	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:

#ifdef UsingTextOut
		hdc = BeginPaint(hWnd, &ps);
		SetTextAlign(hdc, TA_TOP | TA_LEFT );
		/* ○ SetTextAlgin
		    - TA_TOP		: 수직 상단 정렬
			- TA_BOTTOM		: 수직 하단 정렬
			- TA_CENTER		: 수평 중앙 정렬
			- TA_LEFT		: 수평 왼쪽 정렬
			- TA_RIGHT		: 수평 우측 정렬
			- TA_UPDATECP	: CP를 사용하여 문자열 출력. 문자열 출력 후, CP는 문자열 끝 위치
			- TA_NOUPDATECP : CP를 사용하지 않고, 지정 좌표 사용. ( 디펄트로 사용됨 ! )
		
			 ※ CP : 그래픽 출력 때 사용하는 좌표. HDC에서 사용. TA_UPDATECP 사용시, CP를 좌표로 사용하여, 
			         하단 TextOut의 (2), (3) 에 입력한 좌표가 유효하지 않음

			 ※ TA_VCENTER는 없음. 수직 중앙 정렬 미지원 (왜..)
		*/


		TextOut(hdc, 20, 20, st1, lstrlen(st1));
		TextOut(hdc, 20, 40, st2, lstrlen(st2));
		TextOut(hdc, 20, 60, st3, lstrlen(st3));
		EndPaint(hWnd, &ps);
		return 0;
#endif


#ifdef UsingDrawText
		hdc = BeginPaint(hWnd, &ps);
		DrawText(hdc, st, -1, &rt, DT_LEFT | DT_TOP | DT_WORDBREAK);
		/* □ DrawText
		    - (3) : 출력할 문자열 수. -1일시, \0까지 문자열 수를 자동 계산
		    ○ (4)
			 - DT_LEFT			: 수평 왼쪽 정렬
			 - DT_RIGHT			: 수평 오른쪽 정렬
			 - DT_CENTER		: 수평 중앙 정렬
			 - DT_BOTTOM		: 수직 바닥 정렬
			 - DT_VCENTER		: 수직 중앙 정렬
			 - DT_TOP			: 수직 위쪽 정렬
			 - DT_WORKDBREAK	: 사각영역 오른쪽 끝에서 자동 개행
			 - DT_SINGLELINE	: 한 줄로 출력
			 - DT_NOCLIP		: 사각영역의 경계를 벗어나도 문자열을 자르지 않고 그대로 출력
		*/

		EndPaint(hWnd, &ps);
		return 0;
#endif


#ifdef Using_wsprintf
		hdc = BeginPaint(hWnd, &ps);
		SetTextAlign(hdc, TA_TOP | TA_LEFT);
		TextOut(hdc, 20, 20, st, lstrlen(st));
		EndPaint(hWnd, &ps);
		return 0;
#endif
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}




#endif // 주석

#if 1 // 코드만
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("DrawText");

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
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
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

//#define UsingTextOut
//#define UsingDrawText
#define Using_wsprintf

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

#ifdef UsingTextOut
	const TCHAR* st1 = TEXT("Harry is Cute");
	const TCHAR* st2 = TEXT("Bori is Also Cute");
	const TCHAR* st3 = TEXT("need to Clean Teeth");
#endif

#ifdef UsingDrawText
	RECT rt = { 20, 20, 400, 200 };
	const TCHAR* st = TEXT("님은 갔습니다. 아아 사랑하는 나의 님은 갔습니다. 푸른 산빛을 "
		"깨치고 단풍나무 숲을 향하여 난 작은 길을 걸어서 차마 떨치고 갔습니다."
		"황금의 꽃같이 굳고 빛나던 옛 맹세는 차디찬 티끝이 되어 한숨의 미풍에 "
		"날아갔습니다.");
#endif

#ifdef Using_wsprintf
	TCHAR wspSt[200];
	wsprintf(wspSt, TEXT("%d 입니다"), 10);
#endif

	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
#ifdef UsingTextOut
		hdc = BeginPaint(hWnd, &ps);
		SetTextAlign(hdc, TA_TOP | TA_LEFT);

		TextOut(hdc, 20, 20, st1, lstrlen(st1));
		TextOut(hdc, 20, 40, st2, lstrlen(st2));
		TextOut(hdc, 20, 60, st3, lstrlen(st3));
		EndPaint(hWnd, &ps);
		return 0;
#endif

#ifdef UsingDrawText
		hdc = BeginPaint(hWnd, &ps);
		DrawText(hdc, st, -1, &rt, DT_LEFT | DT_TOP | DT_WORDBREAK);
		EndPaint(hWnd, &ps);
		return 0;
#endif

#ifdef Using_wsprintf
		hdc = BeginPaint(hWnd, &ps);
		SetTextAlign(hdc, TA_TOP | TA_LEFT);

		TextOut(hdc, 20, 20, wspSt, lstrlen(wspSt));
		EndPaint(hWnd, &ps);
		return 0;
#endif
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}



#endif // 코드만

#endif // Total
