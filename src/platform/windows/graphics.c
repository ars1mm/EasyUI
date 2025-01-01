#include "easyui.h"
#include "easyui_platform.h"

#ifdef EASYUI_PLATFORM_WINDOWS

void EUI_DrawRectangleEx(EUI_Window* window, int x, int y, int width, int height, const EUI_ShapeStyle* style) {
    if (!window || !window->handle || !style) return;
    
    HDC hdc = GetDC(window->handle);
    if (!hdc) return;

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
}

void EUI_DrawTextEx(EUI_Window* window, const char* text, int x, int y, const EUI_TextStyle* style) {
    if (!window || !window->handle || !text || !style) return;
    
    HDC hdc = GetDC(window->handle);
    if (!hdc) return;
    
    HFONT font = CreateFont(
        style->fontSize,                // Height
        0,                             // Width
        0,                             // Escapement
        0,                             // Orientation
        style->bold ? FW_BOLD : FW_NORMAL, // Weight
        style->italic,                 // Italic
        style->underline,              // Underline
        0,                             // StrikeOut
        ANSI_CHARSET,                  // CharSet
        OUT_DEFAULT_PRECIS,            // OutPrecision
        CLIP_DEFAULT_PRECIS,           // ClipPrecision
        DEFAULT_QUALITY,               // Quality
        DEFAULT_PITCH | FF_DONTCARE,   // PitchAndFamily
        style->fontFamily              // Face Name
    );
    
    HFONT oldFont = SelectObject(hdc, font);
    SetTextColor(hdc, style->color);
    SetBkMode(hdc, TRANSPARENT);
    
    TextOut(hdc, x, y, text, strlen(text));
    
    SelectObject(hdc, oldFont);
    DeleteObject(font);
    
    ReleaseDC(window->handle, hdc);
}

#endif /* EASYUI_PLATFORM_WINDOWS */
