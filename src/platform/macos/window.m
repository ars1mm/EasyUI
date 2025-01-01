#import <Cocoa/Cocoa.h>
#include "easyui.h"
#include "easyui_platform.h"

#ifdef EASYUI_PLATFORM_MACOS

@interface EUIWindowDelegate : NSObject <NSWindowDelegate>
@end

@implementation EUIWindowDelegate
- (BOOL)windowShouldClose:(NSWindow *)sender {
    return YES;
}
@end

static NSAutoreleasePool* pool = nil;
static NSApplication* app = nil;
static EUIWindowDelegate* windowDelegate = nil;

struct EUI_Window* EUI_CreateWindow(const char* title, int x, int y, int width, int height) {
    return EUI_CreateWindowCocoa(title, x, y, width, height);
}

void EUI_ShowWindow(struct EUI_Window* window) {
    EUI_ShowWindowCocoa(window);
}

void EUI_ProcessMessages(void) {
    NSEvent* event;
    while ((event = [app nextEventMatchingMask:NSEventMaskAny
                                   untilDate:[NSDate distantPast]
                                      inMode:NSDefaultRunLoopMode
                                     dequeue:YES])) {
        [app sendEvent:event];
    }
    [app updateWindows];
}

void EUI_DestroyWindow(struct EUI_Window* window) {
    EUI_DestroyWindowCocoa(window);
}

struct EUI_Window* EUI_CreateWindowCocoa(const char* title, int x, int y, int width, int height) {
    if (!pool) {
        pool = [[NSAutoreleasePool alloc] init];
    }
    
    if (!app) {
        app = [NSApplication sharedApplication];
        [app setActivationPolicy:NSApplicationActivationPolicyRegular];
        [app activateIgnoringOtherApps:YES];
    }
    
    if (!windowDelegate) {
        windowDelegate = [[EUIWindowDelegate alloc] init];
    }

    NSRect frame = NSMakeRect(x, y, width, height);
    NSWindow* window = [[NSWindow alloc]
        initWithContentRect:frame
        styleMask:NSWindowStyleMaskTitled |
                 NSWindowStyleMaskClosable |
                 NSWindowStyleMaskMiniaturizable |
                 NSWindowStyleMaskResizable
        backing:NSBackingStoreBuffered
        defer:NO];

    [window setDelegate:windowDelegate];
    NSString* nsTitle = [NSString stringWithUTF8String:title];
    [window setTitle:nsTitle];
    [window makeKeyAndOrderFront:nil];

    struct EUI_Window* euiWindow = (struct EUI_Window*)malloc(sizeof(struct EUI_Window));
    if (!euiWindow) return NULL;

    euiWindow->handle = (__bridge_retained void*)window;
    euiWindow->rect.x = x;
    euiWindow->rect.y = y;
    euiWindow->rect.width = width;
    euiWindow->rect.height = height;
    euiWindow->title = strdup(title);

    return euiWindow;
}

void EUI_ShowWindowCocoa(struct EUI_Window* window) {
    if (!window || !window->handle) return;
    NSWindow* win = (__bridge NSWindow*)window->handle;
    [win makeKeyAndOrderFront:nil];
}

void EUI_DestroyWindowCocoa(struct EUI_Window* window) {
    if (!window) return;
    if (window->handle) {
        NSWindow* win = (__bridge_transfer NSWindow*)window->handle;
        [win close];
    }
    free((void*)window->title);
    free(window);
}

#endif /* EASYUI_PLATFORM_MACOS */
