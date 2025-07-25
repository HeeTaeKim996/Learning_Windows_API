#if 0 // Total
/*--------------------------------------------------------
	  TextOut���� lstrlen, SetTextAlign, wsprintf�� ���� ���ڿ� ���.
	  DrawText�� Ȱ���� ���ڿ� ��¿� ���� �����Դϴ�
--------------------------------------------------------*/

#if 0 // �ּ�
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("DrawText");

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
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
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


//#define UsingTextOut
//#define UsingDrawText
#define Using_wsprintf

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

#ifdef UsingTextOut
	const TCHAR* st1 = TEXT("Hary is Cute");
	const TCHAR* st2 = TEXT("bori is Also Cute");
	const TCHAR* st3 = TEXT("need to Clean Teeth");
#endif



#ifdef UsingDrawText
	RECT rt = { 20, 20, 300, 200 };
	const TCHAR* st = TEXT("���� �����ϴ�. �ƾ� ����ϴ� ���� ���� �����ϴ�. Ǫ�� ����� "
		"��ġ�� ��ǳ���� ���� ���Ͽ� �� ���� ���� �ɾ ���� ��ġ�� �����ϴ�."
		"Ȳ���� �ɰ��� ���� ������ �� �ͼ��� ������ Ƽ���� �Ǿ� �Ѽ��� ��ǳ�� "
		"���ư����ϴ�.");
#endif

#ifdef Using_wsprintf
	TCHAR st[200];
	wsprintf(st, TEXT("%d �Դϴ�"), 10);
	/* �� wsprintf
	    - ���ڿ� �ܿ� �������� ���ڿ��� ����Ϸ���, wsprintf�� ���ڿ��� �������� �Է� �� ���ڿ� �߷�
		- ���� TCHAR instnace[n] ���� ������ �ִ밪�� 1024�� ����. 
	*/
#endif


	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:

#ifdef UsingTextOut
		hdc = BeginPaint(hWnd, &ps);
		SetTextAlign(hdc, TA_TOP | TA_LEFT );
		/* �� SetTextAlgin
		    - TA_TOP		: ���� ��� ����
			- TA_BOTTOM		: ���� �ϴ� ����
			- TA_CENTER		: ���� �߾� ����
			- TA_LEFT		: ���� ���� ����
			- TA_RIGHT		: ���� ���� ����
			- TA_UPDATECP	: CP�� ����Ͽ� ���ڿ� ���. ���ڿ� ��� ��, CP�� ���ڿ� �� ��ġ
			- TA_NOUPDATECP : CP�� ������� �ʰ�, ���� ��ǥ ���. ( ����Ʈ�� ���� ! )
		
			 �� CP : �׷��� ��� �� ����ϴ� ��ǥ. HDC���� ���. TA_UPDATECP ����, CP�� ��ǥ�� ����Ͽ�, 
			         �ϴ� TextOut�� (2), (3) �� �Է��� ��ǥ�� ��ȿ���� ����

			 �� TA_VCENTER�� ����. ���� �߾� ���� ������ (��..)
		*/


		TextOut(hdc, 20, 20, st1, lstrlen(st1));
		TextOut(hdc, 20, 40, st2, lstrlen(st2));
		TextOut(hdc, 20, 60, st3, lstrlen(st3));
		EndPaint(hWnd, &ps);
		return 0;
#endif


#ifdef UsingDrawText
		hdc = BeginPaint(hWnd, &ps);
		DrawText(hdc, st, -1, &rt, DT_LEFT | DT_TOP | DT_WORDBREAK);
		/* �� DrawText
		    - (3) : ����� ���ڿ� ��. -1�Ͻ�, \0���� ���ڿ� ���� �ڵ� ���
		    �� (4)
			 - DT_LEFT			: ���� ���� ����
			 - DT_RIGHT			: ���� ������ ����
			 - DT_CENTER		: ���� �߾� ����
			 - DT_BOTTOM		: ���� �ٴ� ����
			 - DT_VCENTER		: ���� �߾� ����
			 - DT_TOP			: ���� ���� ����
			 - DT_WORKDBREAK	: �簢���� ������ ������ �ڵ� ����
			 - DT_SINGLELINE	: �� �ٷ� ���
			 - DT_NOCLIP		: �簢������ ��踦 ����� ���ڿ��� �ڸ��� �ʰ� �״�� ���
		*/

		EndPaint(hWnd, &ps);
		return 0;
#endif


#ifdef Using_wsprintf
		hdc = BeginPaint(hWnd, &ps);
		SetTextAlign(hdc, TA_TOP | TA_LEFT);
		TextOut(hdc, 20, 20, st, lstrlen(st));
		EndPaint(hWnd, &ps);
		return 0;
#endif
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}




#endif // �ּ�

#if 1 // �ڵ常
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("DrawText");

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
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
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

//#define UsingTextOut
//#define UsingDrawText
#define Using_wsprintf

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

#ifdef UsingTextOut
	const TCHAR* st1 = TEXT("Harry is Cute");
	const TCHAR* st2 = TEXT("Bori is Also Cute");
	const TCHAR* st3 = TEXT("need to Clean Teeth");
#endif

#ifdef UsingDrawText
	RECT rt = { 20, 20, 400, 200 };
	const TCHAR* st = TEXT("���� �����ϴ�. �ƾ� ����ϴ� ���� ���� �����ϴ�. Ǫ�� ����� "
		"��ġ�� ��ǳ���� ���� ���Ͽ� �� ���� ���� �ɾ ���� ��ġ�� �����ϴ�."
		"Ȳ���� �ɰ��� ���� ������ �� �ͼ��� ������ Ƽ���� �Ǿ� �Ѽ��� ��ǳ�� "
		"���ư����ϴ�.");
#endif

#ifdef Using_wsprintf
	TCHAR wspSt[200];
	wsprintf(wspSt, TEXT("%d �Դϴ�"), 10);
#endif

	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
#ifdef UsingTextOut
		hdc = BeginPaint(hWnd, &ps);
		SetTextAlign(hdc, TA_TOP | TA_LEFT);

		TextOut(hdc, 20, 20, st1, lstrlen(st1));
		TextOut(hdc, 20, 40, st2, lstrlen(st2));
		TextOut(hdc, 20, 60, st3, lstrlen(st3));
		EndPaint(hWnd, &ps);
		return 0;
#endif

#ifdef UsingDrawText
		hdc = BeginPaint(hWnd, &ps);
		DrawText(hdc, st, -1, &rt, DT_LEFT | DT_TOP | DT_WORDBREAK);
		EndPaint(hWnd, &ps);
		return 0;
#endif

#ifdef Using_wsprintf
		hdc = BeginPaint(hWnd, &ps);
		SetTextAlign(hdc, TA_TOP | TA_LEFT);

		TextOut(hdc, 20, 20, wspSt, lstrlen(wspSt));
		EndPaint(hWnd, &ps);
		return 0;
#endif
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}



#endif // �ڵ常

#endif // Total
