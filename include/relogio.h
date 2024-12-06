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

bool relogio_fim(Refeicao ref) __attribute__((pure));

int relogio_range(Refeicao ref) __attribute__((const));

int relogio_hora_relativa(Refeicao ref) __attribute__((pure));

double relogio_hora_fracionada(Refeicao ref);

void relogio_incrementa(int velocidade);

char *relogio_formatado(int segundos) __attribute__((returns_nonnull));


#endif // RELOGIO_H

