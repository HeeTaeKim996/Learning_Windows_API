#if 0 // Total
/*----------------------------------------------------------------------------------------------------

----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_CreateStruct");


struct tag_Param
{
	int x;
	int y;
	TCHAR Mes[128];
};

tag_Param Param = { 100, 100, TEXT("Create Parameter") };


/*	■ CREATESTRUCT 와 LPVOID
    
	○ LP 
	 - 윈도우 API의 타입에는 LP.. 가 앞에 오는 타입이 많은데, 이는 포인터 를 의미
	   -> LPCREATESTRUCT 는 CREATESTRUCT 의 포인터 타입
	 - LPVOID 는 LP VOID 의 의미가 중복돼보이는데, 말그대로 윈도우 API를 사용할 때 자주 사용하는, void* 와 
	   역할이 같은 역할의 타입

	○ CREATESTRUCT
	 - WM_CREATE 일 때, LPARAM 에 CREATESTRUCT 구조체가 포인터 형식 LP 로 전달됨
	 - WM_CREATE 에서 이를 사용할 때, CREATESTRUCT (instance) = *(LPCREATESTRUCT)lParam; 형식으로 사용
	 - CreateWindow 의 마지막항에, (LPVOID) (Any Address) 를 할당하면, CREATESTRUCT의 필드멤버
	   lpCreateParams 에 할당됨. -> WM_CREATE 에서 CREATESTRUCT 에서 뽑아 사용 가능

*/

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
		NULL, (HMENU)NULL, hInstance, (LPVOID)&Param);
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
	CREATESTRUCT cs;
	static tag_Param WndParam;


	switch (iMessage)
	{
	case WM_CREATE:
		cs = *(LPCREATESTRUCT)lParam;
		WndParam = *((tag_Param*)(cs.lpCreateParams));

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, WndParam.x, WndParam.y, WndParam.Mes, lstrlen(WndParam.Mes));
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
LPCTSTR lpszClass = TEXT("Learning_CreateStruct");


struct tag_Param
{
	int x;
	int y;
	TCHAR Mes[128];
};

tag_Param Param = { 100, 100, TEXT("Create Parameter") };

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
		NULL, (HMENU)NULL, hInstance, (LPVOID)&Param);
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
	CREATESTRUCT cs;
	static tag_Param WndParam;

	switch (iMessage)
	{
	case WM_CREATE:
		cs = *(LPCREATESTRUCT)lParam;
		WndParam = *((tag_Param*)(cs.lpCreateParams));

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, WndParam.x, WndParam.y, WndParam.Mes, lstrlen(WndParam.Mes));
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