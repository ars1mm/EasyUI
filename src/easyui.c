#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "easyui.h"
#include <stdlib.h>
#include <string.h>

// Window procedure
static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    EUI_Window* window = (EUI_Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    
    switch (uMsg) {
        case WM_CREATE: {
            CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)cs->lpCreateParams);
            return 0;
        }
        
        case WM_PAINT:
            if (window && window->onPaint) {
                window->onPaint(window);
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

// Initialize the library
static BOOL EUI_Initialize(void) {
    static BOOL initialized = FALSE;
    if (initialized) return TRUE;
    
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "EasyUI_Window";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassEx(&wc)) {
        return FALSE;
    }
    
    initialized = TRUE;
    return TRUE;
}

// Create a window
EUI_Window* EUI_CreateWindow(const char* title, int x, int y, int width, int height) {
    if (!EUI_Initialize()) return NULL;
    
    EUI_Window* window = (EUI_Window*)malloc(sizeof(EUI_Window));
    if (!window) return NULL;
    
    window->title = _strdup(title);
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
        window->title,
        WS_OVERLAPPEDWINDOW,
        x, y, width, height,
        NULL, NULL,
        GetModuleHandle(NULL),
        window
    );
    
    if (!window->hwnd) {
        free(window->title);
        free(window);
        return NULL;
    }
    
    return window;
}

// Show window
void EUI_ShowWindow(EUI_Window* window) {
    if (window && window->hwnd) {
        ShowWindow(window->hwnd, SW_SHOW);
        UpdateWindow(window->hwnd);
    }
}

// Destroy window
void EUI_DestroyWindow(EUI_Window* window) {
    if (window) {
        if (window->hwnd) {
            DestroyWindow(window->hwnd);
        }
        free(window->title);
        free(window);
    }
}

// Process messages
void EUI_ProcessMessages(void) {
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

// Drawing functions
void EUI_DrawLine(EUI_Window* window, int x1, int y1, int x2, int y2, COLORREF color, int thickness) {
    if (!window || !window->hwnd) return;
    
    HDC hdc = GetDC(window->hwnd);
    HPEN pen = CreatePen(PS_SOLID, thickness, color);
    HPEN oldPen = SelectObject(hdc, pen);
    
    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
    
    SelectObject(hdc, oldPen);
    DeleteObject(pen);
    ReleaseDC(window->hwnd, hdc);
}

void EUI_DrawRectangle(EUI_Window* window, int x, int y, int width, int height, COLORREF fillColor, COLORREF borderColor, int borderWidth) {
    if (!window || !window->hwnd) return;
    
    HDC hdc = GetDC(window->hwnd);
    HPEN pen = CreatePen(PS_SOLID, borderWidth, borderColor);
    HBRUSH brush = CreateSolidBrush(fillColor);
    HPEN oldPen = SelectObject(hdc, pen);
    HBRUSH oldBrush = SelectObject(hdc, brush);
    
    Rectangle(hdc, x, y, x + width, y + height);
    
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(pen);
    DeleteObject(brush);
    ReleaseDC(window->hwnd, hdc);
}

void EUI_DrawCircle(EUI_Window* window, int centerX, int centerY, int radius, COLORREF fillColor, COLORREF borderColor, int borderWidth) {
    if (!window || !window->hwnd) return;
    
    HDC hdc = GetDC(window->hwnd);
    HPEN pen = CreatePen(PS_SOLID, borderWidth, borderColor);
    HBRUSH brush = CreateSolidBrush(fillColor);
    HPEN oldPen = SelectObject(hdc, pen);
    HBRUSH oldBrush = SelectObject(hdc, brush);
    
    Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
    
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(pen);
    DeleteObject(brush);
    ReleaseDC(window->hwnd, hdc);
}

void EUI_DrawEllipse(EUI_Window* window, int x, int y, int width, int height, COLORREF fillColor, COLORREF borderColor, int borderWidth) {
    if (!window || !window->hwnd) return;
    
    HDC hdc = GetDC(window->hwnd);
    HPEN pen = CreatePen(PS_SOLID, borderWidth, borderColor);
    HBRUSH brush = CreateSolidBrush(fillColor);
    HPEN oldPen = SelectObject(hdc, pen);
    HBRUSH oldBrush = SelectObject(hdc, brush);
    
    Ellipse(hdc, x, y, x + width, y + height);
    
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(pen);
    DeleteObject(brush);
    ReleaseDC(window->hwnd, hdc);
}

void EUI_DrawTriangle(EUI_Window* window, int x1, int y1, int x2, int y2, int x3, int y3, COLORREF fillColor, COLORREF borderColor, int borderWidth) {
    if (!window || !window->hwnd) return;
    
    HDC hdc = GetDC(window->hwnd);
    HPEN pen = CreatePen(PS_SOLID, borderWidth, borderColor);
    HBRUSH brush = CreateSolidBrush(fillColor);
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

void EUI_DrawPolygon(EUI_Window* window, POINT* points, int numPoints, COLORREF fillColor, COLORREF borderColor, int borderWidth) {
    if (!window || !window->hwnd || !points || numPoints < 3) return;
    
    HDC hdc = GetDC(window->hwnd);
    HPEN pen = CreatePen(PS_SOLID, borderWidth, borderColor);
    HBRUSH brush = CreateSolidBrush(fillColor);
    HPEN oldPen = SelectObject(hdc, pen);
    HBRUSH oldBrush = SelectObject(hdc, brush);
    
    Polygon(hdc, points, numPoints);
    
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(pen);
    DeleteObject(brush);
    ReleaseDC(window->hwnd, hdc);
}

void EUI_DrawArc(EUI_Window* window, int x, int y, int width, int height, int startAngle, int sweepAngle, COLORREF color, int thickness) {
    if (!window || !window->hwnd) return;
    
    HDC hdc = GetDC(window->hwnd);
    HPEN pen = CreatePen(PS_SOLID, thickness, color);
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

void EUI_DrawText(EUI_Window* window, const char* text, int x, int y, const char* fontName, int fontSize, COLORREF color) {
    if (!window || !window->hwnd || !text) return;
    
    HDC hdc = GetDC(window->hwnd);
    HFONT font = CreateFont(fontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                          DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                          DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, fontName);
    HFONT oldFont = SelectObject(hdc, font);
    
    SetTextColor(hdc, color);
    SetBkMode(hdc, TRANSPARENT);
    TextOut(hdc, x, y, text, strlen(text));
    
    SelectObject(hdc, oldFont);
    DeleteObject(font);
    ReleaseDC(window->hwnd, hdc);
}
