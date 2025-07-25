#if 0 // WinMain

/*------------------------------------------------
   가장 기초적인 윈도우 프로그램 만들기 내용입나다
-------------------------------------------------*/

#if 0 // 주석 VS 코드만
/*--------------------
         주석
--------------------*/

#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst; // 다수의 API 함수들이 hInstance값을 인수로 요구하기 때문에, 이를 위해 전역변수에 저장
LPCTSTR lpszClass = TEXT("First"); // 윈도우 클래스를 정의하는데 사용

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
/* ○ 
    - hInstance		: 프로그램의 인스턴스 핸들. 메모장을 2개킬시, 2개의 메모장별 인스턴스 핸들이 다르다. 
					  핸들은 윈도우 프로그램들을 식별하기 위한 idx와 비슷한 개념
	- hPrevInstance : 이전에 사용된 프로그램의 인스턴스 핸들. Win16에서는 사용됐던 찌꺼기 인자. Win32에서는 사용 안함
	- lpszCmdParam	: 프로그램 실행 직후 열 파일의 경로 전달
	- nCmdShow		: 창을 띄울 때의 초기 형태

	==> 주로 hInstance 만 사용
*/

{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance; 

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	// 두 멤버는 일종의 예약 공간. 윈도우가 내부적으로 사용하는 특수 목적의 여분 공간. 예약영역을 사용하지 않을 경우 둘 다 0
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 윈도우의 배경 색상을 지정
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // 커서 지정. 우항은 디펄트 커서
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 아이콘 지정. 우항은 디펄트 아이온
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc; // 거의 고정으로 WndProc할당. 윈도우의 메세지를 처리하는 함수를 지정
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL; // 프로그램이 사용할 메뉴지정. NULL일시 메뉴 사용 안함
	WndClass.style = CS_HREDRAW | CS_VREDRAW; 
	// 윈도우 스타일 정의. 주로 좌항 사용. 윈도우의 수평 | 수직이 변할 경우, 다시 그린다

	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	/*
	 - (1) : 사용하는 윈도우 클래스 지정
	 - (2) : 윈도우 타이틀 바에 나타날 문자열 지정
	 - (3) : 윈도우의 형태 지정. WS_OVERLAPPEDWINDOW 는 가장 기본적인, 메모장과 비슷한 표준 윈도우
	 - (4), (5) : 윈도우의 위치인 X, Y 지정. CW_USEDEFAULT를 사용하면 운영체제가 화면에 맞는 적당한 크기 지정
	 - (6), (7) : 윈도우의 크기인 Width, Height 지정. 마찬가지로 CW_USEDEFAULT 를 사용하면 화면에 적당한 크기 자동 지정
	 - (8) : 부모 윈도우가 있을 경우, 부모 윈도우의 핸들 지정
	 - (9) : 윈도우에서 사용한 메뉴의 핸들을 지정. 앞선 wNDcLASS의 LPSZmENUnAME은 윈도우 클래스를 기반으로 하는
	         모든 윈도우에 공통으로 적용되는 메뉴인 반면, 해당 인자의 메뉴는 함수로 만들어지는 윈도우에만 적용
     - (10) : 프로그램의 핸들 지정
	 - (11) : 보통 NULL값 사용. 무시해도 됨. 
	          여러개의 윈도우를 만들 때 각 윈도우에 고유의 파라미터를 전달하는 특수 목적 구조체라 함
	*/
	ShowWindow(hWnd, nCmdShow); 
	// - 위 CreateWindow로 만든 윈도우를, 화면에 보이게 함
	// - WinMain의 인자인 nCmdShow는 사용자가 프로그램 등록 정보 대화상자에서 지정한 값이라 함(아직은 경로 모름)
	// - 저 인자를 통해 만들어진 윈도우를 화면에 띄우거나, 숨기거나, 하는 등 방법 지정 가능


	// 루프로 입력된 메세지 처리
	while (GetMessage(&Message, NULL, 0, 0)) // 메세지 수신. 
	{
		TranslateMessage(&Message); // 입력된 메세지를 프로그램이 처리하기 쉽게 가공한다
		DispatchMessage(&Message); // WndProc에 처리하도록 전달한다
	}

	return (int)Message.wParam; // 프로그램이 종료될 때 리턴값을 전달 후 종료. wParam에는 종료될 때의 탈출코드가 입력됨
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
/* ○
    - CALLBACK : 운영체제에 의해 호출되는 응용 프로그램 내의 함수 
	- (1) : 메세지를 받을 윈도우의 핸들
	- (2) : 메세지의 프로토콜. 
	        [Ex) WM_SIZE 면 윈도우의 크기가 변경됨을 알리고, WM_KEYDWON 이면 사용자가 키보드를 눌렀음을 의미 ]
	- (3), (4) : 부가 정보. (2) 가  WM_LBUTTONDOWN (왼쪽 마우스 클릭) 이면, 화면 어디에 마우스 버튼이 눌렸는지, 
	             (2)가 WM_CHAR 면 어떤 문자열이 입력되었는지 에 대한 정보 전달
*/
{
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}






#else
/*---------------------
        코드만
---------------------*/
#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("First");

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

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);

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
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
#endif // 주석 VS 코드만



#endif // WinMain