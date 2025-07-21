#include "log.h"

int main(void)
{
    LOG_INFO("Hello World!");
    LOG_WARN("Hello World 2!");
    LOG_ERROR("Hello World 3!");
    LOG_FATAL("Hello World 4!");
    return 0;
}