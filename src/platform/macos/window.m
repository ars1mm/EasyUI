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

EUI_Window* EUI_CreateWindow(const char* title, int x, int y, int width, int height) {
    return EUI_CreateWindowCocoa(title, x, y, width, height);
}

void EUI_ShowWindow(EUI_Window* window) {
    EUI_ShowWindowCocoa(window);
}

void EUI_ProcessMessages(void) {
    EUI_ProcessMessagesCocoa();
}

void EUI_DestroyWindow(EUI_Window* window) {
    EUI_DestroyWindowCocoa(window);
}

EUI_Window* EUI_CreateWindowCocoa(const char* title, int x, int y, int width, int height) {
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
    [window setTitle:[NSString stringWithUTF8String:title]];
    
    EUI_Window* euiWindow = (EUI_Window*)malloc(sizeof(EUI_Window));
    if (!euiWindow) {
        [window release];
        return NULL;
    }
    
    euiWindow->handle = (void*)window;
    euiWindow->rect.x = x;
    euiWindow->rect.y = y;
    euiWindow->rect.width = width;
    euiWindow->rect.height = height;
    
    return euiWindow;
}

void EUI_ShowWindowCocoa(EUI_Window* window) {
    if (!window || !window->handle) return;
    NSWindow* win = (NSWindow*)window->handle;
    [win makeKeyAndOrderFront:nil];
}

void EUI_ProcessMessagesCocoa(void) {
    NSEvent* event;
    while ((event = [app nextEventMatchingMask:NSEventMaskAny
                                   untilDate:[NSDate distantPast]
                                      inMode:NSDefaultRunLoopMode
                                     dequeue:YES])) {
        [app sendEvent:event];
    }
    [app updateWindows];
}

void EUI_DestroyWindowCocoa(EUI_Window* window) {
    if (!window || !window->handle) return;
    NSWindow* win = (NSWindow*)window->handle;
    [win close];
    [win release];
    free(window);
}

#endif /* EASYUI_PLATFORM_MACOS */
