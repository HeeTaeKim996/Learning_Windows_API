#if 1 // Total
/*----------------------------------------------------------------------------------------------------
	FileOpenDial1 ���� ���߼��ÿ� ���� �ڵ��Դϴ�.
	�Ʒ� ������ ������ �������� ���ߴٸ�, �Ʒ� �ڵ带 �����ϱ� ��Ʊ� ������, �����մϴ�.

	�� lstrcpy
	 - (2)���� (1)�� �����ϴµ�, (2)�� \0 (���Ṯ��)�� �߰��� �ִٸ�, \0 �������� �����մϴ�.
	   
	 - ���� ���, (2) �� text("A\0BB\0CCC") ���, (1)�� ����Ǵ� �� A ���Դϴ�. (2)���� �����͸� �������� �Űܼ�
	   �״��� ���� �����Ѵٸ�, BB �� ����ǰ�, CCC �� (1)�� ������� �ʽ��ϴ�.

	�� OFN.Flags �� �÷��� OFN_EXPLORER | OFN_ALLOWMULTISELECT �� �ԷµǸ�,
	  OFN.lpstrFile ����, ��쿡 ���� ���ڿ��� �ٸ��� �Ҵ�

	  - 1) ���� �ϳ��� ���õ� ��� - ���� ������, C:/... .Exe �������� ���ڿ��� ����
								EX) lpstrFile = ��ü���\0
								EX) lpstrFile = "C:\\Users\\Kim\\file.txt\0"

	  - 2) ������ 2�� �̻� ���õ� ��� - ���ϵ��� �θ� ���ϸ��� \0 ���Ṯ�� ���� �Էµǰ�, ���Ŀ� ���ϸ���� ����.
										  ���ϸ�� ���� \0 �� ���еǾ� ����
								EX) lpstrFile = �������\0\ù�������ϸ�\0\�ι�°���ϸ�\0\...\0
								EX) lpstrFile = "C:\\Users\\Kim\\0file1.txt\0file2.txt\0file3.txt\0\0"

----------------------------------------------------------------------------------------------------*/


#if 1 // �ּ�
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
	const TCHAR* Mes = TEXT("���콺 ���� ��ư�� �����ʽÿ�");
	OPENFILENAME OFN;
	TCHAR str[32'000] = TEXT("");
	TCHAR lpstrFile[10'000] = TEXT("");
	TCHAR* p;
	TCHAR Name[MAX_PATH];
	TCHAR szTmp[MAX_PATH];
	int i = 1;


	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = hWnd;
		OFN.lpstrFilter = TEXT("��� ����(*.)\0*.*\0");
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = 10'000;
		OFN.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT;  // �� ���÷��״� �����Ǿ� �������� ����. ��°�� �ܿ��
		if (GetOpenFileName(&OFN) != 0)
		{
			p = lpstrFile;
			lstrcpy(Name, p);
			if (*(p + lstrlen(Name) + 1) == 0)
			{
				wsprintf(str, TEXT("%s ���� �ϳ��� �����߽��ϴ�"), Name);
			}
			else
			{
				wsprintf(str, TEXT("%s ���丮�� �ִ� ���� ���ϵ��� ���õǾ����ϴ�\r\n\r\n"), Name);

				while (1)
				{
					p = p + lstrlen(Name) + 1;
					if (*p == 0)
					{
						break;
					}
					lstrcpy(Name, p);
					wsprintf(szTmp, TEXT("%d��° ���� = %s \r\n"), i++, Name);
					lstrcat(str, szTmp);
				}
			}

			MessageBox(hWnd, str, TEXT("������ ����"), MB_OK);
		}
		else
		{
			if (CommDlgExtendedError() == FNERR_BUFFERTOOSMALL) // �� ���� ����. �ʰ��� �޼����ڽ��� �˸�
			{
				MessageBox(hWnd, TEXT("���� ũ�Ⱑ �ʹ� �۽��ϴ�"), TEXT("����"), MB_OK);
			}
		}

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 10, Mes, lstrlen(Mes));
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // �ּ�


#if 0 // �ڵ常
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

#endif // �ڵ常


#endif // Total