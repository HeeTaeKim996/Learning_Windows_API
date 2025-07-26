#if 1 // Total
/*----------------------------------------------------------------------------------------------------
	사용자 정의 메세지로 사용되는 DWORD 인 WM_USER, WM_APP, RegisterWindowMessage 에 대한 코드입니다.
	
	웬만함 WM_USER 만 알아도 문제 없습니다.
	
	WM_USER 는 0x400 으로, 0x400 이하의 DWORD 는 WM_CREATE, WM_LBUTTONDOWN 등 시스템 메세지로 사용되므로,
	사용하면 안됩니다. 
	
	따라서 사용자 정의 메세지를 사용할 때에, 
	#define WM_CUSTOM (WM_USER + n) 
	이런 방법으로 사용합니다

	이외에 WM_APP, RegisterWindowMessage는 알 필요는 없어도 될 것 같지만, 간략히 설명하면, 
	WM_APP == (DWORD) 0x8000
	RegisterWindowMessage 의 리턴값은, (DWORD)0xC000 ~ 0x10000 사이의 값을 리턴합니다.
	(문자열을 TEXT 형식으로 주면, 그에 대응하는 고유의 DWORD를 리턴)

	WM_APP 은 규약 같은 것으로, 엔진 같이 기초가 되는? 윈도우일시 WM_USER~ ~WM_APP 의 메세지를 사용하고,
	응용프로그램 윈도우는 WM_APP ~ 의 메세지를 사용하자는 규약입니다.

	RegisterWindowMessage 도 비슷한 개념으로, 서로 다른 어플리캐이션끼리 통신시 규약을 명확히 하기 위해,
	입력한 텍스트에 대응되는 고유한 DWORD를 리턴해주는 겁니다.

	정리하면, 웬만하면 #define WM_CUSTOM (WM_USER + n) 
	이렇게만 처리해도 문제 없습니다.


	※ 하단 코드 내용은, CMD 에서 인자 1 (Send) 2 (Recv) 로 윈도우 2개를 만들어 확인하는 코드입니다.

----------------------------------------------------------------------------------------------------*/


#if 1 // 주석
#include <Windows.h>

LRESULT CALLBACK SendProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK RecvProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;

LPCTSTR SendClass = TEXT("SendClass");
LPCTSTR RecvClass = TEXT("RecvClass");

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
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_VREDRAW | CS_HREDRAW;

	int intParam = atoi(lpszCmdParam);
	LPCTSTR registerClass = NULL;
	int xPos, yPos;
	switch(intParam)
	{
	case 1:
		registerClass = SendClass;
		WndClass.lpfnWndProc = SendProc;
		WndClass.lpszClassName = SendClass;
		xPos = yPos = 100;
		break;

	case 2:
		registerClass = RecvClass;
		WndClass.lpfnWndProc = RecvProc;
		WndClass.lpszClassName = RecvClass;
		xPos = 600;
		yPos = 100;
		break;

	default:
		MessageBox(NULL, TEXT("CMD 에서 1 또는 2 인자 입력"), TEXT("INFO"), MB_OK);
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

#define WM_FIRST (WM_USER + 1)
#define WM_SECOND (WM_APP + 1)
DWORD WM_THIRD;


LRESULT CALLBACK SendProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HWND recvWnd;

	switch (iMessage)
	{
	case WM_CREATE:
		WM_THIRD = RegisterWindowMessage(TEXT("TEST"));
		return 0;

	case WM_KEYDOWN:

		 recvWnd = FindWindow(RecvClass, NULL);
		if (!recvWnd) return 0;

		switch (wParam)
		{
		case 'A':
			SendMessage(recvWnd, WM_FIRST, 0, 0);
			break;

		case 'B':
			SendMessage(recvWnd, WM_SECOND, 0, 0);
			break;

		case 'C':
			SendMessage(recvWnd, WM_THIRD, 0, 0);
			break;
		}

		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}


LRESULT CALLBACK RecvProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HWND sendWnd;
	switch (iMessage)
	{
	case WM_CREATE:
		WM_THIRD = RegisterWindowMessage(TEXT("TEST"));
		return 0;

	case WM_FIRST:
		MessageBox(hWnd, TEXT("FIRST"), TEXT("INFO"), MB_OK);

		sendWnd = FindWindow(SendClass, NULL);
		if (sendWnd)
		{
			SetForegroundWindow(sendWnd);
		}
		return 0;

	case WM_SECOND:
		MessageBox(hWnd, TEXT("SECOND"), TEXT("INFO"), MB_OK);

		sendWnd = FindWindow(SendClass, NULL);
		if (sendWnd)
		{
			SetForegroundWindow(sendWnd);
		}
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;


	default:
		// ※ switch - case 는 컴파일 때 상수인 것만 사용 가능하므로, RegisterWindowMessage 로 받은
		//   DWORD 는 switch 가 아닌 if문에서 사용 가능함
		if (iMessage == WM_THIRD) 
		{
			MessageBox(hWnd, TEXT("THIRD"), TEXT("INFO"), MB_OK);

			sendWnd = FindWindow(SendClass, NULL);
			if (sendWnd)
			{
				SetForegroundWindow(sendWnd);
			}
			return 0;
		}
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}




#endif // 주석


#if 1 // 코드만


#endif // 코드만


#endif // Total