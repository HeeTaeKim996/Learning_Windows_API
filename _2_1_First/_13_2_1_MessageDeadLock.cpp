#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	메세지 데드락에 대한 코드입니다. SendMessage, PostMessage, InSendMessage - ReplyMessage,
	SendNotifyMessage, SendMessageTimeOut 에 대한 코드입니다.

	○ SendMessage	: 해당 윈도우에 즉시 호출 (데드락 발생 가능성)

	○ PostMessage	: 해당 윈도우의 메세지큐에 인풋 (데드락 방지)
					 (가장 무난할 듯 싶음. 유니티도 Update, FixedUpdate, LateUpdate 에 인풋하는 구조일테니)

	○ InSendMessage - ReplyMessage
	 : 메세지를 받는 쪽에서 데드락을 방지하는 구조.

	○ SendNotifyMessage		: 보내는 쪽에서, 락을 방지하는 SendMessage

	○ SendMessageTimeOut	: 지정한 시간을 지났을 때, 할당한 함수가 호출되는 메세지.



	※ 메세지 데드락을 테스트학 위해서는, 메인 윈도우 2개를 시행해야 하므로, F5, ctrl + F5로 시행할 때에는
	  메인 윈도우 하나만 만들 수 있으니, 
	  CMD 에서 C: ...( 주소) ... exe 1(2)  이렇게 exe 옆에 인자 1 또는 2 를 넘기는 방법으로 시행하도록
	  코드를 짰습니다

----------------------------------------------------------------------------------------------------*/


#if 1 // 주석
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

	int inputNumber = atoi(lpszCmdParam); // ※ atoi : 문자열을 정수로 변환
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
		MessageBox(NULL, TEXT("CMD 에서 정수 1 또는 2 를 입력하여 시행하세요"), TEXT("알림"), MB_OK);
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
		wsprintf(Mes, TEXT("프로그램 시작 %d 초 지났습니다"), ++time);
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
				// 마지막항에 함수를 넣어서, timeiut일시 추가 처리하는 함수를 만들어야 한다는데,
				// 귀찮아서 안함
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
		MessageBox(hWnd, TEXT("락을 잡는 메세지입니다."), TEXT("알림"), MB_OK);
		return 0;

	case WM_USER + 2:
		if (InSendMessage())
		{
			ReplyMessage(TRUE);
			MessageBox(hWnd, TEXT("락을 잡지 않고, 바로 리턴해주는 메세지입니다"), TEXT("알림"), MB_OK);
		}
		return 0;



	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}



#endif // 주석
























































































#if 0 // 코드만
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
		MessageBox(NULL, TEXT("CMD 에서 정수 1 또는 2 를 입력하여 시행하세요"), TEXT("알림"), MB_OK);
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
		wsprintf(Mes, TEXT("프로그램 시작 %d 초 지났습니다"), ++time);
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
				// 귀찮
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
		MessageBox(hWnd, TEXT("락을 잡는 메세지입니다"), TEXT("알림"), MB_OK);
		return 0;

	case WM_USER + 2:
		if (InSendMessage())
		{
			ReplyMessage(TRUE);
			MessageBox(hWnd, TEXT("락을 잡지 않고, 바로 리턴해주는 메세지입니다"), TEXT("알림"), MB_OK);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}











#endif // 코드만


#endif // Total