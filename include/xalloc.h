#pragma once

#include "log.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>


#define xmalloc(size) ({ \
    void *_ptr = malloc(size); \
    if (!_ptr) log_err(ERR_FATAL, ERR_MEMORY_ALLOC, strerror(errno)); \
    _ptr; \
})


#define xcalloc(nmemb, size) ({ \
    void *_ptr = calloc(nmemb, size); \
    if (!_ptr) log_err(ERR_FATAL, ERR_MEMORY_ALLOC, strerror(errno)); \
    _ptr; \
})
