#include <windows.h>
LONG WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);
int StrToInt(char* s)
{
    int temp = 0;
    int i = 0;
    int sign = 0;
    if (s[i] == '-')
    {
        sign = 1;
        i++;
    }
    while (s[i] >= 0x30 && s[i] <= 0x39)
    {
        temp = temp + (s[i] & 0x0F);
        temp = temp * 10;
        i++;
    }
    temp = temp / 10;
    if (sign == 1)
        temp = -temp;
    return(temp);
}
char* IntToStr(int n)
{
    char s[40], t, * temp;
    int i, k;
    int sign = 0;
    i = 0;
    k = n;
    if (k < 0)
    {
        sign = 1;
        k = -k;
    }
    do {
        t = k % 10;
        k = k / 10;
        s[i] = t | 0x30;
        i++;
    } while (k > 0);
    if (sign == 1)
    {
        s[i] = '-';
        i++;
    }
    temp = new char[i];
    k = 0;
    i--;
    while (i >= 0) {
        temp[k] = s[i];
        i--; k++;
    }
    temp[k] = '\0';
    return(temp);
}
int  WINAPI WinMain(HINSTANCE  hInstance,
    HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hwnd;
    MSG msg;
    WNDCLASS w;
    memset(&w, 0, sizeof(WNDCLASS));
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.lpfnWndProc = WndProc;
    w.hInstance = hInstance;
    w.hbrBackground = CreateSolidBrush(RGB(255, 20, 147));
    w.lpszClassName = "MyClass";
    RegisterClass(&w);
    hwnd = CreateWindow("MyClass", "100+-",
        WS_OVERLAPPEDWINDOW,
        500, 300, 500, 380,
        NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
LONG WINAPI WndProc(HWND hwnd, UINT Message,
    WPARAM wparam, LPARAM lparam) {
    HINSTANCE hInst;
    static HWND hPlus, hMinus;
    static HWND hStat;
    TCHAR StrA[100];
    int a, Len;
    switch (Message) {
    case WM_CREATE:
        hInst = ((LPCREATESTRUCT)lparam)->hInstance;
        hMinus = CreateWindow("button", "-1",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            180, 150, 20, 20, hwnd, 0, hInst, NULL);
        ShowWindow(hMinus, SW_SHOWNORMAL);
        hPlus = CreateWindow("button", "+1",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            280, 150, 20, 20, hwnd, 0, hInst, NULL);
        ShowWindow(hPlus, SW_SHOWNORMAL);
        hStat = CreateWindow("static", "100", WS_CHILD | WS_VISIBLE,
            210, 150, 60, 20, hwnd, 0, hInst, NULL);
        ShowWindow(hStat, SW_SHOWNORMAL);
        break;
    case WM_COMMAND:
        if (lparam == (LPARAM)hPlus)
        {
            Len = GetWindowText(hStat, StrA, 100);
            a = StrToInt(StrA);
            a++;
            SetWindowText(hStat, IntToStr(a));
        }
        if (lparam == (LPARAM)hMinus)
        {
            Len = GetWindowText(hStat, StrA, 100);
            a = StrToInt(StrA);
            a--;
            SetWindowText(hStat, IntToStr(a));
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, Message, wparam, lparam);
    }
    return 0;
}