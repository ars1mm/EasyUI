#ifndef EASYUI_GRAPHICS_H
#define EASYUI_GRAPHICS_H

#include <windows.h>
#include "../window/window.h"
#include "../styles/styles.h"

// Drawing functions
void EUI_DrawLine(EUI_Window* window, int x1, int y1, int x2, int y2);
void EUI_DrawLineEx(EUI_Window* window, int x1, int y1, int x2, int y2, const EUI_LineStyle* style);

void EUI_DrawRectangle(EUI_Window* window, int x, int y, int width, int height);
void EUI_DrawRectangleEx(EUI_Window* window, int x, int y, int width, int height, const EUI_ShapeStyle* style);

void EUI_DrawCircle(EUI_Window* window, int centerX, int centerY, int radius);
void EUI_DrawCircleEx(EUI_Window* window, int centerX, int centerY, int radius, const EUI_ShapeStyle* style);

void EUI_DrawEllipse(EUI_Window* window, int x, int y, int width, int height);
void EUI_DrawEllipseEx(EUI_Window* window, int x, int y, int width, int height, const EUI_ShapeStyle* style);

void EUI_DrawTriangle(EUI_Window* window, int x1, int y1, int x2, int y2, int x3, int y3);
void EUI_DrawTriangleEx(EUI_Window* window, int x1, int y1, int x2, int y2, int x3, int y3, const EUI_ShapeStyle* style);

void EUI_DrawPolygon(EUI_Window* window, POINT* points, int numPoints);
void EUI_DrawPolygonEx(EUI_Window* window, POINT* points, int numPoints, const EUI_ShapeStyle* style);

void EUI_DrawArc(EUI_Window* window, int x, int y, int width, int height, int startAngle, int sweepAngle);
void EUI_DrawArcEx(EUI_Window* window, int x, int y, int width, int height, int startAngle, int sweepAngle, const EUI_LineStyle* style);

void EUI_DrawText(EUI_Window* window, const char* text, int x, int y);
void EUI_DrawTextEx(EUI_Window* window, const char* text, int x, int y, const EUI_TextStyle* style);

#endif // EASYUI_GRAPHICS_H
