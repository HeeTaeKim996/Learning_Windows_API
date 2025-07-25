#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	PeekMessage 에 대한 코드입니다.

	○ GetMessage 와 PeekMessage
	 - GetMessage는 메세지큐에 메세지가 하나도 없을시, 블로킹 상태가 됨. 다른 작업들 처리 못함
	 - 반면 PeekMessage는 메세지큐에 메세지가 하나도 없을시, PeekMessage(...) 가 false 처리되고, 
	   다른 작업들 처리 가능

	- 게임을 만들 때 대부분 PeekMessage 사용.
	- 물론 앞선 _9_3_ 테트시르 게임처럼, WM_TIMER 에 주기적으로 메세지 큐에 메세지를 넣어, 
	  논블로킹 처럼 게임을 만들 수는 있음

----------------------------------------------------------------------------------------------------*/


#if 1 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Sample_2");

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

	HDC hdc;
	hdc = GetDC(hWnd);
	while (1)
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
			/* ○ PM_REMOVE
			    - 메세지를 읽고나서, 해당 메세지를 큐에서 삭제함. GetMessage의 기본 기능과 같음
				※ PM_NOREMOVE 로 할시, 해당 메세지를 읽고 난 후에도 메세지를 큐에서 삭제하지 않고 냅둠
				  그래서 PeekMessage 라는 이름으로 사용됨
			*/
		{
			if (Message.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
			SetPixel(hdc, rand() % 500, rand() % 400, RGB(rand() % 256, rand() % 256, rand() % 256));
		}
	}

	ReleaseDC(hWnd, hdc);

	return (int)Message.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;


	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석



#endif // Total