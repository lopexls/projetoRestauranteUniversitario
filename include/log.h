#pragma once

typedef enum
{
    ERR_FATAL,
    ERR_CRITICAL,
    ERR_WARNING
} ErrType;


typedef enum
{
    ERR_MEMORY_ALLOC
} ErrSource;


void log_err(ErrType type, ErrSource source, const char *extra_msg);
