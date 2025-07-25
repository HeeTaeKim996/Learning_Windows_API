#if 0 // Total
/*----------------------------------------------------------------------------------------------------
     �ؽ�Ʈ �Է� �������� Edit�� ���� �ڵ��Դϴ�. ���ӻ��� ���� ���� �� �����ϴ�.
	 �߰���, Edit�� ��� �ܿ�, ���ݱ��� ��� Button, Edit �� ��� �������̱� ������,
	 Edit�� MoveWindow, HideWindow �� �������� �ڵ�� ���Դϴ�.

	 Buttom, Edit�� �������̱� ������, ��ü�� WinMain, WndProc, SendMessage �� ��ü�� ó���մϴ�
----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_Edit");

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
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
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

#define ID_EDIT 100
HWND hEdit;
int nTop = 10;
BOOL bShow = TRUE;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[128];

	const TCHAR* Mes = TEXT("Up_DownArrow : ����Ʈ���Ʒ��̵�. Space : ����/����");

	switch (iMessage)
	{
	case WM_CREATE:
		hEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 10, 200, 25,
			hWnd, (HMENU)ID_EDIT, g_hInst, NULL);
		/* �� 3�� ES ENUM
			- ES_AUTOHSCROLL	: ���� ��ũ���� ����
			- ES_AUTOVSCROLL	: ���� �� ������ ���� ��ũ���� ����
			- ES_LEFT			: ���� ����
			- ES_CENTER			: �߾� ����
			- ES_RIGHT			: ������ ����
			- ES_LOWERCASE		: �ҹ��ڷ� ��ȯ�Ͽ� ǥ��
			- ES_UPPDERCASE		: �빮�ڷ� ��ȯ�Ͽ� ǥ��
			- ES_MULTILINE		: ���� ���� ���� ����
			- ES_NOHIDESEEL		: ��Ŀ���� �Ҵ��� ���õ� ������ ǥ��
			- ES_READONLY		: �б� �������� ����� ������ ����
		*/
		SetWindowText(hEdit, TEXT("����Ʈ�� �������. ���� Ŭ���ϸ� �ؽ�Ʈ ���� ����"));

		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_EDIT:
			switch (HIWORD(wParam))
			{
				/* �� EN ENUM
					- EN_CHANGE		: ���ڿ��� �����
					- EN_ERRSPACE	: �޸𸮰� ����
					- EN_HSCROLL	: ����ڰ� ���� ��ũ�� �ٸ� Ŭ��
					- EN_VSCROLL	: ����ڰ� ���� ��ũ�� �ٸ� Ŭ��
					- EN_KILLFOCUS	: ��Ŀ���� �Ҿ���
					- EN_SETFOCUS	: ��Ŀ���� �����
					- EN_MAXTEXT	: ������ ���ڿ� ���̸� �ʰ��Ͽ���
					- EN_UPDATE		: ���ڿ��� ����Ǳ� �����̴�
					 �� EN_CHANGE �� EN_UPDATE�� ���̴�,
					   EN_CHANGE �� ���ڿ��� ȭ�鿡�� ����� ����,
					   EN_UPDATE �� ���ڿ��� ȭ�鿡�� ����Ǳ� ����
					   -> �� ����� ���� ���� ������, ���� �� �� �ϳ� ���. �ַ� EN_CHAGE ���
				*/
			case EN_CHANGE:
				GetWindowText(hEdit, str, 128); // �� Get���� str ����. str�� �迭 �Ǵ� ���������״�.. &���� ����.
				SetWindowText(hWnd, str); // �� (1)�� HWND�� lpWindowName �� ����� str�� ��ü�Ѵ�
				break;
			}

			break;
		}

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			nTop -= 10;
			MoveWindow(hEdit, 10, nTop, 220, 25, TRUE);
			break;
		case VK_DOWN:
			nTop += 10;
			MoveWindow(hEdit, 10, nTop, 220, 25, TRUE);
			break;

		case VK_SPACE:
			if (bShow)
			{
				bShow = FALSE;
				ShowWindow(hEdit, SW_HIDE);
			}
			else
			{
				bShow = TRUE;
				ShowWindow(hEdit, SW_SHOW);
			}
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


#if 1 // �ڵ常
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_Edit");

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
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
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

#define ID_EDIT 100
HWND hEdit;
int nTop = 10;
BOOL bShow = TRUE;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[128];

	const TCHAR* Mes = TEXT("Up_DownArrow : ���������Ʒ� �̵�. Space : ����/����");

	switch (iMessage)
	{
	case WM_CREATE:
		hEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 10, 200, 25,
			hWnd, (HMENU)ID_EDIT, g_hInst, NULL);
		SetWindowText(hEdit, TEXT("����Ʈ�� �������. ���� Ŭ���ϸ� �ؽ�Ʈ ���� ����"));

		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_EDIT:
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
				GetWindowText(hEdit, str, 128);
				SetWindowText(hWnd, str);
				break;
			}

			break;
		}

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			nTop -= 10;
			MoveWindow(hEdit, 10, nTop, 220, 25, TRUE);
			break;
		case VK_DOWN:
			nTop += 10;
			MoveWindow(hEdit, 10, nTop, 220, 25, TRUE);
			break;
		case VK_SPACE:
			if (bShow)
			{
				bShow = FALSE;
				ShowWindow(hEdit, SW_HIDE);
			}
			else
			{
				bShow = TRUE;
				ShowWindow(hEdit, SW_SHOW);
			}
			break;
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