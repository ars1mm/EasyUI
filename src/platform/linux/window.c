#include "easyui.h"
#include "easyui_platform.h"

#ifdef EASYUI_PLATFORM_LINUX

#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>

static Display* display = NULL;

EUI_Window* EUI_CreateWindow(const char* title, int x, int y, int width, int height) {
    if (!display) {
        display = XOpenDisplay(NULL);
        if (!display) {
            return NULL;
        }
    }

    Window root = DefaultRootWindow(display);
    int screen = DefaultScreen(display);
    
    XSetWindowAttributes attrs;
    attrs.background_pixel = WhitePixel(display, screen);
    attrs.event_mask = ExposureMask | KeyPressMask | ButtonPressMask;

    Window win = XCreateWindow(display, root,
        x, y, width, height, 0,
        CopyFromParent, InputOutput,
        CopyFromParent, CWBackPixel | CWEventMask,
        &attrs);

    if (!win) {
        return NULL;
    }

    XStoreName(display, win, title);

    EUI_Window* window = (EUI_Window*)malloc(sizeof(EUI_Window));
    if (!window) {
        XDestroyWindow(display, win);
        return NULL;
    }

    window->handle = win;
    window->rect.x = x;
    window->rect.y = y;
    window->rect.width = width;
    window->rect.height = height;
    window->style = EUI_WINDOW_NORMAL;
    window->onPaint = NULL;
    window->onClick = NULL;

    return window;
}

void EUI_ShowWindow(EUI_Window* window) {
    if (!window || !display) return;
    XMapWindow(display, window->handle);
    XFlush(display);
}

void EUI_ProcessMessages(void) {
    if (!display) return;

    XEvent event;
    while (XPending(display)) {
        XNextEvent(display, &event);
        // Handle events here
    }
}

void EUI_DestroyWindow(EUI_Window* window) {
    if (!window || !display) return;
    XDestroyWindow(display, window->handle);
    free(window);
}

#endif /* EASYUI_PLATFORM_LINUX */
