#include <easyui.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

// Calculator state
static char display[32] = "0";
static double current_value = 0;
static double stored_value = 0;
static char pending_op = 0;
static int clear_on_next = 1;

// Button definitions
typedef struct {
    const char* label;
    int x, y;
    int width, height;
    RECT rect;  // Added for hit testing
} Button;

static Button buttons[] = {
    {"7", 10, 60, 50, 40},
    {"8", 70, 60, 50, 40},
    {"9", 130, 60, 50, 40},
    {"/", 190, 60, 50, 40},
    {"4", 10, 110, 50, 40},
    {"5", 70, 110, 50, 40},
    {"6", 130, 110, 50, 40},
    {"*", 190, 110, 50, 40},
    {"1", 10, 160, 50, 40},
    {"2", 70, 160, 50, 40},
    {"3", 130, 160, 50, 40},
    {"-", 190, 160, 50, 40},
    {"0", 10, 210, 110, 40},
    {".", 130, 210, 50, 40},
    {"+", 190, 210, 50, 40},
    {"=", 250, 160, 50, 90},
    {"C", 250, 60, 50, 90}
};

// Forward declarations
static void update_display(EUI_Window* window);
static void handle_number(const char* num);
static void handle_operator(char op);
static void handle_equals(void);
static void handle_clear(void);

void draw_button(HDC hdc, Button* btn, BOOL pressed) {
    // Update button rectangle
    btn->rect.left = btn->x;
    btn->rect.top = btn->y;
    btn->rect.right = btn->x + btn->width;
    btn->rect.bottom = btn->y + btn->height;

    // Draw button background
    HBRUSH brush = CreateSolidBrush(RGB(240, 240, 240));
    FillRect(hdc, &btn->rect, brush);
    DeleteObject(brush);

    // Draw 3D effect
    if (!pressed) {
        // Raised effect
        HPEN lightPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
        HPEN darkPen = CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
        
        SelectObject(hdc, lightPen);
        MoveToEx(hdc, btn->x, btn->y + btn->height - 1, NULL);
        LineTo(hdc, btn->x, btn->y);
        LineTo(hdc, btn->x + btn->width - 1, btn->y);
        
        SelectObject(hdc, darkPen);
        LineTo(hdc, btn->x + btn->width - 1, btn->y + btn->height - 1);
        LineTo(hdc, btn->x, btn->y + btn->height - 1);
        
        DeleteObject(lightPen);
        DeleteObject(darkPen);
    } else {
        // Pressed effect
        HPEN darkPen = CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
        SelectObject(hdc, darkPen);
        Rectangle(hdc, btn->x, btn->y, btn->x + btn->width, btn->y + btn->height);
        DeleteObject(darkPen);
    }

    // Draw button text
    SetBkMode(hdc, TRANSPARENT);
    RECT textRect = btn->rect;
    if (pressed) {
        textRect.left += 1;
        textRect.top += 1;
    }
    DrawText(hdc, btn->label, -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void draw_display(HDC hdc) {
    // Draw display background
    RECT displayRect = {10, 10, 290, 50};
    HBRUSH brush = CreateSolidBrush(RGB(230, 230, 230));
    FillRect(hdc, &displayRect, brush);
    DeleteObject(brush);

    // Draw display border
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
    SelectObject(hdc, pen);
    Rectangle(hdc, 10, 10, 290, 50);
    DeleteObject(pen);

    // Draw display text
    SetBkMode(hdc, TRANSPARENT);
    HFONT font = CreateFont(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                          DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                          DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
    SelectObject(hdc, font);
    RECT textRect = {15, 15, 285, 45};
    DrawText(hdc, display, -1, &textRect, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
    DeleteObject(font);
}

void onPaint(EUI_Window* window) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(window->hwnd, &ps);
    
    // Draw calculator display
    draw_display(hdc);
    
    // Draw buttons
    for (size_t i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
        draw_button(hdc, &buttons[i], FALSE);
    }
    
    EndPaint(window->hwnd, &ps);
}

void onClick(EUI_Window* window, EUI_Point point) {
    // Check which button was clicked
    for (size_t i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
        Button* btn = &buttons[i];
        if (point.x >= btn->x && point.x < btn->x + btn->width &&
            point.y >= btn->y && point.y < btn->y + btn->height) {
            
            // Visual feedback
            HDC hdc = GetDC(window->hwnd);
            draw_button(hdc, btn, TRUE);
            ReleaseDC(window->hwnd, hdc);
            Sleep(100);  // Brief delay for button press effect
            
            // Handle the button click
            if (strcmp(btn->label, "=") == 0) {
                handle_equals();
            }
            else if (strcmp(btn->label, "C") == 0) {
                handle_clear();
            }
            else if (strchr("+-*/", btn->label[0])) {
                handle_operator(btn->label[0]);
            }
            else {
                handle_number(btn->label);
            }
            
            // Redraw button and update display
            InvalidateRect(window->hwnd, &btn->rect, TRUE);
            update_display(window);
            break;
        }
    }
}

static void update_display(EUI_Window* window) {
    // Force redraw of display area
    RECT displayRect = {10, 10, 290, 50};
    InvalidateRect(window->hwnd, &displayRect, TRUE);
    UpdateWindow(window->hwnd);
}

static void handle_number(const char* num) {
    if (clear_on_next) {
        strcpy(display, num);
        clear_on_next = 0;
    }
    else {
        if (strlen(display) < sizeof(display) - 2) {
            if (strcmp(display, "0") == 0) {
                strcpy(display, num);
            }
            else {
                strcat(display, num);
            }
        }
    }
    current_value = atof(display);
}

static void handle_operator(char op) {
    if (pending_op) {
        handle_equals();
    }
    stored_value = current_value;
    pending_op = op;
    clear_on_next = 1;
}

static void handle_equals(void) {
    if (!pending_op) return;
    
    switch (pending_op) {
        case '+': current_value = stored_value + current_value; break;
        case '-': current_value = stored_value - current_value; break;
        case '*': current_value = stored_value * current_value; break;
        case '/': 
            if (current_value != 0) {
                current_value = stored_value / current_value;
            }
            else {
                strcpy(display, "Error");
                return;
            }
            break;
    }
    
    snprintf(display, sizeof(display), "%.10g", current_value);
    pending_op = 0;
    clear_on_next = 1;
}

static void handle_clear(void) {
    strcpy(display, "0");
    current_value = 0;
    stored_value = 0;
    pending_op = 0;
    clear_on_next = 1;
}

int main() {
    EUI_Window* window = EUI_CreateWindow("Calculator", 100, 100, 320, 270);
    if (!window) {
        printf("Failed to create window\n");
        return 1;
    }
    
    window->onPaint = onPaint;
    window->onClick = onClick;
    
    EUI_ShowWindow(window);
    EUI_ProcessMessages();
    
    return 0;
}
