# EUI_CreateWindow

Creates a new window with the specified title and dimensions.

## Signature

```c
EUI_Window* EUI_CreateWindow(const char* title, int x, int y, int width, int height);
```

## Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| title | const char* | The title text to display in the window's title bar |
| x | int | The x-coordinate of the window's initial position |
| y | int | The y-coordinate of the window's initial position |
| width | int | The width of the window in pixels |
| height | int | The height of the window in pixels |

## Return Value

Returns a pointer to the newly created `EUI_Window` structure. Returns NULL if window creation fails.

## Description

This function creates a new window with the specified parameters. The window is created but not shown - use [EUI_ShowWindow](show_window.md) to make it visible.

## Example Usage

```c
// Create a 800x600 window at position (100, 100)
EUI_Window* window = EUI_CreateWindow("My Window", 100, 100, 800, 600);
if (window != NULL) {
    // Set up window callbacks
    window->onPaint = myPaintHandler;
    window->onClick = myClickHandler;
    
    // Show the window
    EUI_ShowWindow(window);
}
```

## Related Functions
- [EUI_ShowWindow](show_window.md)
- [EUI_DestroyWindow](destroy_window.md)
- [EUI_ProcessMessages](process_messages.md)

## See Also
- [EUI_Window](../types/window.md)
- [EUI_WindowStyle](../types/window_style.md)
