#include "framework.h"
#include "WindowsProject1.h"

#define ClassName "MainWindow"
#define MainWindow "SODAR"

#define ClassNameChildFax "ChildWindowFax"
#define ClassNameChildFax1 "ChildWindowFax1"
#define ClassNameChildFax2 "ChildWindowFax2"
#define ClassNameChildFax3 "ChildWindowFax3"

#define ClassNameChildWind "ChildWindowWind"
#define ClassNameChildWind1 "ChildWindowWind1"
#define ClassNameChildWind2 "ChildWindowWind2"
#define ClassNameChildWind3 "ChildWindowWind3"

HINSTANCE hInst;								// текущий экземпляр

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK	WndChildFax(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndChildFax1(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndChildFax2(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndChildFax3(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK	WndChildWind(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndChildWind1(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndChildWind2(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndChildWind3(HWND, UINT, WPARAM, LPARAM);

HWND hChildFax, hChildFax1, hChildFax2, hChildFax3;
HWND hChildWind, hChildWind1, hChildWind2, hChildWind3;

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
        WNDCLASS wcexFax = { 0 };

        wcexFax.lpfnWndProc = WndChildFax;
        wcexFax.hInstance = hInst;
        wcexFax.lpszClassName = ClassNameChildFax;
        wcexFax.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcexFax.style = CS_DBLCLKS;

        if (!RegisterClass(&wcexFax))
            return 0;

        WNDCLASS wcexFax1 = { 0 };

        wcexFax1.lpfnWndProc = WndChildFax1;
        wcexFax1.hInstance = hInst;
        wcexFax1.lpszClassName = ClassNameChildFax1;
        wcexFax1.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcexFax1.style = CS_DBLCLKS;
        
        if (!RegisterClass(&wcexFax1))
            return 0;

        WNDCLASS wcexFax2 = { 0 };

        wcexFax2.lpfnWndProc = WndChildFax2;
        wcexFax2.hInstance = hInst;
        wcexFax2.lpszClassName = ClassNameChildFax2;
        wcexFax2.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcexFax2.style = CS_DBLCLKS;

        if (!RegisterClass(&wcexFax2))
            return 0;

        WNDCLASS wcexFax3 = { 0 };

        wcexFax3.lpfnWndProc = WndChildFax3;
        wcexFax3.hInstance = hInst;
        wcexFax3.lpszClassName = ClassNameChildFax3;
        wcexFax3.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcexFax3.style = CS_DBLCLKS;

        if (!RegisterClass(&wcexFax3))
            return 0;

        WNDCLASS wcexWind = { 0 };

        wcexWind.lpfnWndProc = WndChildWind;
        wcexWind.hInstance = hInst;
        wcexWind.lpszClassName = ClassNameChildWind;
        wcexWind.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcexWind.style = CS_DBLCLKS;

        if (!RegisterClass(&wcexWind))
            return 0;

        WNDCLASS wcexWind1 = { 0 };

        wcexWind1.lpfnWndProc = WndChildWind1;
        wcexWind1.hInstance = hInst;
        wcexWind1.lpszClassName = ClassNameChildWind1;
        wcexWind1.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcexWind1.style = CS_DBLCLKS;

        if (!RegisterClass(&wcexWind1))
            return 0;

        WNDCLASS wcexWind2 = { 0 };

        wcexWind2.lpfnWndProc = WndChildWind2;
        wcexWind2.hInstance = hInst;
        wcexWind2.lpszClassName = ClassNameChildWind2;
        wcexWind2.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcexWind2.style = CS_DBLCLKS;

        if (!RegisterClass(&wcexWind2))
            return 0;

        WNDCLASS wcexWind3 = { 0 };

        wcexWind3.lpfnWndProc = WndChildWind3;
        wcexWind3.hInstance = hInst;
        wcexWind3.lpszClassName = ClassNameChildWind3;
        wcexWind3.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcexWind3.style = CS_DBLCLKS;

        if (!RegisterClass(&wcexWind3))
            return 0;

        RECT sizeWnd;
        GetClientRect(hWnd, &sizeWnd);

        hChildFax = CreateWindow(wcexFax.lpszClassName, "", WS_CHILDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, sizeWnd.right, sizeWnd.bottom, hWnd, NULL, hInst, NULL);

        hChildFax1 = CreateWindow(wcexFax1.lpszClassName, "", WS_CHILDWINDOW, 0, 0, 0, 0, hChildFax, NULL, hInst, NULL);

        hChildFax2 = CreateWindow(wcexFax2.lpszClassName, "", WS_CHILDWINDOW, 0, 0, 0, 0, hChildFax, NULL, hInst, NULL);

        hChildFax3 = CreateWindow(wcexFax3.lpszClassName, "", WS_CHILDWINDOW, 0, 0, 0, 0, hChildFax, NULL, hInst, NULL);

        hChildWind = CreateWindow(wcexWind.lpszClassName, "", WS_CHILDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, sizeWnd.right, sizeWnd.bottom, hWnd, NULL, hInst, NULL);

        hChildWind1 = CreateWindow(wcexWind1.lpszClassName, "", WS_CHILDWINDOW,0, 0, 0, 0, hChildWind, NULL, hInst, NULL);

        hChildWind2 = CreateWindow(wcexWind2.lpszClassName, "", WS_CHILDWINDOW, 0, 0, 0, 0, hChildWind, NULL, hInst, NULL);

        hChildWind3 = CreateWindow(wcexWind3.lpszClassName, "", WS_CHILDWINDOW, 0, 0, 0, 0, hChildWind, NULL, hInst, NULL);

        ShowWindow(hChildFax1, SW_SHOW);
        ShowWindow(hChildFax2, SW_SHOW);
        ShowWindow(hChildFax3, SW_SHOW);

        ShowWindow(hChildWind1, SW_SHOW);
        ShowWindow(hChildWind2, SW_SHOW);
        ShowWindow(hChildWind3, SW_SHOW);

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
            MoveWindow(hChildFax, 0, 0, (int)(sizeWnd.right), (int)(sizeWnd.bottom), true);

            MoveWindow(hChildFax1, (int)(sizeWnd.right * 0.1), (int)(sizeWnd.bottom * 0.01),
                (int)(sizeWnd.right * 0.89), (int)(sizeWnd.bottom * 0.3029), true);

            MoveWindow(hChildFax2, (int)(sizeWnd.right * 0.1), (int)(sizeWnd.bottom * 0.3229),
                (int)(sizeWnd.right * 0.89), (int)(sizeWnd.bottom * 0.3029), true);

            MoveWindow(hChildFax3, (int)(sizeWnd.right * 0.1), (int)(sizeWnd.bottom * 0.6358),
                (int)(sizeWnd.right * 0.89), (int)(sizeWnd.bottom * 0.3029), true);

            ShowWindow(hChildFax, SW_SHOW);
            ShowWindow(hChildWind, SW_HIDE);
        }

        else
        {
            MoveWindow(hChildWind, 0, 0, (int)(sizeWnd.right), (int)(sizeWnd.bottom), true);

            MoveWindow(hChildWind1, (int)(sizeWnd.right * 0.0015625), (int)(sizeWnd.bottom * 0.0025),
                (int)(sizeWnd.right * 0.7131), (int)(sizeWnd.bottom * 0.995), true);

            MoveWindow(hChildWind2, (int)(sizeWnd.right * 0.7155), (int)(sizeWnd.bottom * 0.0025),
                (int)(sizeWnd.right * 0.9975), (int)(sizeWnd.bottom * 0.7283), true);

            MoveWindow(hChildWind3, (int)(sizeWnd.right * 0.7155), (int)(sizeWnd.bottom * 0.7333),
                (int)(sizeWnd.right * 0.7333), (int)(sizeWnd.bottom * 0.1), true);

            ShowWindow(hChildFax, SW_HIDE);
            ShowWindow(hChildWind, SW_SHOW);
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

LRESULT CALLBACK WndChildFax(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

LRESULT CALLBACK WndChildFax1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

LRESULT CALLBACK WndChildFax2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

LRESULT CALLBACK WndChildFax3(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

LRESULT CALLBACK WndChildWind(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

LRESULT CALLBACK WndChildWind1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

LRESULT CALLBACK WndChildWind2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

LRESULT CALLBACK WndChildWind3(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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