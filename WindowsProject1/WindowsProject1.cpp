#pragma comment (lib, "Lusbapi.lib")

#include "framework.h"
#include "WindowsProject1.h"

#define ClassName "MainWindow"
#define MainWindow "SODAR"

#define ClassNameDlg "Dlg"

#define ClassNameChildFax "ChildWindowFax"
#define ClassNameChildFax1 "ChildWindowFax1"
#define ClassNameChildFax2 "ChildWindowFax2"
#define ClassNameChildFax3 "ChildWindowFax3"

#define ClassNameChildWind "ChildWindowWind"
#define ClassNameChildWind1 "ChildWindowWind1"
#define ClassNameChildWind2 "ChildWindowWind2"
#define ClassNameChildWind3 "ChildWindowWind3"

#define PAGE 200
#define LINE 24

#define M 3000
#define R 50

HINSTANCE hInst;								// текущий экземпляр

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK    WndDlg(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK	WndChildFax(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndChildFax1(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndChildFax2(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndChildFax3(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK	WndChildWind(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndChildWind1(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndChildWind2(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndChildWind3(HWND, UINT, WPARAM, LPARAM);

HWND hWnd;
HWND hDlg;                                     //окно, использующееся как диалоговое
HWND hChildFax, hChildFax1, hChildFax2, hChildFax3;
HWND hChildWind, hChildWind1, hChildWind2, hChildWind3;

// аварийный выход из программы
void AbortProgram(bool AbortionFlag = true);
// функция потока ввода данных с АЦП
DWORD WINAPI ServiceReadThread(PVOID Context);
// функция вывода сообщений с ошибками
void ShowThreadErrorMessage(void);
// главная функция для счтывания
void MainRead();

// идентификатор файла
HANDLE hFile;

// идентификатор потока сбора данных
HANDLE hReadThread;
DWORD ReadTid;

// версия библиотеки
DWORD DllVersion;
// указатель на интерфейс модуля
ILE440* pModule;
// дескриптор устройства
HANDLE ModuleHandle;
// название модуля
char ModuleName[7];
// скорость работы шины USB
BYTE UsbSpeed;
// структура с полной информацией о модуле
MODULE_DESCRIPTION_E440 ModuleDescription;
// структура параметров работы АЦП модуля
ADC_PARS_E440 ap;

// кол-во получаемых отсчетов (кратное 32) для Ф. ReadData()
DWORD DataStep = 256 * 1024;
// будем собирать NDataBlock блоков по DataStep отсчётов в каждом
const WORD NDataBlock = 80;
// буфер данных
SHORT* ReadBuffer;

// флажок завершения работы потока сбора данных
bool IsReadThreadComplete;
// номер ошибки при выполнении сбора данных
WORD ReadThreadErrorNumber;

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

    hWnd = CreateWindow(wcex.lpszClassName, MainWindow, WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,
        (int)(GetSystemMetrics(SM_CXSCREEN) * 0.1), (int)(GetSystemMetrics(SM_CYSCREEN) * 0.1),
        (int)(GetSystemMetrics(SM_CXSCREEN) * 0.8), (int)(GetSystemMetrics(SM_CYSCREEN) * 0.8),
        NULL,hMenu, hInstance, NULL);

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
        WNDCLASS wcexDlg = { 0 };

        wcexDlg.lpfnWndProc = WndDlg;
        wcexDlg.hInstance = hInst;
        wcexDlg.lpszClassName = ClassNameDlg;
        wcexDlg.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcexDlg.style = CS_DBLCLKS;

        if (!RegisterClass(&wcexDlg))
            return 0;

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

        //создаем диалоговое окно
        hDlg = CreateWindow(wcexDlg.lpszClassName, "", WS_OVERLAPPEDWINDOW, (GetSystemMetrics(SM_CXSCREEN) - 300) / 2,
            (GetSystemMetrics(SM_CYSCREEN) - 300) / 2, 300, 300, hWnd, NULL, hInst, NULL);
        
        //создаем окно для факс-записей, в которое добавляем 3 окна
        hChildFax = CreateWindow(wcexFax.lpszClassName, "", WS_CHILDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, sizeWnd.right,
            sizeWnd.bottom, hWnd, NULL, hInst, NULL);

        hChildFax1 = CreateWindow(wcexFax1.lpszClassName, "", WS_CHILDWINDOW, 0, 0, 0, 0, hChildFax, NULL, hInst, NULL);

        hChildFax2 = CreateWindow(wcexFax2.lpszClassName, "", WS_CHILDWINDOW, 0, 0, 0, 0, hChildFax, NULL, hInst, NULL);

        hChildFax3 = CreateWindow(wcexFax3.lpszClassName, "", WS_CHILDWINDOW, 0, 0, 0, 0, hChildFax, NULL, hInst, NULL);

        //создаем окно для ветра, в которое добавляем 3 окна
        hChildWind = CreateWindow(wcexWind.lpszClassName, "", WS_CHILDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, sizeWnd.right,
            sizeWnd.bottom, hWnd, NULL, hInst, NULL);

        hChildWind1 = CreateWindow(wcexWind1.lpszClassName, "", WS_CHILDWINDOW, 0, 0, 0, 0, hChildWind, NULL, hInst, NULL);

        hChildWind2 = CreateWindow(wcexWind2.lpszClassName, "", WS_CHILDWINDOW, 0, 0, 0, 0, hChildWind, NULL, hInst, NULL);

        hChildWind3 = CreateWindow(wcexWind3.lpszClassName, "", WS_CHILDWINDOW, 0, 0, 0, 0, hChildWind, NULL, hInst, NULL);

        ShowWindow(hDlg, SW_SHOW);

        ShowWindow(hChildFax1, SW_SHOW);
        ShowWindow(hChildFax2, SW_SHOW);
        ShowWindow(hChildFax3, SW_SHOW);

        ShowWindow(hChildWind1, SW_SHOW);
        ShowWindow(hChildWind2, SW_SHOW);
        ShowWindow(hChildWind3, SW_SHOW);

        EnableMenuItem(GetMenu(hWnd), IDM_FAX, MF_DISABLED);

        MainRead();

        return 0;
    }

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDM_WIND:
        {
            SetWindowLong(hWnd, GWLP_USERDATA, 1);
            InvalidateRect(hWnd, NULL, true);
            EnableMenuItem(GetMenu(hWnd), IDM_FAX, MF_ENABLED);
            EnableMenuItem(GetMenu(hWnd), IDM_WIND, MF_DISABLED);
            break;
        }
        case IDM_FAX:
        {
            SetWindowLong(hWnd, GWLP_USERDATA, 0);
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
        RECT sizeWnd;

        GetClientRect(hWnd, &sizeWnd);

        //отрисовка окон в зависимости от нажатого пункта в меню
        if (GetWindowLong(hWnd, GWLP_USERDATA) == 0)
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
                (int)(sizeWnd.right * 0.2829375), (int)(sizeWnd.bottom * 0.7283), true);

            MoveWindow(hChildWind3, (int)(sizeWnd.right * 0.7155), (int)(sizeWnd.bottom * 0.7333),
                (int)(sizeWnd.right * 0.2829375), (int)(sizeWnd.bottom * 0.2642), true);

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
    {
        if (hWnd == FindWindow(ClassName, MainWindow))
            PostQuitMessage(0);
        return 0;
    }
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}


LRESULT CALLBACK WndDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {

    case WM_CREATE:
    {
        HWND hButtonOk = CreateWindow("button", "OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            20, 180, 80, 30, hDlg, (HMENU)(ID_BUTTON), (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE),
            NULL);

        HWND hButtonCancel = CreateWindow("button", "Отмена", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            150, 180, 80, 30, hDlg, (HMENU)(ID_BUTTON + 1), (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE),
            NULL);

        return 0;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hDlg, &ps);
        RECT sizeWnd;

        GetClientRect(hDlg, &sizeWnd);
        Rectangle(hdc, sizeWnd.left, sizeWnd.top, sizeWnd.right, sizeWnd.bottom);
        EndPaint(hDlg, &ps);
        return 0;
    }

    case WM_SIZE:
    {
        InvalidateRect(hDlg, NULL, true);
        return 0;
    }

    case WM_DESTROY:
        if (hDlg == FindWindow(ClassName, MainWindow))
            PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hDlg, message, wParam, lParam);
}

LRESULT CALLBACK WndChildFax(HWND hChildFax, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hChildFax, &ps);
        RECT sizeWnd;

        GetClientRect(hChildFax, &sizeWnd);
        Rectangle(hdc, sizeWnd.left, sizeWnd.top, sizeWnd.right, sizeWnd.bottom);
        EndPaint(hChildFax, &ps);
        return 0;
    }

    case WM_SIZE:
    {
        InvalidateRect(hChildFax, NULL, true);
        return 0;
    }

    case WM_DESTROY:
        if (hChildFax == FindWindow(ClassName, MainWindow))
            PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hChildFax, message, wParam, lParam);
}

LRESULT CALLBACK WndChildFax1(HWND hChildFax1, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hChildFax1, &ps);
        RECT sizeWnd;

        GetClientRect(hChildFax1, &sizeWnd);
        Rectangle(hdc, sizeWnd.left, sizeWnd.top, sizeWnd.right, sizeWnd.bottom);
        EndPaint(hChildFax1, &ps);
        return 0;
    }

    case WM_SIZE:
    {
        InvalidateRect(hChildFax1, NULL, true);
        return 0;
    }

    case WM_DESTROY:
    {
        if (hChildFax1 == FindWindow(ClassName, MainWindow))
            PostQuitMessage(0);
        return 0;
    }
    }
    return DefWindowProc(hChildFax1, message, wParam, lParam);
}

LRESULT CALLBACK WndChildFax2(HWND hChildFax2, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hChildFax2, &ps);
        RECT sizeWnd;

        GetClientRect(hChildFax2, &sizeWnd);
        Rectangle(hdc, sizeWnd.left, sizeWnd.top, sizeWnd.right, sizeWnd.bottom);
        EndPaint(hChildFax2, &ps);
        return 0;
    }

    case WM_SIZE:
    {
        InvalidateRect(hChildFax2, NULL, true);
        return 0;
    }

    case WM_DESTROY:
    {
        if (hChildFax2 == FindWindow(ClassName, MainWindow))
            PostQuitMessage(0);
        return 0;
    }
    }
    return DefWindowProc(hChildFax2, message, wParam, lParam);
}

LRESULT CALLBACK WndChildFax3(HWND hChildFax3, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hChildFax3, &ps);
        RECT sizeWnd;

        GetClientRect(hChildFax3, &sizeWnd);
        Rectangle(hdc, sizeWnd.left, sizeWnd.top, sizeWnd.right, sizeWnd.bottom);
        EndPaint(hChildFax3, &ps);
        return 0;
    }

    case WM_SIZE:
    {
        InvalidateRect(hChildFax3, NULL, true);
        return 0;
    }

    case WM_DESTROY:
    {
        if (hChildFax3 == FindWindow(ClassName, MainWindow))
            PostQuitMessage(0);
        return 0;
    }
    }
    return DefWindowProc(hChildFax3, message, wParam, lParam);
}

LRESULT CALLBACK WndChildWind(HWND hChildWind, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hChildWind, &ps);
        RECT sizeWnd;

        GetClientRect(hChildWind, &sizeWnd);
        Rectangle(hdc, sizeWnd.left, sizeWnd.top, sizeWnd.right, sizeWnd.bottom);
        EndPaint(hChildWind, &ps);
        return 0;
    }

    case WM_SIZE:
    {
        InvalidateRect(hChildWind, NULL, true);
        return 0;
    }

    case WM_DESTROY:
    {
        if (hChildWind == FindWindow(ClassName, MainWindow))
            PostQuitMessage(0);
        return 0;
    }
    }
    return DefWindowProc(hChildWind, message, wParam, lParam);
}

LRESULT CALLBACK WndChildWind1(HWND hChildWind1, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hChildWind1, &ps);
        RECT sizeWnd;

        GetClientRect(hChildWind1, &sizeWnd);
        Rectangle(hdc, sizeWnd.left, sizeWnd.top, sizeWnd.right, sizeWnd.bottom);
        EndPaint(hChildWind1, &ps);
        return 0;
    }

    case WM_SIZE:
    {
        InvalidateRect(hChildWind1, NULL, true);
        return 0;
    }

    case WM_DESTROY:
    {
        if (hChildWind1 == FindWindow(ClassName, MainWindow))
            PostQuitMessage(0);
        return 0;
    }
    }
    return DefWindowProc(hChildWind1, message, wParam, lParam);
}

LRESULT CALLBACK WndChildWind2(HWND hChildWind2, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hChildWind2, &ps);
        RECT sizeWnd;

        GetClientRect(hChildWind2, &sizeWnd);
        Rectangle(hdc, sizeWnd.left, sizeWnd.top, sizeWnd.right, sizeWnd.bottom);
        EndPaint(hChildWind2, &ps);
        return 0;
    }

    case WM_SIZE:
    {
        InvalidateRect(hChildWind2, NULL, true);
        return 0;
    }

    case WM_DESTROY:
    {
        if (hChildWind2 == FindWindow(ClassName, MainWindow))
            PostQuitMessage(0);
        return 0;
    }
    }
    return DefWindowProc(hChildWind2, message, wParam, lParam);
}

LRESULT CALLBACK WndChildWind3(HWND hChildWind3, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hChildWind3, &ps);
        RECT sizeWnd;

        GetClientRect(hChildWind3, &sizeWnd);
        Rectangle(hdc, sizeWnd.left, sizeWnd.top, sizeWnd.right, sizeWnd.bottom);
        EndPaint(hChildWind3, &ps);
        return 0;
    }

    case WM_SIZE:
    {
        InvalidateRect(hChildWind3, NULL, true);
        return 0;
    }

    case WM_DESTROY:
    {
        if (hChildWind3 == FindWindow(ClassName, MainWindow))
            PostQuitMessage(0);
        return 0;
    }
    }
    return DefWindowProc(hChildWind3, message, wParam, lParam);
}


//------------------------------------------------------------------------
// Главная функция для считывания файлов
//------------------------------------------------------------------------
void MainRead() {
    WORD i;


    // пока ничего не выделено под буфер данных
    ReadBuffer = NULL;
    // пока не создан поток ввода данных
    hReadThread = NULL;
    // пока откытого файла нет :(
    hFile = INVALID_HANDLE_VALUE;
    // сбросим флаг ошибок потока ввода данных
    ReadThreadErrorNumber = 0x0;

    //проверим версию используемой библиотеки Lusbapi.dll
    if ((DllVersion = GetDllVersion()) != CURRENT_VERSION_LUSBAPI)
    {
        MessageBox(hWnd, "Lusbapi.dll Version Error!!!", "ERROR", NULL);
        AbortProgram();
    }

    // попробуем получить указатель на интерфейс
    pModule = static_cast<ILE440*>(CreateLInstance(PCHAR("e440")));
    if (!pModule)
    {
        MessageBox(hWnd, "Module Interface --> Bad", "ERROR", NULL);
        AbortProgram();
    }

    // попробуем обнаружить модуль E14-440 в первых MAX_VIRTUAL_SLOTS_QUANTITY_LUSBAPI виртуальных слотах
    for (i = 0x0; i < MAX_VIRTUAL_SLOTS_QUANTITY_LUSBAPI; i++)
    {
        if (pModule->OpenLDevice(i))
        {
            break;
        }
    }
    // что-нибудь обнаружили?
    if (i == MAX_VIRTUAL_SLOTS_QUANTITY_LUSBAPI)
    {
        MessageBox(hWnd, "Can't find any module E14-440 in first 127 virtual slots!", "ERROR", NULL);
        AbortProgram();
    }

    // попробуем прочитать дескриптор устройства
    ModuleHandle = pModule->GetModuleHandle();
    if (ModuleHandle == INVALID_HANDLE_VALUE)
    {
        MessageBox(hWnd, "GetModuleHandle() --> Bad", "ERROR", NULL);
        AbortProgram();
    }

    // прочитаем название модуля в обнаруженном виртуальном слоте
    if (!pModule->GetModuleName(ModuleName))
    {
        MessageBox(hWnd, "GetModuleName() --> Bad", "ERROR", NULL);
        AbortProgram();
    }

    // проверим, что это 'E14-440'
    if (strcmp(ModuleName, "E440"))
    {
        MessageBox(hWnd, "The module is not 'E14-440'", "ERROR", NULL);
        AbortProgram();
    }

    // попробуем получить скорость работы шины USB
    if (!pModule->GetUsbSpeed(&UsbSpeed))
    {
        MessageBox(hWnd, "GetUsbSpeed() --> Bad", "ERROR", NULL);
        AbortProgram();
    }

    // код LBIOS'а возьмём из соответствующего ресурса штатной DLL библиотеки
    if (!pModule->LOAD_MODULE())
    {
        MessageBox(hWnd, "LOAD_MODULE() --> Bad", "ERROR", NULL);
        AbortProgram();
    }

    // проверим загрузку модуля
    if (!pModule->TEST_MODULE())
    {
        MessageBox(hWnd, "TEST_MODULE() --> Bad", "ERROR", NULL);
        AbortProgram();
    }

    // получим информацию из ППЗУ модуля
    if (!pModule->GET_MODULE_DESCRIPTION(&ModuleDescription))
    {
        MessageBox(hWnd, "GET_MODULE_DESCRIPTION() --> Bad", "ERROR", NULL);
        AbortProgram();
    }

    // получим текущие параметры работы АЦП
    if (!pModule->GET_ADC_PARS(&ap))
    {
        AbortProgram();
    }

    // установим желаемые параметры работы АЦП
    ap.IsCorrectionEnabled = TRUE;			// разрешим корректировку данных на уровне драйвера DSP
    ap.InputMode = NO_SYNC_E440;				// обычный сбор данных безо всякой синхронизации ввода
    ap.ChannelsQuantity = 0x4;					// четыре активных канала
    // формируем управляющую таблицу 
    for (i = 0x0; i < ap.ChannelsQuantity; i++)
    {
        ap.ControlTable[i] = (WORD)(i | (ADC_INPUT_RANGE_2500mV_E440 << 0x6));
    }
    ap.AdcRate = 400.0;							// частота работы АЦП в кГц
    ap.InterKadrDelay = 0.0;					// межкадровая задержка в мс
    ap.AdcFifoBaseAddress = 0x0;			  	// базовый адрес FIFO буфера АЦП в DSP модуля
    ap.AdcFifoLength = MAX_ADC_FIFO_SIZE_E440;	// длина FIFO буфера АЦП в DSP модуля
    // будем использовать фирменные калибровочные коэффициенты, которые храняться в ППЗУ модуля
    for (i = 0x0; i < ADC_CALIBR_COEFS_QUANTITY_E440; i++)
    {
        ap.AdcOffsetCoefs[i] = ModuleDescription.Adc.OffsetCalibration[i];
        ap.AdcScaleCoefs[i] = ModuleDescription.Adc.ScaleCalibration[i];
    }

    // передадим требуемые параметры работы АЦП в модуль
    if (!pModule->SET_ADC_PARS(&ap))
    {
        MessageBox(hWnd, "SET_ADC_PARS() --> Bad", "ERROR", NULL);
        AbortProgram();
    }

    // выделим память под буфер
    ReadBuffer = new SHORT[2 * DataStep];
    if (!ReadBuffer)
    {
        MessageBox(hWnd, "Can not allocate memory", "ERROR", NULL);
        AbortProgram();
    }

    // откроем файл для записи получаемых с модуля данных
    hFile = CreateFile("Test.dat", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN | FILE_FLAG_WRITE_THROUGH, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        MessageBox(hWnd, "Can't create file 'Test.dat'!", "ERROR", NULL);
        AbortProgram();
    }

    // сбросим флажок завершения потока ввода данных
    IsReadThreadComplete = false;

    // Создаём и запускаем поток сбора данных
    hReadThread = CreateThread(0, 0x2000, ServiceReadThread, (PVOID)hWnd, 0, NULL);//hWnd дескриптор главного окна
    if (!hReadThread)
    {
        MessageBox(hWnd, "ServiceReadThread() --> Bad", "ERROR", NULL);
        AbortProgram();
    }

    // ждём окончания работы потока ввода данных
    WaitForSingleObject(hReadThread, INFINITE);

    // проверим была ли ошибка выполнения потока сбора данных
    if (ReadThreadErrorNumber)
    {
        AbortProgram(false);
        ShowThreadErrorMessage();
    }
    else
    {
        AbortProgram(false);
    }

}


//------------------------------------------------------------------------
// Поток, в котором осуществляется сбор данных
//------------------------------------------------------------------------
DWORD WINAPI ServiceReadThread(PVOID Context)
{
    HWND hwndMain = (HWND)Context;
    WORD i;
    WORD RequestNumber;
    DWORD FileBytesWritten;
    // массив OVERLAPPED структур из двух элементов
    OVERLAPPED ReadOv[2];
    // массив структур с параметрами запроса на ввод/вывод данных
    IO_REQUEST_LUSBAPI IoReq[2];

    // остановим работу АЦП и одновременно сбросим USB-канал чтения данных
    if (!pModule->STOP_ADC())
    {
        ReadThreadErrorNumber = 0x1;
        IsReadThreadComplete = true;
        return 0x0;
    }

    // формируем необходимые для сбора данных структуры
    for (i = 0x0; i < 0x2; i++)
    {
        // инициализация структуры типа OVERLAPPED
        ZeroMemory(&ReadOv[i], sizeof(OVERLAPPED));
        // создаём событие для асинхронного запроса
        ReadOv[i].hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
        // формируем структуру IoReq
        IoReq[i].Buffer = ReadBuffer + i * DataStep;
        IoReq[i].NumberOfWordsToPass = DataStep;
        IoReq[i].NumberOfWordsPassed = 0x0;
        IoReq[i].Overlapped = &ReadOv[i];
        IoReq[i].TimeOut = (DWORD)(DataStep / ap.AdcRate + 1000);
    }

    // делаем предварительный запрос на ввод данных
    RequestNumber = 0x0;
    if (!pModule->ReadData(&IoReq[RequestNumber]))
    {
        CloseHandle(ReadOv[0].hEvent);
        CloseHandle(ReadOv[1].hEvent);
        ReadThreadErrorNumber = 0x2;
        IsReadThreadComplete = true;
        return 0x0;
    }


    // запустим АЦП
    if (pModule->START_ADC())
    {
        // цикл сбора данных
        for (i = 0x1; i < NDataBlock; i++)
        {
            // сделаем запрос на очередную порцию данных
            RequestNumber ^= 0x1;
            if (!pModule->ReadData(&IoReq[RequestNumber]))
            {
                ReadThreadErrorNumber = 0x2;
                break;
            }
            if (ReadThreadErrorNumber)
            {
                break;
            }

            //// ждём завершения операции сбора предыдущей порции данных
            //if (WaitForSingleObject(ReadOv[RequestNumber ^ 0x1].hEvent, IoReq[RequestNumber ^ 0x1].TimeOut) == WAIT_TIMEOUT)
            //{
            //    ReadThreadErrorNumber = 0x3;
            //    break;
            //}
            //if (ReadThreadErrorNumber)
            //{
            //    break;
            //}

            // запишем полученную порцию данных в файл
            if (!WriteFile(hFile,													// handle to file to write to
                IoReq[RequestNumber ^ 0x1].Buffer,					// pointer to data to write to file
                2 * DataStep,	 											// number of bytes to write
                &FileBytesWritten,									// pointer to number of bytes written
                NULL			  											// pointer to structure needed for overlapped I/O
            ))
            {
                ReadThreadErrorNumber = 0x4;
                break;
            }
            if (ReadThreadErrorNumber)
            {
                break;
            }
            else
            {
                Sleep(20);
            }
        }

        // последняя порция данных
        if (!ReadThreadErrorNumber)
        {
            RequestNumber ^= 0x1;
            // ждём окончания операции сбора последней порции данных
            if (WaitForSingleObject(ReadOv[RequestNumber ^ 0x1].hEvent, IoReq[RequestNumber ^ 0x1].TimeOut) == WAIT_TIMEOUT)
            {
                ReadThreadErrorNumber = 0x3;
            }
            // запишем последнюю порцию данных в файл
            if (!WriteFile(hFile,													// handle to file to write to
                IoReq[RequestNumber ^ 0x1].Buffer,					// pointer to data to write to file
                2 * DataStep,	 											// number of bytes to write
                &FileBytesWritten,									// pointer to number of bytes written
                NULL			  											// pointer to structure needed for overlapped I/O
            )) ReadThreadErrorNumber = 0x4;
        }
    }
    else
    {
        ReadThreadErrorNumber = 0x6;
    }

    // остановим работу АЦП
    if (!pModule->STOP_ADC())
    {
        ReadThreadErrorNumber = 0x1;
    }
    // прервём возможно незавершённый асинхронный запрос на приём данных
    if (!CancelIo(ModuleHandle))
    {
        ReadThreadErrorNumber = 0x7;
    }
    // освободим все идентификаторы событий
    for (i = 0x0; i < 0x2; i++)
    {
        CloseHandle(ReadOv[i].hEvent);
    }
    // небольшая задержка
    Sleep(100);
    // установим флажок завершения работы потока сбора данных
    IsReadThreadComplete = true;
    // теперь можно спокойно выходить из потока
    return 0x0;
}

//------------------------------------------------------------------------
// Отобразим сообщение с ошибкой
//------------------------------------------------------------------------
void ShowThreadErrorMessage(void)
{
    switch (ReadThreadErrorNumber)
    {
    case 0x1:
    {
        MessageBox(hWnd, "ADC Thread: STOP_ADC() --> Bad", "ERROR", NULL);
        break;
    }

    case 0x2:
    {
        MessageBox(hWnd, "ADC Thread: ReadData() --> Bad", "ERROR", NULL);
        break;
    }

    case 0x3:
    {
        MessageBox(hWnd, "ADC Thread: Timeout is occured!", "ERROR", NULL);
        break;
    }

    case 0x4:
    {
        MessageBox(hWnd, "ADC Thread: Writing data file error!", "ERROR", NULL);
        break;
    }

    case 0x5:
    {
        // если программа была злобно прервана, предъявим ноту протеста
        MessageBox(hWnd, "ADC Thread: The program was terminated!", "ERROR", NULL);
        break;
    }

    case 0x6:
    {
        MessageBox(hWnd, "ADC Thread: START_ADC() --> Bad", "ERROR", NULL);
        break;
    }

    case 0x7:
    {
        MessageBox(hWnd, "ADC Thread: Can't cancel ending input and output (I/O) operations!", "ERROR", NULL);
        break;
    }

    default:
    {
        MessageBox(hWnd, "Unknown error!", "ERROR", NULL);
        break;
    }
    }

    return;
}

//------------------------------------------------------------------------
// аварийное завершение программы
//------------------------------------------------------------------------
void AbortProgram(bool AbortionFlag)
{
    // подчищаем интерфейс модуля
    if (pModule)
    {
        // освободим интерфейс модуля
        if (!pModule->ReleaseLInstance())
        {
            MessageBox(hWnd, "ReleaseLInstance() --> Bad!", "ERROR", NULL);
        }
        // обнулим указатель на интерфейс модуля
        pModule = NULL;
    }

    // освободим память буфера
    if (ReadBuffer)
    {
        delete[] ReadBuffer;
        ReadBuffer = NULL;
    }
    // освободим идентификатор потока сбора данных
    if (hReadThread)
    {
        CloseHandle(hReadThread);
        hReadThread = NULL;
    }
    // освободим идентификатор файла данных
    if (hFile != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hFile);
        hFile = INVALID_HANDLE_VALUE;
    }

    // если нужно - аварийно завершаем программу
    if (AbortionFlag)
    {
        exit(0x1);
    }
    // или спокойно выходим из функции   
    else
    {
        return;
    }
}