#if 0 // Total

/* 
	�� CreateDC
	 - ���ݱ��� GetDC ( BeginPaint ) �� WND�� ���ӵ�, GDI �� ������ �޴� DC���� �����ϰ� �ٷ���
	 - CreateDC �� ���� DC�� WND�� ���ӵ��� �ʰ�, GDI �� ������ ���� �ʱ� ������, �ڵ�� ���� ���� �ؾ���
	 - CreateDC �Լ��� �Ű����� �� ���ڴ� �������� ���� (
	   ( ���翡�� �����ϰ� ������ �� ���� ������, ������. �׳� TEXt("DISPLAY"), NULL, NULL, NULL �������� �ܿ� )��
*/


#if 0 // �ּ�
#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdShow, int nCmdShow)
{
	HDC hdc, hMemDC;
	HBITMAP MyBitmap;
	int x, y;

	int sx = GetSystemMetrics(SM_CXSCREEN);
	int sy = GetSystemMetrics(SM_CYSCREEN);


	hdc = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
	
	hMemDC = CreateCompatibleDC(hdc);
	MyBitmap = CreateCompatibleBitmap(hdc, sx, sy);

	SelectObject(hMemDC, MyBitmap);
	BitBlt(hMemDC, 0, 0, sx, sy, hdc, 0, 0, SRCCOPY);

	for (int y = sy; y >= 0; y -= 10)
	{
		BitBlt(hdc, 0, y, sx, sy, hMemDC, 0, 0, SRCCOPY);
		Sleep(10);
	}

	for (int x = sx; x >= 0; x -= 10)
	{
		BitBlt(hdc, x, 0, sx, sy, hMemDC, 0, 0, SRCCOPY);
		Sleep(10);
	}

	BitBlt(hdc, 0, 0, sx, sy, hMemDC, 0, 0, SRCCOPY);


	Sleep(3'000);

	DeleteDC(hMemDC);
	DeleteDC(hdc);
	DeleteObject(MyBitmap);
	return 0;
}





#endif // �ּ�

#if 1 // �ڵ常
#include  <Windows.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HDC hdc, hMemDC;
	HBITMAP MyBitmap;
	int x, y;

	int sx = GetSystemMetrics(SM_CXSCREEN);
	int sy = GetSystemMetrics(SM_CYSCREEN);

	hdc = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);

	hMemDC = CreateCompatibleDC(hdc);
	MyBitmap = CreateCompatibleBitmap(hdc, sx, sy);

	SelectObject(hMemDC, MyBitmap);
	BitBlt(hMemDC, 0, 0, sx, sy, hdc, 0, 0, SRCCOPY);

	for (int y = sy; y >= 0; y -= 10)
	{
		BitBlt(hdc, 0, y, sx, sy, hMemDC, 0, 0, SRCCOPY);
		Sleep(10);
	}

	for (int x = sx; x >= 0; x -= 10)
	{
		BitBlt(hdc, x, 0, sx, sy, hMemDC, 0, 0, SRCCOPY);
		Sleep(10);
	}
	
	BitBlt(hdc, 0, 0, sx, sy, hMemDC, 0, 0, SRCCOPY);

	Sleep(3'000);


	DeleteDC(hMemDC);
	DeleteDC(hdc);
	DeleteObject(MyBitmap);
	
	return 0;
}



#endif // �ڵ常




#endif //Total