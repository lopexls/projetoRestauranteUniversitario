/** @file descanso.h
 * Implementação de uma área de descanso para serventes no RU.
 *
 * A área de descanso assume algumas funções bastante importantes no contexto
 * do programa.
 * 1. É o espaço que mantém as referências para os serventes que não esteja
 *    trabalhando nas bancadas.
 * 2. Permite uma área central para a existência dos serventes independente
 *    da bancada.
 * 3. É responsável pela criação inicial dos serventes e pela sua destruição ao
 *    fim do programa.
 *
 * A implementação é muito simples, trantando-se apenas de uma fila de
 * ponteiros para serventes. Como a quantidade de serventes é estabelecida
 * por uma macro, o descanso não precisa lidar com alocação e dealocação de
 * espaço para a fila.
 *
 * A principal limitação desta implementação é que ela não permite a passagem
 * temporária de serventes pela área de descanso. A situação hipotética seria:
 * um servente é dispensado da bancada sem que tenha atingido o tempo máximo de
 * trabalho. Tal servente poderia voltar para outra bancada sem cumprir o tempo
 * mínimo de descanso, situação em que o tempo de trabalho simplesmente
 * continua contanto. Implementar esta dinâmica exigiria ou abandonar o modelo
 * de fila para a organização do descanso ou (o que talvez seria bem melhor)
 * criar uma segunda fila apenas para estas passagens temporárias.
 */
#ifndef DESCANSO_H
#define DESCANSO_H

#include "servente.h"


/** TAD representando uma área de descanso para serventes.
 *
 * É implementado como uma fila estática circular.
 */
typedef struct
{
    Servente *serventes[QTDSERMAX + 1]; /**< Vetor de ponteiros para `Servente`. */
    int inicio;                         /**< Índice do 1º elemento. */
    int fim;                            /**< Índice do último elemento. */
} Descanso;


/** Libera a memória alocada para uma instância de `Descanso`.
 *
 * Ao ser liberada, a instância se encarrega de liberar todos os serventes
 * que se encontrar armazenados por ela.
 *
 * @param descanso Ponteiro para uma instância de `Descanso`.
 */
void descanso_free(Descanso *descanso) __attribute__((nonnull(1)));


/** Cria uma nova instância de `Descanso`.
 *
 * A função aloca espaço em memória para uma estrutura do tipo `Descanso` e
 * retorna um ponteiro para este espaço. Não pode retornar nulo.
 *
 * O espaço de descanso é responsável por criar os serventes
 * @return Ponteiro para uma instância de `Descanso`.
 */
Descanso *descanso_new(void) __attribute__((malloc(descanso_free)));


/** Retira um servente do descanso, retornando-o.
 *
 * O servente retornado será o primeiro da fila no descanso, o que equivale a
 * pegar aquele que estiver no descanso à mais tempo. Pode ocorrer de a área
 * de descanso estar vazia ou de o primeiro servente não ter tirado o tempo
 * mínimo de descanso. Nestes casos, esta funcão retorna NULL.
 *
 * @param descanso Ponteiro para uma instância de `Descanso`.
 * @return Ponteiro para uma instância de `Servente`. A propriedade do ponteiro
 *         é transferida para o cliente.
 */
Servente *descanso_despacha_servente(Descanso *descanso)
    __attribute__((nonnull(1)));


/** Recebe um servente e armazena no descanso.
 *
 * O servente é armazenado na última posição do descanso. Além disso, no momento
 * em que entra no descanso, o tempo mínimo de descanso `TEMPSERINT` passa
 * a contar e o servente não pode sair antes deste acabar.
 *
 * A propriedade do ponteiro para o servente é assumida pelo descanso.
 *
 * @warning Está rotina pode falhar, caso o descanso esteja cheio. Nesta
 * situação, descanso não pode assumir a propriedade do ponteiro para servente,
 * que permanece com o cliente.
 *
 * @param descanso Ponteiro para uma instância de `Descanso`.
 * @param servente Ponteiro para a instância de `Servente` que será incluída
 *                 no descanso.
 * @return 0 se a função for bem sucedida e -1 no caso contrário.
 */
int descanso_recebe_servente(Descanso *descanso, Servente *servente)
    __attribute__((nonnull(1, 2)));


/** Retira um servente do descanso e armazena outro.
 *
 * É 2-em-1. Esta rotina funciona encadecando as de inserção e remoção. Como
 * trata-se de uma troca, é garantido que o descanso não vai estar cheio.
 * Contudo, ainda é possível que o descanso esteja vazio no momento em que
 * esta função for chamada. Nesta situação, o servente à ser incluído
 * **é incluído**, mas nenhum servente é retirado do descanso e está função
 * retorna nulo.
 *
 * @param descanso Ponteiro para uma instância de `Descanso`.
 * @param servente Ponteiro para a instância de `Servente` que será incluída em
 *                 `descanso`.
 * @return Ponteiro para a instância de `Servente` retirada do descanso ou NULL.
 */
Servente *descanso_troca_servente(Descanso *descanso, Servente *servente)
    __attribute__((nonnull(1, 2)));


#endif // DESCANSO_H
