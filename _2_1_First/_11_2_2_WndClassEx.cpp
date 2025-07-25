#if 0 // Total
/*----------------------------------------------------------------------------------------------------
	WndClassEx �� ���� �ڵ��Դϴ�. WndClass�� ���̰� ���� �����ϴ�. ���� ���絵 WndClass�� ���
	����� �����̹Ƿ� ���� ������ �ʿ䵵 ���� ���Դϴ�.

	WndClassEx�� WndClass���� ��������, 
	1) cbSize ��� ����� �߰��ƴµ�, ���� ���������� sizeof(WNDCLASSEX); �� �Ҵ��ϸ� �˴ϴ�.  
	  ( WndClass�� ���� ������� ���� ������ �ڵ����� �Ѵ� �մϴ�. )
	2) hIconSm �� �߰��ƴµ�, ���� WndClass�� ���������� 32 * 32 ����� �����ϴµ�, WndClassEx��
	  32 * 32 �� ���پ�, 16 * 16 �������� �����ܵ� �����մϴ�. 

	=> ����� WndClassEx�� ������ �ʿ� �����ϴ�. �������̶��� 16 * 16 �������� �������� �����Ѵ�.
	   �ϳ� ���Դϴ�.
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
	WNDCLASSEX WndClassEx;
	g_hInst = hInstance;

	WndClassEx.cbSize = sizeof(WNDCLASSEX);
	WndClassEx.cbClsExtra = 0;
	WndClassEx.cbWndExtra = 0;
	WndClassEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClassEx.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
	//WndClassEx.hIconSm = NULL;
	WndClassEx.hIconSm = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 
		GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	WndClassEx.hInstance = hInstance;
	WndClassEx.lpfnWndProc = WndProc;
	WndClassEx.lpszClassName = lpszClass;
	WndClassEx.lpszMenuName = NULL;
	WndClassEx.style = CS_VREDRAW | CS_HREDRAW;
	if (RegisterClassEx(&WndClassEx) == 0)
	{
		MessageBox(NULL, TEXT("������ Ŭ���� ��� ����"), TEXT("����"), MB_OK);
		return -1;
	}

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


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;


	switch (iMessage)
	{


	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // �ּ�



#endif // Total