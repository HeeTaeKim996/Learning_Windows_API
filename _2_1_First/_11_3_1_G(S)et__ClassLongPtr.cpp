#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	�̹� ������ WndClass ����� �����ϴ�, SetClassLongPtr �Լ��� ���� �����Դϴ�. �׿ܿ��� ���� ������,
	�� ���븸 ���� �Ǵ� ������ �ڵ��Դϴ�.
----------------------------------------------------------------------------------------------------*/


#if 1 // �ּ�
#include <Windows.h>

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

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static HBRUSH hRed, hGreen, hBlue;
	static HBRUSH NowBrush;

	switch (iMessage)
	{
	case WM_CREATE:
		hRed = CreateSolidBrush(RGB(255, 0, 0));
		hGreen = CreateSolidBrush(RGB(0, 255, 0));
		hBlue = CreateSolidBrush(RGB(0, 0, 255));
		NowBrush = hRed;
		
		return 0;

	case WM_LBUTTONDOWN:
		if (NowBrush == hRed)
		{
			NowBrush = hGreen;
		}
		else if (NowBrush == hGreen)
		{
			NowBrush = hBlue;
		}
		else if (NowBrush == hBlue)
		{
			NowBrush = hRed;
		}

		SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)NowBrush);
		/* �� SetClassLongPtr : WndClass ��� ����
		    - (2) : ���� ��� �÷���
			   - GCL_CBEXTRA, GCL_CBWNDEXTRA, GCLP_HBRBACKGROUND, GCLP_HCURSOR .... 
			- (3) : ���� ����
			
		   �� GetClassLongPtr : WndClass ��� ��������

		*/


		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	
	case WM_DESTROY:
		DeleteObject(hRed);
		DeleteObject(hGreen);
		DeleteObject(hBlue);
		PostQuitMessage(0);

		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // �ּ�




#endif // Total