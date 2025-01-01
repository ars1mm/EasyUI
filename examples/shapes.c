#include <easyui.h>
#include <math.h>

// Custom styles
static EUI_LineStyle redLine = {
    .color = EUI_RGB(255, 0, 0),
    .width = 2
};

static EUI_ShapeStyle blueRect = {
    .fillColor = EUI_RGB(200, 200, 255),
    .borderColor = EUI_RGB(0, 0, 255),
    .borderWidth = 2
};

static EUI_ShapeStyle redCircle = {
    .fillColor = EUI_RGB(255, 200, 200),
    .borderColor = EUI_RGB(255, 0, 0),
    .borderWidth = 2
};

static EUI_ShapeStyle greenEllipse = {
    .fillColor = EUI_RGB(200, 255, 200),
    .borderColor = EUI_RGB(0, 255, 0),
    .borderWidth = 2
};

static EUI_ShapeStyle yellowTriangle = {
    .fillColor = EUI_RGB(255, 255, 200),
    .borderColor = EUI_RGB(128, 128, 0),
    .borderWidth = 2
};

static EUI_ShapeStyle purpleHexagon = {
    .fillColor = EUI_RGB(255, 200, 255),
    .borderColor = EUI_RGB(255, 0, 255),
    .borderWidth = 2
};

static EUI_LineStyle orangeArc = {
    .color = EUI_RGB(255, 128, 0),
    .width = 2
};

static EUI_TextStyle titleText = {
    .fontFamily = "Arial",
    .fontSize = 20,
    .color = EUI_RGB(0, 0, 0),
    .bold = 0,
    .italic = 0,
    .underline = 0
};

static EUI_TextStyle labelText = {
    .fontFamily = "Arial",
    .fontSize = 12,
    .color = EUI_RGB(0, 0, 0),
    .bold = 0,
    .italic = 0,
    .underline = 0
};

void onPaint(EUI_Window* window) {
    // Draw title
    EUI_DrawTextEx(window, "EasyUI Shapes Demo", 200, 10, &titleText);
    
    // Line
    EUI_DrawLineEx(window, 50, 50, 150, 50, &redLine);
    EUI_DrawTextEx(window, "Line", 80, 30, &labelText);
    
    // Rectangle
    EUI_DrawRectangleEx(window, 50, 100, 100, 60, &blueRect);
    EUI_DrawTextEx(window, "Rectangle", 65, 130, &labelText);
    
    // Circle
    EUI_DrawCircleEx(window, 250, 130, 40, &redCircle);
    EUI_DrawTextEx(window, "Circle", 230, 130, &labelText);
    
    // Ellipse
    EUI_DrawEllipseEx(window, 400, 100, 120, 60, &greenEllipse);
    EUI_DrawTextEx(window, "Ellipse", 440, 130, &labelText);
    
    // Triangle
    EUI_DrawTriangleEx(window, 50, 300, 150, 300, 100, 200, &yellowTriangle);
    EUI_DrawTextEx(window, "Triangle", 80, 270, &labelText);
    
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
    EUI_DrawPolygonEx(window, hexPoints, 6, &purpleHexagon);
    EUI_DrawTextEx(window, "Hexagon", 220, 250, &labelText);
    
    // Arc
    EUI_DrawArcEx(window, 400, 200, 100, 100, 0, 270, &orangeArc);
    EUI_DrawTextEx(window, "Arc", 440, 250, &labelText);
}

void onClick(EUI_Window* window, EUI_Point point) {
    // Add some interactivity - draw a small circle where the user clicks
    EUI_ShapeStyle clickStyle = {
        .fillColor = EUI_RGB(255, 0, 0),
        .borderColor = EUI_RGB(128, 0, 0),
        .borderWidth = 1
    };
    EUI_DrawCircleEx(window, point.x, point.y, 5, &clickStyle);
}

int main() {
    // Create main window
    EUI_Window* window = EUI_CreateWindow("EasyUI Shapes Demo", 100, 100, 600, 400);
    if (!window) {
        return 1;
    }
    
    // Set callbacks
    window->onPaint = onPaint;
    window->onClick = onClick;
    
    // Show and run
    EUI_ShowWindow(window);
    EUI_ProcessMessages();
    
    return 0;
}
