#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	WndClassEx 에 대한 코드입니다. WndClass와 차이거 거의 없습니다. 추후 교재도 WndClass를 계속
	사용할 예정이므로 굳이 공부할 필요도 없어 보입니다.

	WndClassEx의 WndClass와의 차이점은, 
	1) cbSize 라는 멤버가 추가됐는데, 버전 검증용으로 sizeof(WNDCLASSEX); 를 할당하면 됩니다.  
	  ( WndClass도 같은 방식으로 버전 검증을 자동으로 한다 합니다. )
	2) hIconSm 이 추가됐는데, 기존 WndClass는 아이콘으로 32 * 32 사이즈만 지원하는데, WndClassEx는
	  32 * 32 와 더붙어, 16 * 16 사이즈의 아이콘도 지원합니다. 

	=> 결론은 WndClassEx는 공부할 필요 없습니다. 차이점이라고는 16 * 16 사이즈의 아이콘을 지원한다.
	   하나 뿐입니다.
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
	WNDCLASSEX WndClassEx;
	g_hInst = hInstance;

	WndClassEx.cbSize = sizeof(WNDCLASSEX);
	WndClassEx.cbClsExtra = 0;
	WndClassEx.cbWndExtra = 0;
	WndClassEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClassEx.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
	//WndClassEx.hIconSm = NULL;
	WndClassEx.hIconSm = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 
		GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	WndClassEx.hInstance = hInstance;
	WndClassEx.lpfnWndProc = WndProc;
	WndClassEx.lpszClassName = lpszClass;
	WndClassEx.lpszMenuName = NULL;
	WndClassEx.style = CS_VREDRAW | CS_HREDRAW;
	if (RegisterClassEx(&WndClassEx) == 0)
	{
		MessageBox(NULL, TEXT("윈도우 클래스 등록 실패"), TEXT("에러"), MB_OK);
		return -1;
	}

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


	switch (iMessage)
	{


	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석



#endif // Total