#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	슈퍼 에딧 에 대한 코드입니다.
	앞선 서브에딧의 경우, 지정된 WndClass 의 함수가 만들어진 후에, SetWindow(Class)LongPtr 로 
	WNDPROC 을 교체하는 방법인 반면,
	슈퍼 에딧은 기존 만들어진 WndClass를 GetClassInfo 로 복사하여 가져온 후, 복사한 WndClass를 수정하여, 
	새로운 클래스로 등록하여 사용하는 방법입니다.
----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_SuperEdit");

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
	WndClass.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
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



LPCTSTR superClass = TEXT("SuperEditExam");
WNDPROC OldProc;
#define ID_EDIT1 100
HWND hEdit1;
LRESULT CALLBACK SuperProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		MessageBeep(0);
		break;
	}

	return CallWindowProc(OldProc, hWnd, iMessage, wParam, lParam);
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	WNDCLASS superWndClass;
	const TCHAR* Mes = TEXT("에디트에서 키보드를 누를 때마다 소리를 냅니다");

	switch (iMessage)
	{
	case WM_CREATE:
		GetClassInfo(NULL, TEXT("edit"), &superWndClass);
		/* ○ GetClassInfo 의 (1)항
		    - 복사하려는 클래스가 시스템 클래스 (edit, button, combobox..) 인 경우, NULL 을 입력
			- 복사하려는 클래스가 사용자 정의 클래스인 경우, 대부분 g_hInst 입력
		*/

		superWndClass.hInstance = g_hInst;
		superWndClass.lpszClassName = superClass;
		superWndClass.hCursor = LoadCursor(NULL, IDC_WAIT);
		OldProc = superWndClass.lpfnWndProc;
		superWndClass.lpfnWndProc = SuperProc;
		RegisterClass(&superWndClass);

		hEdit1 = CreateWindow(superClass, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 10, 200, 25,
			hWnd, (HMENU)ID_EDIT1, g_hInst, NULL);
		SetFocus(hEdit1);

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 100, Mes, lstrlen(Mes));
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

LRESULT CALLBACK SendProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR SendClass = TEXT("Learning_SuperEdit");

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
	WndClass.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = SendProc;
	WndClass.lpszClassName = SendClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_VREDRAW | CS_HREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(SendClass, SendClass, WS_OVERLAPPEDWINDOW,
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


LPCTSTR superClass = TEXT("SuperEditExam");
WNDPROC OldProc;
#define ID_EDIT1 100
HWND hEdit1;
LRESULT CALLBACK SuperProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		MessageBeep(0);
		break;
	}

	return CallWindowProc(OldProc, hWnd, iMessage, wParam, lParam);
}



LRESULT CALLBACK SendProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	WNDCLASS superWndClass;
	const TCHAR* Mes = TEXT("에디트에서 키보드를 누를 때마다 소리를 냅니다");


	switch (iMessage)
	{
	case WM_CREATE:
		GetClassInfo(NULL, TEXT("edit"), &superWndClass);

		superWndClass.hInstance = g_hInst;
		superWndClass.lpszClassName = superClass;
		superWndClass.hCursor = LoadCursor(NULL, IDC_WAIT);
		OldProc = superWndClass.lpfnWndProc;
		superWndClass.lpfnWndProc = SuperProc;
		RegisterClass(&superWndClass);

		hEdit1 = CreateWindow(superClass, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 10, 200, 25,
			hWnd, (HMENU)ID_EDIT1, g_hInst, NULL);
		SetFocus(hEdit1);

		return 0;


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 100, Mes, lstrlen(Mes));
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