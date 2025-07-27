#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	PAINTSTRUCT 의 구조체인 rcPaint 에대한 코드입니다.

	PAINTSTRUCT ps - ps.rcPaint 는 rcPaint.top, bottom, left, right 로,
	화면 크기 조정 또는 가시 영역이 새로 갱신될 시, 새로 그려야 할 영역만을 나타내는 RECT 입니다.

	이를 활용하여, 새로 그려야할 부분만 렌더링하면 연산 비용을 아낄 수 있습니다.

	아래 코드는 rcPaint 를 사용해서 렌더링 하는 것과, rcPaint가 아닌 Cleint영역을 렌더링 하는 것을
	비교하는 코드입니다.

	※ 원인은 모르겠지만, rcPaint 사용해도 화면을 늘릴 때, 전체가 렌더링 됩니다. rcPaint 의 효과를 확인하려면
	   화면을 늘렸다 줄이는 게 아니라, 윈도우를 아래로 내려서 가시 영역을 일부 없앤 다음, 다시 위로 올려서
	   가시 영역을 갱신했을 때, 새로 갱신된 부분만 렌더링 함을 확인할 수 있습니다.
----------------------------------------------------------------------------------------------------*/


#if 1 // 주석
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Sample_2");







void Swap(int* a, int* b) // Swap 과 밑의 CalColor 는 연산 비용이 높은 렌더링을 표현. 자세히 볼 필요 없음
{
	int t;
	t = *a; *a = *b; *b = t;
}
COLORREF CalColor()
{
	int r = rand() % 256;
	int g = rand() % 256;
	int b = rand() % 256;

	for (int i = 0; i < 10; i++)
	{
		Swap(&r, &g);
	}

	return RGB(r, g, b);
}


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


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt;
	static BOOL isRcPaint;

	switch (iMessage)
	{
	case WM_CREATE:
		isRcPaint = FALSE;
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		GetClientRect(hWnd, &rt);

		if (!isRcPaint)
		{
			for (int y = 0; y < rt.bottom; y++)
			{
				for (int x = 0; x < rt.right; x++)
				{
					SetPixel(hdc, x, y, CalColor());
				}
			}
		}
		else
		{
			for (int y = ps.rcPaint.top; y < ps.rcPaint.bottom; y++)
			{
				for (int x = ps.rcPaint.left; x < ps.rcPaint.right; x++)
				{
					SetPixel(hdc, x, y, CalColor());
				}
			}
		}



		EndPaint(hWnd, &ps);
		return 0;
		

	case WM_KEYDOWN:
		if (wParam == 'A')
		{
			isRcPaint = !isRcPaint;

			TCHAR Mes[64];
			wsprintf(Mes, TEXT("현재 isRCPAint : %d"), isRcPaint);
			MessageBox(hWnd, Mes, TEXT("알림"), MB_OK);

			break;
		}


		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석



#endif // Total