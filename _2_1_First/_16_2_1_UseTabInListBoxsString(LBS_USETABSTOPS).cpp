#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	�� LBS_USETABSTOPS
	 - .rc �� DialogBox �� ����Ʈ�ڽ���, LBS_USETABSTOPS �� �߰��ؾ� �۵���
	 - ����Ʈ �ڽ� ���� string �� \t �ν� ����. .rc �� LBS_USETABSTOPS �߰� ó�� �� LB_SETTABSTOPS ó�� �ʿ�.
	 - ���� int inTList[n]; �� �����ϰ�, SendDlgITemMessage���� (4)���� �迭��, (5)�׿� �迭 ó��

	 -->> ������ �迭���� ����, n��° \t �� ��ġ�� �ش� �迭�� int������ �̵���

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


const TCHAR* data[] = { TEXT("���ѹα�\t����\t�ѹ���"), TEXT("�Ϻ�\t����\t��ȭ��"), TEXT("�߱�\t����¡\t����") };
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
		// �� ���⼭�� LB_SETTABSTOPS ó��
		//   - (4) : ���� ����
		//   - (5) : ���� ������ ���� int �迭��. �ش� �迭�� ����, n��° ���� ��ġ�� ����. ��������, ù���� ���� 50, �ι�° ���� 100 ����
		
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





#endif // �ּ�


#endif // Total