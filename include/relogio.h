#ifndef RELOGIO_H
#define RELOGIO_H

#include <stdbool.h>
#include <stdio.h>

// horários do dia
typedef enum {
    CAFE_DA_MANHA,
    ALMOCO,
    JANTA
} Refeicao;

// variável global para o relógio
extern int hora_atual;

void relogio_set(Refeicao ref);

bool relogio_check_end(Refeicao ref);

char *relogio_formatado(void);

#endif // RELOGIO_H

