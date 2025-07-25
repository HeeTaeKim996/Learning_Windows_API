#if 0 // Total
/*----------------------------------------------------------------------------------------------------
    ���̾Ʒα� �ڽ� �� ���� ó������ �Ұ��ϴ� �ڵ��Դϴ�.
----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Introducing Dialog Box");

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

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG: // �� DlgProc�� WndProc�� �ٸ���, WM_CREATE�� �ƴ� WM_INITDIALOG �� �ʱ�ȭ
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hDlg, IDOK);
			/* �� EndDialog �� (2)��
			    - �Ʒ��� ����������, DialogBox�� ���� �ż���. DialogBox�� (4)�� �Լ��� ó���Ǳ���� ���
				- (4)�� �Լ�(���� �� �Լ�)�� ó���Ǹ�, 
				  EndDialog�� �Էµ� (2)����, (4)�� �Լ��� ȣ���� DialogBox�� ������
			*/

			return TRUE;
		case IDCANCEL: 
			/* ��� ��ư �ܿ�, �⺻���� ������ X ��ư��, IDCANCEL���� ó���ϹǷ�,
			   ��� ��ư�� ���� �ϴ���, IDCANCEL�� �ݵ�� ó���ؾ� �Ѵ�
			*/ 
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}



		/* �� DialogBox (4)�� �Լ��� ���ϰ�
		    - ���ϰ��� TRUE �Ǵ� FALSE�� �޴µ�, TRUEó����, ������ �ü���� �߰��� ó���� ���� ������
			  �ǹ�
			- ���ϰ��� FALSE�� ���, ������ �ü���� �˾Ƽ� �߰� ó���ϵ��� ��
			  [ EX) x ��ư�� ������, idcancel �� LOWORD(wParam)���� ȣ��
					tab Ű�� ������, ��Ŀ���� ���� ��Ʈ�ѷ� �̵�  ]
		*/
	}

	return FALSE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG4), hWnd, DlgProc);
		// �� DialogBox�� ���������� �۵��ϱ� ������, (4)���� �Լ��� ���ϰ��� �� ������, �����
		//   ���ϰ��� ����, WndProc���� �ٸ��� ó���ϴ� �ڵ尡 �ַ� ����
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // �ּ�


#if 1 // �ڵ常
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Introducing Dialog Box");

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

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hDlg, IDOK);
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}

	}

	return FALSE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG4), hWnd, DlgProc);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // �ڵ常


#endif // Total