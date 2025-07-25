#if 0 // Total
/*------------------------------------------------------------------------------------------------------------
- ������ ������ ���⿡ ���信 ���� ������ ��� �����ϴ�.

- ������Ͽ��� �׻� Resources.h�� ����
- ���׸� - aaa.rc �� ������ rc ���ϵ��� #include "resource.h"�� �ڵ� ����.  Resource.h���� �� rc���ϵ��� �����ϴµ�
- Win�ڵ��� cpp���� #include "resources.h" �� �� rc �鿡 ���� ����
- ��� ����� �Ʒ� �ڵ� ���� �� ������

- !! ����. ������ ������, vs 2022�� ������ε�, rc���� ��Ŭ�� -> �ڵ庸�� -> ��LANGUAGE ... ���⿡ KOREAN... DEFAULT..
     �̷� �������� ���ִµ�, �̻��¼� �����ϸ�, ���� ����. �Ƹ� #if !defined(AFX_RESOURCE_DLL) || defined(AFX_TANG_KOR)
	 �̺κп��� ������ ����, �ν��� ���ϴ� �� ����.
	 �� KOREAN... DEFAULT�� �������� 18, 1 �� ������ �Ҵ��ϸ� ������ �ذ��
	�� .rc �� �����ϸ�, �׻� �ڵ尡 �ٽ� KOREAN.., DEFAULT... �� �ٲ�µ�, ������ ������ ������ �ڵ带 ���� 18, 1 ��
	   �ٽ� �����ϰ� ����.. 

 - MAKEINTRESOURCE ���� �Է��ؾ��� ��, WM_COMMAND�� wParam �б� ������ ��� rc ��Ŭ�� -> �ڵ� ���� �� ���� ���� 

 �� Alt ����Ű, Ctrl ����Ű( Accelerator )
  - Alt ����Ű : rc ���� ĸ�� ������ �����ϸ� �ȴ�. Alt����Ű�� ���� ���� �տ� & �� ���̸� �ȴ�. 
                �̷��� �ϸ�, Alt -> &�� ����Ű -> & �� ����Ű �� ������ ó�� ����. ���� �ڵ�� ���� ���� ����
  - Ctrl ����Ű :  1) rc -> ���ҽ� �߰� -> Accelerator -> Ctrl, Alt �� �ʿ�� �ϴ� �� TRUE�� �ϰ�, 
				     ID ���� (���ϴ� �޴�)  Ű������ ���ϴ� ���� �Է�. ������ ����Ʈ ���(VIRTKEY)
				     ���������� �ڵ�� ���� ���� ����
				   2) �ϴ�ó�� �ڵ� �߰� �ۼ�. ACCEL ������ �����, GetMessage �� �켱 Acceló���ϵ��� ó�� 

 �� StringTable
   - �� ������ ����. 
------------------------------------------------------------------------------------------------------------*/

#if 0 // �ּ�
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Menu");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style = CS_VREDRAW | CS_HREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);


	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1)); 
	// �� IDR_ACCELERATOR1�� ���������� .rc ->��Ŭ�� �ڵ庸�� �� �� �� �ִ� �ڵ� �����ϸ� �ȴ�
	while (GetMessage(&Message, NULL, 0, 0))
	{
		if (!TranslateAccelerator(hWnd, hAccel, &Message))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR str[256];

	switch (iMessage)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam)) // �� !! wParam�� ����, ���� ������ ������ ���� ������, LOWRD�ʼ�
		{
		case 999:
			MessageBox(hWnd, TEXT("ù��° �޴��� �����߽��ϴ�"), TEXT("Menu Demo"), MB_OK);
			break;
		case ID_FILE_MENU2:
			MessageBox(hWnd, TEXT("�ι�° �޴��� �����߽��ϴ�"), TEXT("Menu Demo"), MB_OK);
			break;
		case ID_FILE_EXIT:
			DestroyWindow(hWnd); // �� PostQuitMessage(0); ���� �� �����? ����̶�� ���翡 ����..
			break;
		case ID_VIEW_LOVE:
			MessageBox(hWnd, TEXT("����"), TEXT("lOVE"), MB_OK);
			break;
		case ID_VIEW_HARRY:
			MessageBox(hWnd, TEXT("�ظ�"), TEXT("HARRY"), MB_OK);
			break;
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		LoadString(g_hInst, IDR_STRING101, str, 256);
		TextOut(hdc, 100, 100, str, lstrlen(str));
		EndPaint(hWnd, &ps);
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
LPCTSTR lpszClass = TEXT("UsingMenu2");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdShow, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU2);
	WndClass.style = CS_VREDRAW | CS_HREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR2));
	while (GetMessage(&Message, NULL, 0, 0))
	{
		if (!TranslateAccelerator(hWnd, hAccel, &Message))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static TCHAR str[256];

	switch (iMessage)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_HARRY_LOVE:
			MessageBox(hWnd, TEXT("�ظ�"), TEXT("LOVE"), MB_OK);
			break;
		case ID_BORI_FOOD:
			MessageBox(hWnd, TEXT("����"), TEXT("FOOD"), MB_OK);
			break;
		case ID_SETTINGS_EXIT:
			DestroyWindow(hWnd);
			break;
		}

		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		LoadString(g_hInst, IDR_STRING101, str, 256);
		TextOut(hdc, 100, 100, str, lstrlen(str));
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