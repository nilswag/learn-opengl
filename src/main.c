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

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    s_width = width;
    s_height = height;
    glViewport(0, 0, width, height);
}

/************************************************************/
/* EXTERN FUNCTIONS                                         */
/************************************************************/

int main(void)
{
    if (!glfwInit()) LOG_FATAL("Unable to initialize glfw.");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    s_window = glfwCreateWindow(s_width, s_height, "glfw window", NULL, NULL);
    if (!s_window) LOG_FATAL("Unable to initialize glfw window.");

    glfwMakeContextCurrent(s_window);
    glfwSetFramebufferSizeCallback(s_window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        LOG_FATAL("Unable to initialize glad.");
    glViewport(0, 0, s_width, s_height);

    while (!glfwWindowShouldClose(s_window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glfwSwapBuffers(s_window);
    }

    return 0;
}