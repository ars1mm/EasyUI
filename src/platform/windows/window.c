#include "easyui.h"
#include "easyui_platform.h"

#ifdef EASYUI_PLATFORM_WINDOWS

// Windows-specific window implementation
EUI_Window* EUI_CreateWindow(const char* title, int x, int y, int width, int height) {
    EUI_Window* window = (EUI_Window*)malloc(sizeof(EUI_Window));
    if (!window) return NULL;

    // Initialize window structure
    memset(window, 0, sizeof(EUI_Window));

    // Register window class if not already registered
    static BOOL classRegistered = FALSE;
    if (!classRegistered) {
        WNDCLASSEX wc = {0};
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = EUI_WindowProc;
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
    window->hwnd = CreateWindowEx(
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

    if (!window->hwnd) {
        free(window);
        return NULL;
    }

    // Store window pointer in window's user data
    SetWindowLongPtr(window->hwnd, GWLP_USERDATA, (LONG_PTR)window);

    return window;
}

void EUI_ShowWindow(EUI_Window* window) {
    if (window && window->hwnd) {
        ShowWindow(window->hwnd, SW_SHOW);
        UpdateWindow(window->hwnd);
    }
}

void EUI_ProcessMessages(void) {
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

#endif /* EASYUI_PLATFORM_WINDOWS */
