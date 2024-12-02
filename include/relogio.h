#ifndef RELOGIO_H
#define RELOGIO_H

#include <stdio.h>

// horários do dia
typedef enum {
    CAFE_DA_MANHA,
    ALMOCO,
    JANTA
} Horarios;

// variável global para o relógio
extern int hora_atual;

// manipulação do relógio
void relogio_set(Horarios horario);    
void relogio_formatado(char *buffer);     
void relogio_incrementar(int segundos);    
int relogio_obter();                       

#endif // RELOGIO_H

