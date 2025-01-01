# EUI_Point

A structure representing a 2D point in EasyUI.

## Definition

```c
typedef struct {
    int x;
    int y;
} EUI_Point;
```

## Members

| Member | Type | Description |
|--------|------|-------------|
| x | int | The x-coordinate of the point |
| y | int | The y-coordinate of the point |

## Description

The `EUI_Point` structure is used to represent positions and coordinates in the EasyUI system. It's commonly used in drawing operations and event handling.

## Example Usage

```c
// Create a point at coordinates (100, 200)
EUI_Point point = {
    .x = 100,
    .y = 200
};

// Use in window click handler
void onWindowClick(EUI_Window* window, EUI_Point clickPos) {
    printf("Click at position: (%d, %d)\n", clickPos.x, clickPos.y);
}
```

## Related Types
- [EUI_Rect](rect.md)
- [EUI_Size](size.md)
