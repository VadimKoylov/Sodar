﻿#include "framework.h"
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

    HWND  hWnd = CreateWindow(wcex.lpszClassName, MainWindow, WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,
        (int)(GetSystemMetrics(SM_CXSCREEN) * 0.1), (int)(GetSystemMetrics(SM_CYSCREEN) * 0.1),
        (int)(GetSystemMetrics(SM_CXSCREEN) * 0.8), (int)(GetSystemMetrics(SM_CYSCREEN) * 0.8), NULL, hMenu, hInstance, NULL);

    HWND hChild1 = CreateWindow(wcex.lpszClassName, "", WS_CHILDWINDOW,
        (int)(GetSystemMetrics(SM_CXSCREEN) * 0.1), (int)(GetSystemMetrics(SM_CYSCREEN) * 0.00741),
        (int)(GetSystemMetrics(SM_CXSCREEN) * 0.89), (int)(GetSystemMetrics(SM_CYSCREEN) * 0.280556), hWnd, NULL, hInstance, NULL);

    HWND hChild2 = CreateWindow(wcex.lpszClassName, "", WS_CHILDWINDOW,
        (int)(GetSystemMetrics(SM_CXSCREEN) * 0.1), (int)(GetSystemMetrics(SM_CYSCREEN) * 0.299074),
        (int)(GetSystemMetrics(SM_CXSCREEN) * 0.89), (int)(GetSystemMetrics(SM_CYSCREEN) * 0.280556), hWnd, NULL, hInstance, NULL);

    HWND hChild3 = CreateWindow(wcex.lpszClassName, "", WS_CHILDWINDOW,
        (int)(GetSystemMetrics(SM_CXSCREEN) * 0.1), (int)(GetSystemMetrics(SM_CYSCREEN) * 0.588889),
        (int)(GetSystemMetrics(SM_CXSCREEN) * 0.89), (int)(GetSystemMetrics(SM_CYSCREEN) * 0.280556), hWnd, NULL, hInstance, NULL);

    if (hWnd == NULL)
        return 0;

    ShowWindow(hWnd, nCmdShow);
    ShowWindow(hChild1, nCmdShow);
    ShowWindow(hChild2, nCmdShow);
    ShowWindow(hChild3, nCmdShow);

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
        //SetWindowLong(hWnd, GWL_USERDATA, 0);
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

            Rectangle(hdc, sizeWnd.left, sizeWnd.top, sizeWnd.right, sizeWnd.bottom);
            //Rectangle(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom);
            //Rectangle(hdc, rc2.left, rc2.top, rc2.right, rc2.bottom);
            //Rectangle(hdc, rc3.left, rc3.top, rc3.right, rc3.bottom);
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

            Rectangle(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom);
            Rectangle(hdc, rc2.left, rc2.top, rc2.right, rc2.bottom);
            Rectangle(hdc, rc3.left, rc3.top, rc3.right, rc3.bottom);
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