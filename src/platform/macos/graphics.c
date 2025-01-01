#include "easyui.h"
#include "easyui_platform.h"

#ifdef EASYUI_PLATFORM_MACOS

// Stub implementation for macOS graphics
void EUI_DrawRectangleEx(EUI_Window* window, int x, int y, int width, int height, const EUI_ShapeStyle* style) {
    // TODO: Implement Cocoa rectangle drawing
}

void EUI_DrawTextEx(EUI_Window* window, const char* text, int x, int y, const EUI_TextStyle* style) {
    // TODO: Implement Cocoa text drawing
}

#endif /* EASYUI_PLATFORM_MACOS */
