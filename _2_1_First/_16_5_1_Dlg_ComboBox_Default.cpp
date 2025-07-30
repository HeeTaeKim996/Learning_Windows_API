#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	DialogBox 에서 콤보박스를 사용하는 가장 기본적인 코드입니다. 
	다이아로그 박스에서 콤보박스를 사용할 때 주의할 점은, rc 에서 디자인할 때에, 콤보박스를 드롭다운 할 때에
	크기 에서 높이를 충분히 드래그로 조절해야, 드롬다운 때 요소들이 나열돼서 보인다는 것입니다.

	디펄트로 할시, 드롭다운 때 요소가 1개밖에 보이지 않습니다.

	
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



const TCHAR* arItem[3] = { TEXT("라면"), TEXT("떡볶이"), TEXT("튀김") };

INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		for (int i = 0; i < 3; i++)
		{
			SendDlgItemMessage(hDlg, IDC_COMBO_16_5_1, CB_ADDSTRING, 0, (LPARAM)arItem[i]);
			SendDlgItemMessage(hDlg, IDC_COMBO_16_5_2, CB_ADDSTRING, 0, (LPARAM)arItem[i]);
			SendDlgItemMessage(hDlg, IDC_COMBO_16_5_3, CB_ADDSTRING, 0, (LPARAM)arItem[i]);
		}

		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}

		return FALSE;

	}

	return FALSE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	

	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG_16_5_1), hWnd, MainDlgProc);
		
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;


	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석



#endif // Total