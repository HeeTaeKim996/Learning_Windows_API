#if 0 // Total
/*-------------------------------------------
        메세지박스를 구현하는 코드입니다
-------------------------------------------*/


#if 0 // 주석
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MessageBox");

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
    WndClass.style = CS_HREDRAW | CS_VREDRAW;
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    switch (iMessage)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_LBUTTONDOWN:
        MessageBox(hWnd, TEXT("마우스 왼쪽 버튼을 눌렀습니다"), TEXT("메세지 박스"),
            MB_ABORTRETRYIGNORE | MB_ICONWARNING);
        /* □ MessageBox
            □ (2) : 메세지 본문
            □ (3) : 메세지 제목(위쪽)
            □ (4) : 버튼 설정

             ○ 버튼 설정
              - MB_ABORTERYIGNORE    : 중단 - 다시시도 - 무시     총 3버튼
              - MB_OK                : OK 버튼
              - MB_OKCANCEL          : OK - CANCEL
              - MB_RETRYCANCEL       : RETRY - CANCEL
              - MB_YESNO             : YES - NO
              - YESNOCANCEL          : YES - NO - CANCEL

             ○ 아이콘 설정
              - MB_ICONEXCLAMATION, MB_ICONWARNING      : 경고 표시
              - MB_ICONINFORMATION, MB_ICONASTERISK     : 느낌표 동그라미
              - MB_ICONQUESTION                         : 물음표
              - MB_ICONSTOP, MB_ICONERROR, MB_ICONHED   : X 표시

        */
        return 0;
    case WM_RBUTTONDOWN:
        switch (MessageBox(hWnd, TEXT("중지를 원하면, '예' 를 누르세요"), TEXT("프로그램중단?"),
            MB_YESNO | MB_ICONSTOP))
        {
        case IDYES:
            PostQuitMessage(0);
            return 0;
        case IDNO:
            MessageBeep(MB_ICONEXCLAMATION);
            return 0;
        }

        /* ○ MessageBox 리턴값
            - IDABORT   : ABOR 누름
            - IDCANCEL  : CANCEL 누름
            - IDIGNORE  : IGNORE 누름
            - IDNO      : NO 누름
            - IDOK      : OK 누름
            - IDRETRY   : RETRY 누름
            - IDYES     : YES 누름

           ○ MessageBeep : 소리 출력
            - 0XFFFFFFFF        : PC의 스피커를 통해 음을 낸다
            - MB_ICONASTERISK       : ASTERISK 비프음
            - MB_ICONEXCLAMATION    : EXCLAMATION
            - MB_ICONHAND           : HAND
            - MB_ICONQUESTION       : QUESTION
            - MB_OK                 : OK
        */
    }


    return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}


#endif // 주석


#if 1// 코드만
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MessageBox");

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
    WndClass.style = CS_HREDRAW | CS_VREDRAW;
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    switch (iMessage)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_LBUTTONDOWN:
        MessageBox(hWnd, TEXT("마우스 왼쪽 버튼을 눌렀습니다"), TEXT("메세지 박스"),
            MB_ABORTRETRYIGNORE | MB_ICONWARNING);
        return 0;
    case WM_RBUTTONDOWN:
        switch (MessageBox(hWnd, TEXT("중지를 원하면, '예' 를 누르세요"), TEXT("프로그램중단?"),
            MB_YESNO | MB_ICONSTOP))
        {
        case IDYES:
            PostQuitMessage(0);
            return 0;
        case IDNO:
            MessageBeep(MB_ICONEXCLAMATION);
            return 0;
        }
    }
    return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}


#endif // 코드만


#endif // Total