#include <api/window.h>

void def_framebuffer_size_callback(GLFWwindow* window, int32 width, int32 height) {
    glViewport(0, 0, width, height);
}

uint32 windowCount = 0;
int32 callouts = 0, glfwTerminated = 1;
const char* focusedWindow;
uint32 wGetWindowCount() { return windowCount; }
void wUseCallouts(int32 value) { callouts = value; }
const char* wGetFocusedWindow() { return focusedWindow; }

Window* wCreateWindow(uint32 width, uint32 height, const char* title) {
    Window* window = (Window*)calloc(1, sizeof(Window));
    window->title = title;
    window->resizable = 1;
    window->fullscreen = 0;
    window->closed = 0;
    window->width = width;
    window->height = height;

    if (callouts) printf("Window: Creating window %s\n", title);

    // Prepare GLFW for window creation
    if (glfwTerminated) {
        glfwInit();
        glfwTerminated = 0;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    window->address = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window->address == NULL) perror("Failed to create window\n");
    glfwMakeContextCurrent(window->address);

    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) perror("Failed to initializa GLAD\n");

    // First GL Call
    glViewport(0, 0, width, height);

    // Set window params
    glfwSetFramebufferSizeCallback(window->address, def_framebuffer_size_callback);
	glfwSwapInterval(1);
	glfwSetInputMode(window->address, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwShowWindow(window->address);

    // Increment window counter
    windowCount++;

    return window;
}
void wDestroyWindow(Window* window) {
	// Discard resources
	if (!window->closed) {
		glfwSetWindowShouldClose(window->address, 1);
		glfwDestroyWindow(window->address);
		windowCount--;
		if (callouts) printf("Window: Destructing window %s\n", window->title);
	}
	if (windowCount < 1 && !glfwTerminated) {
		glfwTerminate();
		if (callouts) printf("Window: No windows remaining\n");
		if (callouts) printf("Window: Terminating GLFW\n");
		glfwTerminated = 1;
	}
	window->closed = 1;
    free(window);
}
void wCloseWindow(Window* window) {
	// Discard resources
	if (!window->closed) {
		glfwSetWindowShouldClose(window->address, 1);
		glfwDestroyWindow(window->address);
		windowCount--;
		if (callouts) printf("Window: Closing window %s\n", window->title);
	}
	if (windowCount < 1 && !glfwTerminated) {
		glfwTerminate();
		if (callouts) printf("Window: No windows remaining\n");
		if (callouts) printf("Window: Terminating GLFW\n");
		glfwTerminated = 1;
	}
	window->closed = 1;
}
void wFlushWindow(Window* window) {
	glfwSwapBuffers(window->address);
	glfwPollEvents();
}
void wSetWindowTitle(Window* window, const char* title) {
    glfwSetWindowTitle(window->address, title);
    window->title = title;
}
void wSetWindowFrameBufferSizeCallback(Window* window, void(*func)(GLFWwindow* window, int32 width, int32 height)) {
	glfwSetFramebufferSizeCallback(window->address, func);
}
void wResetWindowFrameBufferSizeCallback(Window* window) {
	glfwSetFramebufferSizeCallback(window->address, def_framebuffer_size_callback);
}
void wSetWindowCursorPosCallback(Window* window, void(*func)(GLFWwindow* window, float64 xpos, float64 ypos)) {
    glfwSetCursorPosCallback(window->address, func);
}
GLFWwindow* wGetWindowAddress(Window* window) {
    return window->address;
}
void wFullscreenWindow(Window* window) {
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwSetWindowMonitor(window->address, monitor, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
	window->fullscreen = 1;
}
void wWindowedWindow(Window* window) {
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowMonitor(window->address, NULL, (int32)(mode->width / 2.0f - window->width / 2.0f), (int32)(mode->height / 2.0f - window->height / 2.0f), window->width, window->height, GLFW_DONT_CARE);
	window->fullscreen = 0;
}
int32 wIsWindowFullscreen(Window* window) {
    return window->fullscreen;
}
int32 wIsWindowResizable(Window* window) {
    return window->resizable;
}
int32 wShoudWindowClose(Window* window) {
    return glfwWindowShouldClose(window->address);
}
int32 wKeyPressed(Window* window, int16 key) {
    return (glfwGetKey(window->address, key) == GLFW_PRESS);
}
int32 wKeyTyped(Window* window, int16 key, int32* schedule) {
	if (wKeyPressed(window, key)) *schedule = 1;
	if (*schedule && !wKeyPressed(window, key)) {
		*schedule = 0;
		return 1;
	}
	else return 0;
}
int32 wMousePressed(Window* window, int16 button) {
    return (glfwGetMouseButton(window->address, button) == GLFW_PRESS);
}
void wFocusWindow(Window* window) {
    glfwMakeContextCurrent(window->address);
    focusedWindow = window->title;
}
void wReleaseWindowMouse(Window* window) {
	glfwSetInputMode(window->address, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
void wCaptureWindowMouse(Window* window) {
	glfwSetInputMode(window->address, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void wShowWindow(Window* window) {
	glfwShowWindow(window->address);
}
void wHideWindow(Window* window) {
    glfwHideWindow(window->address);
}
void wSetWindowResizable(Window* window, int32 resizable) {
	glfwSetWindowAttrib(window->address, GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
    window->resizable = resizable;
}
void wGetWindowSize(Window* window, int32* width, int32* height) {
	glfwGetWindowSize(window->address, width, height);
}
void wEnableVSync() {
	glfwSwapInterval(1);
}
void wDisableVSync() {
	glfwSwapInterval(1);
}