#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	���� ���� �ǽ� 2��° �Դϴ�.
	ù�� _15_3_1 �� ������ �����ϰ�, ���� �� Ȯ��� �����Դϴ�.
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
	TCHAR str[300];
	TCHAR lpstrFile[MAX_PATH] = TEXT("");
	TCHAR szFileTile[MAX_PATH];
	TCHAR InitDir[MAX_PATH];
	TCHAR CustFilter[40] = TEXT("���� ����");

	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = hWnd;
		OFN.lpstrFilter = TEXT(
			"��� ����(*.*)\0*.*\0"
			"�ؽ�Ʈ ���� (*.txt)\0*.txt\0"
			"c �ҽ� ���� (*.c; *.h)\0*.c;*.h\0");
		/*	�� lpstrFilter
			 - �˻� �� ���� ���͸� ���ڿ� \0 ... \0 �̷��� ... �� ����. \0 ����, ������ �������� ���ڿ�.
			 - \0 ������ ... �� �˻� ����

			 �� \0 ������ ���͸� ���ڿ���, Regex ���ϰ� ����.
			  - * �� �ּ� 1�� �̻��� CHAR �� �ǹ�
			  - ; �� OR �� ����� �ǹ�
		*/
		OFN.nFilterIndex = 2; // �� ���� ������ lpstrFilter �� ����Ʈ �ε���
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = MAX_PATH;
		OFN.lpstrTitle = TEXT("������ ������ �ֽʽÿ�"); // �� Ÿ��Ʋ�ٸ� ����. ����Ʈ�� '����'
		OFN.lpstrFileTitle = szFileTile; // �� �������� �˻��ؼ� ��ó�� �߰ߵǴ� \ �� �ǹ�����, ���ϸ� A.x ����
		OFN.nMaxFileTitle = MAX_PATH;
		OFN.lpstrDefExt = TEXT("abc"); 
		// ���ϸ��� ����ڰ� Ÿ�������� ��, ���� Ȯ���� ( . ����) �� �������� �ʴٸ�, ����Ʈ�� �Ҵ��� lpstDefExt �� ����
		// Ex) A\B -> A\B.abc
		GetWindowsDirectory(InitDir, MAX_PATH); // �� C:\Windows  �� InitDir �� �Է�
		OFN.lpstrInitialDir = InitDir; // �� ó�� ���Ͽ��� �� ���� ���� ������ ����Ʈ ���

		if (GetOpenFileName(&OFN) != 0)
		{
			wsprintf(str, TEXT("%s ������ �����߽��ϴ�. ���ϸ��� %s �Դϴ�. ���ϸ� ������ %d, Ȯ���� ������ %d"),
				lpstrFile, szFileTile, OFN.nFileOffset, OFN.nFileExtension);
			/*
				�� nFileOffset
				 - lpstrFile ����, �����̸� �� ���۵Ǵ� �ε���
				
				�� nFileExtension
				 - lpstrFile ����, Ȯ���� �� ���۵Ǵ� �ε���
			
			*/
			MessageBox(hWnd, str, TEXT("���� ���� ����"), MB_OK);
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
	PAINTSTRUCT ps;
	const TCHAR* Mes = TEXT("���콺 ���� ��ư�� �����ʽÿ�");
	OPENFILENAME OFN;
	TCHAR str[300];
	TCHAR lpstrFile[MAX_PATH] = TEXT("");
	TCHAR szFileTitle[MAX_PATH];
	TCHAR InitDir[MAX_PATH];


	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = hWnd;
		OFN.lpstrFilter = TEXT(
			"��� ����(*.*)\0*.*\0"
			"�ؽ�Ʈ ���� (*.txt)\0*.txt\0"
			"c �ҽ� ���� (*.c; *.h)\0*.c;*.h\0");
		OFN.nFilterIndex = 2;
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = MAX_PATH;
		OFN.lpstrTitle = TEXT("������ ������ �ֽʽÿ�");
		OFN.lpstrFileTitle = szFileTitle;
		OFN.nMaxFileTitle = MAX_PATH;
		OFN.lpstrDefExt = TEXT("abc");
		GetWindowsDirectory(InitDir, MAX_PATH);
		OFN.lpstrInitialDir = InitDir;

		if (GetOpenFileName(&OFN) != 0)
		{
			wsprintf(str, TEXT("%s ������ �����߽��ϴ�. ���ϸ��� %s �Դϴ�. ���ϸ� ������ %d, Ȯ���� ������ %d"),
				lpstrFile, szFileTitle, OFN.nFileOffset, OFN.nFileExtension);
			MessageBox(hWnd, str, TEXT("���� ���� ����"), MB_OK);
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

#endif // �ڵ常


#endif // Total