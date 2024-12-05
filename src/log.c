#define _DEFAULT_SOURCE

#include "log.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>


static const char *err_types[] = {
    "FATAL",
    "CRITICAL",
    "WARNING"
};


static const char *err_messages[] = {
    "erro de alocação de memória.",
    "descanso cheio. Isso é um bug.",
    "horário de refeição solicitada não está definido."
};


void log_err(ErrType type, ErrSource source)
{
    fprintf(stderr, "[%s] %s\n", err_types[type], err_messages[source]);

    if (type == ERR_FATAL)
        exit(EXIT_FAILURE);
}
