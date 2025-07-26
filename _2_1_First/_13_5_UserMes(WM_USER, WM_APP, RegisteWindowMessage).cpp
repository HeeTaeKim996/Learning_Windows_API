#if 1 // Total
/*----------------------------------------------------------------------------------------------------
	����� ���� �޼����� ���Ǵ� DWORD �� WM_USER, WM_APP, RegisterWindowMessage �� ���� �ڵ��Դϴ�.
	
	������ WM_USER �� �˾Ƶ� ���� �����ϴ�.
	
	WM_USER �� 0x400 ����, 0x400 ������ DWORD �� WM_CREATE, WM_LBUTTONDOWN �� �ý��� �޼����� ���ǹǷ�,
	����ϸ� �ȵ˴ϴ�. 
	
	���� ����� ���� �޼����� ����� ����, 
	#define WM_CUSTOM (WM_USER + n) 
	�̷� ������� ����մϴ�

	�̿ܿ� WM_APP, RegisterWindowMessage�� �� �ʿ�� ��� �� �� ������, ������ �����ϸ�, 
	WM_APP == (DWORD) 0x8000
	RegisterWindowMessage �� ���ϰ���, (DWORD)0xC000 ~ 0x10000 ������ ���� �����մϴ�.
	(���ڿ��� TEXT �������� �ָ�, �׿� �����ϴ� ������ DWORD�� ����)

	WM_APP �� �Ծ� ���� ������, ���� ���� ���ʰ� �Ǵ�? �������Ͻ� WM_USER~ ~WM_APP �� �޼����� ����ϰ�,
	�������α׷� ������� WM_APP ~ �� �޼����� ������ڴ� �Ծ��Դϴ�.

	RegisterWindowMessage �� ����� ��������, ���� �ٸ� ���ø�ĳ�̼ǳ��� ��Ž� �Ծ��� ��Ȯ�� �ϱ� ����,
	�Է��� �ؽ�Ʈ�� �����Ǵ� ������ DWORD�� �������ִ� �̴ϴ�.

	�����ϸ�, �����ϸ� #define WM_CUSTOM (WM_USER + n) 
	�̷��Ը� ó���ص� ���� �����ϴ�.


	�� �ϴ� �ڵ� ������, CMD ���� ���� 1 (Send) 2 (Recv) �� ������ 2���� ����� Ȯ���ϴ� �ڵ��Դϴ�.

----------------------------------------------------------------------------------------------------*/


#if 1 // �ּ�
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
		MessageBox(NULL, TEXT("CMD ���� 1 �Ǵ� 2 ���� �Է�"), TEXT("INFO"), MB_OK);
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
		// �� switch - case �� ������ �� ����� �͸� ��� �����ϹǷ�, RegisterWindowMessage �� ����
		//   DWORD �� switch �� �ƴ� if������ ��� ������
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




#endif // �ּ�


#if 1 // �ڵ常


#endif // �ڵ常


#endif // Total