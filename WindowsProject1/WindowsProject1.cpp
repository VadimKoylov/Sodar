#include "framework.h"
#include "WindowsProject1.h"

#define ClassName "ClassName"
#define MainWindow "MainWindow"

HINSTANCE hInst;								// текущий экземпляр
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

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
    HWND  hWnd = CreateWindow(wcex.lpszClassName, MainWindow, WS_OVERLAPPEDWINDOW | WS_SIZEBOX,
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
        EnableMenuItem(GetMenu(hWnd), IDM_FAX, MF_DISABLED);
        SetWindowLong(hWnd, GWL_USERDATA, 0);
        break;
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
        break;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        RECT rc1, rc2, rc3;
        RECT sizeWnd;

        GetClientRect(hWnd, &sizeWnd);

        switch (GetWindowLong(hWnd, GWL_USERDATA))
        {
        case 0:
        {
            rc1.left = sizeWnd.right * 0.1;
            rc1.right = sizeWnd.right * 0.99;
            rc1.top = sizeWnd.bottom * 0.0185;
            rc1.bottom = sizeWnd.bottom * 0.3148;

            rc2.left = sizeWnd.right * 0.1;
            rc2.right = sizeWnd.right * 0.99;
            rc2.top = sizeWnd.bottom * 0.3333;
            rc2.bottom = sizeWnd.bottom * 0.6296;

            rc3.left = sizeWnd.right * 0.1;
            rc3.right = sizeWnd.right * 0.99;
            rc3.top = sizeWnd.bottom * 0.6481;
            rc3.bottom = sizeWnd.bottom * 0.9444;

            Rectangle(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom);
            Rectangle(hdc, rc2.left, rc2.top, rc2.right, rc2.bottom);
            Rectangle(hdc, rc3.left, rc3.top, rc3.right, rc3.bottom);
        }

        case 1:
        {

        }
        }
        
        EndPaint(hWnd, &ps);
        break;
    }

    case WM_SIZE:
    {
        InvalidateRect(hWnd, NULL, true);
        break;
    }
 

    case WM_DESTROY:
        if (hWnd == FindWindow(ClassName, MainWindow))
            PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}