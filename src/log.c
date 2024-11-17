#include "log.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>


const char *err_types[] = {
    "FATAL",
    "CRITICAL",
    "WARNING"
};


const char *err_messages[] = {
    "erro de alocação de memória"
};


void log_err(ErrType type, ErrSource source, const char *extra_msg)
{
    fprintf(stderr, "[%s] %s: %s\n",
            err_types[type], err_messages[source], extra_msg);

    if (type == ERR_FATAL)
        exit(EXIT_FAILURE);
}
