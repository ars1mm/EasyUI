#import <Cocoa/Cocoa.h>
#include "easyui.h"
#include "easyui_platform.h"

#ifdef EASYUI_PLATFORM_MACOS

static NSColor* EUI_ColorToNSColor(unsigned long color) {
    float r = ((color >> 16) & 0xFF) / 255.0f;
    float g = ((color >> 8) & 0xFF) / 255.0f;
    float b = (color & 0xFF) / 255.0f;
    return [NSColor colorWithRed:r green:g blue:b alpha:1.0f];
}

void EUI_DrawRectangleCocoa(struct EUI_Window* window, int x, int y, int width, int height, const struct EUI_ShapeStyle* style) {
    if (!window || !window->handle) return;
    NSWindow* win = (__bridge NSWindow*)window->handle;
    NSView* view = [win contentView];
    [view lockFocus];
    
    NSRect rect = NSMakeRect(x, y, width, height);
    NSBezierPath* path = [NSBezierPath bezierPathWithRect:rect];
    
    NSColor* fillColor = EUI_ColorToNSColor(style->fillColor);
    [fillColor set];
    [path fill];
    
    NSColor* strokeColor = EUI_ColorToNSColor(style->strokeColor);
    [strokeColor set];
    [path setLineWidth:style->strokeWidth];
    [path stroke];
    
    [view unlockFocus];
}

void EUI_DrawTextCocoa(struct EUI_Window* window, const char* text, int x, int y, const struct EUI_TextStyle* style) {
    if (!window || !window->handle || !text) return;
    NSWindow* win = (__bridge NSWindow*)window->handle;
    NSView* view = [win contentView];
    [view lockFocus];
    
    NSString* nsText = [NSString stringWithUTF8String:text];
    NSFont* font = [NSFont fontWithName:[NSString stringWithUTF8String:style->fontFamily] 
                                 size:style->fontSize];
    if (!font) {
        font = [NSFont systemFontOfSize:style->fontSize];
    }
    
    NSDictionary* attrs = @{
        NSFontAttributeName: font,
        NSForegroundColorAttributeName: EUI_ColorToNSColor(style->color)
    };
    
    NSPoint point = NSMakePoint(x, y);
    [nsText drawAtPoint:point withAttributes:attrs];
    
    [view unlockFocus];
}

void EUI_DrawPolygonCocoa(struct EUI_Window* window, const EUI_Point* points, int numPoints, const struct EUI_ShapeStyle* style) {
    if (!window || !window->handle || !points || numPoints < 3) return;
    NSWindow* win = (__bridge NSWindow*)window->handle;
    NSView* view = [win contentView];
    [view lockFocus];
    
    NSBezierPath* path = [NSBezierPath bezierPath];
    [path moveToPoint:NSMakePoint(points[0].x, points[0].y)];
    
    for (int i = 1; i < numPoints; i++) {
        [path lineToPoint:NSMakePoint(points[i].x, points[i].y)];
    }
    [path closePath];
    
    NSColor* fillColor = EUI_ColorToNSColor(style->fillColor);
    [fillColor set];
    [path fill];
    
    NSColor* strokeColor = EUI_ColorToNSColor(style->strokeColor);
    [strokeColor set];
    [path setLineWidth:style->strokeWidth];
    [path stroke];
    
    [view unlockFocus];
}

#endif // EASYUI_PLATFORM_MACOS
