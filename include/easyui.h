#ifndef EASYUI_H
#define EASYUI_H

#include <windows.h>
#include <stdint.h>

// Window and control styles
#define EUI_WINDOW_NORMAL     0x00000001
#define EUI_WINDOW_POPUP      0x00000002
#define EUI_CONTROL_BUTTON    0x00000004
#define EUI_CONTROL_TEXTBOX   0x00000008

// Colors
typedef uint32_t EUI_Color;

// Basic structures
typedef struct {
    int x;
    int y;
} EUI_Point;

typedef struct {
    int width;
    int height;
} EUI_Size;

typedef struct {
    int x;
    int y;
    int width;
    int height;
} EUI_Rect;

// Window structure
typedef struct EUI_Window {
    HWND hwnd;
    char* title;
    EUI_Rect rect;
    uint32_t style;
    void (*onPaint)(struct EUI_Window* window);
    void (*onClick)(struct EUI_Window* window, EUI_Point point);
} EUI_Window;

// Function declarations
EUI_Window* EUI_CreateWindow(const char* title, int x, int y, int width, int height);
void EUI_ShowWindow(EUI_Window* window);
void EUI_DestroyWindow(EUI_Window* window);
void EUI_ProcessMessages(void);

// Drawing functions
void EUI_DrawLine(EUI_Window* window, int x1, int y1, int x2, int y2, COLORREF color, int thickness);
void EUI_DrawRectangle(EUI_Window* window, int x, int y, int width, int height, COLORREF fillColor, COLORREF borderColor, int borderWidth);
void EUI_DrawCircle(EUI_Window* window, int centerX, int centerY, int radius, COLORREF fillColor, COLORREF borderColor, int borderWidth);
void EUI_DrawEllipse(EUI_Window* window, int x, int y, int width, int height, COLORREF fillColor, COLORREF borderColor, int borderWidth);
void EUI_DrawTriangle(EUI_Window* window, int x1, int y1, int x2, int y2, int x3, int y3, COLORREF fillColor, COLORREF borderColor, int borderWidth);
void EUI_DrawPolygon(EUI_Window* window, POINT* points, int numPoints, COLORREF fillColor, COLORREF borderColor, int borderWidth);
void EUI_DrawArc(EUI_Window* window, int x, int y, int width, int height, int startAngle, int sweepAngle, COLORREF color, int thickness);
void EUI_DrawText(EUI_Window* window, const char* text, int x, int y, const char* fontName, int fontSize, COLORREF color);

#endif // EASYUI_H
