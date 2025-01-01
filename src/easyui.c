#include "easyui.h"
#include "easyui_platform.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// Default styles
const EUI_LineStyle EUI_DEFAULT_LINE_STYLE = {
    .color = EUI_RGB(0, 0, 0),
    .width = 1
};

const EUI_ShapeStyle EUI_DEFAULT_SHAPE_STYLE = {
    .fillColor = EUI_RGB(255, 255, 255),
    .borderColor = EUI_RGB(0, 0, 0),
    .borderWidth = 1
};

const EUI_TextStyle EUI_DEFAULT_TEXT_STYLE = {
    .fontFamily = "Arial",
    .fontSize = 12,
    .color = EUI_RGB(0, 0, 0),
    .bold = 0,
    .italic = 0,
    .underline = 0
};

// Core EasyUI implementation that delegates to platform-specific code
struct EUI_Window* EUI_CreateWindow(const char* title, int x, int y, int width, int height) {
#ifdef EASYUI_PLATFORM_WINDOWS
    return EUI_CreateWindowWin32(title, x, y, width, height);
#elif defined(EASYUI_PLATFORM_LINUX)
    return EUI_CreateWindowX11(title, x, y, width, height);
#elif defined(EASYUI_PLATFORM_MACOS)
    return EUI_CreateWindowCocoa(title, x, y, width, height);
#else
    return NULL;
#endif
}

void EUI_ShowWindow(struct EUI_Window* window) {
    if (!window) return;
#ifdef EASYUI_PLATFORM_WINDOWS
    EUI_ShowWindowWin32(window);
#elif defined(EASYUI_PLATFORM_LINUX)
    EUI_ShowWindowX11(window);
#elif defined(EASYUI_PLATFORM_MACOS)
    EUI_ShowWindowCocoa(window);
#endif
}

void EUI_DestroyWindow(struct EUI_Window* window) {
    if (!window) return;
#ifdef EASYUI_PLATFORM_WINDOWS
    EUI_DestroyWindowWin32(window);
#elif defined(EASYUI_PLATFORM_LINUX)
    EUI_DestroyWindowX11(window);
#elif defined(EASYUI_PLATFORM_MACOS)
    EUI_DestroyWindowCocoa(window);
#endif
    free(window);
}

void EUI_ProcessMessages(void) {
#ifdef EASYUI_PLATFORM_WINDOWS
    EUI_ProcessMessagesWin32();
#elif defined(EASYUI_PLATFORM_LINUX)
    EUI_ProcessMessagesX11();
#elif defined(EASYUI_PLATFORM_MACOS)
    EUI_ProcessMessagesCocoa();
#endif
}

// Drawing functions that delegate to platform-specific implementations
void EUI_DrawRectangle(struct EUI_Window* window, int x, int y, int width, int height, const struct EUI_ShapeStyle* style) {
#ifdef EASYUI_PLATFORM_WINDOWS
    // Windows implementation
    if (!window || !style) return;
    HDC hdc = GetDC((HWND)window->handle);
    if (!hdc) return;

    HPEN hPen = CreatePen(PS_SOLID, style->strokeWidth, style->strokeColor);
    HBRUSH hBrush = CreateSolidBrush(style->fillColor);
    
    HPEN oldPen = SelectObject(hdc, hPen);
    HBRUSH oldBrush = SelectObject(hdc, hBrush);

    Rectangle(hdc, x, y, x + width, y + height);

    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(hPen);
    DeleteObject(hBrush);
    ReleaseDC((HWND)window->handle, hdc);
#elif defined(EASYUI_PLATFORM_LINUX)
    // Linux implementation will be in platform/linux/graphics.c
    EUI_DrawRectangleX11(window, x, y, width, height, style);
#elif defined(EASYUI_PLATFORM_MACOS)
    // macOS implementation will be in platform/macos/graphics.m
    EUI_DrawRectangleCocoa(window, x, y, width, height, style);
#endif
}

void EUI_DrawText(struct EUI_Window* window, const char* text, int x, int y, const struct EUI_TextStyle* style) {
#ifdef EASYUI_PLATFORM_WINDOWS
    // Windows implementation
    if (!window || !text || !style) return;
    HDC hdc = GetDC((HWND)window->handle);
    if (!hdc) return;

    SetTextColor(hdc, style->color);
    TextOutA(hdc, x, y, text, (int)strlen(text));
    ReleaseDC((HWND)window->handle, hdc);
#elif defined(EASYUI_PLATFORM_LINUX)
    // Linux implementation will be in platform/linux/graphics.c
    EUI_DrawTextX11(window, text, x, y, style);
#elif defined(EASYUI_PLATFORM_MACOS)
    // macOS implementation will be in platform/macos/graphics.m
    EUI_DrawTextCocoa(window, text, x, y, style);
#endif
}

void EUI_DrawPolygon(struct EUI_Window* window, const EUI_Point* points, int numPoints, const struct EUI_ShapeStyle* style) {
#ifdef EASYUI_PLATFORM_WINDOWS
    // Windows implementation
    if (!window || !points || numPoints < 3 || !style) return;
    HDC hdc = GetDC((HWND)window->handle);
    if (!hdc) return;

    POINT* winPoints = (POINT*)malloc(numPoints * sizeof(POINT));
    if (!winPoints) {
        ReleaseDC((HWND)window->handle, hdc);
        return;
    }

    for (int i = 0; i < numPoints; i++) {
        winPoints[i].x = points[i].x;
        winPoints[i].y = points[i].y;
    }

    HPEN hPen = CreatePen(PS_SOLID, style->strokeWidth, style->strokeColor);
    HBRUSH hBrush = CreateSolidBrush(style->fillColor);

    HPEN oldPen = SelectObject(hdc, hPen);
    HBRUSH oldBrush = SelectObject(hdc, hBrush);

    Polygon(hdc, winPoints, numPoints);

    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(hPen);
    DeleteObject(hBrush);
    free(winPoints);
    ReleaseDC((HWND)window->handle, hdc);
#elif defined(EASYUI_PLATFORM_LINUX)
    // Linux implementation will be in platform/linux/graphics.c
    EUI_DrawPolygonX11(window, points, numPoints, style);
#elif defined(EASYUI_PLATFORM_MACOS)
    // macOS implementation will be in platform/macos/graphics.m
    EUI_DrawPolygonCocoa(window, points, numPoints, style);
#endif
}

void EUI_DrawLine(EUI_Window* window, int x1, int y1, int x2, int y2) {
    EUI_DrawLineEx(window, x1, y1, x2, y2, &EUI_DEFAULT_LINE_STYLE);
}

void EUI_DrawLineEx(EUI_Window* window, int x1, int y1, int x2, int y2, const EUI_LineStyle* style) {
#ifdef EASYUI_PLATFORM_WINDOWS
    HDC hdc = GetDC(window->handle);
    HPEN pen = CreatePen(PS_SOLID, style->width, style->color);
    HPEN oldPen = SelectObject(hdc, pen);
    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
    SelectObject(hdc, oldPen);
    DeleteObject(pen);
    ReleaseDC(window->handle, hdc);
#elif defined(EASYUI_PLATFORM_LINUX)
    if (!window || !window->handle) return;
    Display* display = XOpenDisplay(NULL);
    Window win = window->handle;
    GC gc = XCreateGC(display, win, 0, NULL);
    XSetForeground(display, gc, style->color);
    XSetLineAttributes(display, gc, style->width, LineSolid, CapButt, JoinMiter);
    XDrawLine(display, win, gc, x1, y1, x2, y2);
    XFreeGC(display, gc);
    XFlush(display);
#elif defined(EASYUI_PLATFORM_MACOS)
    if (!window || !window->handle) return;
    NSWindow* win = window->handle;
    NSView* view = [win contentView];
    [view lockFocus];
    NSBezierPath* path = [NSBezierPath bezierPath];
    [path moveToPoint:NSMakePoint(x1, y1)];
    [path lineToPoint:NSMakePoint(x2, y2)];
    [path setLineWidth:style->width];
    [[NSColor colorWithRed:((style->color >> 16) & 0xFF) / 255.0
                    green:((style->color >> 8) & 0xFF) / 255.0
                     blue:(style->color & 0xFF) / 255.0
                    alpha:1.0] set];
    [path stroke];
    [view unlockFocus];
#endif
}

void EUI_DrawCircle(EUI_Window* window, int centerX, int centerY, int radius) {
    EUI_DrawCircleEx(window, centerX, centerY, radius, &EUI_DEFAULT_SHAPE_STYLE);
}

void EUI_DrawCircleEx(EUI_Window* window, int centerX, int centerY, int radius, const EUI_ShapeStyle* style) {
#ifdef EASYUI_PLATFORM_WINDOWS
    HDC hdc = GetDC(window->handle);
    HPEN pen = CreatePen(PS_SOLID, style->borderWidth, style->borderColor);
    HBRUSH brush = CreateSolidBrush(style->fillColor);
    HPEN oldPen = SelectObject(hdc, pen);
    HBRUSH oldBrush = SelectObject(hdc, brush);
    Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(pen);
    DeleteObject(brush);
    ReleaseDC(window->handle, hdc);
#elif defined(EASYUI_PLATFORM_LINUX)
    if (!window || !window->handle) return;
    Display* display = XOpenDisplay(NULL);
    Window win = window->handle;
    GC gc = XCreateGC(display, win, 0, NULL);
    XSetForeground(display, gc, style->fillColor);
    XFillArc(display, win, gc, centerX - radius, centerY - radius, radius * 2, radius * 2, 0, 360 * 64);
    XSetForeground(display, gc, style->borderColor);
    XSetLineAttributes(display, gc, style->borderWidth, LineSolid, CapButt, JoinMiter);
    XDrawArc(display, win, gc, centerX - radius, centerY - radius, radius * 2, radius * 2, 0, 360 * 64);
    XFreeGC(display, gc);
    XFlush(display);
#elif defined(EASYUI_PLATFORM_MACOS)
    if (!window || !window->handle) return;
    NSWindow* win = window->handle;
    NSView* view = [win contentView];
    [view lockFocus];
    NSRect rect = NSMakeRect(centerX - radius, centerY - radius, radius * 2, radius * 2);
    NSColor* fillColor = [NSColor colorWithRed:((style->fillColor >> 16) & 0xFF) / 255.0
                                        green:((style->fillColor >> 8) & 0xFF) / 255.0
                                         blue:(style->fillColor & 0xFF) / 255.0
                                        alpha:1.0];
    [fillColor set];
    NSRectFill(rect);
    NSColor* borderColor = [NSColor colorWithRed:((style->borderColor >> 16) & 0xFF) / 255.0
                                         green:((style->borderColor >> 8) & 0xFF) / 255.0
                                          blue:(style->borderColor & 0xFF) / 255.0
                                         alpha:1.0];
    [borderColor set];
    NSFrameRect(rect);
    [view unlockFocus];
#endif
}

void EUI_DrawEllipse(EUI_Window* window, int x, int y, int width, int height) {
    EUI_DrawEllipseEx(window, x, y, width, height, &EUI_DEFAULT_SHAPE_STYLE);
}

void EUI_DrawEllipseEx(EUI_Window* window, int x, int y, int width, int height, const EUI_ShapeStyle* style) {
#ifdef EASYUI_PLATFORM_WINDOWS
    HDC hdc = GetDC(window->handle);
    HPEN pen = CreatePen(PS_SOLID, style->borderWidth, style->borderColor);
    HBRUSH brush = CreateSolidBrush(style->fillColor);
    HPEN oldPen = SelectObject(hdc, pen);
    HBRUSH oldBrush = SelectObject(hdc, brush);
    Ellipse(hdc, x, y, x + width, y + height);
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(pen);
    DeleteObject(brush);
    ReleaseDC(window->handle, hdc);
#elif defined(EASYUI_PLATFORM_LINUX)
    if (!window || !window->handle) return;
    Display* display = XOpenDisplay(NULL);
    Window win = window->handle;
    GC gc = XCreateGC(display, win, 0, NULL);
    XSetForeground(display, gc, style->fillColor);
    XFillEllipse(display, win, gc, x, y, width, height);
    XSetForeground(display, gc, style->borderColor);
    XSetLineAttributes(display, gc, style->borderWidth, LineSolid, CapButt, JoinMiter);
    XDrawEllipse(display, win, gc, x, y, width, height);
    XFreeGC(display, gc);
    XFlush(display);
#elif defined(EASYUI_PLATFORM_MACOS)
    if (!window || !window->handle) return;
    NSWindow* win = window->handle;
    NSView* view = [win contentView];
    [view lockFocus];
    NSRect rect = NSMakeRect(x, y, width, height);
    NSColor* fillColor = [NSColor colorWithRed:((style->fillColor >> 16) & 0xFF) / 255.0
                                        green:((style->fillColor >> 8) & 0xFF) / 255.0
                                         blue:(style->fillColor & 0xFF) / 255.0
                                        alpha:1.0];
    [fillColor set];
    NSRectFill(rect);
    NSColor* borderColor = [NSColor colorWithRed:((style->borderColor >> 16) & 0xFF) / 255.0
                                         green:((style->borderColor >> 8) & 0xFF) / 255.0
                                          blue:(style->borderColor & 0xFF) / 255.0
                                         alpha:1.0];
    [borderColor set];
    NSFrameRect(rect);
    [view unlockFocus];
#endif
}

void EUI_DrawTriangle(EUI_Window* window, int x1, int y1, int x2, int y2, int x3, int y3) {
    EUI_DrawTriangleEx(window, x1, y1, x2, y2, x3, y3, &EUI_DEFAULT_SHAPE_STYLE);
}

void EUI_DrawTriangleEx(EUI_Window* window, int x1, int y1, int x2, int y2, int x3, int y3, const EUI_ShapeStyle* style) {
#ifdef EASYUI_PLATFORM_WINDOWS
    HDC hdc = GetDC(window->handle);
    HPEN pen = CreatePen(PS_SOLID, style->borderWidth, style->borderColor);
    HBRUSH brush = CreateSolidBrush(style->fillColor);
    HPEN oldPen = SelectObject(hdc, pen);
    HBRUSH oldBrush = SelectObject(hdc, brush);
    POINT points[3] = {{x1, y1}, {x2, y2}, {x3, y3}};
    Polygon(hdc, points, 3);
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(pen);
    DeleteObject(brush);
    ReleaseDC(window->handle, hdc);
#elif defined(EASYUI_PLATFORM_LINUX)
    if (!window || !window->handle) return;
    Display* display = XOpenDisplay(NULL);
    Window win = window->handle;
    GC gc = XCreateGC(display, win, 0, NULL);
    XSetForeground(display, gc, style->fillColor);
    XFillPolygon(display, win, gc, points, 3, Convex, CoordModeOrigin);
    XSetForeground(display, gc, style->borderColor);
    XSetLineAttributes(display, gc, style->borderWidth, LineSolid, CapButt, JoinMiter);
    XDrawPolygon(display, win, gc, points, 3, Convex, CoordModeOrigin);
    XFreeGC(display, gc);
    XFlush(display);
#elif defined(EASYUI_PLATFORM_MACOS)
    if (!window || !window->handle) return;
    NSWindow* win = window->handle;
    NSView* view = [win contentView];
    [view lockFocus];
    NSBezierPath* path = [NSBezierPath bezierPath];
    [path moveToPoint:NSMakePoint(x1, y1)];
    [path lineToPoint:NSMakePoint(x2, y2)];
    [path lineToPoint:NSMakePoint(x3, y3)];
    [path closePath];
    NSColor* fillColor = [NSColor colorWithRed:((style->fillColor >> 16) & 0xFF) / 255.0
                                        green:((style->fillColor >> 8) & 0xFF) / 255.0
                                         blue:(style->fillColor & 0xFF) / 255.0
                                        alpha:1.0];
    [fillColor set];
    [path fill];
    NSColor* borderColor = [NSColor colorWithRed:((style->borderColor >> 16) & 0xFF) / 255.0
                                         green:((style->borderColor >> 8) & 0xFF) / 255.0
                                          blue:(style->borderColor & 0xFF) / 255.0
                                         alpha:1.0];
    [borderColor set];
    [path setLineWidth:style->borderWidth];
    [path stroke];
    [view unlockFocus];
#endif
}

void EUI_DrawPolygon(EUI_Window* window, EUI_Point* points, int numPoints) {
    EUI_ShapeStyle style = { 0 };
    style.fillColor = EUI_RGB(255, 255, 255);
    style.strokeColor = EUI_RGB(0, 0, 0);
    style.strokeWidth = 1;
    EUI_DrawPolygonEx(window, points, numPoints, &style);
}

void EUI_DrawPolygonEx(EUI_Window* window, EUI_Point* points, int numPoints, const EUI_ShapeStyle* style) {
#ifdef EASYUI_PLATFORM_WINDOWS
    if (!window || !points || numPoints < 3 || !style) return;

    HDC hdc = GetDC((HWND)window->handle);
    if (!hdc) return;

    HPEN hPen = CreatePen(PS_SOLID, style->strokeWidth, style->strokeColor);
    HBRUSH hBrush = CreateSolidBrush(style->fillColor);

    POINT* winPoints = (POINT*)malloc(numPoints * sizeof(POINT));
    if (!winPoints) {
        DeleteObject(hPen);
        DeleteObject(hBrush);
        ReleaseDC((HWND)window->handle, hdc);
        return;
    }

    for (int i = 0; i < numPoints; i++) {
        winPoints[i].x = points[i].x;
        winPoints[i].y = points[i].y;
    }

    HPEN oldPen = SelectObject(hdc, hPen);
    HBRUSH oldBrush = SelectObject(hdc, hBrush);

    Polygon(hdc, winPoints, numPoints);

    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(hPen);
    DeleteObject(hBrush);
    free(winPoints);
    ReleaseDC((HWND)window->handle, hdc);
#elif defined(EASYUI_PLATFORM_LINUX)
    if (!window || !window->handle || !points || numPoints < 3 || !style) return;
    Display* display = XOpenDisplay(NULL);
    if (!display) return;
    Window win = window->handle;
    GC gc = XCreateGC(display, win, 0, NULL);
    XSetForeground(display, gc, style->strokeColor);
    XSetLineAttributes(display, gc, style->strokeWidth, LineSolid, CapRound, JoinRound);
    XPoint* xPoints = (XPoint*)malloc(numPoints * sizeof(XPoint));
    if (!xPoints) {
        XFreeGC(display, gc);
        return;
    }
    for (int i = 0; i < numPoints; i++) {
        xPoints[i].x = points[i].x;
        xPoints[i].y = points[i].y;
    }
    XFillPolygon(display, win, gc, xPoints, numPoints, Complex, CoordModeOrigin);
    XSetForeground(display, gc, style->fillColor);
    XDrawLines(display, win, gc, xPoints, numPoints, CoordModeOrigin);
    XFreeGC(display, gc);
    XFlush(display);
    free(xPoints);
#elif defined(EASYUI_PLATFORM_MACOS)
    if (!window || !window->handle || !points || numPoints < 3 || !style) return;
    NSWindow* win = window->handle;
    NSView* view = [win contentView];
    [view lockFocus];
    NSBezierPath* path = [NSBezierPath bezierPath];
    [path moveToPoint:NSMakePoint(points[0].x, points[0].y)];
    for (int i = 1; i < numPoints; i++) {
        [path lineToPoint:NSMakePoint(points[i].x, points[i].y)];
    }
    [path closePath];
    NSColor* fillColor = [NSColor colorWithRed:((style->fillColor >> 16) & 0xFF) / 255.0
                                        green:((style->fillColor >> 8) & 0xFF) / 255.0
                                         blue:(style->fillColor & 0xFF) / 255.0
                                        alpha:1.0];
    [fillColor set];
    [path fill];
    NSColor* borderColor = [NSColor colorWithRed:((style->strokeColor >> 16) & 0xFF) / 255.0
                                         green:((style->strokeColor >> 8) & 0xFF) / 255.0
                                          blue:(style->strokeColor & 0xFF) / 255.0
                                         alpha:1.0];
    [borderColor set];
    [path setLineWidth:style->strokeWidth];
    [path stroke];
    [view unlockFocus];
#endif
}

void EUI_DrawArc(EUI_Window* window, int x, int y, int width, int height, int startAngle, int sweepAngle) {
    EUI_DrawArcEx(window, x, y, width, height, startAngle, sweepAngle, &EUI_DEFAULT_LINE_STYLE);
}

void EUI_DrawArcEx(EUI_Window* window, int x, int y, int width, int height, int startAngle, int sweepAngle, const EUI_LineStyle* style) {
#ifdef EASYUI_PLATFORM_WINDOWS
    HDC hdc = GetDC(window->handle);
    HPEN pen = CreatePen(PS_SOLID, style->width, style->color);
    HPEN oldPen = SelectObject(hdc, pen);
    Arc(hdc, x, y, x + width, y + height, x + width / 2, y + height / 2, x + width / 2, y + height / 2);
    SelectObject(hdc, oldPen);
    DeleteObject(pen);
    ReleaseDC(window->handle, hdc);
#elif defined(EASYUI_PLATFORM_LINUX)
    if (!window || !window->handle) return;
    Display* display = XOpenDisplay(NULL);
    Window win = window->handle;
    GC gc = XCreateGC(display, win, 0, NULL);
    XSetForeground(display, gc, style->color);
    XSetLineAttributes(display, gc, style->width, LineSolid, CapButt, JoinMiter);
    XDrawArc(display, win, gc, x, y, width, height, startAngle * 64, sweepAngle * 64);
    XFreeGC(display, gc);
    XFlush(display);
#elif defined(EASYUI_PLATFORM_MACOS)
    if (!window || !window->handle) return;
    NSWindow* win = window->handle;
    NSView* view = [win contentView];
    [view lockFocus];
    NSBezierPath* path = [NSBezierPath bezierPath];
    [path appendBezierPathWithArcWithCenter:NSMakePoint(x + width / 2, y + height / 2)
                                     radius:width / 2
                                     startAngle:startAngle
                                       endAngle:startAngle + sweepAngle
                                      clockwise:YES];
    [[NSColor colorWithRed:((style->color >> 16) & 0xFF) / 255.0
                    green:((style->color >> 8) & 0xFF) / 255.0
                     blue:(style->color & 0xFF) / 255.0
                    alpha:1.0] set];
    [path setLineWidth:style->width];
    [path stroke];
    [view unlockFocus];
#endif
}

// Convenience functions
void EUI_DrawRectangle(EUI_Window* window, int x, int y, int width, int height) {
    EUI_DrawRectangleEx(window, x, y, width, height, &EUI_DEFAULT_SHAPE_STYLE);
}

void EUI_DrawText(EUI_Window* window, const char* text, int x, int y) {
    EUI_DrawTextEx(window, text, x, y, &EUI_DEFAULT_TEXT_STYLE);
}

#ifdef EASYUI_PLATFORM_MACOS
// Implement drawing functions in platform-specific files
void EUI_DrawRectangle(struct EUI_Window* window, int x, int y, int width, int height, const struct EUI_ShapeStyle* style) {
    // This should be implemented in src/platform/macos/graphics.m
}

void EUI_DrawText(struct EUI_Window* window, const char* text, int x, int y, const struct EUI_TextStyle* style) {
    // This should be implemented in src/platform/macos/graphics.m
}

void EUI_DrawLine(struct EUI_Window* window, int x1, int y1, int x2, int y2, const struct EUI_ShapeStyle* style) {
    // This should be implemented in src/platform/macos/graphics.m
}

void EUI_DrawPolygon(struct EUI_Window* window, const EUI_Point* points, int numPoints, const struct EUI_ShapeStyle* style) {
    // Implement in platform/macos/graphics.m
    NSWindow* win = window->handle;
    NSView* view = [win contentView];
    [view lockFocus];
    NSBezierPath* path = [NSBezierPath bezierPath];
    [path moveToPoint:NSMakePoint(points[0].x, points[0].y)];
    for (int i = 1; i < numPoints; i++) {
        [path lineToPoint:NSMakePoint(points[i].x, points[i].y)];
    }
    [path closePath];
    NSColor* fillColor = [NSColor colorWithRed:((style->fillColor >> 16) & 0xFF) / 255.0
                                        green:((style->fillColor >> 8) & 0xFF) / 255.0
                                         blue:(style->fillColor & 0xFF) / 255.0
                                        alpha:1.0];
    [fillColor set];
    [path fill];
    NSColor* borderColor = [NSColor colorWithRed:((style->strokeColor >> 16) & 0xFF) / 255.0
                                         green:((style->strokeColor >> 8) & 0xFF) / 255.0
                                          blue:(style->strokeColor & 0xFF) / 255.0
                                         alpha:1.0];
    [borderColor set];
    [path setLineWidth:style->strokeWidth];
    [path stroke];
    [view unlockFocus];
}
#endif
