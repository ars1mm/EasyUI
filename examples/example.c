#include "easyui.h"
#include <stdio.h>

void onWindowPaint(EUI_Window* window) {
    // In a real application, we would draw here
    printf("Window paint event\n");
}

void onWindowClick(EUI_Window* window, EUI_Point point) {
    printf("Click at position: x=%d, y=%d\n", point.x, point.y);
}

int main() {
    // Create a window
    EUI_Window* window = EUI_CreateWindow("EasyUI Example", 100, 100, 800, 600);
    if (!window) {
        printf("Failed to create window\n");
        return 1;
    }

    // Set callbacks
    window->onPaint = onWindowPaint;
    window->onClick = onWindowClick;

    // Show the window
    EUI_ShowWindow(window);

    // Main message loop
    EUI_ProcessMessages();

    return 0;
}
