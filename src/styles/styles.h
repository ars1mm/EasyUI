#ifndef EASYUI_STYLES_H
#define EASYUI_STYLES_H

#include <windows.h>

// Style structures
typedef struct {
    COLORREF color;
    int thickness;
} EUI_LineStyle;

typedef struct {
    COLORREF fillColor;
    COLORREF borderColor;
    int borderWidth;
} EUI_ShapeStyle;

typedef struct {
    const char* fontName;
    int fontSize;
    COLORREF color;
} EUI_TextStyle;

// Default styles
extern const EUI_LineStyle EUI_DEFAULT_LINE_STYLE;
extern const EUI_ShapeStyle EUI_DEFAULT_SHAPE_STYLE;
extern const EUI_TextStyle EUI_DEFAULT_TEXT_STYLE;

#endif // EASYUI_STYLES_H
