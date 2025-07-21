#include "log.h"
#include <glad/glad.h>
#include "gfx/window.h"

int main(void)
{
    struct window window = { 0 };
    window.width = 800;
    window.height = 800;
    window.title = "glfw window";
    if (!Window_Init(&window)) LOG_FATAL("Unable to initialize window.");

    while (Window_Loop(&window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glfwSwapBuffers(window.handle);
    }

    Window_Free(&window);
    return 0;
}