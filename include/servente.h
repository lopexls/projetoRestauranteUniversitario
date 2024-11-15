#pragma once

#include <stdbool.h>

typedef struct
{
    int cooldown;
    int n_usuarios_servidos;
    int tempo_servico_acumulado;
    int hora_ultima_mudanca;
} Servente;


Servente *servente_new(int hora_atual);

Servente *servente_transfere(Servente *servente, int hora_atual);
int servente_inicia_servico(Servente *servente);
void servente_continua_servico(Servente *servente);

bool servente_esta_servindo(const Servente *servente);
bool servente_precisa_descansar(const Servente *servente, int hora_atual);
bool servente_pode_trabalhar(const Servente *servente, int hora_atual);
double servente_tempo_servico_medio(const Servente *servente);
