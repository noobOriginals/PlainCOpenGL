#include <string.h>

#include <api/window.h>

int main() {
    wUseCallouts(1);
    Window* window0 = wCreateWindow(800, 600, "C GL Test 0");
    Window* window1 = wCreateWindow(800, 600, "C GL Test 1");

    uint64 itt = 0;
    uint64 totalSecs = 0;

    int64 startTime = gluGetMilliseconds();
    while (!wShoudWindowClose(window0) && !wShoudWindowClose(window1)) {
        itt++;
        
        wFocusWindow(window0);        
        glClearColor(1.0f, 0.6f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        wFlushWindow(window0);

        wFocusWindow(window1);
        glClearColor(0.3f, 0.6f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        wFlushWindow(window1);
    }
    printf("Average loop time is %f seconds along %lli iiterations\n", (float64)(gluGetMilliseconds() - startTime) / (1000 * itt), itt);

    wDestroyWindow(window1);
    wDestroyWindow(window0);
    return 0;
}
