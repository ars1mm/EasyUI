#ifndef EASYUI_H
#define EASYUI_H

#include "easyui_platform.h"

// Point structure
typedef struct {
    int x;
    int y;
} EUI_Point;

// Size structure
typedef struct {
    int width;
    int height;
} EUI_Size;

// Rect structure
typedef struct {
    int x;
    int y;
    int width;
    int height;
} EUI_Rect;

// Style structures
typedef struct {
    unsigned long color;
    int width;
} EUI_LineStyle;

typedef struct {
    unsigned long fillColor;
    unsigned long borderColor;
    int borderWidth;
} EUI_ShapeStyle;

typedef struct {
    unsigned long color;
    int fontSize;
    const char* fontFamily;
    int bold;
    int italic;
    int underline;
} EUI_TextStyle;

// Window styles
typedef enum {
    EUI_WINDOW_NORMAL = 0,
    EUI_WINDOW_BORDERLESS = 1,
    EUI_WINDOW_FULLSCREEN = 2
} EUI_WindowStyle;

// Window structure
typedef struct EUI_Window {
    EUI_Rect rect;
    EUI_WindowStyle style;
    EUI_NativeWindow handle;
    void (*onPaint)(struct EUI_Window*);
    void (*onClick)(struct EUI_Window*, EUI_Point);
} EUI_Window;

// Default styles
extern const EUI_LineStyle EUI_DEFAULT_LINE_STYLE;
extern const EUI_ShapeStyle EUI_DEFAULT_SHAPE_STYLE;
extern const EUI_TextStyle EUI_DEFAULT_TEXT_STYLE;

// Window functions
EUI_Window* EUI_CreateWindow(const char* title, int x, int y, int width, int height);
void EUI_ShowWindow(EUI_Window* window);
void EUI_DestroyWindow(EUI_Window* window);
void EUI_ProcessMessages(void);

// Drawing functions
void EUI_DrawLine(EUI_Window* window, int x1, int y1, int x2, int y2);
void EUI_DrawLineEx(EUI_Window* window, int x1, int y1, int x2, int y2, const EUI_LineStyle* style);

void EUI_DrawRectangle(EUI_Window* window, int x, int y, int width, int height);
void EUI_DrawRectangleEx(EUI_Window* window, int x, int y, int width, int height, const EUI_ShapeStyle* style);

void EUI_DrawCircle(EUI_Window* window, int centerX, int centerY, int radius);
void EUI_DrawCircleEx(EUI_Window* window, int centerX, int centerY, int radius, const EUI_ShapeStyle* style);

void EUI_DrawEllipse(EUI_Window* window, int centerX, int centerY, int radiusX, int radiusY);
void EUI_DrawEllipseEx(EUI_Window* window, int centerX, int centerY, int radiusX, int radiusY, const EUI_ShapeStyle* style);

void EUI_DrawTriangle(EUI_Window* window, int x1, int y1, int x2, int y2, int x3, int y3);
void EUI_DrawTriangleEx(EUI_Window* window, int x1, int y1, int x2, int y2, int x3, int y3, const EUI_ShapeStyle* style);

void EUI_DrawPolygon(EUI_Window* window, POINT* points, int numPoints);
void EUI_DrawPolygonEx(EUI_Window* window, POINT* points, int numPoints, const EUI_ShapeStyle* style);

void EUI_DrawArc(EUI_Window* window, int x, int y, int width, int height, int startAngle, int sweepAngle);
void EUI_DrawArcEx(EUI_Window* window, int x, int y, int width, int height, int startAngle, int sweepAngle, const EUI_LineStyle* style);

void EUI_DrawText(EUI_Window* window, const char* text, int x, int y);
void EUI_DrawTextEx(EUI_Window* window, const char* text, int x, int y, const EUI_TextStyle* style);

#endif /* EASYUI_H */
