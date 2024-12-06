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
#include "fila.h"
#include "servente.h"
#include "usuario.h"
#include "vasilha.h"

#include <stdbool.h>


typedef struct
{
    int n_serventes;
    bool vegetariana;
    bool ativa;
    bool acolhendo;

    int n_usuarios_atendidos;
    int tempo_atendimento;

    Fila fila;
    Vasilha vasilhas[NING];
    Usuario *usuarios[NING];
    Servente *serventes[NING];
    Descanso *descanso;
} Bancada;


void bancada_free(Bancada *bancada) __attribute__((nonnull(1)));

Bancada *bancada_new(Ingrediente cardapio[NING], Descanso *descanso, bool vegetariana)
    __attribute__((malloc(bancada_free)));

bool bancada_tem_usuarios(const Bancada *bancada) __attribute__((nonnull(1)));

bool bancada_esta_ativa(const Bancada *bancada) __attribute__((nonnull(1)));

bool bancada_esta_acolhendo(const Bancada *bancada) __attribute__((nonnull(1)));

int bancada_tempo_atendimento(const Bancada *bancada)
    __attribute((nonnull(1), pure));

int bancada_tamanho_fila(const Bancada *bancada) __attribute__((nonnull(1)));

int bancada_ativar(Bancada *bancada) __attribute__((nonnull(1)));

void bancada_desativar(Bancada *bancada) __attribute__((nonnull(1)));

int bancada_solicita_servente(Bancada *bancada) __attribute__((nonnull(1)));

int bancada_dispensa_servente(Bancada *bancada) __attribute__((nonnull(1)));

int bancada_descansos_obrigatorios(Bancada *bancada) __attribute__((nonnull(1)));

void bancada_recebe_usuario(Bancada *bancada, Usuario *usuario)
    __attribute__((nonnull(1, 2)));

Usuario *bancada_atendimento(Bancada *bancada) __attribute__((nonnull(1)));


#endif // BANCADA_H
