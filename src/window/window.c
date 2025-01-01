#include "window.h"
#include <stdlib.h>

// Window procedure
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

// Window functions
EUI_Window* EUI_CreateWindow(const char* title, int x, int y, int width, int height) {
    static WNDCLASSEX wc = {0};
    static BOOL registered = FALSE;
    
    if (!registered) {
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = "EasyUI_Window";
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        
        if (!RegisterClassEx(&wc)) {
            return NULL;
        }
        registered = TRUE;
    }
    
    EUI_Window* window = (EUI_Window*)malloc(sizeof(EUI_Window));
    if (!window) {
        return NULL;
    }
    
    window->rect.x = x;
    window->rect.y = y;
    window->rect.width = width;
    window->rect.height = height;
    window->style = EUI_WINDOW_NORMAL;
    window->onPaint = NULL;
    window->onClick = NULL;
    
    window->hwnd = CreateWindowEx(
        0,
        "EasyUI_Window",
        title,
        WS_OVERLAPPEDWINDOW,
        x, y, width, height,
        NULL,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );
    
    if (!window->hwnd) {
        free(window);
        return NULL;
    }
    
    SetWindowLongPtr(window->hwnd, GWLP_USERDATA, (LONG_PTR)window);
    
    return window;
}

void EUI_ShowWindow(EUI_Window* window) {
    if (window && window->hwnd) {
        ShowWindow(window->hwnd, SW_SHOW);
        UpdateWindow(window->hwnd);
    }
}

void EUI_DestroyWindow(EUI_Window* window) {
    if (window) {
        if (window->hwnd) {
            DestroyWindow(window->hwnd);
        }
        free(window);
    }
}

void EUI_ProcessMessages(void) {
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
