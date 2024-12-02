/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/


#ifndef CONFIG_H
#define CONFIG_H

#define TEMPO_MANHA 360
#define TEMPO_TARDE 180
#define TEMPO_JANTAR 120
#define TEMPO_MIN 3
#define TEMPO_MAX 6
#define NUM_FILAS 5
#define BANCADA_MIN 1
#define BANCADA_MAX 5
#define SERVENTE_MIN 3
#define SERVENTE_MAX 6
#define TEMPO_MAX_SERVENTE 3600
#define TEMPO_INTERVALO_SERVENTE 1800
#define SERVENTE_MIN_QUANTIDADE 3
#define SERVENTE_MAX_QUANTIDADE 10

#define NUM_INGREDIENTES 6
#define INGREDIENTE_CAPACIDADE_PADRAO 5000
#define INGREDIENTE_QUANTIDADE_PADRAO 5000
#define INGREDIENTE_REPOSICAO_PADRAO 30
#define INGREDIENTE_ACEITACAO_PADRAO 0.8

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USUARIOS 500
#define MAX_BANCADAS 5
#define MAX_SERVENTES 6

typedef struct {
    int id;
    int vegetariano;
    int filaEscolhida;
    int chegada;
    int espera;
    int atendimento;
    int tempoTotal;
} Usuario;

typedef struct {
    int id;
    int ativo;
    int tempoTrabalho;
    int intervalo;
    int atendidos;
    int tempoAtendimento;
} Servente;

typedef struct {
    int id;
    Servente serventes[MAX_SERVENTES];
    int ativa;
    int tamFila;
    int atendidos;
    int tempoAtendimento;
} Bancada;

typedef struct {
    int id;
    char nome[50];
    int capacidade;
    int quantidadeAtual;
    int consumido;
    double aceitacao;
} Ingrediente;

typedef struct {
    int id;
    int idIngrediente;
    int quantidadeAtual;
    int capacidade;
    int tempoReposicao;
} Vasilha;

typedef struct {
    Usuario usuarios[MAX_USUARIOS];
    Bancada bancadas[MAX_BANCADAS];
    Ingrediente ingredientes[NUM_INGREDIENTES];
    Vasilha vasilhas[NUM_INGREDIENTES];
    int tempoAtual;
    int totalUsuarios;
} Restaurante;

void inicializarRestaurante(Restaurante* ru) {
    ru->tempoAtual = 0;
    ru->totalUsuarios = 0;

    for (int i = 0; i < MAX_BANCADAS; i++) {
        ru->bancadas[i].id = i;
        ru->bancadas[i].ativa = 0;
        ru->bancadas[i].tamFila = 0;
        ru->bancadas[i].atendidos = 0;
        ru->bancadas[i].tempoAtendimento = 0;
        for (int j = 0; j < MAX_SERVENTES; j++) {
            ru->bancadas[i].serventes[j].id = j;
            ru->bancadas[i].serventes[j].ativo = 0;
            ru->bancadas[i].serventes[j].tempoTrabalho = 0;
            ru->bancadas[i].serventes[j].intervalo = 0;
            ru->bancadas[i].serventes[j].atendidos = 0;
            ru->bancadas[i].serventes[j].tempoAtendimento = 0;
        }
    }

    for (int i = 0; i < NUM_INGREDIENTES; i++) {
        ru->ingredientes[i].id = i;
        snprintf(ru->ingredientes[i].nome, 50, "Ingrediente %d", i + 1);
        ru->ingredientes[i].capacidade = INGREDIENTE_CAPACIDADE_PADRAO;
        ru->ingredientes[i].quantidadeAtual = INGREDIENTE_QUANTIDADE_PADRAO;
        ru->ingredientes[i].consumido = 0;
        ru->ingredientes[i].aceitacao = INGREDIENTE_ACEITACAO_PADRAO;

        ru->vasilhas[i].id = i;
        ru->vasilhas[i].idIngrediente = i;
        ru->vasilhas[i].capacidade = INGREDIENTE_CAPACIDADE_PADRAO;
        ru->vasilhas[i].quantidadeAtual = INGREDIENTE_QUANTIDADE_PADRAO;
        ru->vasilhas[i].tempoReposicao = INGREDIENTE_REPOSICAO_PADRAO;
    }
}

int main() {
    Restaurante ru;
    inicializarRestaurante(&ru);
    return 0;
}
