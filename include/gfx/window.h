#pragma once
#include "defines.h"
#include <GLFW/glfw3.h>

struct window
{
    GLFWwindow* handle;
    u32 width, height;
    const char* title;

    f64 delta;
    u64 ticks;
};

bool Window_Init(struct window* window);
void Window_Free(struct window* window);

bool Window_Loop(struct window* window);