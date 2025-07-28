#if 0 // Total

/* 
	○ CreateDC
	 - 지금까지 GetDC ( BeginPaint ) 로 WND에 종속된, GDI 에 관리를 받는 DC만을 생성하고 다뤘음
	 - CreateDC 로 만든 DC는 WND에 종속되지 않고, GDI 에 관리를 받지 않기 때문에, 코드로 직접 삭제 해야함
	 - CreateDC 함수의 매개변수 및 인자는 공부하지 않음 (
	   ( 교재에서 복잡하고 공부할 게 많기 때문에, 생략함. 그냥 TEXt("DISPLAY"), NULL, NULL, NULL 고정으로 외움 )ㅜ
*/


#if 0 // 주석
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





#endif // 주석

#if 1 // 코드만
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



#endif // 코드만




#endif //Total