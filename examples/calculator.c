#include <easyui.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Calculator state
static char display[32] = "0";
static double current_value = 0;
static double stored_value = 0;
static char pending_op = 0;
static int clear_on_next = 1;

// Button definitions
typedef struct {
    const char* label;
    EUI_Rect rect;
    EUI_ShapeStyle style;
    EUI_TextStyle textStyle;
} Button;

static Button buttons[] = {
    {"7",  {10, 60, 50, 40}},
    {"8",  {70, 60, 50, 40}},
    {"9",  {130, 60, 50, 40}},
    {"/",  {190, 60, 50, 40}},
    {"4",  {10, 110, 50, 40}},
    {"5",  {70, 110, 50, 40}},
    {"6",  {130, 110, 50, 40}},
    {"*",  {190, 110, 50, 40}},
    {"1",  {10, 160, 50, 40}},
    {"2",  {70, 160, 50, 40}},
    {"3",  {130, 160, 50, 40}},
    {"-",  {190, 160, 50, 40}},
    {"0",  {10, 210, 110, 40}},
    {".",  {130, 210, 50, 40}},
    {"+",  {190, 210, 50, 40}},
    {"=",  {250, 160, 50, 90}},
    {"C",  {250, 60, 50, 90}}
};

// Forward declarations
static void update_display(EUI_Window* window);
static void handle_number(const char* num);
static void handle_operator(char op);
static void handle_equals(void);
static void handle_clear(void);

void draw_button(EUI_Window* window, Button* btn, int pressed) {
    // Set up button styles
    btn->style = EUI_DEFAULT_SHAPE_STYLE;
    btn->style.fillColor = RGB(240, 240, 240);
    btn->style.borderColor = pressed ? RGB(128, 128, 128) : RGB(200, 200, 200);
    btn->style.borderWidth = 1;

    btn->textStyle = EUI_DEFAULT_TEXT_STYLE;
    btn->textStyle.fontSize = 14;

    // Draw button background
    EUI_DrawRectangleEx(window, btn->rect.x, btn->rect.y, 
                       btn->rect.width, btn->rect.height, &btn->style);

    // Draw button text
    int textX = btn->rect.x + (btn->rect.width - strlen(btn->label) * 8) / 2;
    int textY = btn->rect.y + (btn->rect.height - 14) / 2;
    if (pressed) {
        textX += 1;
        textY += 1;
    }
    EUI_DrawTextEx(window, btn->label, textX, textY, &btn->textStyle);
}

void draw_display(EUI_Window* window) {
    // Draw display background
    EUI_ShapeStyle displayStyle = EUI_DEFAULT_SHAPE_STYLE;
    displayStyle.fillColor = RGB(230, 230, 230);
    displayStyle.borderColor = RGB(200, 200, 200);
    displayStyle.borderWidth = 1;
    EUI_DrawRectangleEx(window, 10, 10, 280, 40, &displayStyle);

    // Draw display text
    EUI_TextStyle textStyle = EUI_DEFAULT_TEXT_STYLE;
    textStyle.fontSize = 20;
    textStyle.color = RGB(0, 0, 0);
    EUI_DrawTextEx(window, display, 20, 20, &textStyle);
}

void onPaint(EUI_Window* window) {
    // Draw calculator display
    draw_display(window);
    
    // Draw buttons
    for (size_t i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
        draw_button(window, &buttons[i], 0);
    }
}

void onClick(EUI_Window* window, EUI_Point point) {
    // Check which button was clicked
    for (size_t i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
        Button* btn = &buttons[i];
        if (point.x >= btn->rect.x && 
            point.x < btn->rect.x + btn->rect.width &&
            point.y >= btn->rect.y && 
            point.y < btn->rect.y + btn->rect.height) {
            
            // Visual feedback
            draw_button(window, btn, 1);
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
            draw_button(window, btn, 0);
            update_display(window);
            break;
        }
    }
}

static void update_display(EUI_Window* window) {
    draw_display(window);
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
