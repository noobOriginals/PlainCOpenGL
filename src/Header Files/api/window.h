#ifndef WINDOW_H
#define WINDOW_H

// Std includes
#include <stdlib.h>
#include <stdio.h>

// Local includes
#include <util/glutils.h>

typedef struct Window {
    GLFWwindow* address;
    const char* title;
    int32 width, height;
    int32 fullscreen, resizable, closed;
} Window;

uint32 wGetWindowCount();
void wUseCallouts(int32 callouts);
const char* wGetFocusedWindow();

Window* wCreateWindow(uint32 width, uint32 height, const char* title);
void wDestroyWindow(Window* window);
void wCloseWindow(Window* window);
void wFlushWindow(Window* window);
void wSetWindowTitle(Window* window, const char* title);
void wSetWindowFrameBufferSizeCallback(Window* window, void(*func)(GLFWwindow* window, int32 width, int32 height));
void wResetWindowFrameBufferSizeCallback(Window* window);
void wSetWindowCursorPosCallback(Window* window, void(*func)(GLFWwindow* window, float64 xpos, float64 ypos));
GLFWwindow* wGetWindowAddress(Window* window);
void wFullscreenWindow(Window* window);
void wWindowedWindow(Window* window);
int32 wIsWindowFullscreen(Window* window);
int32 wIsWindowResizable(Window* window);
int32 wShoudWindowClose(Window* window);
int32 wKeyPressed(Window* window, int16 key);
int32 wKeyTyped(Window* window, int16 key, int32* schedule);
int32 wMousePressed(Window* window, int16 button);
void wFocusWindow(Window* window);
void wReleaseWindowMouse(Window* window);
void wCaptureWindowMouse(Window* window);
void wShowWindow(Window* window);
void wHideWindow(Window* window);
void wSetWindowResizable(Window* window, int32 resizable);
void wGetWindowSize(Window* window, int32* width, int32* height);
void wEnableVSync();
void wDisableVSync();

#endif