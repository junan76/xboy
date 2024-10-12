
#include <stdio.h>

enum log_level
{
    LOG_LEVEL_MIN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_MAX,
};

static int default_log_level = LOG_LEVEL_INFO;

void log_set_level(int level)
{
    if (level < LOG_LEVEL_MIN || level > LOG_LEVEL_MAX)
        return;
    default_log_level = level;
}