#if 1 // Total
/*----------------------------------------------------------------------------------------------------
	�� ���͸� �˻� �� string ��ȯ �ڵ�	
	 - Ȯ���ڰ� ������ �ƴ�, ���͸� ������ �����ϰ�, �ش� �ּҸ� ���ڿ��� ��ȯ�ϴ� �ڵ��Դϴ�.
	 - ������ Ÿ��, �Լ��� ���Ƽ�, �����ϰ� ���������� ���߰�, ����Ƽ�� �������� �뷫������ ��� ���ư��� ����
	   ������ �����߰�, ������ ������ ����߽��ϴ�.
	 - �۵� �������, �ڵ带 �����մϴ�.

	�� SHBrowseForFolder
	 - ����ڰ� ������ ������ �� �ִ� Ž���� â�� ����ִ� �Լ�
	 - ���ϰ����� ������ ������ ��Ÿ���� LPITEMIDLIST �� ��ȯ

	�� BROWSEINFO
	 - SHBrowseForFolder �� ���޵Ǵ� �Ű�������, ���� ���� ��ȭ������ ������ ����
	 - hwndOwner		: ��ȭ������ �θ� ������
	 - pidlRoot			: ?
	 - pszDisplayName	: ?
	 - lpszTitle		: ��ܿ� ǥ���� Ÿ��Ʋ
	 - uFlags			: ��ȭ������ ���� �ɼ�
	 - lpfn				: �ݹ��Լ��� ������. SHBrowseForFolder �� BROWSEINFO �� lfpn �� �Ҵ�ɽ�, SHBroweForFolder
						  ȣ�� �ʱ���, ��ȭ���� �ʱ�ȭ �� lpfn �� �Ҵ�� �Լ��� ȣ��. ȣ���ϴ� �Լ��� (4)�׿���,
						  �ٷ� �ؿ� �����ϴ� lParam �� ���ڷ� �־� ȣ��.
	 - lParam			: �ݹ��Լ��� (4)�׿� �Էµ� ����
	 
	 �� BroweCallbackProc
	  - ���� BrowseInfo�� lpfn ���� �����ߵ�, SHBorwseForFolder ���� ��ȭ���� �ʱ�ȭ �� ȣ��ǵ��� �ϴ� �Լ�
	  - �Ʒ� �ڵ忡���� BROWSEINFO �� lParam ���ڷ� ���� StartPath (TCHAR[]) �� ��ȭ������ �ʱ� ��η� �����ϴ� ����

	 �� SHGetPathFromIDList
	  - SHBrowseForFolder �� ��ȯ�� LPITEMIDLIST ��, ���� ��� ���ڿ��� ��ȯ�ϴ� �Լ�
	   
	 �� SHGetMalloc
	  - ??? �̺κ��� ���ظ���.. @@@@@@@@ ���� �߰�����!!!

	  �� ����Ƽ �߰� ���� ���� ����!! @@@@@@@@@@@@@@@@@
	  1) SH �� WND�� �ϳ��� �Ҵ�ǳ�? ��� SHBrowseForFolder �� �ߴµ�, 
		  SHGetMalloc ���� ��ȿ? �߾������� �Ǵ��� �� �ִ���.

	  2) BROWSEINFO �� pidlRoot, pszDisplayName

	  3) BFFM_INITAILIZED �� ȣ��Ǵ� Ÿ���� ���� �����ϰ��� ( ��ȭ���ڰ� �ʱ�ȭ �� �� ) �׷��ٸ�, hWnd (�θ� WND)  �� 
	     SendMEssage��  BFFM_SETSELECTION �� ȣ���, lpData �� StartPath
	     (TCHAR[] ) �� ���ڷ�, SendMessage �ϸ�, ��� ��ȭ���ڰ� StartPath�� �ʱⰪ�� ���� ���·� ������ �� �ִ� ����? 
		 BFFM_SETSELECTION �� ó���ϴ� �ڵ尡 ��� �ֳ�? #include <SHlob.h> �� �ִ°ǰ�?

----------------------------------------------------------------------------------------------------*/


#if 1 // �ּ�
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Sample_2");
HWND hWndMain;

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


#include <Shlobj.h>
BOOL BrowseFolder(HWND hParent, LPCTSTR szTitle, LPCTSTR StartPath, TCHAR* szFolder);


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR* Mes = TEXT("���� ���콺 ��ư�� ���� ������ �����Ͻÿ�.");
	static TCHAR StartPath[MAX_PATH];
	TCHAR Folder[MAX_PATH];


	switch (iMessage)
	{
	case WM_CREATE:
		hWndMain = hWnd;
		return 0;

	case WM_LBUTTONDOWN:
		if (BrowseFolder(hWnd, TEXT("������ �����Ͻÿ�"), StartPath, Folder))
		{
			MessageBox(hWnd, Folder, TEXT("������ ����"), MB_OK);
			lstrcpy(StartPath, Folder);
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

int CALLBACK BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch (uMsg)
	{
	case BFFM_INITIALIZED:
		if (lpData != NULL)
		{
			SendMessage(hWnd, BFFM_SETSELECTION, TRUE, (LPARAM)lpData);
		}
		break;
	}
	return 0;
}

BOOL BrowseFolder(HWND hParent, LPCTSTR szTitle, LPCTSTR StartPath, TCHAR* szFolder)
{
	LPMALLOC pMalloc;
	LPITEMIDLIST pidl;
	BROWSEINFO bi;

	bi.hwndOwner = hParent;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = NULL;
	bi.lpszTitle = szTitle;
	bi.ulFlags = 0;
	bi.lpfn = BrowseCallbackProc;
	bi.lParam = (LPARAM)StartPath;

	pidl = SHBrowseForFolder(&bi);

	if (pidl == NULL)
	{
		return FALSE;
	}

	SHGetPathFromIDList(pidl, szFolder);

	if (SHGetMalloc(&pMalloc) != NOERROR)
	{
		return FALSE;
	}

	pMalloc->Free(pidl);
	pMalloc->Release();
	return TRUE;
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