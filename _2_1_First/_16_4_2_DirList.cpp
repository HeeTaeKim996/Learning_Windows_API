#if 0 // Total
/*-------------------------------------------------------------------------------------------------------------------
	LB_DIR �� Ư�� �ּ� + ������ Ư�� �Ӽ��� ����+���͸��� ����Ʈ ��ҷ� ����ϴ� �ڵ��Դϴ�.
	
	�� LB_DIR
	 - (3)�� WPARAM �� �˻� ��� ����, (4)�� LPARAM �� [ �ּ� + ���� ] �Է½�, �ش� �ּ��� ������ ����Ʈ ��ҷ� �Է�
	  �� (3)�� WPARAM �÷��� �Ϻ� ����
	      - DDL_ARCHIVE		: ���Ͽ��� ��ī�̺� �Ӽ��� �ִ� ���ϵ鸸 �˻�. ��κ� ��ī�̺� �Ӽ��� ���ϴ�, ��κ� ������ �˻��Ѵ� �󺸸��
		  - DDL_DIRECTORY	: ���丮�� �˻�
		  - DDL_DRIVE		: ����̺� �� ������, -C-, -D- �������� ǥ��
		  - DDL_READWRITE	: ������ �б�-���� �Ӽ��� �ִ� ������ �˻�. ��κ��� �б�-���� �Ӽ��� ���ϴ�, ��κ� ������ �˻��Ѵ� �����


	 �� DlgDirSelectEx
	  - (4) HMENU �� ����Ʈ�� ��Ҹ�, (2) ��  TCHAR* �� �Ҵ�.���� (2) �� ���͸� �� �Ǵܵɽ�, BOOL TRUE ����. �ƴҽ�, FALSE ����

-------------------------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
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


#define ID_LISTBOX 100
HWND hList;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR File[MAX_PATH];
	TCHAR Mes[256];
	BOOL dir;


	switch (iMessage)
	{
	case WM_CREATE:
		hList = CreateWindow(TEXT("listbox"), NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_NOTIFY,
			10, 10, 300, 200,
			hWnd, (HMENU)ID_LISTBOX, g_hInst, NULL);
		SendMessage(hList, LB_DIR, (WPARAM)(DDL_ARCHIVE | DDL_DIRECTORY | DDL_DRIVES | DDL_READWRITE), (LPARAM)TEXT("c:\\Windows\\*.*"));
		
		return 0;
		

	case WM_LBUTTONDOWN:
		dir = DlgDirSelectEx(hWnd, File, MAX_PATH, ID_LISTBOX);
		if (lstrlen(File) != 0)
		{
			if (dir)
			{
				wsprintf(Mes, TEXT("%s ���丮�� �����߽��ϴ�."), File);
			}
			else
			{
				wsprintf(Mes, TEXT("%s ������ �����߽��ϴ�."), File);
			}

			MessageBox(hWnd, Mes, TEXT("�˸�"), MB_OK);
		}
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



#define ID_LISTBOX 100

HWND hList;


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR File[MAX_PATH];
	TCHAR Mes[256];
	BOOL dir;

	switch (iMessage)
	{
	case WM_CREATE:
		hList = CreateWindow(TEXT("listbox"), NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_NOTIFY,
			10, 10, 300, 200,
			hWnd, (HMENU)ID_LISTBOX, g_hInst, NULL);

		SendMessage(hList, LB_DIR, (WPARAM)(DDL_ARCHIVE | DDL_DIRECTORY | DDL_DRIVES | DDL_READWRITE),
			(LPARAM)TEXT("C:\\Windows\\*.*"));

		return 0;
		

	case WM_LBUTTONDOWN:
		dir = DlgDirSelectEx(hWnd, File, MAX_PATH, ID_LISTBOX);
		if (lstrlen(File) != 0)
		{
			if (dir)
			{
				wsprintf(Mes, TEXT("%s ���͸��� �����߽��ϴ�."), File);
			}
			else
			{
				wsprintf(Mes, TEXT("%s ������ �����߽��ϴ�"), File);
			}
			
			MessageBox(hWnd, Mes, TEXT("�˸�"), MB_OK);
		}
		
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // �ڵ常


#endif // Total