#include "easyui.h"
#include "easyui_platform.h"

#ifdef EASYUI_PLATFORM_LINUX

// Stub implementation for Linux graphics
void EUI_DrawRectangleEx(EUI_Window* window, int x, int y, int width, int height, const EUI_ShapeStyle* style) {
    // TODO: Implement X11 rectangle drawing
}

void EUI_DrawTextEx(EUI_Window* window, const char* text, int x, int y, const EUI_TextStyle* style) {
    // TODO: Implement X11 text drawing
}

#endif /* EASYUI_PLATFORM_LINUX */
