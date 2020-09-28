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

    HWND  hWnd = CreateWindow(wcex.lpszClassName, MainWindow, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

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
        HMENU hMenuBar = CreateMenu();
        HMENU hView = CreateMenu();
        HMENU hFile = CreateMenu();
        HMENU hSettings = CreateMenu();
        HMENU hFaks = CreateMenu();
        HMENU hVeter = CreateMenu();

        AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hView, "Вид");
        AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFile, "Файл");
        AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hSettings, "Настройки");

        AppendMenu(hView, MF_STRING, (UINT_PTR)hFaks, "Факс-записи");
        AppendMenu(hView, MF_STRING, (UINT_PTR)hVeter, "Ветровые данные");

        SetMenu(hWnd, hMenuBar);

        break;
    }

    case WM_DESTROY:
        if (hWnd == FindWindow(ClassName, MainWindow))
            PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}