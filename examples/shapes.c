#include <easyui.h>
#include <windows.h>
#include <math.h>

void onPaint(EUI_Window* window) {
    // Draw various shapes to demonstrate the new functions
    
    // Line
    EUI_DrawLine(window, 50, 50, 150, 50, RGB(255, 0, 0), 2);  // Red line
    EUI_DrawText(window, "Line", 80, 30, "Arial", 12, RGB(0, 0, 0));
    
    // Rectangle
    EUI_DrawRectangle(window, 50, 100, 100, 60, RGB(200, 200, 255), RGB(0, 0, 255), 2);  // Blue rectangle
    EUI_DrawText(window, "Rectangle", 65, 130, "Arial", 12, RGB(0, 0, 0));
    
    // Circle
    EUI_DrawCircle(window, 250, 130, 40, RGB(255, 200, 200), RGB(255, 0, 0), 2);  // Red circle
    EUI_DrawText(window, "Circle", 230, 130, "Arial", 12, RGB(0, 0, 0));
    
    // Ellipse
    EUI_DrawEllipse(window, 400, 100, 120, 60, RGB(200, 255, 200), RGB(0, 255, 0), 2);  // Green ellipse
    EUI_DrawText(window, "Ellipse", 440, 130, "Arial", 12, RGB(0, 0, 0));
    
    // Triangle
    EUI_DrawTriangle(window, 50, 300, 150, 300, 100, 200, 
                    RGB(255, 255, 200), RGB(128, 128, 0), 2);  // Yellow triangle
    EUI_DrawText(window, "Triangle", 80, 270, "Arial", 12, RGB(0, 0, 0));
    
    // Regular polygon (hexagon)
    POINT hexPoints[6];
    int centerX = 250;
    int centerY = 250;
    int radius = 40;
    for (int i = 0; i < 6; i++) {
        double angle = i * 3.14159265358979323846 * 2 / 6;
        hexPoints[i].x = centerX + (int)(cos(angle) * radius);
        hexPoints[i].y = centerY + (int)(sin(angle) * radius);
    }
    EUI_DrawPolygon(window, hexPoints, 6, RGB(255, 200, 255), RGB(255, 0, 255), 2);  // Purple hexagon
    EUI_DrawText(window, "Hexagon", 220, 250, "Arial", 12, RGB(0, 0, 0));
    
    // Arc
    EUI_DrawArc(window, 400, 200, 100, 100, 0, 270, RGB(255, 128, 0), 2);  // Orange arc
    EUI_DrawText(window, "Arc", 440, 250, "Arial", 12, RGB(0, 0, 0));
    
    // Draw title
    EUI_DrawText(window, "EasyUI Shapes Demo", 200, 10, "Arial", 20, RGB(0, 0, 0));
}

void onClick(EUI_Window* window, EUI_Point point) {
    // Add some interactivity - draw a small circle where the user clicks
    EUI_DrawCircle(window, point.x, point.y, 5, RGB(255, 0, 0), RGB(128, 0, 0), 1);
}

int main() {
    EUI_Window* window = EUI_CreateWindow("Shapes Demo", 100, 100, 600, 400);
    if (!window) {
        return 1;
    }
    
    window->onPaint = onPaint;
    window->onClick = onClick;
    
    EUI_ShowWindow(window);
    EUI_ProcessMessages();
    
    return 0;
}
