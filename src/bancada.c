#define _DEFAULT_SOURCE

#include "bancada.h"
#include "log.h"
#include "xalloc.h"

#include <stdlib.h>


static void rebalanco(Bancada *bancada, Servente *novo)
{
    Servente *set[BANSERMAX] = { NULL };
    int qtd_vas_por_serv[BANSERMAX] = { 0 };
    int ind_set = 0, ind_bancada = 0;
    int quociente = NING / bancada->n_serventes;
    int resto = NING % bancada->n_serventes;

    if (novo)
        set[ind_set++] = novo;

    for (ind_bancada = 0; ind_bancada < BANSERMAX; ++ind_bancada)
    {
        if (!bancada->serventes[ind_bancada])
            continue;

        bool found = false;

        for (int i = 0; i < ind_set && !found; ++i)
            if (bancada->serventes[ind_bancada] == set[i])
                found = true;

        if (!found)
            set[ind_set++] = bancada->serventes[ind_bancada];
    }

    for (int i = ind_set - 1; i >= 0; --i)
    {
        qtd_vas_por_serv[i] = quociente;
        if (resto > 0)
        {
            ++qtd_vas_por_serv[i];
            --resto;
        }
    }

    ind_bancada = 0;
    for (int i = 0; i < ind_set; ++i)
        for (int j = 0; j < qtd_vas_por_serv[i]; ++j)
            bancada->serventes[ind_bancada++] = set[i];
}


static void atende_usuario(Bancada *bancada, int pos)
{
    int tempo = servirDaVasilha(&bancada->vasilhas[pos]);
    
    if (tempo >= 0)
        tempo += servente_inicia_atendimento(bancada->serventes[pos]);
    else
        tempo = 0;

    usuario_inicia_atendimento(bancada->usuarios[pos], tempo);
}


void bancada_free(Bancada *bancada)
{
    free(bancada);
}


Bancada *bancada_new(const Ingrediente cardapio[NING])
{
    Bancada *new = xcalloc(1, sizeof(Bancada));

    inicializarFila(&new->fila);

    for (int i = 0; i < NING; ++i)
        inicializarVasilha(&new->vasilhas[i], &cardapio[i]);

    return new;
}


bool bancada_tem_usuarios(const Bancada *bancada)
{
    for (int i = 0; i < NING; ++i)
        if (bancada->usuarios[i])
            return true;

    if (!filaVazia(&bancada->fila))
        return true;

    return false;
}


int bancada_ativar(Bancada *bancada, Descanso *descanso)
{
    int erro = 0;

    // Não faz nada se a bancada já estiver ativa;
    // Também, garante que o estado inicial da bancada é com 0 serventes.
    if (bancada->n_serventes || bancada->ativa)
        return 1;

    for (int i = 0; i < BANSERMIN && !erro; ++i)
    {
        if (bancada_solicita_servente(bancada, descanso) != i + 1)
            erro = 1;
    }

    if (!erro)
    {
        bancada->ativa = true;
        bancada->acolhendo = true;
    }

    return erro;
}


void bancada_desativar(Bancada *bancada, Descanso *descanso)
{
    if (!bancada_tem_usuarios(bancada))
    {
        const int c = bancada->n_serventes;

        for (int i = 0; i < c; ++i)
            bancada_dispensa_servente(bancada, descanso);

        bancada->ativa = false;
    }

    bancada->acolhendo = false;
}


int bancada_solicita_servente(Bancada *bancada, Descanso *descanso)
{
    if (bancada->n_serventes < BANSERMAX)
    {
        Servente *novo = descanso_despacha_servente(descanso);

        if (novo)
        {
            ++bancada->n_serventes;
            rebalanco(bancada, novo);
        }
    }

    return bancada->n_serventes;
}


int bancada_dispensa_servente(Bancada *bancada, Descanso *descanso)
{
    Servente *mais_antigo = bancada->serventes[0];

    if (!bancada->n_serventes)
        return 0;

    for (int i = 1; i < BANSERMAX; ++i)
        mais_antigo = servente_mais_antigo(bancada->serventes[i], mais_antigo);

    for (int i = 0; i < BANSERMAX; ++i)
        if (bancada->serventes[i] == mais_antigo)
            bancada->serventes[i] = NULL;

    descanso_recebe_servente(descanso, mais_antigo);
    --bancada->n_serventes;

    if (bancada->n_serventes)
        rebalanco(bancada, NULL);

    return bancada->n_serventes;
}


int bancada_descansos_obrigatorios(Bancada *bancada, Descanso *descanso)
{
    Servente *dispensado = NULL;

    if (!bancada->n_serventes)
        return 0;

    for (int i = 0; i < BANSERMAX; ++i)
    {
        if (bancada->serventes[i] == dispensado)
            bancada->serventes[i] = NULL;

        else if (servente_precisa_descansar(bancada->serventes[i]) &&
                 servente_pode_atender(bancada->serventes[i]))
        {
            dispensado = bancada->serventes[i];
            bancada->serventes[i] = NULL;
            descanso_recebe_servente(descanso, dispensado);
            --bancada->n_serventes;
        }
    }

    if (bancada->n_serventes && dispensado)
        rebalanco(bancada, NULL);

    return bancada->n_serventes;
}


void bancada_recebe_usuario(Bancada *bancada, Usuario *usuario)
{
    enfileirar(&bancada->fila, usuario);
}


Usuario *bancada_atendimento(Bancada *bancada)
{
    Usuario *ret = NULL;

    if (bancada->usuarios[NING - 1] &&
        usuario_foi_atendido(bancada->usuarios[NING - 1]))
    {
        ret = usuario_deixar_bancada(bancada->usuarios[NING - 1]);
        bancada->usuarios[NING - 1] = NULL;
    }

    for (int pos = NING - 1; pos > 0; --pos)
    {
        if (!bancada->usuarios[pos] &&
            bancada->usuarios[pos - 1] &&
            usuario_foi_atendido(bancada->usuarios[pos - 1]))
        {
            bancada->usuarios[pos] = usuario_avancar(bancada->usuarios[pos - 1]);
            bancada->usuarios[pos - 1] = NULL;
        }

        if (bancada->usuarios[pos] &&
            usuario_esta_aguardando(bancada->usuarios[pos]) &&
            servente_pode_atender(bancada->serventes[pos]))
        {
            atende_usuario(bancada, pos);
        }
    }

    if (!bancada->usuarios[0])
        bancada->usuarios[0] = usuario_entrar_bancada(desenfileirar(&bancada->fila));

    if (bancada->usuarios[0] &&
        usuario_esta_aguardando(bancada->usuarios[0]) &&
        servente_pode_atender(bancada->serventes[0]))
    {
        atende_usuario(bancada, 0);
    }

    return ret;
}
