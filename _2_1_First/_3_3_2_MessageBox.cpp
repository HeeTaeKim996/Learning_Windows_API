#if 0 // Total
/*-------------------------------------------
        �޼����ڽ��� �����ϴ� �ڵ��Դϴ�
-------------------------------------------*/


#if 0 // �ּ�
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
        MessageBox(hWnd, TEXT("���콺 ���� ��ư�� �������ϴ�"), TEXT("�޼��� �ڽ�"),
            MB_ABORTRETRYIGNORE | MB_ICONWARNING);
        /* �� MessageBox
            �� (2) : �޼��� ����
            �� (3) : �޼��� ����(����)
            �� (4) : ��ư ����

             �� ��ư ����
              - MB_ABORTERYIGNORE    : �ߴ� - �ٽýõ� - ����     �� 3��ư
              - MB_OK                : OK ��ư
              - MB_OKCANCEL          : OK - CANCEL
              - MB_RETRYCANCEL       : RETRY - CANCEL
              - MB_YESNO             : YES - NO
              - YESNOCANCEL          : YES - NO - CANCEL

             �� ������ ����
              - MB_ICONEXCLAMATION, MB_ICONWARNING      : ��� ǥ��
              - MB_ICONINFORMATION, MB_ICONASTERISK     : ����ǥ ���׶��
              - MB_ICONQUESTION                         : ����ǥ
              - MB_ICONSTOP, MB_ICONERROR, MB_ICONHED   : X ǥ��

        */
        return 0;
    case WM_RBUTTONDOWN:
        switch (MessageBox(hWnd, TEXT("������ ���ϸ�, '��' �� ��������"), TEXT("���α׷��ߴ�?"),
            MB_YESNO | MB_ICONSTOP))
        {
        case IDYES:
            PostQuitMessage(0);
            return 0;
        case IDNO:
            MessageBeep(MB_ICONEXCLAMATION);
            return 0;
        }

        /* �� MessageBox ���ϰ�
            - IDABORT   : ABOR ����
            - IDCANCEL  : CANCEL ����
            - IDIGNORE  : IGNORE ����
            - IDNO      : NO ����
            - IDOK      : OK ����
            - IDRETRY   : RETRY ����
            - IDYES     : YES ����

           �� MessageBeep : �Ҹ� ���
            - 0XFFFFFFFF        : PC�� ����Ŀ�� ���� ���� ����
            - MB_ICONASTERISK       : ASTERISK ������
            - MB_ICONEXCLAMATION    : EXCLAMATION
            - MB_ICONHAND           : HAND
            - MB_ICONQUESTION       : QUESTION
            - MB_OK                 : OK
        */
    }


    return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}


#endif // �ּ�


#if 1// �ڵ常
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
        MessageBox(hWnd, TEXT("���콺 ���� ��ư�� �������ϴ�"), TEXT("�޼��� �ڽ�"),
            MB_ABORTRETRYIGNORE | MB_ICONWARNING);
        return 0;
    case WM_RBUTTONDOWN:
        switch (MessageBox(hWnd, TEXT("������ ���ϸ�, '��' �� ��������"), TEXT("���α׷��ߴ�?"),
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


#endif // �ڵ常


#endif // Total