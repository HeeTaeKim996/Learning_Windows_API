#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	LB_SETITEMDATA, LB_GETITEMDATA 에 대한 코드입니다. 두 플래그는, HWND 중 리스트박스, 콤보박스, ListView 
	를 대상으로 설정할 수 있는 플래그입니다.

	인덱스를 지정하면, 해당 인덱스 위치에 데이터를 저장, 인덱스를 주면, 해당 인덱스의 데이터를 가져오는 코드입니다.
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




struct tagMyCom
{
	TCHAR CPU[20];
	int Memory;
	int HDD;
	TCHAR VGA[20];
	BOOL bCDRom;
};
tagMyCom MyCom[3] =
{
	{TEXT("Pentium 166"), 64, 12'000, TEXT("WinX Perfect 2"), TRUE},
	{TEXT("Pentium 100"), 32, 2'500, TEXT("Trident"), FALSE},
	{TEXT("Pentium max 166"), 166, 2'100, TEXT("Cyrus Logic"), TRUE}
};

const TCHAR* MySystem[3] = { TEXT("desktop"), TEXT("Server"), TEXT("Notebook") };

#define ID_LISTBOX 100

HWND hList;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR str[128];
	tagMyCom* pCom;
	int index;

	switch (iMessage)
	{
	case WM_CREATE:
		hList = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_NOTIFY,
			10, 10, 100, 200,
			hWnd, (HMENU)ID_LISTBOX, g_hInst, NULL);
		for (int i = 0; i < sizeof(MySystem) / sizeof(MySystem[0]); i++)
		{
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)MySystem[i]);
			SendMessage(hList, LB_SETITEMDATA, i, (LPARAM)&MyCom[i]);
		}
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_LISTBOX:
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			}
		}

		return 0;


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		index = SendMessage(hList, LB_GETCURSEL, 0, 0);

		if (index != -1)
		{
			pCom = (tagMyCom*)SendMessage(hList, LB_GETITEMDATA, index, 0);
			wsprintf(str, TEXT("CPU(%s)		Memory(%d)		HDD(%d)		CD-ROM(%s)"),
				pCom->CPU, pCom->Memory, pCom->HDD, (pCom->bCDRom ? TEXT("TRUE") : TEXT("FALSE")));
			TextOut(hdc, 120, 10, str, lstrlen(str));
		}

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