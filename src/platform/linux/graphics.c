#include "easyui.h"
#include "easyui_platform.h"

#ifdef EASYUI_PLATFORM_LINUX

#include <X11/Xlib.h>
#include <stdlib.h>

static Display* display = NULL;

static GC create_gc(Display* display, Window window) {
    GC gc = XCreateGC(display, window, 0, NULL);
    XSetForeground(display, gc, BlackPixel(display, DefaultScreen(display)));
    return gc;
}

void EUI_DrawLine(EUI_Window* window, int x1, int y1, int x2, int y2) {
    if (!window || !display) return;
    
    GC gc = create_gc(display, window->handle);
    XDrawLine(display, window->handle, gc, x1, y1, x2, y2);
    XFreeGC(display, gc);
    XFlush(display);
}

void EUI_DrawRectangle(EUI_Window* window, int x, int y, int width, int height) {
    if (!window || !display) return;
    
    GC gc = create_gc(display, window->handle);
    XDrawRectangle(display, window->handle, gc, x, y, width, height);
    XFreeGC(display, gc);
    XFlush(display);
}

void EUI_DrawCircle(EUI_Window* window, int centerX, int centerY, int radius) {
    if (!window || !display) return;
    
    GC gc = create_gc(display, window->handle);
    XDrawArc(display, window->handle, gc, 
        centerX - radius, centerY - radius,
        radius * 2, radius * 2,
        0, 360 * 64);  // X11 uses degrees * 64 for angles
    XFreeGC(display, gc);
    XFlush(display);
}

void EUI_DrawText(EUI_Window* window, const char* text, int x, int y) {
    if (!window || !display || !text) return;
    
    GC gc = create_gc(display, window->handle);
    XDrawString(display, window->handle, gc, x, y, text, strlen(text));
    XFreeGC(display, gc);
    XFlush(display);
}

void EUI_DrawRectangleEx(EUI_Window* window, int x, int y, int width, int height, const EUI_ShapeStyle* style) {
    EUI_DrawRectangle(window, x, y, width, height);
}

void EUI_DrawTextEx(EUI_Window* window, const char* text, int x, int y, const EUI_TextStyle* style) {
    EUI_DrawText(window, text, x, y);
}

#endif /* EASYUI_PLATFORM_LINUX */
