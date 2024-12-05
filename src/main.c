/** @file main.c
 * Ponto de entrada do programa.
 *
 * A única coisa que esta peça faz é processar os argumentos passados pelo
 * terminal para o programa. Para isso, usa a funcionalidade definida em
 * argp.h na biblioteca padrão.
 *
 * Após processar os argumentos, `main()` cria uma instância de `Restaurante`
 * e executa a simulação.
 *
 * Ver https://sourceware.org/glibc/manual/latest/html_mono/libc.html#Argp.
 */
#define _DEFAULT_SOURCE

#include "config.h"
#include "relogio.h"
#include "restaurante.h"

#include <argp.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>


/** Função chamada para processar cada argumento ou opção dada ao programa.
 *
 * Para cada opção, argp_parse irá chamar esta função. A responsabilidade
 * da função é identificar a opção dada e modificar os parâmetros do programa
 * de acordo.
 *
 * @param key Chave que identifica a opção ou argumento.
 * @param arg Ponteiro para o valor da opção ou argumento.
 * @param state Ponteiro para a estrutura de estado de argp.
 * @return 0 se bem sucedido ou um código de erro.
 */
error_t parse_func(int key, char *arg, struct argp_state *state);

/** Versão do programa. */
const char *argp_program_version = VERSIONSTR;

/** Referência na web. */
const char *argp_program_bug_address =
    "https://github.com/lopexls/projetoRestauranteUniversitario";

/** String que identifica os argumentos do programa. */
const static char *const escolha_refeicao = "<cafe|almoco|janta>";

/** String com descrição geral do programa. */
const static char *const doc =
    "Simulador de Filas em Restaurante Universitário\v"
    "Este programa é usado para simular as filas em um restaurante. "
    "Trabalho final da disciplina Algoritimos e Estruturas de Dados, "
    "grupo 4.\n"
    "Copyright (c) 2024\n"
    "Bianca Mendes, Dennis Gonçalves, Geovana Espinosa, "
    "Kathleen Caroline B. de Oliveira e Stella Moreira.";

/** Opções compreendidas. */
const static struct argp_option opcoes[] = {
    {
        "velocidade", 'v',
        "ciclos", 0,
        "Velocidade de simulação (ciclos/segundo). Padrão: 60", 0
    },
    { 0 }
};

/** Estrutura do parser para as opções. */
static struct argp argp = {opcoes, parse_func, escolha_refeicao, doc};

/** Estrutura onde guardamos os valores das opções e argumentos. */
struct argumentos
{
    int velocidade;
    Refeicao refeicao;
};


error_t parse_func(int key, char *arg, struct argp_state *state)
{
    struct argumentos *opts = state->input;

    switch (key)
    {
        case 'v':
            int v = atoi(arg);
            if (v == 0)
            {
                argp_failure(state, 1, EINVAL,
                    "Erro: valor [%s] inválido para a velocidade",
                    arg);
            }

            opts->velocidade = v;
            break;

        case ARGP_KEY_NO_ARGS:
            argp_usage(state);
            break;

        case ARGP_KEY_ARG:
            if (strcmp(arg, "cafe") == 0)
                opts->refeicao = CAFE_DA_MANHA;
            else if (strcmp(arg, "almoco") == 0)
                opts->refeicao = ALMOCO;
            else if (strcmp(arg, "janta") == 0)
                opts->refeicao = JANTA;
            else
            {
                argp_failure(state, 1, EINVAL,
                    "Erro: argumento [%s] desconhecido",
                    arg);
            }

            break;

        default:
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}


int main(int argc, char *argv[])
{
    struct argumentos opts = {VELOPADRAO, CAFE_DA_MANHA};

    argp_parse(&argp, argc, argv, 0, 0, &opts);

    Restaurante *ru = restaurante_new(opts.refeicao, opts.velocidade);

    int ret = restaurante_simula(ru);

    restaurante_free(ru);

    return ret;
}

