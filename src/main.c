#include "defines.h"
#include "log.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>

/************************************************************/
/* STATIC VARIABLES                                         */
/************************************************************/

static GLFWwindow* s_window = NULL;
static u32 s_width = 800, s_height = 800;
static u64 s_ticks = 0;

/************************************************************/
/* STATIC FUNCTIONS                                         */
/************************************************************/

static void _framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    s_width = width;
    s_height = height;
    glViewport(0, 0, width, height);
}

static bool _window_init(void)
{
    if (!glfwInit())
    {
        LOG_ERROR("Unable to initialize glfw.");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    s_window = glfwCreateWindow(s_width, s_height, "glfw window", NULL, NULL);
    if (!s_window)
    {
        LOG_ERROR("Unable to initialize glfw window.");
        return false;
    }

    glfwMakeContextCurrent(s_window);
    glfwSetFramebufferSizeCallback(s_window, _framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_ERROR("Unable to initialize glad.");
        return false;
    }
    glViewport(0, 0, s_width, s_height);

    return true;
}

/************************************************************/
/* EXTERN FUNCTIONS                                         */
/************************************************************/

int main(void)
{
    if (!_window_init()) LOG_FATAL("Unable to initialize window.");

    while (!glfwWindowShouldClose(s_window))
    {
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(s_window);
    }

    glfwDestroyWindow(s_window);
    glfwTerminate();
    return 0;
}