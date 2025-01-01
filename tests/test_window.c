#include <easyui.h>
#include <assert.h>
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#elif defined(__linux__)
#include <X11/Xlib.h>
#endif

void test_window_creation() {
#ifdef CI_BUILD
    // Skip window creation test in CI environment
    printf("Skipping window creation test in CI environment\n");
#else
    EUI_Window* window = EUI_CreateWindow("Test Window", 100, 100, 400, 300);
    assert(window != NULL);
    assert(window->rect.width == 400);
    assert(window->rect.height == 300);
    EUI_DestroyWindow(window);
    printf("Window creation test passed\n");
#endif
}

void test_basic_types() {
    // Test EUI_Point
    EUI_Point point = {10, 20};
    assert(point.x == 10);
    assert(point.y == 20);
    printf("Basic types test passed\n");
}

int main() {
    test_basic_types();  // Run this test first as it doesn't require a display
    test_window_creation();
    return 0;
}
