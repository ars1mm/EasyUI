#include "easyui.h"
#include "easyui_platform.h"

#ifdef EASYUI_PLATFORM_MACOS

// Stub implementation for macOS
EUI_Window* EUI_CreateWindow(const char* title, int x, int y, int width, int height) {
    // TODO: Implement Cocoa window creation
    return NULL;
}

void EUI_ShowWindow(EUI_Window* window) {
    // TODO: Implement Cocoa window show
}

void EUI_ProcessMessages(void) {
    // TODO: Implement Cocoa run loop
}

#endif /* EASYUI_PLATFORM_MACOS */
