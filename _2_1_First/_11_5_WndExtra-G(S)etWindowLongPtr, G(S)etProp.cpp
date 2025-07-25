#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	WndExtra - G(S)etWindowLong, G(S)etProp �� ���� �����Դϴ�. ������ thread_local �� ������ �����̶� ���� �˴ϴ�.
	
	G(S)etWindowLong, G(S)etProp ��� 4����Ʈ�� �����͸� �����մϴ�.
	���� ����������,
	G(S)etWindowLong ��  ��������� �޸���ġ �� �ĺ��ϰ�, �����츦 ������ �� �޸𸮸� WndClass.cbWndExtra�� ���� �Ҵ��ϰ�
	����Ͽ� ���ǹ��ϰ� ���ں��� ������,
	G(S)etProp �� �������� �޸𸮸� �Ҵ��Ͽ� ����� �� �ֱ� ������, Ȱ�� �󵵰� �����ϴ�.
----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);



HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_WndExtra");

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


	WndClass.cbWndExtra = 4; // �ش� ������ ������ 4����Ʈ �޸� �߰� �Ҵ�
	WndClass.hCursor = LoadCursor(NULL, IDC_CROSS);
	WndClass.lpfnWndProc = ChildProc;
	WndClass.lpszClassName = TEXT("ChildCls");
	WndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
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
	switch (iMessage)
	{
	case WM_CREATE:
	{
		for (int x = 0; x < 300; x += 100)
		{
			for (int y = 0; y < 300; y += 100)
			{
				HWND child = CreateWindow(TEXT("ChildCls"), NULL, WS_CHILD | WS_VISIBLE,
					x, y, 100, 100,
					hWnd, (HMENU)NULL, g_hInst, NULL);

				int num = (x << 8) + y;
				SendMessage(child, WM_COMMAND, 0, num);
			}
		}
		return 0;

	}
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK ChildProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMessage)
	{
	case WM_CREATE:
		SetWindowLong(hWnd, 0, TRUE); // �� cWndExtra �� �޸� ���� 0 ��, TRUE (1) �� signed long ���� �Է�
		return 0;

	case WM_LBUTTONDOWN:
		SetWindowLong(hWnd, 0, !GetWindowLong(hWnd, 0)); 
		// �� GetWindowLong : cWndExtra�� 0�� ������ signed long ���� ������
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		if (GetWindowLong(hWnd, 0))
		{
			Ellipse(hdc, 10, 10, 90, 90);
		}
		else
		{
			MoveToEx(hdc, 10, 10, NULL); LineTo(hdc, 90, 90);
			MoveToEx(hdc, 10, 90, NULL); LineTo(hdc, 90, 10);
		}

		EndPaint(hWnd, &ps);
		
		return 0;


	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 0:
			int prop = SetProp(hWnd, TEXT("prop"), (HANDLE)lParam); 
			// �� SetProp : lpsClassName + (2) - TEXT... 2���� ��������, 2�������� �����͸� �����Ͽ� ����
			//             ���� SetWindowLong ó�� ���� 4����Ʈ�� ������ ����
			break;
			
		}
		return 0;

	case WM_RBUTTONDOWN:
		int prop = (int)GetProp(hWnd, TEXT("prop"));

		TCHAR Mes[64];
		wsprintf(Mes, TEXT("%d, %d"), prop >> 8 , prop & 0xFF);
		MessageBox(hWnd, Mes, TEXT("�˸�"), MB_OK);

		return 0;
	}
	


	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}




#endif // �ּ�


#if 1 // �ڵ常
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_WndExtra");

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


	WndClass.cbWndExtra = 4;
	WndClass.hCursor = LoadCursor(NULL, IDC_CROSS);
	WndClass.lpfnWndProc = ChildProc;
	WndClass.lpszClassName = TEXT("ChildCls");
	WndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
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
	switch (iMessage)
	{
	case WM_CREATE:
		for (int x = 0; x < 300; x += 100)
		{
			for (int y = 0; y < 300; y += 100)
			{
				HWND child = CreateWindow(TEXT("ChildCls"), NULL, WS_CHILD | WS_VISIBLE,
					x, y, 100, 100,
					hWnd, (HMENU)NULL, g_hInst, NULL);

				int num = (x << 8) + y;
				SendMessage(child, WM_COMMAND, 0, num);
				
			}
		}
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}



LRESULT CALLBACK ChildProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMessage)
	{
	case WM_CREATE:
		SetWindowLong(hWnd, 0, 1);
		return 0;


	case WM_LBUTTONDOWN:
		SetWindowLong(hWnd, 0, !GetWindowLong(hWnd, 0));
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		if (GetWindowLong(hWnd, 0))
		{
			Ellipse(hdc, 10, 10, 90, 90);
		}
		else
		{
			MoveToEx(hdc, 10, 10, NULL); LineTo(hdc, 90, 90);
			MoveToEx(hdc, 10, 90, NULL); LineTo(hdc, 90, 10);
		}

		EndPaint(hWnd, &ps);

		return 0;


	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 0:
			int prop = SetProp(hWnd, TEXT("prop"), (HANDLE)lParam);
			break;
		}
		
		return 0;

	case WM_RBUTTONDOWN:
		int prop = (int)GetProp(hWnd, TEXT("prop"));

		TCHAR Mes[64];
		wsprintf(Mes, TEXT("%d, %d"), prop >> 8, prop & 0xFF);
		MessageBox(hWnd, Mes, TEXT("�˸�"), MB_OK);

		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}



#endif // �ڵ常


#endif // Total