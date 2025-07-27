#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	PAINTSTRUCT �� ����ü�� rcPaint ������ �ڵ��Դϴ�.

	PAINTSTRUCT ps - ps.rcPaint �� rcPaint.top, bottom, left, right ��,
	ȭ�� ũ�� ���� �Ǵ� ���� ������ ���� ���ŵ� ��, ���� �׷��� �� �������� ��Ÿ���� RECT �Դϴ�.

	�̸� Ȱ���Ͽ�, ���� �׷����� �κи� �������ϸ� ���� ����� �Ƴ� �� �ֽ��ϴ�.

	�Ʒ� �ڵ�� rcPaint �� ����ؼ� ������ �ϴ� �Ͱ�, rcPaint�� �ƴ� Cleint������ ������ �ϴ� ����
	���ϴ� �ڵ��Դϴ�.

	�� ������ �𸣰�����, rcPaint ����ص� ȭ���� �ø� ��, ��ü�� ������ �˴ϴ�. rcPaint �� ȿ���� Ȯ���Ϸ���
	   ȭ���� �÷ȴ� ���̴� �� �ƴ϶�, �����츦 �Ʒ��� ������ ���� ������ �Ϻ� ���� ����, �ٽ� ���� �÷���
	   ���� ������ �������� ��, ���� ���ŵ� �κи� ������ ���� Ȯ���� �� �ֽ��ϴ�.
----------------------------------------------------------------------------------------------------*/


#if 1 // �ּ�
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Sample_2");







void Swap(int* a, int* b) // Swap �� ���� CalColor �� ���� ����� ���� �������� ǥ��. �ڼ��� �� �ʿ� ����
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
			wsprintf(Mes, TEXT("���� isRCPAint : %d"), isRcPaint);
			MessageBox(hWnd, Mes, TEXT("�˸�"), MB_OK);

			break;
		}


		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // �ּ�



#endif // Total