#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	○ LBS_USETABSTOPS
	 - .rc 의 DialogBox 의 리스트박스에, LBS_USETABSTOPS 를 추가해야 작동함
	 - 리스트 박스 내의 string 은 \t 인식 못함. .rc 에 LBS_USETABSTOPS 추가 처리 및 LB_SETTABSTOPS 처리 필요.
	 - 또한 int inTList[n]; 로 지정하고, SendDlgITemMessage에서 (4)항을 배열수, (5)항에 배열 처리

	 -->> 지정한 배열값에 따라, n번째 \t 의 위치가 해당 배열의 int값으로 이동함

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


const TCHAR* data[] = { TEXT("대한민국\t서울\t한민족"), TEXT("일본\t도쿄\t대화족"), TEXT("중국\t베이징\t한족") };
int arTab[2] = { 50, 100 };

INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM  lParm)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		for (int i = 0; i < 3; i++)
		{
			SendDlgItemMessage(hDlg, IDC_LIST_16_2_1, LB_ADDSTRING, 0, (LPARAM)data[i]);
		}


		SendDlgItemMessage(hDlg, IDC_LIST_16_2_1, LB_SETTABSTOPS, 2, (LPARAM)arTab); 
		// ※ 여기서도 LB_SETTABSTOPS 처리
		//   - (4) : 탭의 갯수
		//   - (5) : 탭의 갯수에 따른 int 배열수. 해당 배열에 따라, n번째 탭의 위치를 지정. 위에서는, 첫번재 탭은 50, 두번째 탭은 100 지정
		
		return TRUE;

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