#ifndef EASYUI_TYPES_H
#define EASYUI_TYPES_H

#include <windows.h>
#include <stdint.h>

// Forward declaration
typedef struct EUI_Window EUI_Window;

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

// Window structure
struct EUI_Window {
    HWND hwnd;
    EUI_Rect rect;
    uint32_t style;
    void (*onPaint)(EUI_Window*);
    void (*onClick)(EUI_Window*, EUI_Point);
};

#endif // EASYUI_TYPES_H
