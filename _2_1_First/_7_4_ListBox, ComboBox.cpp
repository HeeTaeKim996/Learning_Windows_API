#if 0 // Total
/*----------------------------------------------------------------------------------------------------
   ¸®½ºÆ®¹Ú½º¿Í ÄÞº¸¹Ú½º¿¡ °üÇÑ ³»¿ëÀÔ´Ï´Ù.
   ¸®½ºÆ® ¹Ú½º´Â C#ÀÇ ¸®½ºÆ®¿Í À¯»çÇÏ¸ç,
   ÄÞº¸¹Ú½º´Â Edit °ú ¸®½ºÆ®¹Ú½º¸¦ ÇÕÄ£ ±â´ÉÀ¸·Î,
   À¥ÆäÀÌÁö¿¡¼­ ÀÚÁÖ º¸´Â ÇüÅÂÀÌ´Ï ¾²ÀÓ»õ°¡ ¸¹À» °Í °°½À´Ï´Ù
----------------------------------------------------------------------------------------------------*/


#if 0 // ÁÖ¼®
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_ListBox_ComoboBox");

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
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
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

/*---------------------------------------------------------------------------------------------------
	¡à ¸®½ºÆ®¹Ú½º
	¡Û °³¿ä
	 - ¸¶Âù°¡Áö·Î À©µµ¿ìÀÇ ÀÏÁ¾
	 - C#ÀÇ List¿Í À¯»ç
	   ( LB_ADDSTRING À¸·Î µ¥ÀÌÅÍ¸¦ Ãß°¡, LB_DELETESTRING À¸·Î »èÁ¦, LB_GETCURSEL ·Î ÇöÀç È°¼ºÈ­ ÀÎµ¦½º,
		 LB_GETTEXT·Î ÇÒ´çÇÑ ÀÎµ¦½ºÀÇ ÅØ½ºÆ®¸¦ ºÒ·¯¿À´Â µî..  )

	¡Û LBS (ENUM) - ¸®½ºÆ® ¹Ú½º¸¦ »ý¼ºÇÒ ¶§ »ç¿ëÇÏ´Â ÀÌ³Ñ
	 - LBS_MULTIPLESEL	: ¿©·¯ °³ÀÇ Ç×¸ñÀ» ¼±ÅÃÇÒ ¼ö ÀÖÀ½. ( µðÆÞÆ®·Î´Â ÇÏ³ª¸¸ ¼±ÅÃ °¡´ÉÇÔ )
	 - LBS_NOTIFY		: »ç¿ëÀÚ°¡ ¸ñ·Ï Áß ÇÏ³ª¸¦ ¼±ÅÃÇßÀ» ¶§, ºÎ¸ð À©µµ¿ì·Î Åëº¸ ¸Þ¼¼Áö (°ÅÀÇ ÇÊ¼ö·Î »ç¿ë)
	 - LBS_SORT			: Ãß°¡µÈ Ç×¸ñµéÀ» ÀÚµ¿ Á¤·Ä
	 - LBS_OWNERDRAW	: ¹®ÀÚ¿­ÀÌ ¾Æ´Ñ ºñÆ®¸ÊÀÌ³ª ±×¸²À» ³ÖÀ» ¼ö ÀÖ´Ù
	 - LBS_STANDARD		: LBS_NOTIFY | LBS_SORT | WS_BORDER

	  => LBS_NOTIFY ´Â °ÅÀÇ ÇÊ¼ö. LOBS_SORT ³ª LBS_MULTIPLE À» °£È¤ »ç¿ë

	¡Û LB (ENUM) - ÁÖ·Î ºÎ¸ð À©µµ¿ì -> ¸®½ºÆ®¹Ú½º À©µµ¿ì ·Î SendMessage ¶§ »ç¿ëÇÏ´Â ENUM
	 - LB_ADDSTRING		: ¸®½ºÆ® ¹Ú½º¿¡ Ç×¸ñÀ» Ãß°¡. LPARAM¿¡ TCHAR [] ¸¦ LPARAMÀ¸·Î Çüº¯È¯ÇÏ¿© ³Ñ°ÜÁÜ
	 - LB_DELETESTRING	: Ç×¸ñÀ» »èÁ¦. WPARAM¿¡ »èÁ¦ÇÒ Ç×¸ñ ¹øÈ£¸¦ ³Ñ°ÜÁÖ¸ç, ³²Àº Ç×¸ñ¼ö¸¦ ¸®ÅÏ¹ÞÀ½
	 - LB_GETCURSEL		: ÇöÀç ¼±ÅÃµÈ Ç×¸ñÀÇ ¹øÈ£ ¸¦ ¸®ÅÏ¹Þ´Â´Ù
	 - LB_GETTEXT		: Ç×¸ñ¹øÈ£¸¦ ³Ñ°ÜÁÖ¸é, ÇØ´ç ÀÎµ¦½ºÀÇ Ç×¸ñÀ» ¸®ÅÏ¹Þ´Â´Ù.
						  WPARAM ¿¡´Â Ç×¸ñ¹øÈ£. LPARAM¿¡´Â Ç×¸ñ µ¥ÀÌÅÍ¸¦ ´ã±â À§ÇÑ TCHAR[] ¸¦ LPARAM Çüº¯È¯ÇÏ¿© ³Ñ°ÜÁÜ
	 - LB_GETCOUNT		: Ç×¸ñÀÇ °³¼ö¸¦ Á¶»ç
	 - LB_SETCURSEL		: WPARAM ¿¡ ÀÎµ¦½º¸¦ ³Ñ°ÜÁØ´Ù. ¸®½ºÆ® ¹Ú½º À©µµ¿ì´Â ÇØ´ç ÀÎµ¦½º¸¦ '¼±ÅÃ' ÇÑ´Ù

	¡Û LBN (ENUM) - ¸®½ºÆ®¹Ú½º À©µµ¿ì -> ºÎ¸ð À©µµ¿ì·Î º¸³»´Â ¸Þ¼¼ÁöÀÇ ½Äº° ÀÌ³Ñ. HIWORD(WPARAM) ¿¡¼­ ½Äº°
	 - LBN_DBLCLK		: ¸®½ºÆ® ¹Ú½º¸¦ ´õºíÅ¬¸¯ÇÏ¿´À½À» Åëº¸
	 - LBN_ERRSPACE		: ¸Þ¸ð¸® ºÎÁ· Åëº¸
	 - LBN_KILLFOCUS	: Å°º¸µå Æ÷Ä¿½º¸¦ ÀÒ¾ú´Ù
						 ( ¸®½ºÆ®¹Ú½º¸¦ Tab Å°·Î ¼±ÅÃÇÒ º¯°æÇÒ ¼ö ÀÖ´Â »óÅÂ¸¦ Å°º¸µå Æ÷Ä¿½º »óÅÂ¶ó ÇÑ´Ù.
						   ÁÖ·Î ¸®½ºÆ®¹Ú½º¸¦ ¸¶¿ì½º Å¬¸¯ ÈÄ È°¼ºÈ­)
	 - LBN_SELCANCEL	: »ç¿ëÀÚ°¡ ¼±ÅÃÀ» ®g¼ÒÇß´Ù
	 - LBN_SELCHANGE	: »ç¿ëÀÚ°¡ ¼±ÅÃÀ» º¯°æÇß´Ù
	 - LBN_SETFOCUS		: Å°º¸µå Æ÷Ä¿¸£¸£ ¾ò¾ú´Ù


	 ¡à ÄÞº¸¹Ú½º
	 ¡Û °³¿ä
	  - ¾Õ¼± Edit°ú, ¸®½ºÆ®¹Ú½º¸¦ ÇÕÄ£ ÇüÅÂ
	  - EditÃ³·³, ¹Ú½º¸¦ Å¬¸¯ÇÏ¸é ¹®ÀÚ¿­ ÀÔ·Â ¹× Edit Ã³·³ Ã³¸® °¡´É
	  - ¹Ú½º ¿·ÀÇ ¾Æ·¡ È­»ìÇ¥ Å¬¸¯½Ã, ¸®½ºÆ®¹Ú½ºÃ³·³ ¹Ì¸® ÁØºñÇÑ ¿ä¼ÒµéÀÌ ³ª¿­µÇ°í, ÇØ´ç ¿ä¼Ò¸¦ ¼±ÅÃ °¡´É
	  - ENUM µé ¶ÇÇÑ, ¸®½ºÆ® ¹Ú½º¿Í ¸Å¿ì À¯»ç. LBS -> CBS, LB -> CB, LBN -> CBN À¸·Î, ÀÌÈÄ ³»¿ëÀº
		¸®½ºÆ® ¹Ú½º¿Í ¸Å¿ì À¯»çÇÔ

	 ¡Û CBS (ÀÏºÎ)
	  - CBS_SIMPLE			: ¿¡µðÆ®¿Í ¸®½ºÆ® ¹Ú½º¸¦ °¡ÁöµÇ, ¸®½ºÆ® ¹Ú½º°¡ Ç×»ó ÆîÃÄÁ® ÀÖ´Ù
	  - CBS_DROPDOWN		: ¿¡µðÆ®¿Í ¸®½ºÆ® ¹Ú½º¸¦ °¡Áø´Ù
	  - CBS_DROPDOWNLIST	: ¸®½ºÆ®¹Ú½º¸¸ °¡Áö¸ç, ¿¡µðÆ®¿¡ Ç×¸ñÀ» ÀÔ·ÂÇÒ ¼ö ¾ø´Ù (ÀÌ·³ ¸®½ºÆ®¹Ú½º ¾²Áö ¿Ö¾µ±î..)
---------------------------------------------------------------------------------------------------*/

#define ID_LISTBOX 100
HWND hList;

#define ID_COMBOBOX 101
HWND hCombo;

const TCHAR* Items[] = { TEXT("Apple"), TEXT("Orange"), TEXT("Melon"), TEXT("Grape"), TEXT("Strawberry") };


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[128];

	switch (iMessage)
	{
	case WM_CREATE:
	{ // ¸®½ºÆ®¹Ú½º
		hList = CreateWindow(TEXT("listBox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,
			10, 10, 100, 200,
			hWnd, (HMENU)ID_LISTBOX, g_hInst, NULL);
		for (int i = 0; i < 5; i++)
		{
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)Items[i]);
		}
	}

	{ // ÄÞº¸ ¹Ú½º
		hCombo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,
			600, 10, 100, 200,
			hWnd, (HMENU)ID_COMBOBOX, g_hInst, NULL);
		for (int i = 0; i < 5; i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)Items[i]);
		}
	}


	return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_LISTBOX: // ¸®½ºÆ®¹Ú½º
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
			{

				int i = SendMessage(hList, LB_GETCURSEL, 0, 0);
				SendMessage(hList, LB_GETTEXT, i, (LPARAM)str);
				SetWindowText(hWnd, str);

				break;
			}
			break;
			}

		case ID_COMBOBOX: // ÄÞº¸ ¹Ú½º
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				int i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
				SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)str);
				SetWindowText(hWnd, str);

				break;
			}
			case CBN_EDITCHANGE:
				GetWindowText(hCombo, str, 128);
				SetWindowText(hWnd, str);

				break;

			case CBN_KILLFOCUS:
				GetWindowText(hCombo, str, 128);

				if (SendMessage(hCombo, CB_FINDSTRINGEXACT, -1, (LPARAM)str) == CB_ERR)
					// ¡Ø (3)Ç× n + 1 ÀÎµ¦½ººÎÅÍ Á¶È¸. -1ÀÏ½Ã, ÀÎµ¦½º 0ºÎÅÍ Á¶È¸´Ï ÀüÃ¼ Á¶È¸. 
					// ¡Ø CB_ERR == -1. CB¿¡¼­ Findµî ½ÇÆÐ½Ã, -1 ¹ÝÈ¯
				{
					SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)str);
				}


				break;
			}


			break;
		}

		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // ÁÖ¼®


#if 1 // ÄÚµå¸¸
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_ListBox_ComoboBox");

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
	WndClass.hIcon = LoadCursor(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_VREDRAW | CS_HREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, g_hInst, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}


#define ID_LISTBOX 100
HWND hList;

#define ID_COMBOBOX 101
HWND hCombo;

const TCHAR* Items[] = { TEXT("Apple"), TEXT("Orange"), TEXT("Melon"), TEXT("Grape"), TEXT("Strawberry") };

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[128];

	switch (iMessage)
	{
	case WM_CREATE:
	{ 
		{ // ListBox
			hList = CreateWindow(TEXT("listBox"), NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY,
				10, 10, 100, 200,
				hWnd, (HMENU)ID_LISTBOX, g_hInst, NULL);
			for (int i = 0; i < 5; i++)
			{
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)Items[i]);
			}
		}

		{ // ComboBox
			hCombo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,
				600, 10, 100, 200,
				hWnd, (HMENU)ID_COMBOBOX, g_hInst, NULL);
			for (int i = 0; i < 5; i++)
			{
				SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)Items[i]);
			}
		}

		return 0;
	}

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_LISTBOX: // ListBox
		{
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
			{
				int i = SendMessage(hList, LB_GETCURSEL, 0, 0);
				SendMessage(hList, LB_GETTEXT, i, (LPARAM)str);
				SetWindowText(hWnd, str);

				break;
			}

			}
			break;
		}

		case ID_COMBOBOX: // ComboBox
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				int i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
				SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)str);
				SetWindowText(hWnd, str);

				break;
			}
				

			case CBN_EDITCHANGE:
				GetWindowText(hCombo, str, 128);
				SetWindowText(hWnd, str);
				
				break;

			case CBN_KILLFOCUS:
				GetWindowText(hCombo, str, 128);

				if (SendMessage(hCombo, CB_FINDSTRINGEXACT, -1, (LPARAM)str) == CB_ERR)
				{
					SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)str);
				}

				break;
			}

			break;
		}

		return 0;



	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}



#endif // ÄÚµå¸¸


#endif // Total