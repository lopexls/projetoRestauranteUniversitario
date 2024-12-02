/** @file bancada.h
 * Implementa uma bancada no simulador de filas no RU.
 *
 * Uma bancada funciona como o ponto de processamento das filas e é o elemento
 * central do simulador. Ela Agrega referências para as vasilhas e para os
 * serventes, com a finalidade de simular a lógica de atendimento.
 *
 * Cada bancada:
 * 1. Pode processar mais de um usuário de cada vez. Contudo, um usuário que
 *    tenha entrado depois na bancada não pode passar à frente de outro que
 *    tenha entrado antes.
 * 2. Processa o usuário em um número fixo de etapas, dado por `NING` (o
 *    número de ingredientes servidos na refeição).
 */
#ifndef BANCADA_H
#define BANCADA_H

#include "config.h"
#include "descanso.h"
#include "servente.h"
#include "usuario.h"

#include <stdbool.h>


typedef struct
{
    int n_serventes;

    Fila fila;
    Vasilha vasilhas[NING];
    Usuario *usuarios[NING];
    Servente *serventes[NING];

    Descanso *descanso;
} Bancada;


#endif // BANCADA_H
