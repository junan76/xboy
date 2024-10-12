
#include <stdio.h>
#include <stdarg.h>

#include <xboy.h>

static int default_log_level = LOG_LEVEL_INFO;

void logging_with(int level, const char *fmt, ...)
{
    if (level > default_log_level)
        return;

    va_list args;
    va_start(args, fmt);

    switch (level)
    {
    case LOG_LEVEL_ERROR:
        printf("\033[31mERROR: \033[0m");
        break;
    case LOG_LEVEL_WARNING:
        printf("\033[35mWARN: \033[0m");
        break;
    case LOG_LEVEL_INFO:
        printf("\033[32mINFO: \033[0m");
        break;
    case LOG_LEVEL_DEBUG:
        printf("\033[33mDEBUG: \033[0m");
        break;
    }

    vprintf(fmt, args);
    printf("\n");

    va_end(args);
}

void logger_set_level(int level)
{
    if (level < LOG_LEVEL_MIN || level > LOG_LEVEL_MAX)
        return;
    default_log_level = level;
}