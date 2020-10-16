#include "framework.h"
#include "WindowsProject1.h"

#define ClassName "MainWindow"
#define MainWindow "SODAR"
#define ClassNameChild1 "ChildWindow1"
#define ClassNameChild2 "ChildWindow2"
#define ClassNameChild3 "ChildWindow3"

HINSTANCE hInst;								// текущий экземпляр
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndChild1(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndChild2(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndChild3(HWND, UINT, WPARAM, LPARAM);

HWND hChild1;
HWND hChild2;
HWND hChild3;

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    WNDCLASS wcex = { 0 };

    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.lpszClassName = ClassName;
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.style = CS_DBLCLKS;

    if (!RegisterClass(&wcex))
        return 0;




    HMENU hMenu = LoadMenu(NULL, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    HWND  hWnd = CreateWindow(wcex.lpszClassName, MainWindow, WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,
        (int)(GetSystemMetrics(SM_CXSCREEN) * 0.1), (int)(GetSystemMetrics(SM_CYSCREEN) * 0.1),
        (int)(GetSystemMetrics(SM_CXSCREEN) * 0.8), (int)(GetSystemMetrics(SM_CYSCREEN) * 0.8), NULL, hMenu, hInstance, NULL);


    WNDCLASS wcex1 = { 0 };

    wcex1.lpfnWndProc = WndChild1;
    wcex1.hInstance = hInst;
    wcex1.lpszClassName = ClassNameChild1;
    wcex1.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex1.style = CS_DBLCLKS;

    if (!RegisterClass(&wcex1))
        return 0;

    WNDCLASS wcex2 = { 0 };

    wcex2.lpfnWndProc = WndChild2;
    wcex2.hInstance = hInst;
    wcex2.lpszClassName = ClassNameChild2;
    wcex2.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex2.style = CS_DBLCLKS;

    if (!RegisterClass(&wcex2))
        return 0;

    WNDCLASS wcex3 = { 0 };

    wcex3.lpfnWndProc = WndChild3;
    wcex3.hInstance = hInst;
    wcex3.lpszClassName = ClassNameChild3;
    wcex3.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex3.style = CS_DBLCLKS;

    if (!RegisterClass(&wcex3))
        return 0;

    RECT sizeWnd;
    GetClientRect(hWnd, &sizeWnd);

    hChild1 = CreateWindow(wcex1.lpszClassName, "", WS_CHILDWINDOW,
        (int)(sizeWnd.right * 0.1), (int)(sizeWnd.bottom * 0.01),
        (int)(sizeWnd.right * 0.89), (int)(sizeWnd.bottom * 0.3029), hWnd, NULL, hInst, NULL);

    hChild2 = CreateWindow(wcex2.lpszClassName, "", WS_CHILDWINDOW,
        (int)(sizeWnd.right * 0.1), (int)(sizeWnd.bottom * 0.3229),
        (int)(sizeWnd.right * 0.89), (int)(sizeWnd.bottom * 0.3029), hWnd, NULL, hInst, NULL);

    hChild3 = CreateWindow(wcex3.lpszClassName, "", WS_CHILDWINDOW,
        (int)(sizeWnd.right * 0.1), (int)(sizeWnd.bottom * 0.6358),
        (int)(sizeWnd.right * 0.89), (int)(sizeWnd.bottom * 0.3029), hWnd, NULL, hInst, NULL);

    ShowWindow(hChild1, SW_NORMAL);
    ShowWindow(hChild2, SW_NORMAL);
    ShowWindow(hChild3, SW_NORMAL);


    if (hWnd == NULL)
        return 0;

    ShowWindow(hWnd, nCmdShow);



    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, NULL, 0, 0))
    {
        DispatchMessage(&msg);
    }

    return 0;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {

    case WM_CREATE:
    {
        EnableMenuItem(GetMenu(hWnd), IDM_FAX, MF_DISABLED);
        return 0;
    }

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDM_WIND:
        {
            SetWindowLong(hWnd, GWL_USERDATA, 1);
            InvalidateRect(hWnd, NULL, true);
            EnableMenuItem(GetMenu(hWnd), IDM_FAX, MF_ENABLED);
            EnableMenuItem(GetMenu(hWnd), IDM_WIND, MF_DISABLED);
            break;
        }
        case IDM_FAX:
        {
            SetWindowLong(hWnd, GWL_USERDATA, 0);
            InvalidateRect(hWnd, NULL, true);
            EnableMenuItem(GetMenu(hWnd), IDM_FAX, MF_DISABLED);
            EnableMenuItem(GetMenu(hWnd), IDM_WIND, MF_ENABLED);
            break;
        }
        }
        return 0;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        RECT rc1, rc2, rc3;
        RECT sizeWnd;

        GetClientRect(hWnd, &sizeWnd);

        if (GetWindowLong(hWnd, GWL_USERDATA) == 0)
        {
            MoveWindow(hChild1, (int)(sizeWnd.right * 0.1), (int)(sizeWnd.bottom * 0.01),
                (int)(sizeWnd.right * 0.89), (int)(sizeWnd.bottom * 0.3029), true);

            MoveWindow(hChild2, (int)(sizeWnd.right * 0.1), (int)(sizeWnd.bottom * 0.3229),
                (int)(sizeWnd.right * 0.89), (int)(sizeWnd.bottom * 0.3029), true);

            MoveWindow(hChild3, (int)(sizeWnd.right * 0.1), (int)(sizeWnd.bottom * 0.6358),
                (int)(sizeWnd.right * 0.89), (int)(sizeWnd.bottom * 0.3029), true);

            Rectangle(hdc, sizeWnd.left, sizeWnd.top, sizeWnd.right, sizeWnd.bottom);
        }

        else
        {
            rc1.left = sizeWnd.right * 0.0025;
            rc1.right = sizeWnd.right * 0.7131;
            rc1.top = sizeWnd.top;
            rc1.bottom = sizeWnd.bottom * 0.9975;

            rc2.left = sizeWnd.right * 0.7155;
            rc2.right = sizeWnd.right * 0.9975;
            rc2.top = sizeWnd.top;
            rc2.bottom = sizeWnd.bottom * 0.7308;

            rc3.left = sizeWnd.right * 0.7155;
            rc3.right = sizeWnd.right * 0.9975;
            rc3.top = sizeWnd.bottom * 0.7333;
            rc3.bottom = sizeWnd.bottom * 0.9975;

            //Rectangle(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom);
            //Rectangle(hdc, rc2.left, rc2.top, rc2.right, rc2.bottom);
            //Rectangle(hdc, rc3.left, rc3.top, rc3.right, rc3.bottom);
        }
        
        EndPaint(hWnd, &ps);
        return 0;
    }

    case WM_SIZE:
    {
        InvalidateRect(hWnd, NULL, true);
        return 0;
    }
 

    case WM_DESTROY:
        if (hWnd == FindWindow(ClassName, MainWindow))
            PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK WndChild1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        RECT sizeWnd;

        GetClientRect(hWnd, &sizeWnd);
        Rectangle(hdc, sizeWnd.left, sizeWnd.top, sizeWnd.right, sizeWnd.bottom);
        EndPaint(hWnd, &ps);
        return 0;
    }

    case WM_SIZE:
    {
        InvalidateRect(hWnd, NULL, true);
        return 0;
    }

    case WM_DESTROY:
        if (hWnd == FindWindow(ClassName, MainWindow))
            PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK WndChild2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        RECT sizeWnd;

        GetClientRect(hWnd, &sizeWnd);
        Rectangle(hdc, sizeWnd.left, sizeWnd.top, sizeWnd.right, sizeWnd.bottom);
        EndPaint(hWnd, &ps);
        return 0;
    }

    case WM_SIZE:
    {
        InvalidateRect(hWnd, NULL, true);
        return 0;
    }

    case WM_DESTROY:
        if (hWnd == FindWindow(ClassName, MainWindow))
            PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK WndChild3(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        RECT sizeWnd;

        GetClientRect(hWnd, &sizeWnd);
        Rectangle(hdc, sizeWnd.left, sizeWnd.top, sizeWnd.right, sizeWnd.bottom);
        EndPaint(hWnd, &ps);
        return 0;
    }

    case WM_SIZE:
    {
        InvalidateRect(hWnd, NULL, true);
        return 0;
    }

    case WM_DESTROY:
        if (hWnd == FindWindow(ClassName, MainWindow))
            PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}