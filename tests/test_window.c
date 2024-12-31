#include <easyui.h>
#include <assert.h>
#include <stdio.h>

void test_window_creation() {
    EUI_Window* window = EUI_CreateWindow("Test Window", 100, 100, 400, 300);
    assert(window != NULL);
    assert(window->rect.width == 400);
    assert(window->rect.height == 300);
    EUI_DestroyWindow(window);
    printf("Window creation test passed\n");
}

int main() {
    test_window_creation();
    return 0;
}
