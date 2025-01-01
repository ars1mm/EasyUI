#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "easyui.h"
#include "easyui_platform.h"

// Default styles
const EUI_LineStyle EUI_DEFAULT_LINE_STYLE = {
    .color = RGB(0, 0, 0),
    .thickness = 1
};

const EUI_ShapeStyle EUI_DEFAULT_SHAPE_STYLE = {
    .fillColor = RGB(255, 255, 255),
    .borderColor = RGB(0, 0, 0),
    .borderWidth = 1
};

const EUI_TextStyle EUI_DEFAULT_TEXT_STYLE = {
    .fontName = "Arial",
    .fontSize = 12,
    .color = RGB(0, 0, 0)
};

// Core EasyUI implementation that delegates to platform-specific code
EUI_Window* EUI_CreateWindow(const char* title, int x, int y, int width, int height) {
#if defined(EASYUI_PLATFORM_WINDOWS)
    return EUI_CreateWindowWin32(title, x, y, width, height);
#elif defined(EASYUI_PLATFORM_LINUX)
    return EUI_CreateWindowX11(title, x, y, width, height);
#elif defined(EASYUI_PLATFORM_MACOS)
    return EUI_CreateWindowCocoa(title, x, y, width, height);
#else
    #error "Unsupported platform"
#endif
}

void EUI_ShowWindow(EUI_Window* window) {
#if defined(EASYUI_PLATFORM_WINDOWS)
    EUI_ShowWindowWin32(window);
#elif defined(EASYUI_PLATFORM_LINUX)
    EUI_ShowWindowX11(window);
#elif defined(EASYUI_PLATFORM_MACOS)
    EUI_ShowWindowCocoa(window);
#endif
}

void EUI_ProcessMessages(void) {
#if defined(EASYUI_PLATFORM_WINDOWS)
    EUI_ProcessMessagesWin32();
#elif defined(EASYUI_PLATFORM_LINUX)
    EUI_ProcessMessagesX11();
#elif defined(EASYUI_PLATFORM_MACOS)
    EUI_ProcessMessagesCocoa();
#endif
}

void EUI_DrawRectangleEx(EUI_Window* window, int x, int y, int width, int height, const EUI_ShapeStyle* style) {
#if defined(EASYUI_PLATFORM_WINDOWS)
    EUI_DrawRectangleExWin32(window, x, y, width, height, style);
#elif defined(EASYUI_PLATFORM_LINUX)
    EUI_DrawRectangleExX11(window, x, y, width, height, style);
#elif defined(EASYUI_PLATFORM_MACOS)
    EUI_DrawRectangleExCocoa(window, x, y, width, height, style);
#endif
}

void EUI_DrawTextEx(EUI_Window* window, const char* text, int x, int y, const EUI_TextStyle* style) {
#if defined(EASYUI_PLATFORM_WINDOWS)
    EUI_DrawTextExWin32(window, text, x, y, style);
#elif defined(EASYUI_PLATFORM_LINUX)
    EUI_DrawTextExX11(window, text, x, y, style);
#elif defined(EASYUI_PLATFORM_MACOS)
    EUI_DrawTextExCocoa(window, text, x, y, style);
#endif
}

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

// Drawing functions
void EUI_DrawLine(EUI_Window* window, int x1, int y1, int x2, int y2) {
    EUI_DrawLineEx(window, x1, y1, x2, y2, &EUI_DEFAULT_LINE_STYLE);
}

void EUI_DrawLineEx(EUI_Window* window, int x1, int y1, int x2, int y2, const EUI_LineStyle* style) {
    if (!window || !window->hwnd) return;
    const EUI_LineStyle* s = style ? style : &EUI_DEFAULT_LINE_STYLE;
    
    HDC hdc = GetDC(window->hwnd);
    HPEN pen = CreatePen(PS_SOLID, s->thickness, s->color);
    HPEN oldPen = SelectObject(hdc, pen);
    
    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
    
    SelectObject(hdc, oldPen);
    DeleteObject(pen);
    ReleaseDC(window->hwnd, hdc);
}

void EUI_DrawCircle(EUI_Window* window, int centerX, int centerY, int radius) {
    EUI_DrawCircleEx(window, centerX, centerY, radius, &EUI_DEFAULT_SHAPE_STYLE);
}

void EUI_DrawCircleEx(EUI_Window* window, int centerX, int centerY, int radius, const EUI_ShapeStyle* style) {
    if (!window || !window->hwnd) return;
    const EUI_ShapeStyle* s = style ? style : &EUI_DEFAULT_SHAPE_STYLE;
    
    HDC hdc = GetDC(window->hwnd);
    HPEN pen = CreatePen(PS_SOLID, s->borderWidth, s->borderColor);
    HBRUSH brush = CreateSolidBrush(s->fillColor);
    HPEN oldPen = SelectObject(hdc, pen);
    HBRUSH oldBrush = SelectObject(hdc, brush);
    
    Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
    
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(pen);
    DeleteObject(brush);
    ReleaseDC(window->hwnd, hdc);
}

void EUI_DrawEllipse(EUI_Window* window, int x, int y, int width, int height) {
    EUI_DrawEllipseEx(window, x, y, width, height, &EUI_DEFAULT_SHAPE_STYLE);
}

void EUI_DrawEllipseEx(EUI_Window* window, int x, int y, int width, int height, const EUI_ShapeStyle* style) {
    if (!window || !window->hwnd) return;
    const EUI_ShapeStyle* s = style ? style : &EUI_DEFAULT_SHAPE_STYLE;
    
    HDC hdc = GetDC(window->hwnd);
    HPEN pen = CreatePen(PS_SOLID, s->borderWidth, s->borderColor);
    HBRUSH brush = CreateSolidBrush(s->fillColor);
    HPEN oldPen = SelectObject(hdc, pen);
    HBRUSH oldBrush = SelectObject(hdc, brush);
    
    Ellipse(hdc, x, y, x + width, y + height);
    
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(pen);
    DeleteObject(brush);
    ReleaseDC(window->hwnd, hdc);
}

void EUI_DrawTriangle(EUI_Window* window, int x1, int y1, int x2, int y2, int x3, int y3) {
    EUI_DrawTriangleEx(window, x1, y1, x2, y2, x3, y3, &EUI_DEFAULT_SHAPE_STYLE);
}

void EUI_DrawTriangleEx(EUI_Window* window, int x1, int y1, int x2, int y2, int x3, int y3, const EUI_ShapeStyle* style) {
    if (!window || !window->hwnd) return;
    const EUI_ShapeStyle* s = style ? style : &EUI_DEFAULT_SHAPE_STYLE;
    
    HDC hdc = GetDC(window->hwnd);
    HPEN pen = CreatePen(PS_SOLID, s->borderWidth, s->borderColor);
    HBRUSH brush = CreateSolidBrush(s->fillColor);
    HPEN oldPen = SelectObject(hdc, pen);
    HBRUSH oldBrush = SelectObject(hdc, brush);
    
    POINT points[3] = {{x1, y1}, {x2, y2}, {x3, y3}};
    Polygon(hdc, points, 3);
    
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(pen);
    DeleteObject(brush);
    ReleaseDC(window->hwnd, hdc);
}

void EUI_DrawPolygon(EUI_Window* window, POINT* points, int numPoints) {
    EUI_DrawPolygonEx(window, points, numPoints, &EUI_DEFAULT_SHAPE_STYLE);
}

void EUI_DrawPolygonEx(EUI_Window* window, POINT* points, int numPoints, const EUI_ShapeStyle* style) {
    if (!window || !window->hwnd || !points || numPoints < 3) return;
    const EUI_ShapeStyle* s = style ? style : &EUI_DEFAULT_SHAPE_STYLE;
    
    HDC hdc = GetDC(window->hwnd);
    HPEN pen = CreatePen(PS_SOLID, s->borderWidth, s->borderColor);
    HBRUSH brush = CreateSolidBrush(s->fillColor);
    HPEN oldPen = SelectObject(hdc, pen);
    HBRUSH oldBrush = SelectObject(hdc, brush);
    
    Polygon(hdc, points, numPoints);
    
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(pen);
    DeleteObject(brush);
    ReleaseDC(window->hwnd, hdc);
}

void EUI_DrawArc(EUI_Window* window, int x, int y, int width, int height, int startAngle, int sweepAngle) {
    EUI_DrawArcEx(window, x, y, width, height, startAngle, sweepAngle, &EUI_DEFAULT_LINE_STYLE);
}

void EUI_DrawArcEx(EUI_Window* window, int x, int y, int width, int height, int startAngle, int sweepAngle, const EUI_LineStyle* style) {
    if (!window || !window->hwnd) return;
    const EUI_LineStyle* s = style ? style : &EUI_DEFAULT_LINE_STYLE;
    
    HDC hdc = GetDC(window->hwnd);
    HPEN pen = CreatePen(PS_SOLID, s->thickness, s->color);
    HPEN oldPen = SelectObject(hdc, pen);
    
    // Convert angles from degrees to radians
    double startRad = startAngle * 3.14159265358979323846 / 180.0;
    double sweepRad = sweepAngle * 3.14159265358979323846 / 180.0;
    
    // Calculate start and end points
    int centerX = x + width / 2;
    int centerY = y + height / 2;
    int startX = centerX + (int)(cos(startRad) * width / 2);
    int startY = centerY - (int)(sin(startRad) * height / 2);
    int endX = centerX + (int)(cos(startRad + sweepRad) * width / 2);
    int endY = centerY - (int)(sin(startRad + sweepRad) * height / 2);
    
    Arc(hdc, x, y, x + width, y + height, startX, startY, endX, endY);
    
    SelectObject(hdc, oldPen);
    DeleteObject(pen);
    ReleaseDC(window->hwnd, hdc);
}
