#define _DEFAULT_SOURCE

#include "bancada.h"
#include "xalloc.h"

#include <stdlib.h>


#define HORA_SAIDA NING
#define HORA_ENTRADA 0

void bancada_free(Bancada *bancada)
{
    free(bancada);
}


Bancada *bancada_new(Descanso *descanso)
{
    Bancada *new = xcalloc(1, sizeof(Bancada));

    new->descanso = descanso;

    inicializarFila(&new->fila);

    // cria as vasilhas.
}


int bancada_requisita_servente(Bancada *bancada)
{
    for (int i = 0; i < NING; ++i)
        if (!bancada->serventes[i])
        {
            bancada->serventes[i] =
                descanso_despacha_servente(bancada->descanso);

            return 0;
        }

    return -1;
}


void bancada_libera_servente(Bancada *bancada, int pos)
{
    descanso_recebe_servente(bancada->descanso, bancada->serventes[pos]);

    bancada->serventes[pos] = NULL;
}


static Servente *localiza_servente_livre(Bancada *bancada)
{
    for (int i = 0; !s && i < NING; ++i)
    {
        if (bancada->serventes[i] &&
            servente_pode_atender(bancada->serventes[i]))
        {
            return bancada->serventes[i];
        }
    }

    return NULL;
}


static void atende_usuario(Usuario *u, Vasilha *v, Servente *s)
{
    usuario_inicia_atendimento(u, servente_inicia_atendimento(s, v));
}


Usuario *bancada_atendimento(Bancada *bancada)
{
    Usuario *ret = NULL;

    for (int pos = 0; pos < NING; ++pos)
    {
        if (bancada->servente[pos] &&
            servente_precisa_descansar(bancada->serventes[pos]))
        {
            bancada_libera_servente(bancada, pos);
        }
    }

    if (bancada->usuarios[NING - 1] &&
        usuario_status(bancada->usuarios[NING - 1]) == USUARIO_ATENDIDO)
    {
        ret = usuario_deixar_bancada(bancada->usuarios[NING - 1]);
        bancada->usuarios[NING - 1] = NULL;
    }

    Servente *servente_livre = localiza_servente_livre(bancada);

    for (int pos = NING - 1; pos > 0 && servente_livre; --pos)
    {
        if (!bancada->usuarios[pos] &&
            usuario_status(bancada->usuarios[pos - 1]) == USUARIO_ATENDIDO)
        {
            bancada->usuarios[pos] = usuario_avancar(bancada->usuarios[pos - 1]);
            bancada->usuarios[pos - 1] = NULL;
        }

        if (bancada->usuarios[pos] &&
            usuario_status(bancada->usuarios[pos] == USUARIO_AGUARDANDO)
        {
            atende_usuario(bancada->usuarios[pos],
                           bancada->vasilhas[pos],
                           servente_livre);

            servente_livre = localiza_servente_livre(bancada);
        }
    }

    if (!bancada->usuarios[0])
        bancada->usuarios[0] = usuario_entrar_bancada(desenfileirar(bancada->fila));

    if (bancada->usuarios[0] &&
        servente_livre &&
        usuario_status(bancada->usuarios[0]) == USUARIO_AGUARDANDO)
    {
        atende_usuario(bancada->usuarios[0],
                       bancada->vasilhas[0],
                       servente_livre);
    }

    return ret;
}
