#include "easyui.h"
#include "easyui_platform.h"
#include <stdlib.h>

void EUI_DestroyWindow(EUI_Window* window) {
#ifdef EASYUI_PLATFORM_WINDOWS
    if (window) {
        if (window->handle) {
            DestroyWindow((HWND)window->handle);
        }
        free(window);
    }
#elif defined(EASYUI_PLATFORM_LINUX)
    if (window) {
        if (window->handle) {
            Display* display = XOpenDisplay(NULL);
            if (display) {
                XDestroyWindow(display, window->handle);
                XCloseDisplay(display);
            }
        }
        free(window);
    }
#elif defined(EASYUI_PLATFORM_MACOS)
    if (window) {
        if (window->handle) {
            [(NSWindow*)window->handle close];
        }
        free(window);
    }
#endif
}
