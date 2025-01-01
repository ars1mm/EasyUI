# EUI_DrawLine

Draws a line between two points using default line style.

## Signature

```c
void EUI_DrawLine(EUI_Window* window, int x1, int y1, int x2, int y2);
```

## Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| window | EUI_Window* | Target window to draw on |
| x1 | int | Starting x-coordinate |
| y1 | int | Starting y-coordinate |
| x2 | int | Ending x-coordinate |
| y2 | int | Ending y-coordinate |

## Description

Draws a straight line from point (x1, y1) to point (x2, y2) using the default line style. For styled lines, use [EUI_DrawLineEx](line_ex.md).

## Example Usage

```c
// Draw a diagonal line from (10,10) to (100,100)
EUI_Window* window = EUI_CreateWindow("Line Example", 100, 100, 200, 200);
if (window != NULL) {
    window->onPaint = function(EUI_Window* win) {
        EUI_DrawLine(win, 10, 10, 100, 100);
    };
    EUI_ShowWindow(window);
}
```

## Related Functions
- [EUI_DrawLineEx](line_ex.md)

## See Also
- [EUI_LineStyle](../types/line_style.md)
- [EUI_DEFAULT_LINE_STYLE](../types/line_style.md#default-style)
