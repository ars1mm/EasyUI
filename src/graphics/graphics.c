#include "graphics.h"
#include <math.h>

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

void EUI_DrawRectangle(EUI_Window* window, int x, int y, int width, int height) {
    EUI_DrawRectangleEx(window, x, y, width, height, &EUI_DEFAULT_SHAPE_STYLE);
}

void EUI_DrawRectangleEx(EUI_Window* window, int x, int y, int width, int height, const EUI_ShapeStyle* style) {
    if (!window || !window->hwnd) return;
    const EUI_ShapeStyle* s = style ? style : &EUI_DEFAULT_SHAPE_STYLE;
    
    HDC hdc = GetDC(window->hwnd);
    HPEN pen = CreatePen(PS_SOLID, s->borderWidth, s->borderColor);
    HBRUSH brush = CreateSolidBrush(s->fillColor);
    HPEN oldPen = SelectObject(hdc, pen);
    HBRUSH oldBrush = SelectObject(hdc, brush);
    
    Rectangle(hdc, x, y, x + width, y + height);
    
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(pen);
    DeleteObject(brush);
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

void EUI_DrawText(EUI_Window* window, const char* text, int x, int y) {
    EUI_DrawTextEx(window, text, x, y, &EUI_DEFAULT_TEXT_STYLE);
}

void EUI_DrawTextEx(EUI_Window* window, const char* text, int x, int y, const EUI_TextStyle* style) {
    if (!window || !window->hwnd || !text) return;
    const EUI_TextStyle* s = style ? style : &EUI_DEFAULT_TEXT_STYLE;
    
    HDC hdc = GetDC(window->hwnd);
    HFONT font = CreateFont(s->fontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                          DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                          DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, s->fontName);
    HFONT oldFont = SelectObject(hdc, font);
    
    SetTextColor(hdc, s->color);
    SetBkMode(hdc, TRANSPARENT);
    TextOut(hdc, x, y, text, strlen(text));
    
    SelectObject(hdc, oldFont);
    DeleteObject(font);
    ReleaseDC(window->hwnd, hdc);
}
