#include "easyui.h"
#include <assert.h>
#include <stdio.h>

// Basic structure tests that don't require a window
void test_point_struct() {
    EUI_Point point = {10, 20};
    assert(point.x == 10);
    assert(point.y == 20);
    printf("Point struct test passed\n");
}

void test_rect_struct() {
    EUI_Rect rect = {10, 20, 30, 40};
    assert(rect.x == 10);
    assert(rect.y == 20);
    assert(rect.width == 30);
    assert(rect.height == 40);
    printf("Rect struct test passed\n");
}

void test_shape_style() {
    struct EUI_ShapeStyle style = {
        .fillColor = 0xFF0000,
        .strokeColor = 0x00FF00,
        .strokeWidth = 2
    };
    assert(style.fillColor == 0xFF0000);
    assert(style.strokeColor == 0x00FF00);
    assert(style.strokeWidth == 2);
    printf("Shape style test passed\n");
}

#ifndef CI_BUILD
void test_window_creation() {
    struct EUI_Window* window = EUI_CreateWindow("Test Window", 100, 100, 800, 600);
    assert(window != NULL);
    EUI_DestroyWindow(window);
    printf("Window creation test passed\n");
}
#endif

int main() {
    printf("Running EasyUI tests...\n");
    
    // Run basic structure tests
    test_point_struct();
    test_rect_struct();
    test_shape_style();
    
#ifndef CI_BUILD
    // Run window tests only when not in CI
    test_window_creation();
#endif
    
    printf("All tests passed!\n");
    return 0;
}
