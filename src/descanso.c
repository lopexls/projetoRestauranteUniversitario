#define _GNU_SOURCE

#include "config.h"
#include "descanso.h"
#include "servente.h"
#include "xalloc.h"

#include <stddef.h>


void descanso_free(Descanso *descanso)
{
    for (int i = 0; i < QTDSERMAX + 1; ++i)
    {
        if (descanso->serventes[i])
            servente_free(descanso->serventes[i]);
    }
}


Descanso *descanso_new(void)
{
    Descanso *ptr = xmalloc(sizeof(*ptr));

    for (int i = 0; i < QTDSERMAX; ++i)
        ptr->serventes[i] = servente_new();

    ptr->inicio = 0;
    ptr->fim = QTDSERMAX;
    ptr->serventes[ptr->fim] = NULL;

    return ptr;
}


Servente *descanso_despacha_servente(Descanso *descanso)
{
    Servente *ret = NULL;

    // Se a fila estiver vazia e se o servente puder trabalhar.
    if (descanso->inicio != descanso->fim &&
        servente_pode_trabalhar(descanso->serventes[descanso->inicio]))
    {
        ret = servente_transfere(descanso->serventes[descanso->inicio]);

        descanso->serventes[descanso->inicio] = NULL;
        descanso->inicio = (descanso->inicio + 1) % (QTDSERMAX + 1);
    }

    return ret;
}


int descanso_recebe_servente(Descanso *descanso, Servente *servente)
{
    // Condição que sinaliza que a fila está cheia.
    if (descanso->serventes[descanso->fim])
        return -1;

    /* Não é esperado que a fila fique cheia, uma vez que ela tem o
     * tamanho adequado para o número de serventes no sistema. Contudo, esta
     * condição poderá ocorrer no código do cliente caso sejam criadas mais de
     * uma instância de `Descanso` e os serventes sejam misturados entre elas.
     *
     * Por isso, resolvemos não tratar isso como um bug no código, e sim como
     * uma condição normal e retornar o erro pela função.
     */

    descanso->serventes[descanso->fim] = servente_transfere(servente);
    descanso->fim = (descanso->fim + 1) % (QTDSERMAX + 1);
    return 0;
}


Servente *descanso_troca_servente(Descanso *descanso, Servente *servente)
{
    /* A ordem dos fatores altera o produto, neste caso.
     *   1) Retirar um servente do descanso;
     *   2) Incluir o servente no descanso.
     *
     * Assim, previne-se duas situações. A primeira, de a fila estar cheia,
     * o que foi discutido acima. A segunda, de o servente retirado ser o mesmo
     * que acabou de ser incluído, o que aconteceria se a fila estivesse
     * inicialmente vazia.
     */
    Servente *ptr = descanso_despacha_servente(descanso);
    descanso_recebe_servente(descanso, servente);
    return ptr;
}
