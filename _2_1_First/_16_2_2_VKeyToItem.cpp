#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	○ LBS_WANTKEYBOARDINPUT 
	 - .rc 의  DialogBox 의 ListBox 항목에, LBS_WANTKEYBOARDINPUT 을 추가하면, 해당 리스트박스 에 포커스를 둔 채로 키보드 입력시,
	   MainDlgProc ( DialogBox의 WNDPROC ) 의 WM_VKEYTOITEM 이 발동됨
	 - WM_VKEYTOITEM 이 발동될 때, (BOOL) - 2 를 리턴하면, 해당 리스트박스에 아무런 동작을 하지 말라고 전달.
	 - WM_VKEYTOITEM 이 발동될 때, (BOOL) - 1 를 리턴하면, 리스트박스에 디펄트 동작 처리 전달
	 - WM_VKEYTOITEM 이 발동될 때, 양수       를 리턴하면, 리스트박스에 디펄트 동작 처리 전달
	 
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


const TCHAR* Items[] = { TEXT("Apple"), TEXT("Orange"), TEXT("Melon"), TEXT("Grape"), TEXT("Great"), TEXT("Strawberry") };

INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		for (int i = 0; i < sizeof(Items) / sizeof(Items[0]); i++)
		{
			SendDlgItemMessage(hDlg, IDC_LIST_16_2_1, LB_ADDSTRING, 0, (LPARAM)Items[i]);
		}
		return TRUE;

	case WM_VKEYTOITEM: // 리스트박스에 바로 전달될 것 뺏어옴. 추후 리스트박스에 전달함. rc 에 LBS_WANTKEYBOARDINPUT 추가 필요
		if (LOWORD(wParam) == 'D')
		{
			int i = SendDlgItemMessage(hDlg, IDC_LIST_16_2_1, LB_GETCURSEL, 0, 0);
			if (i != LB_ERR)
			{
				SendDlgItemMessage(hDlg, IDC_LIST_16_2_1, LB_DELETESTRING, i, 0);

				return (BOOL)-2; // 리스트박스 아무것도 하지 말기
			}
		}

		return (BOOL)-1; // 리스트박스 디펄트 동작 하기

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}

		break;
	}

	return FALSE;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;


	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG_16_2_1), hWnd, MainDlgProc);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석


#endif // Total