#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	�ڵ� �۵� �ȵȴ�. ���� �ִµ� ��ã�ڴ�.
	�ڵ��, rc �� ������� �ʰ�, �ڵ常���� DialogBox �� ���� �����ϴ� �ڵ��.

	����� ��Ȯ�ϴ�. ���꼺�� ����������, rc �� ������� �ʱ⿡ ������ �����ϰ� Ȯ���� DlgBox�� ���� �� �־�,
	������ �����ϴ�. rc�� ������� �ʰ� �ڵ常 ����ϱ⿡ �뷮�� ���� �Ծ� ȿ�����̴�.
	
	�����ϰ�, ������ �ʿ䰡 �־������, ������ �����Ѵ�. ���� �ʿ��ϴٸ�, ������ �ʿ䰡 �־�δ�.
	�ٸ� �Ʒ� �ڵ�� �۵����� �ʴ´�. �������µ� ������ ��ã��. �׳� ������ ������
----------------------------------------------------------------------------------------------------*/


#if 1 // �ּ�
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

INT_PTR CALLBACK DialogProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}


LRESULT DisplayMyMessage(HINSTANCE hInst, HWND hWndOwner)
{
	HGLOBAL hGbl;
	LPDLGTEMPLATE pdt;
	LPDLGITEMTEMPLATE pEdit;
	LPWORD pw;
	LPWSTR pwsz;
	int nchar;

	hGbl = GlobalAlloc(GMEM_ZEROINIT, 1024);
	pdt = (LPDLGTEMPLATE)GlobalLock(hGbl);


	// ��ȭ ���� ���ø� ����
	pdt->style = WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION;
	pdt->cdit = 1;
	pdt->x = 10;
	pdt->y = 10;
	pdt->cx = 200;
	pdt->cy = 100;


	// �޴��� ���� Ŭ������ ����Ʈ�� ���Ѵ�
	pw = (LPWORD)(pdt + 1);
	*pw++ = 0;
	*pw++ = 0;

	pwsz = (LPWSTR)pw;
	nchar = MultiByteToWideChar(CP_ACP, 0, "Run Time Dialog", -1, pwsz, 50) + 1;
	pw += nchar;

	// Ȯ�� ��ư�� �����Ѵ�
	pw = (LPWORD)((ULONG)pw + 3 & 0xFFFFFFFC);
	pEdit = (LPDLGITEMTEMPLATE)pw;
	pEdit->x = 50;
	pEdit->y = 40;
	pEdit->cx = 100;
	pEdit->cy = 20;
	pEdit->id = IDOK;
	pEdit->style = WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON;

	pw = (LPWORD)(pEdit + 1);
	*pw++ = 0xFFFF;
	*pw++ = 0x0080;

	pwsz = (LPWSTR)pw;
	nchar = MultiByteToWideChar(CP_ACP, 0, "Ȯ��", -1, pwsz, 50) + 1;
	pw += nchar;
	pw = (LPWORD)((ULONG)pw + 3 & 0xFFFFFFFC);
	*pw++ = 0;

	LRESULT Result;
	GlobalUnlock(hGbl);
	Result = DialogBoxIndirect(hInst, (LPDLGTEMPLATE)hGbl, hWndOwner, (DLGPROC)DialogProc);
	GlobalFree(hGbl);

	return Result;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR* Mes = TEXT("���콺 ���� ��ư�� ������ �����߿� ��ȭ���ڸ� ����� �����ݴϴ�.");


	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		DisplayMyMessage(g_hInst, hWnd);
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





#endif // �ּ�




#endif // Total