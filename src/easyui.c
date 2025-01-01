#include "easyui.h"
#include "easyui_platform.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

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
EUI_Window* EUI_CreateWindow(const char* title, int x, int y, int width, int height) {
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

void EUI_ShowWindow(EUI_Window* window) {
#ifdef EASYUI_PLATFORM_WINDOWS
    EUI_ShowWindowWin32(window);
#elif defined(EASYUI_PLATFORM_LINUX)
    EUI_ShowWindowX11(window);
#elif defined(EASYUI_PLATFORM_MACOS)
    EUI_ShowWindowCocoa(window);
#endif
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

void EUI_DrawRectangleEx(EUI_Window* window, int x, int y, int width, int height, const EUI_ShapeStyle* style) {
#ifdef EASYUI_PLATFORM_WINDOWS
    HDC hdc = GetDC(window->handle);
    HPEN pen = CreatePen(PS_SOLID, style->borderWidth, style->borderColor);
    HBRUSH brush = CreateSolidBrush(style->fillColor);
    HPEN oldPen = SelectObject(hdc, pen);
    HBRUSH oldBrush = SelectObject(hdc, brush);
    Rectangle(hdc, x, y, x + width, y + height);
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
    XFillRectangle(display, win, gc, x, y, width, height);
    XSetForeground(display, gc, style->borderColor);
    XSetLineAttributes(display, gc, style->borderWidth, LineSolid, CapButt, JoinMiter);
    XDrawRectangle(display, win, gc, x, y, width, height);
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

void EUI_DrawTextEx(EUI_Window* window, const char* text, int x, int y, const EUI_TextStyle* style) {
#ifdef EASYUI_PLATFORM_WINDOWS
    HDC hdc = GetDC(window->handle);
    HFONT font = CreateFont(style->fontSize, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, style->fontFamily);
    HFONT oldFont = SelectObject(hdc, font);
    SetTextColor(hdc, style->color);
    SetBkMode(hdc, TRANSPARENT);
    TextOut(hdc, x, y, text, strlen(text));
    SelectObject(hdc, oldFont);
    DeleteObject(font);
    ReleaseDC(window->handle, hdc);
#elif defined(EASYUI_PLATFORM_LINUX)
    if (!window || !window->handle || !text) return;
    Display* display = XOpenDisplay(NULL);
    Window win = window->handle;
    GC gc = XCreateGC(display, win, 0, NULL);
    XSetForeground(display, gc, style->color);
    char fontname[256];
    snprintf(fontname, sizeof(fontname), "-*-%s-%s-%c-*-*-%d-*-*-*-*-*-*-*",
             style->fontFamily,
             "medium",
             'r',
             style->fontSize);
    XFontStruct* font = XLoadQueryFont(display, fontname);
    if (font) {
        XSetFont(display, gc, font->fid);
        XDrawString(display, win, gc, x, y + font->ascent, text, strlen(text));
        XFreeFont(display, font);
    } else {
        XDrawString(display, win, gc, x, y, text, strlen(text));
    }
    XFreeGC(display, gc);
    XFlush(display);
#elif defined(EASYUI_PLATFORM_MACOS)
    if (!window || !window->handle || !text) return;
    NSWindow* win = window->handle;
    NSView* view = [win contentView];
    [view lockFocus];
    NSString* nsText = [NSString stringWithUTF8String:text];
    NSFont* font = [NSFont fontWithName:[NSString stringWithUTF8String:style->fontFamily]
                                  size:style->fontSize];
    if (!font) {
        font = [NSFont systemFontOfSize:style->fontSize];
    }
    NSDictionary* attrs = @{
        NSFontAttributeName: font,
        NSForegroundColorAttributeName: [NSColor colorWithRed:((style->color >> 16) & 0xFF) / 255.0
                                               green:((style->color >> 8) & 0xFF) / 255.0
                                                blue:(style->color & 0xFF) / 255.0
                                               alpha:1.0]
    };
    [nsText drawAtPoint:NSMakePoint(x, y) withAttributes:attrs];
    [view unlockFocus];
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
    // Convert EUI_Point to POINT
    POINT* winPoints = (POINT*)malloc(numPoints * sizeof(POINT));
    for (int i = 0; i < numPoints; i++) {
        winPoints[i].x = points[i].x;
        winPoints[i].y = points[i].y;
    }
    // Draw polygon using Windows GDI
    HPEN pen = CreatePen(PS_SOLID, style->strokeWidth, style->strokeColor);
    HBRUSH brush = CreateSolidBrush(style->fillColor);
    SelectObject(window->dc, pen);
    SelectObject(window->dc, brush);
    Polygon(window->dc, winPoints, numPoints);
    DeleteObject(pen);
    DeleteObject(brush);
    free(winPoints);
#elif defined(EASYUI_PLATFORM_LINUX)
    // Convert EUI_Point to XPoint
    XPoint* xPoints = (XPoint*)malloc(numPoints * sizeof(XPoint));
    for (int i = 0; i < numPoints; i++) {
        xPoints[i].x = points[i].x;
        xPoints[i].y = points[i].y;
    }
    // Draw polygon using X11
    Display* display = XOpenDisplay(NULL);
    if (display) {
        GC gc = XCreateGC(display, window->handle, 0, NULL);
        XSetForeground(display, gc, style->strokeColor);
        XSetLineAttributes(display, gc, style->strokeWidth, LineSolid, CapRound, JoinRound);
        XFillPolygon(display, window->handle, gc, xPoints, numPoints, Complex, CoordModeOrigin);
        XSetForeground(display, gc, style->fillColor);
        XDrawLines(display, window->handle, gc, xPoints, numPoints, CoordModeOrigin);
        XFreeGC(display, gc);
        XFlush(display);
    }
    free(xPoints);
#elif defined(EASYUI_PLATFORM_MACOS)
    // Cocoa implementation will be in a separate .m file
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
