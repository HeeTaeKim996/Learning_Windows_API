#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	�޼��� ������� ���� �ڵ��Դϴ�. SendMessage, PostMessage, InSendMessage - ReplyMessage,
	SendNotifyMessage, SendMessageTimeOut �� ���� �ڵ��Դϴ�.

	�� SendMessage	: �ش� �����쿡 ��� ȣ�� (����� �߻� ���ɼ�)

	�� PostMessage	: �ش� �������� �޼���ť�� ��ǲ (����� ����)
					 (���� ������ �� ����. ����Ƽ�� Update, FixedUpdate, LateUpdate �� ��ǲ�ϴ� �������״�)

	�� InSendMessage - ReplyMessage
	 : �޼����� �޴� �ʿ��� ������� �����ϴ� ����.

	�� SendNotifyMessage		: ������ �ʿ���, ���� �����ϴ� SendMessage

	�� SendMessageTimeOut	: ������ �ð��� ������ ��, �Ҵ��� �Լ��� ȣ��Ǵ� �޼���.



	�� �޼��� ������� �׽�Ʈ�� ���ؼ���, ���� ������ 2���� �����ؾ� �ϹǷ�, F5, ctrl + F5�� ������ ������
	  ���� ������ �ϳ��� ���� �� ������, 
	  CMD ���� C: ...( �ּ�) ... exe 1(2)  �̷��� exe ���� ���� 1 �Ǵ� 2 �� �ѱ�� ������� �����ϵ���
	  �ڵ带 ®���ϴ�

----------------------------------------------------------------------------------------------------*/


#if 1 // �ּ�
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LockProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;

LPCTSTR lpszClass = TEXT("Learning_DeadLock");
LPCTSTR lockClass = TEXT("LockClass");

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
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_VREDRAW | CS_HREDRAW;

	int inputNumber = atoi(lpszCmdParam); // �� atoi : ���ڿ��� ������ ��ȯ
	LPCTSTR regisetrClass;
	int xPos, yPos;
	switch (inputNumber)
	{
	case 1:
		WndClass.lpfnWndProc = WndProc;
		WndClass.lpszClassName = lpszClass;
		regisetrClass = lpszClass;
		xPos = 100;
		yPos = 100;

		break;

	case 2:
		WndClass.lpfnWndProc = LockProc;
		WndClass.lpszClassName = lockClass;
		regisetrClass = lockClass;
		xPos = 600;
		yPos = 100;


		break;

	default:
		MessageBox(NULL, TEXT("CMD ���� ���� 1 �Ǵ� 2 �� �Է��Ͽ� �����ϼ���"), TEXT("�˸�"), MB_OK);
		return 0;
	}

	RegisterClass(&WndClass);

	hWnd = CreateWindow(regisetrClass, regisetrClass, WS_OVERLAPPEDWINDOW,
		xPos, yPos, 400, 300,
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
	static int time;

	switch (iMessage)
	{
	case WM_CREATE:

		time = 0;
		SetTimer(hWnd, 0, 1'000, 0);
		return 0;

	case WM_TIMER:
		hdc = GetDC(hWnd);

		TCHAR Mes[128];
		wsprintf(Mes, TEXT("���α׷� ���� %d �� �������ϴ�"), ++time);
		TextOut(hdc, 100, 100, Mes, lstrlen(Mes));

		ReleaseDC(hWnd, hdc);

		return 0;

	case WM_LBUTTONDOWN:
	{
		HWND lockHwnd = FindWindow(lockClass, NULL);
		if (lockHwnd)
		{
			SendMessage(lockHwnd, WM_USER + 1, 0, 0);
		}

		return 0;
	}

	case WM_RBUTTONDOWN:
	{
		HWND lockHwnd = FindWindow(lockClass, NULL);
		if (lockHwnd)
		{
			PostMessage(lockHwnd, WM_USER + 1, 0, 0);
		}

		return 0;
	}

	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'A':
		{
			HWND lockHwnd = FindWindow(lockClass, NULL);
			if (lockHwnd)
			{
				SendMessage(lockHwnd, WM_USER + 2, 0, 0);
			}
			break;
		}


		case 'B':
		{

			HWND lockHwnd = FindWindow(lockClass, NULL);
			if (lockHwnd)
			{
				SendNotifyMessage(lockHwnd, WM_USER + 1, 0, 0);
			}
			break;
		}

		case 'C':
		{
			HWND lockHwnd = FindWindow(lockClass, NULL);
			if (lockHwnd)
			{
				SendMessageTimeout(lockHwnd, WM_USER + 1, 0, 0, NULL, 1'000, NULL);
				// �������׿� �Լ��� �־, timeiut�Ͻ� �߰� ó���ϴ� �Լ��� ������ �Ѵٴµ�,
				// �����Ƽ� ����
			}
			break;

		}
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));


}


LRESULT CALLBACK LockProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_USER + 1:
		MessageBox(hWnd, TEXT("���� ��� �޼����Դϴ�."), TEXT("�˸�"), MB_OK);
		return 0;

	case WM_USER + 2:
		if (InSendMessage())
		{
			ReplyMessage(TRUE);
			MessageBox(hWnd, TEXT("���� ���� �ʰ�, �ٷ� �������ִ� �޼����Դϴ�"), TEXT("�˸�"), MB_OK);
		}
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
LRESULT CALLBACK LockProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;

LPCTSTR lpszClass = TEXT("Learning_DeadLock");
LPCTSTR lockClass = TEXT("LockClass");

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
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_VREDRAW | CS_HREDRAW;

	int inputNumber = atoi(lpszCmdParam);
	LPCTSTR registerClass;
	int xPos, yPos;
	switch (inputNumber)
	{
	case 1:
		WndClass.lpfnWndProc = WndProc;
		WndClass.lpszClassName = lpszClass;
		registerClass = lpszClass;
		xPos = yPos = 100;

		break;


	case 2:
		WndClass.lpfnWndProc = LockProc;
		WndClass.lpszClassName = lockClass;
		registerClass = lockClass;
		xPos = 600;
		yPos = 100;

		break;


	default:
		MessageBox(NULL, TEXT("CMD ���� ���� 1 �Ǵ� 2 �� �Է��Ͽ� �����ϼ���"), TEXT("�˸�"), MB_OK);
		return 0;
	}



	RegisterClass(&WndClass);

	hWnd = CreateWindow(registerClass, registerClass, WS_OVERLAPPEDWINDOW,
		xPos, yPos, 400, 300,
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
	static int time;
	HWND lockHwnd;


	switch (iMessage)
	{
	case WM_CREATE:
		time = 0;
		SetTimer(hWnd, 0, 1'000, 0);
		return 0;

	case WM_TIMER:
		hdc = GetDC(hWnd);

		TCHAR Mes[128];
		wsprintf(Mes, TEXT("���α׷� ���� %d �� �������ϴ�"), ++time);
		TextOut(hdc, 100, 100, Mes, lstrlen(Mes));

		ReleaseDC(hWnd, hdc);

		return 0;

	case WM_LBUTTONDOWN:
		lockHwnd = FindWindow(lockClass, NULL);
		if (lockHwnd)
		{
			SendMessage(lockHwnd, WM_USER + 1, 0, 0);
		}
		return 0;

	case WM_RBUTTONDOWN:
		lockHwnd = FindWindow(lockClass, NULL);
		if (lockHwnd)
		{
			PostMessage(lockHwnd, WM_USER + 1, 0, 0);
		}
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'A':
			lockHwnd = FindWindow(lockClass, NULL);
			if (lockHwnd)
			{
				SendMessage(lockHwnd, WM_USER + 2, 0, 0);
			}
			break;


		case 'B':
			lockHwnd = FindWindow(lockClass, NULL);
			if (lockHwnd)
			{
				SendNotifyMessage(lockHwnd, WM_USER + 1, 0, 0);
			}
			break;

		case 'C':
			lockHwnd = FindWindow(lockClass, NULL);
			if (lockHwnd)
			{
				//SendMessageTimeout 
				// ����
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



LRESULT CALLBACK LockProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_USER + 1:
		MessageBox(hWnd, TEXT("���� ��� �޼����Դϴ�"), TEXT("�˸�"), MB_OK);
		return 0;

	case WM_USER + 2:
		if (InSendMessage())
		{
			ReplyMessage(TRUE);
			MessageBox(hWnd, TEXT("���� ���� �ʰ�, �ٷ� �������ִ� �޼����Դϴ�"), TEXT("�˸�"), MB_OK);
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