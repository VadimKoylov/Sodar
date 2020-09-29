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

        break;
    }

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDM_WIND:
        {
            int idWind = 1;
            SetWindowLong(hWnd, GWL_USERDATA, idWind);
            InvalidateRect(hWnd, NULL, true);
        }
        }
    }

 

    case WM_DESTROY:
        if (hWnd == FindWindow(ClassName, MainWindow))
            PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}