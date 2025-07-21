#include <glad/glad.h>
#include "gfx/window.h"
#include "log.h"
#include <stdlib.h>

/************************************************************/
/* STATIC FUNCTIONS                                         */
/************************************************************/

static void framebuffer_size_callback(GLFWwindow* handle, int width, int height)
{
    struct window* window = (struct window*)glfwGetWindowUserPointer(handle);
    window->width = width;
    window->height = height;

    glViewport(0, 0, width, height);
}

/************************************************************/
/* EXTERN FUNCTIONS                                         */
/************************************************************/

bool Window_Init(struct window* window)
{
    if (!glfwInit())
    {
        LOG_ERROR("Unable to initialize glfw.");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window->handle = glfwCreateWindow(window->width, window->height, window->title, NULL, NULL);
    if (!window->handle)
    {
        LOG_ERROR("Unable to initialize glfw window.");
        return false;
    }

    glfwMakeContextCurrent(window->handle);
    glfwSetWindowUserPointer(window->handle, window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_ERROR("Unable to initialize glad.");
        return false;
    }

    glfwSetFramebufferSizeCallback(window->handle, framebuffer_size_callback);
    glViewport(0, 0, window->width, window->height);

    return true;
}

void Window_Free(struct window* window)
{
    glfwDestroyWindow(window->handle);
}

bool Window_Loop(struct window* window)
{
    glfwPollEvents();
    return !glfwWindowShouldClose(window->handle);
}