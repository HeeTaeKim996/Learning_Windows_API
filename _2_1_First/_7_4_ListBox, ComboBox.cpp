#if 0 // Total
/*----------------------------------------------------------------------------------------------------
   ����Ʈ�ڽ��� �޺��ڽ��� ���� �����Դϴ�.
   ����Ʈ �ڽ��� C#�� ����Ʈ�� �����ϸ�,
   �޺��ڽ��� Edit �� ����Ʈ�ڽ��� ��ģ �������,
   ������������ ���� ���� �����̴� ���ӻ��� ���� �� �����ϴ�
----------------------------------------------------------------------------------------------------*/


#if 0 // �ּ�
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_ListBox_ComoboBox");

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

/*---------------------------------------------------------------------------------------------------
	�� ����Ʈ�ڽ�
	�� ����
	 - ���������� �������� ����
	 - C#�� List�� ����
	   ( LB_ADDSTRING ���� �����͸� �߰�, LB_DELETESTRING ���� ����, LB_GETCURSEL �� ���� Ȱ��ȭ �ε���,
		 LB_GETTEXT�� �Ҵ��� �ε����� �ؽ�Ʈ�� �ҷ����� ��..  )

	�� LBS (ENUM) - ����Ʈ �ڽ��� ������ �� ����ϴ� �̳�
	 - LBS_MULTIPLESEL	: ���� ���� �׸��� ������ �� ����. ( ����Ʈ�δ� �ϳ��� ���� ������ )
	 - LBS_NOTIFY		: ����ڰ� ��� �� �ϳ��� �������� ��, �θ� ������� �뺸 �޼��� (���� �ʼ��� ���)
	 - LBS_SORT			: �߰��� �׸���� �ڵ� ����
	 - LBS_OWNERDRAW	: ���ڿ��� �ƴ� ��Ʈ���̳� �׸��� ���� �� �ִ�
	 - LBS_STANDARD		: LBS_NOTIFY | LBS_SORT | WS_BORDER

	  => LBS_NOTIFY �� ���� �ʼ�. LOBS_SORT �� LBS_MULTIPLE �� ��Ȥ ���

	�� LB (ENUM) - �ַ� �θ� ������ -> ����Ʈ�ڽ� ������ �� SendMessage �� ����ϴ� ENUM
	 - LB_ADDSTRING		: ����Ʈ �ڽ��� �׸��� �߰�. LPARAM�� TCHAR [] �� LPARAM���� ����ȯ�Ͽ� �Ѱ���
	 - LB_DELETESTRING	: �׸��� ����. WPARAM�� ������ �׸� ��ȣ�� �Ѱ��ָ�, ���� �׸���� ���Ϲ���
	 - LB_GETCURSEL		: ���� ���õ� �׸��� ��ȣ �� ���Ϲ޴´�
	 - LB_GETTEXT		: �׸��ȣ�� �Ѱ��ָ�, �ش� �ε����� �׸��� ���Ϲ޴´�.
						  WPARAM ���� �׸��ȣ. LPARAM���� �׸� �����͸� ��� ���� TCHAR[] �� LPARAM ����ȯ�Ͽ� �Ѱ���
	 - LB_GETCOUNT		: �׸��� ������ ����
	 - LB_SETCURSEL		: WPARAM �� �ε����� �Ѱ��ش�. ����Ʈ �ڽ� ������� �ش� �ε����� '����' �Ѵ�

	�� LBN (ENUM) - ����Ʈ�ڽ� ������ -> �θ� ������� ������ �޼����� �ĺ� �̳�. HIWORD(WPARAM) ���� �ĺ�
	 - LBN_DBLCLK		: ����Ʈ �ڽ��� ����Ŭ���Ͽ����� �뺸
	 - LBN_ERRSPACE		: �޸� ���� �뺸
	 - LBN_KILLFOCUS	: Ű���� ��Ŀ���� �Ҿ���
						 ( ����Ʈ�ڽ��� Tab Ű�� ������ ������ �� �ִ� ���¸� Ű���� ��Ŀ�� ���¶� �Ѵ�.
						   �ַ� ����Ʈ�ڽ��� ���콺 Ŭ�� �� Ȱ��ȭ)
	 - LBN_SELCANCEL	: ����ڰ� ������ �g���ߴ�
	 - LBN_SELCHANGE	: ����ڰ� ������ �����ߴ�
	 - LBN_SETFOCUS		: Ű���� ��Ŀ���� �����


	 �� �޺��ڽ�
	 �� ����
	  - �ռ� Edit��, ����Ʈ�ڽ��� ��ģ ����
	  - Editó��, �ڽ��� Ŭ���ϸ� ���ڿ� �Է� �� Edit ó�� ó�� ����
	  - �ڽ� ���� �Ʒ� ȭ��ǥ Ŭ����, ����Ʈ�ڽ�ó�� �̸� �غ��� ��ҵ��� �����ǰ�, �ش� ��Ҹ� ���� ����
	  - ENUM �� ����, ����Ʈ �ڽ��� �ſ� ����. LBS -> CBS, LB -> CB, LBN -> CBN ����, ���� ������
		����Ʈ �ڽ��� �ſ� ������

	 �� CBS (�Ϻ�)
	  - CBS_SIMPLE			: ����Ʈ�� ����Ʈ �ڽ��� ������, ����Ʈ �ڽ��� �׻� ������ �ִ�
	  - CBS_DROPDOWN		: ����Ʈ�� ����Ʈ �ڽ��� ������
	  - CBS_DROPDOWNLIST	: ����Ʈ�ڽ��� ������, ����Ʈ�� �׸��� �Է��� �� ���� (�̷� ����Ʈ�ڽ� ���� �־���..)
---------------------------------------------------------------------------------------------------*/

#define ID_LISTBOX 100
HWND hList;

#define ID_COMBOBOX 101
HWND hCombo;

const TCHAR* Items[] = { TEXT("Apple"), TEXT("Orange"), TEXT("Melon"), TEXT("Grape"), TEXT("Strawberry") };


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[128];

	switch (iMessage)
	{
	case WM_CREATE:
	{ // ����Ʈ�ڽ�
		hList = CreateWindow(TEXT("listBox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,
			10, 10, 100, 200,
			hWnd, (HMENU)ID_LISTBOX, g_hInst, NULL);
		for (int i = 0; i < 5; i++)
		{
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)Items[i]);
		}
	}

	{ // �޺� �ڽ�
		hCombo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,
			600, 10, 100, 200,
			hWnd, (HMENU)ID_COMBOBOX, g_hInst, NULL);
		for (int i = 0; i < 5; i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)Items[i]);
		}
	}


	return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_LISTBOX: // ����Ʈ�ڽ�
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
			{

				int i = SendMessage(hList, LB_GETCURSEL, 0, 0);
				SendMessage(hList, LB_GETTEXT, i, (LPARAM)str);
				SetWindowText(hWnd, str);

				break;
			}
			break;
			}

		case ID_COMBOBOX: // �޺� �ڽ�
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				int i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
				SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)str);
				SetWindowText(hWnd, str);

				break;
			}
			case CBN_EDITCHANGE:
				GetWindowText(hCombo, str, 128);
				SetWindowText(hWnd, str);

				break;

			case CBN_KILLFOCUS:
				GetWindowText(hCombo, str, 128);

				if (SendMessage(hCombo, CB_FINDSTRINGEXACT, -1, (LPARAM)str) == CB_ERR)
					// �� (3)�� n + 1 �ε������� ��ȸ. -1�Ͻ�, �ε��� 0���� ��ȸ�� ��ü ��ȸ. 
					// �� CB_ERR == -1. CB���� Find�� ���н�, -1 ��ȯ
				{
					SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)str);
				}


				break;
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
LPCTSTR lpszClass = TEXT("Learning_ListBox_ComoboBox");

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
	WndClass.hIcon = LoadCursor(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_VREDRAW | CS_HREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, g_hInst, NULL);
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

#define ID_COMBOBOX 101
HWND hCombo;

const TCHAR* Items[] = { TEXT("Apple"), TEXT("Orange"), TEXT("Melon"), TEXT("Grape"), TEXT("Strawberry") };

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[128];

	switch (iMessage)
	{
	case WM_CREATE:
	{ 
		{ // ListBox
			hList = CreateWindow(TEXT("listBox"), NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY,
				10, 10, 100, 200,
				hWnd, (HMENU)ID_LISTBOX, g_hInst, NULL);
			for (int i = 0; i < 5; i++)
			{
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)Items[i]);
			}
		}

		{ // ComboBox
			hCombo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,
				600, 10, 100, 200,
				hWnd, (HMENU)ID_COMBOBOX, g_hInst, NULL);
			for (int i = 0; i < 5; i++)
			{
				SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)Items[i]);
			}
		}

		return 0;
	}

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_LISTBOX: // ListBox
		{
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
			{
				int i = SendMessage(hList, LB_GETCURSEL, 0, 0);
				SendMessage(hList, LB_GETTEXT, i, (LPARAM)str);
				SetWindowText(hWnd, str);

				break;
			}

			}
			break;
		}

		case ID_COMBOBOX: // ComboBox
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				int i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
				SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)str);
				SetWindowText(hWnd, str);

				break;
			}
				

			case CBN_EDITCHANGE:
				GetWindowText(hCombo, str, 128);
				SetWindowText(hWnd, str);
				
				break;

			case CBN_KILLFOCUS:
				GetWindowText(hCombo, str, 128);

				if (SendMessage(hCombo, CB_FINDSTRINGEXACT, -1, (LPARAM)str) == CB_ERR)
				{
					SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)str);
				}

				break;
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