#include "easyui.h"
#include "easyui_platform.h"

#ifdef EASYUI_PLATFORM_LINUX

// Stub implementation for Linux
EUI_Window* EUI_CreateWindow(const char* title, int x, int y, int width, int height) {
    // TODO: Implement X11 window creation
    return NULL;
}

void EUI_ShowWindow(EUI_Window* window) {
    // TODO: Implement X11 window show
}

void EUI_ProcessMessages(void) {
    // TODO: Implement X11 message loop
}

#endif /* EASYUI_PLATFORM_LINUX */
