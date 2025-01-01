#ifndef EASYUI_WINDOW_H
#define EUI_WINDOW_H

#include "../core/types.h"

// Window styles
#define EUI_WINDOW_NORMAL     0x00000001
#define EUI_WINDOW_POPUP      0x00000002

// Window functions
EUI_Window* EUI_CreateWindow(const char* title, int x, int y, int width, int height);
void EUI_ShowWindow(EUI_Window* window);
void EUI_DestroyWindow(EUI_Window* window);
void EUI_ProcessMessages(void);

#endif // EUI_WINDOW_H
