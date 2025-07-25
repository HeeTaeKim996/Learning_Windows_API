#if 0 // Total
/*------------------------------------------------------------------------------------------------------------
- 정리할 내용이 많기에 개요에 정리 내용을 모두 적습니다.

- 헤더파일에는 항상 Resources.h가 있음
- 새항목 - aaa.rc 로 생성된 rc 파일들은 #include "resource.h"가 자동 생성.  Resource.h에서 이 rc파일들을 관리하는듯
- Win코드인 cpp에서 #include "resources.h" 로 이 rc 들에 접근 가능
- 사용 방법은 아래 코드 보는 게 나을듯

- !! 주의. 이유는 모르지만, vs 2022를 사용중인데, rc파일 우클릭 -> 코드보기 -> ㅣLANGUAGE ... 여기에 KOREAN... DEFAULT..
     이런 형식으로 돼있는데, 이상태서 빌드하면, 오류 생김. 아마 #if !defined(AFX_RESOURCE_DLL) || defined(AFX_TANG_KOR)
	 이부분에서 오류가 나서, 인식을 못하는 것 같음.
	 위 KOREAN... DEFAULT를 수동으로 18, 1 로 정수로 할당하면 오류가 해결됨
	※ .rc 를 수정하면, 항상 코드가 다시 KOREAN.., DEFAULT... 로 바뀌는데, 지금은 수정할 때마다 코드를 직접 18, 1 로
	   다시 수정하고 있음.. 

 - MAKEINTRESOURCE 내에 입력해야할 값, WM_COMMAND의 wParam 분기 값들은 모두 rc 우클릭 -> 코드 보기 로 보면 나옴 

 ○ Alt 단축키, Ctrl 단축키( Accelerator )
  - Alt 단축키 : rc 에서 캡션 내용을 수정하면 된다. Alt단축키로 사용될 문자 앞에 & 를 붙이면 된다. 
                이렇게 하면, Alt -> &뒤 단축키 -> & 뒤 단축키 로 빠르게 처리 가능. 물론 코드로 직접 수정 가능
  - Ctrl 단축키 :  1) rc -> 리소스 추가 -> Accelerator -> Ctrl, Alt 등 필요로 하는 거 TRUE로 하고, 
				     ID 지정 (원하는 메뉴)  키지정에 원하는 문자 입력. 형식은 디펄트 사용(VIRTKEY)
				     마찬가지로 코드로 직접 수정 가능
				   2) 하단처럼 코드 추가 작성. ACCEL 변수를 만들고, GetMessage 후 우선 Accel처리하도록 처리 

 ○ StringTable
   - 위 내용들과 동일. 
------------------------------------------------------------------------------------------------------------*/

#if 0 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Menu");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style = CS_VREDRAW | CS_HREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);


	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1)); 
	// ※ IDR_ACCELERATOR1은 마찬가지로 .rc ->우클릭 코드보기 로 볼 수 있는 코드 복붙하면 된다
	while (GetMessage(&Message, NULL, 0, 0))
	{
		if (!TranslateAccelerator(hWnd, hAccel, &Message))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR str[256];

	switch (iMessage)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam)) // ※ !! wParam도 상위, 하위 나눠서 데이터 오기 때문에, LOWRD필수
		{
		case 999:
			MessageBox(hWnd, TEXT("첫번째 메뉴를 선택했습니다"), TEXT("Menu Demo"), MB_OK);
			break;
		case ID_FILE_MENU2:
			MessageBox(hWnd, TEXT("두번째 메뉴를 선택했습니다"), TEXT("Menu Demo"), MB_OK);
			break;
		case ID_FILE_EXIT:
			DestroyWindow(hWnd); // ※ PostQuitMessage(0); 보다 더 우아한? 방법이라고 교재에 나옴..
			break;
		case ID_VIEW_LOVE:
			MessageBox(hWnd, TEXT("러브"), TEXT("lOVE"), MB_OK);
			break;
		case ID_VIEW_HARRY:
			MessageBox(hWnd, TEXT("해리"), TEXT("HARRY"), MB_OK);
			break;
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		LoadString(g_hInst, IDR_STRING101, str, 256);
		TextOut(hdc, 100, 100, str, lstrlen(str));
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
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("UsingMenu2");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdShow, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU2);
	WndClass.style = CS_VREDRAW | CS_HREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR2));
	while (GetMessage(&Message, NULL, 0, 0))
	{
		if (!TranslateAccelerator(hWnd, hAccel, &Message))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static TCHAR str[256];

	switch (iMessage)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_HARRY_LOVE:
			MessageBox(hWnd, TEXT("해리"), TEXT("LOVE"), MB_OK);
			break;
		case ID_BORI_FOOD:
			MessageBox(hWnd, TEXT("보리"), TEXT("FOOD"), MB_OK);
			break;
		case ID_SETTINGS_EXIT:
			DestroyWindow(hWnd);
			break;
		}

		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		LoadString(g_hInst, IDR_STRING101, str, 256);
		TextOut(hdc, 100, 100, str, lstrlen(str));
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