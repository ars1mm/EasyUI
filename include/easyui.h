#ifndef EASYUI_H
#define EASYUI_H

#include "easyui_platform.h"
#include <stdlib.h>

// Style structures
typedef struct EUI_ShapeStyle {
    unsigned long fillColor;
    unsigned long strokeColor;
    int strokeWidth;
} EUI_ShapeStyle;

typedef struct EUI_TextStyle {
    unsigned long color;
    const char* fontFamily;
    int fontSize;
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
struct EUI_Window* EUI_CreateWindow(const char* title, int x, int y, int width, int height);
void EUI_ShowWindow(struct EUI_Window* window);
void EUI_DestroyWindow(struct EUI_Window* window);
void EUI_ProcessMessages(void);

// Drawing functions
void EUI_DrawLine(struct EUI_Window* window, int x1, int y1, int x2, int y2);
void EUI_DrawLineEx(struct EUI_Window* window, int x1, int y1, int x2, int y2, const EUI_LineStyle* style);

void EUI_DrawRectangle(struct EUI_Window* window, int x, int y, int width, int height, const struct EUI_ShapeStyle* style);
void EUI_DrawRectangleEx(struct EUI_Window* window, int x, int y, int width, int height, const EUI_ShapeStyle* style);

void EUI_DrawCircle(struct EUI_Window* window, int centerX, int centerY, int radius);
void EUI_DrawCircleEx(struct EUI_Window* window, int centerX, int centerY, int radius, const EUI_ShapeStyle* style);

void EUI_DrawEllipse(struct EUI_Window* window, int centerX, int centerY, int radiusX, int radiusY);
void EUI_DrawEllipseEx(struct EUI_Window* window, int centerX, int centerY, int radiusX, int radiusY, const EUI_ShapeStyle* style);

void EUI_DrawTriangle(struct EUI_Window* window, int x1, int y1, int x2, int y2, int x3, int y3);
void EUI_DrawTriangleEx(struct EUI_Window* window, int x1, int y1, int x2, int y2, int x3, int y3, const EUI_ShapeStyle* style);

void EUI_DrawPolygon(struct EUI_Window* window, const EUI_Point* points, int numPoints, const struct EUI_ShapeStyle* style);
void EUI_DrawPolygonEx(struct EUI_Window* window, EUI_Point* points, int numPoints, const EUI_ShapeStyle* style);

void EUI_DrawArc(struct EUI_Window* window, int x, int y, int width, int height, int startAngle, int sweepAngle);
void EUI_DrawArcEx(struct EUI_Window* window, int x, int y, int width, int height, int startAngle, int sweepAngle, const EUI_LineStyle* style);

void EUI_DrawText(struct EUI_Window* window, const char* text, int x, int y, const struct EUI_TextStyle* style);
void EUI_DrawTextEx(struct EUI_Window* window, const char* text, int x, int y, const EUI_TextStyle* style);

#endif /* EASYUI_H */
