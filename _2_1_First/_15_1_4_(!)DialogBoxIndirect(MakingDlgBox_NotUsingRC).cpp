#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	코드 작동 안된다. 오류 있는데 못찾겠다.
	코드는, rc 를 사용하지 않고, 코드만으로 DialogBox 를 직접 생성하는 코드다.

	장단은 명확하다. 생산성은 떨어지지만, rc 를 사용하지 않기에 버전에 무관하게 확실히 DlgBox를 만들 수 있어,
	배포에 용이하다. rc를 사용하지 않고 코드만 사용하기에 용량도 적게 먹어 효율적이다.
	
	유용하고, 공부할 필요가 있어보이지만, 지금은 생략한다. 추후 필요하다면, 공부할 필요가 있어보인다.
	다만 아래 코드는 작동하지 않는다. 오류나는데 원인을 못찾음. 그냥 뇌비우고 적었음
----------------------------------------------------------------------------------------------------*/


#if 1 // 주석
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


	// 대화 상자 템플릿 만듬
	pdt->style = WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION;
	pdt->cdit = 1;
	pdt->x = 10;
	pdt->y = 10;
	pdt->cx = 200;
	pdt->cy = 100;


	// 메뉴는 없고 클래스는 디폴트를 취한다
	pw = (LPWORD)(pdt + 1);
	*pw++ = 0;
	*pw++ = 0;

	pwsz = (LPWSTR)pw;
	nchar = MultiByteToWideChar(CP_ACP, 0, "Run Time Dialog", -1, pwsz, 50) + 1;
	pw += nchar;

	// 확인 버튼을 생성한다
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
	nchar = MultiByteToWideChar(CP_ACP, 0, "확인", -1, pwsz, 50) + 1;
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
	const TCHAR* Mes = TEXT("마우스 왼쪽 버튼을 누르면 실행중에 대화상자를 만들어 보여줍니다.");


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





#endif // 주석




#endif // Total