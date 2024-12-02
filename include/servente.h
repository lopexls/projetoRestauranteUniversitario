/** @file servente.h
 * Implementação de um servente no RU simulado.
 *
 * São requisitos de um servente:
 * 1. Manter o registro de quantos usuários ele atendeu e a soma dos tempos
 *    de atendimento de cada um destes usuários, permitindo o cálculo do tempo
 *    médio de atendimento por servente.
 * 2. Saber quando ele precisa descansar. I. e. sem ultrapassar o tempo máximo
 *    de trabalho contíguo.
 * 3. Saber quando ele pode voltar a trabalhar. I. e. após o tempo mínimo de
 *    descanso.
 * 4. Atender um usuário de cada vez. Enquanto estiver atendendo, não pode
 *    iniciar outro atendimento.
 */
#ifndef SERVENTE_H
#define SERVENTE_H

#include "config.h"
#include "vasilha.h"

#include <stdbool.h>

/** TAD representando um servente. */
typedef struct
{
    int livre_as;                   /**< Marca o horário à partir do qual o servente estará livre. */
    int n_usuarios_servidos;        /**< Registro do número de usuários servidos pela instância. */
    int s_atendimento_acumulado;    /**< Acumulado do tempo que o servente passou efetivamente servindo. */
    int hora_ultima_mudanca;        /**< Marca a hora em que o servente transitou entre a bancada e o descanso. */
} Servente;


/** Libera a memória alocada para uma instância de `Servente`.
 *
 * Por debaixo dos panos, esta função apenas chama `free()` com o ponteiro
 * passado como argumento. Ela existe só para manter a consistência com os
 * demais TADs no programa.
 *
 * @param servente ponteiro para uma instância de `Servente`.
 */
void servente_free(Servente *servente) __attribute__((nonnull(1)));


/** Cria uma nova instância de `Servente`.
 *
 * A função cria um novo servente alocado dinâmicamente na memória.
 *
 * @return ponteiro para uma instâcia de `Servente`.
 */
Servente *servente_new(void) __attribute__((malloc(servente_free)));


/** Sinaliza pra instância de `Servente` a transição entre bancada e descanso.
 *
 * Esta função é chamada quando o servente transita entre a bancada e o espaço
 * de descanso. Ela apenas marca a hora em que isso ocorreu.
 *
 * @param servente ponteiro para uma instância de `Servente`.
 * @return ponteiro para a mesma instância alterada.
 */
Servente *servente_transfere(Servente *servente)
    __attribute__((nonnull(1), returns_nonnull));


/** Põe o servente em estado de atendimento.
 *
 * Chamada no momento em que o servente começa a atender algum usuário. Calcula
 * o tempo de atendimento e deixa o servente ocupado até que este tempo se
 * esgote.
 *
 * @param servente ponteiro para uma instância de `Servente`.
 */
void servente_inicia_atendimento(Servente *servente) __attribute__((nonnull(1)));


/** Verifica se o servente pode atender algum usuário.
 *
 * Um servente estará livre para atender se já não estiver atendendo outro
 * usuário.
 *
 * @param servente ponteiro para uma instância de `Servente`.
 * @return `true` se estiver livre e `false` do contrário.
 */
bool servente_pode_atender(const Servente *servente)
    __attribute__((nonnull(1), pure));


/** Verifica se o servente precisa ir para o descanso.
 *
 * De acordo com os requisitos do programa, um servente não pode trabalhar
 * na bancada por um tempo maior do que `TEMPSERMAX`. Ao atingir este tempo,
 * ele precisa ir pro descanso.
 *
 * @param servente ponteiro para uma instância de `Servente`.
 * @return `true` se precisa descansar e `false`do contrário.
 */
bool servente_precisa_descansar(const Servente *servente)
    __attribute__((nonnull(1), pure));


/** Verifica se o servente pode ir para a bancada.
 *
 * De acordo com os requisitos do programa, um servente precisa de um tempo
 * mínimo de `TEMPSERINT` de descanso antes de poder retornar para a bancada.
 *
 * @param servente ponteiro para uma instância de `Servente`.
 * @return `true` se puder ir para a bancada e `false` do contrário.
 */
bool servente_pode_trabalhar(const Servente *servente)
    __attribute__((nonnull(1), pure));


/** Calcula o tempo médio de atendimento do servente.
 *
 * O tempo médio de atendimento é definido como o tempo em o servente passou
 * efetivamente atendendo dividido pelo número de usuários atendidos.
 *
 * @param servente ponteiro para uma instância de `Servente`.
 * @return o tempo médio de atendimento, em segundos.
 */
double servente_tempo_atendimento_medio(const Servente *servente)
    __attribute__((nonnull(1), pure));


#endif // SERVENTE_H
