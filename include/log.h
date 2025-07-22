#pragma once

#ifdef _DEBUG
#include "defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

enum log_level
{
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL
};

static inline void log(enum log_level level, const char* file, u32 line, const char* fmt, ...)
{
    switch (level)
    {
    case LOG_LEVEL_INFO:
        printf("%s:%u [INFO] ", file, line);
        break;

    case LOG_LEVEL_WARN:
        printf("%s:%u [WARN] ", file, line);
        break;

    case LOG_LEVEL_ERROR:
        printf("%s:%u [ERROR] ", file, line);
        break;

    case LOG_LEVEL_FATAL:
        printf("%s:%u [FATAL] ", file, line);
        break;

    default:
        printf("%s:%u [LOG] ", file, line);
        break;
    }

    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    puts("");
    va_end(args);

    if (level == LOG_LEVEL_FATAL)
        exit(EXIT_FAILURE);
}

#define LOG_INFO(msg, ...) do { log(LOG_LEVEL_INFO, __FILENAME__, __LINE__, msg, ##__VA_ARGS__); } while (false)
#define LOG_WARN(msg, ...) do { log(LOG_LEVEL_WARN, __FILENAME__, __LINE__, msg, ##__VA_ARGS__); } while (false)
#define LOG_ERROR(msg, ...) do { log(LOG_LEVEL_ERROR, __FILENAME__, __LINE__, msg, ##__VA_ARGS__); } while (false)
#define LOG_FATAL(msg, ...) do { log(LOG_LEVEL_FATAL, __FILENAME__, __LINE__, msg, ##__VA_ARGS__); } while (false)

#else

#define LOG_INFO(msg, ...)
#define LOG_WARN(msg, ...)
#define LOG_ERROR(msg, ...)
#define LOG_FATAL(msg, ...)

#endif
