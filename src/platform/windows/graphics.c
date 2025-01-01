#include "easyui.h"
#include "easyui_platform.h"

#ifdef EASYUI_PLATFORM_WINDOWS

void EUI_DrawRectangleEx(EUI_Window* window, int x, int y, int width, int height, const EUI_ShapeStyle* style) {
    if (!window || !window->hwnd || !style) return;

    HDC hdc = GetDC(window->hwnd);
    if (!hdc) return;

    HBRUSH fillBrush = CreateSolidBrush(style->fillColor);
    HPEN borderPen = CreatePen(PS_SOLID, style->borderWidth, style->borderColor);

    SelectObject(hdc, fillBrush);
    SelectObject(hdc, borderPen);

    Rectangle(hdc, x, y, x + width, y + height);

    DeleteObject(fillBrush);
    DeleteObject(borderPen);
    ReleaseDC(window->hwnd, hdc);
}

void EUI_DrawTextEx(EUI_Window* window, const char* text, int x, int y, const EUI_TextStyle* style) {
    if (!window || !window->hwnd || !text || !style) return;

    HDC hdc = GetDC(window->hwnd);
    if (!hdc) return;

    HFONT font = CreateFont(
        style->fontSize,        // Height
        0,                      // Width
        0,                      // Escapement
        0,                      // Orientation
        style->bold ? FW_BOLD : FW_NORMAL,  // Weight
        style->italic,          // Italic
        style->underline,       // Underline
        0,                      // StrikeOut
        DEFAULT_CHARSET,        // CharSet
        OUT_DEFAULT_PRECIS,     // OutputPrecision
        CLIP_DEFAULT_PRECIS,    // ClipPrecision
        DEFAULT_QUALITY,        // Quality
        DEFAULT_PITCH | FF_DONTCARE,  // PitchAndFamily
        style->fontFamily       // FaceName
    );

    SelectObject(hdc, font);
    SetTextColor(hdc, style->color);
    SetBkMode(hdc, TRANSPARENT);

    TextOut(hdc, x, y, text, strlen(text));

    DeleteObject(font);
    ReleaseDC(window->hwnd, hdc);
}

#endif /* EASYUI_PLATFORM_WINDOWS */
