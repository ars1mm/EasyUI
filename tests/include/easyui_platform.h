#ifndef EASYUI_PLATFORM_H
#define EASYUI_PLATFORM_H

/* Forward declarations */
struct EUI_Window;
struct EUI_LineStyle;
struct EUI_ShapeStyle;
struct EUI_TextStyle;

/* Platform detection */
#define EASYUI_PLATFORM_WINDOWS
/* #undef EASYUI_PLATFORM_LINUX */
/* #undef EASYUI_PLATFORM_MACOS */

/* Platform-specific includes */
#ifdef EASYUI_PLATFORM_WINDOWS
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #define NOGDI
    #define NOMINMAX
    typedef HWND EUI_NativeWindow;
    typedef HDC EUI_NativeContext;
    #define EUI_RGB(r,g,b) RGB(r,g,b)
#elif defined(EASYUI_PLATFORM_LINUX)
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <X11/Xatom.h>
    typedef Window EUI_NativeWindow;
    typedef GC EUI_NativeContext;
    #define EUI_RGB(r,g,b) ((r << 16) | (g << 8) | b)
#elif defined(EASYUI_PLATFORM_MACOS)
    #include <Cocoa/Cocoa.h>
    typedef NSWindow* EUI_NativeWindow;
    typedef NSGraphicsContext* EUI_NativeContext;
    #define EUI_RGB(r,g,b) ((r << 16) | (g << 8) | b)
#else
    #error "Unsupported platform"
#endif

/* Platform-specific function declarations */
#ifdef EASYUI_PLATFORM_WINDOWS
    struct EUI_Window* EUI_CreateWindowWin32(const char* title, int x, int y, int width, int height);
    void EUI_ShowWindowWin32(struct EUI_Window* window);
    void EUI_ProcessMessagesWin32(void);
    void EUI_DrawRectangleExWin32(struct EUI_Window* window, int x, int y, int width, int height, const struct EUI_ShapeStyle* style);
    void EUI_DrawTextExWin32(struct EUI_Window* window, const char* text, int x, int y, const struct EUI_TextStyle* style);
#endif

#endif /* EASYUI_PLATFORM_H */
