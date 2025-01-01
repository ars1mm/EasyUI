#include "easyui.h"
#include "easyui_platform.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef EASYUI_PLATFORM_WINDOWS

// Windows-specific window implementation
static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    EUI_Window* window = (EUI_Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    
    switch (uMsg) {
        case WM_PAINT:
            if (window && window->onPaint) {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                window->onPaint(window);
                EndPaint(hwnd, &ps);
            }
            return 0;
            
        case WM_LBUTTONDOWN:
            if (window && window->onClick) {
                EUI_Point pt = {LOWORD(lParam), HIWORD(lParam)};
                window->onClick(window, pt);
            }
            return 0;
            
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

EUI_Window* EUI_CreateWindowWin32(const char* title, int x, int y, int width, int height) {
    EUI_Window* window = (EUI_Window*)malloc(sizeof(EUI_Window));
    if (!window) return NULL;

    // Initialize window structure
    memset(window, 0, sizeof(EUI_Window));
    window->rect.x = x;
    window->rect.y = y;
    window->rect.width = width;
    window->rect.height = height;
    window->style = EUI_WINDOW_NORMAL;

    // Register window class if not already registered
    static BOOL classRegistered = FALSE;
    if (!classRegistered) {
        WNDCLASSEX wc = {0};
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszClassName = "EasyUIWindow";
        
        if (!RegisterClassEx(&wc)) {
            free(window);
            return NULL;
        }
        classRegistered = TRUE;
    }

    // Create the window
    window->handle = CreateWindowEx(
        0,                          // Extended style
        "EasyUIWindow",             // Class name
        title,                      // Window title
        WS_OVERLAPPEDWINDOW,        // Style
        x, y,                       // Position
        width, height,              // Size
        NULL,                       // Parent window
        NULL,                       // Menu
        GetModuleHandle(NULL),      // Instance
        NULL                        // Additional data
    );

    if (!window->handle) {
        free(window);
        return NULL;
    }

    // Store window pointer in window's user data
    SetWindowLongPtr(window->handle, GWLP_USERDATA, (LONG_PTR)window);

    return window;
}

void EUI_ShowWindowWin32(EUI_Window* window) {
    if (window && window->handle) {
        ShowWindow(window->handle, SW_SHOW);
        UpdateWindow(window->handle);
    }
}

void EUI_ProcessMessagesWin32(void) {
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

#endif /* EASYUI_PLATFORM_WINDOWS */
