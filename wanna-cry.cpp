#include <windows.h>
#include <string>

#define ID_CLOSE_BUTTON 1
#define ID_LOG_BUTTON   2

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_COMMAND:
        if (LOWORD(wParam) == ID_CLOSE_BUTTON) {
            PostQuitMessage(0);
        }
        else if (LOWORD(wParam) == ID_LOG_BUTTON) {
            MessageBox(hwnd, "Viewing file log...", "File Log", MB_OK);
        }
        break;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Set background and text color
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(255, 0, 0));

        HFONT hFontTitle = CreateFont(
            36, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
            ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_SWISS, "Consolas");

        HFONT hFontSmall = CreateFont(
            18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_SWISS, "Consolas");

        SelectObject(hdc, hFontTitle);
        TextOut(hdc, 50, 40, "YOUR FILES HAVE BEEN", 23);
        TextOut(hdc, 50, 90, "RESTCRED", 8); // Simulated typo

        SelectObject(hdc, hFontSmall);
        TextOut(hdc, 50, 160, "FILES DECRYPTED SUCCESSFULLY", 30);
        TextOut(hdc, 50, 190, "All encrypted files have been successfully decrypted.", 50);
        TextOut(hdc, 50, 215, "Thank you for your cooperation.", 33);

        TextOut(hdc, 50, 270, "TOTAL FILES DECRYPTED: 213,048", 33);
        TextOut(hdc, 50, 300, "TIME ELAPSED: 02:43", 23);
        TextOut(hdc, 50, 330, "KEY: RSA-4096-VALIDATED", 27);

        DeleteObject(hFontTitle);
        DeleteObject(hFontSmall);
        EndPaint(hwnd, &ps);
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "DecryptionNotificationUI";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(20, 0, 0)); // dark red/black bg

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, "Nemesis | 4.4.9.2",
        WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 700, 500,
        NULL, NULL, hInstance, NULL);

    if (!hwnd) return 0;

    // Buttons
    CreateWindow("BUTTON", "CLOSE SESSION",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        100, 390, 200, 40, hwnd, (HMENU)ID_CLOSE_BUTTON, hInstance, NULL);

    CreateWindow("BUTTON", "VIEW FILE LOG",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        360, 390, 200, 40, hwnd, (HMENU)ID_LOG_BUTTON, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Message Loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
