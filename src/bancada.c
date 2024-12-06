#define _DEFAULT_SOURCE

#include "bancada.h"
#include "log.h"
#include "xalloc.h"

#include <stdlib.h>

#define QUANDO_CHAMAR_SERVENTE 300 // 5 minutos de espera na fila.

static void rebalanco(Bancada *bancada, Servente *novo)
{
    Servente *set[BANSERMAX] = { NULL };
    int qtd_vas_por_serv[BANSERMAX] = { 0 };
    int ind_set = 0, ind_bancada = 0;
    int quociente = NING / bancada->n_serventes;
    int resto = NING % bancada->n_serventes;

    if (novo)
        set[ind_set++] = novo;

    for (ind_bancada = 0; ind_bancada < NING; ++ind_bancada)
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
    int tempo = servirDaVasilha(&bancada->vasilhas[pos],
                                usuario_vegetariano(bancada->usuarios[pos]));
    
    if (tempo >= 0)
        tempo += servente_inicia_atendimento(bancada->serventes[pos]);
    else
        tempo = 0;

    usuario_inicia_atendimento(bancada->usuarios[pos], tempo);
}


static void manda_embora_servente(Bancada *bancada, int pos)
{
    Servente *serv = bancada->serventes[pos];

    for (int i = 0; i < NING; ++i)
        if (bancada->serventes[i] == serv)
            bancada->serventes[i] = NULL;

    --bancada->n_serventes;

    descanso_recebe_servente(bancada->descanso, serv);

    if (bancada->n_serventes)
        rebalanco(bancada, NULL);
}


void bancada_free(Bancada *bancada)
{
    Servente *serv = NULL;

    for (int i = 0; i < NING; ++i)
    {
        if (bancada->serventes[i] != serv)
        {
            serv = bancada->serventes[i];
            servente_free(serv);
        }

        if (bancada->usuarios[i])
            usuario_free(bancada->usuarios[i]);
    }

    free(bancada);
}


Bancada *bancada_new(Ingrediente cardapio[NING], Descanso *descanso, bool vegetariana)
{
    Bancada *new = xcalloc(1, sizeof(Bancada));

    new->vegetariana = vegetariana;
    new->descanso = descanso;

    inicializarFila(&new->fila);

    for (int i = 0; i < NING; ++i)
        inicializarVasilha(&new->vasilhas[i], &cardapio[i]);

    new->n_usuarios_atendidos = 0;
    new->tempo_atendimento = 0;

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


bool bancada_esta_ativa(const Bancada *bancada)
{
    return bancada->ativa;
}


bool bancada_esta_acolhendo(const Bancada *bancada)
{
    return bancada->acolhendo;
}


int bancada_tempo_atendimento(const Bancada *bancada)
{
    return (bancada->n_usuarios_atendidos?
           bancada->tempo_atendimento / bancada->n_usuarios_atendidos
           : 0);
}


int bancada_tamanho_fila(const Bancada *bancada)
{
    return bancada->fila.tamanho;
}


int bancada_ativar(Bancada *bancada)
{
    int erro = 0;

    // Não faz nada se a bancada já estiver ativa;
    // Também, garante que o estado inicial da bancada é com 0 serventes.
    if (bancada->n_serventes || bancada->ativa)
        return 1;

    for (int i = 0; i < BANSERMIN && !erro; ++i)
    {
        if (bancada_solicita_servente(bancada) != i + 1)
            erro = 1;
    }

    if (!erro)
    {
        bancada->ativa = true;
        bancada->acolhendo = true;
    }
    else
        bancada_desativar(bancada);

    return erro;
}


void bancada_desativar(Bancada *bancada)
{
    if (!bancada_tem_usuarios(bancada))
    {
        const int c = bancada->n_serventes;

        bancada->ativa = false;

        for (int i = 0; i < c; ++i)
            bancada_dispensa_servente(bancada);
    }

    bancada->acolhendo = false;
}


int bancada_solicita_servente(Bancada *bancada)
{
    if (bancada->n_serventes < BANSERMAX)
    {
        Servente *novo = descanso_despacha_servente(bancada->descanso);

        if (novo)
        {
            ++bancada->n_serventes;
            rebalanco(bancada, novo);
        }
    }

    return bancada->n_serventes;
}


int bancada_dispensa_servente(Bancada *bancada)
{
    if (bancada->n_serventes <= 1 && bancada->ativa)
        return bancada->n_serventes;

    int mais_antigo = 0;

    for (int i = 1; i < NING; ++i)
        if (bancada->serventes[i] != bancada->serventes[mais_antigo]
            && servente_mais_antigo(bancada->serventes[i],
                                    bancada->serventes[mais_antigo]) < 0)
        {
            mais_antigo = i;
        }

    manda_embora_servente(bancada, mais_antigo);

    return bancada->n_serventes;
}


int bancada_descansos_obrigatorios(Bancada *bancada)
{
    if (bancada->n_serventes <= 1 && bancada->ativa)
        return bancada->n_serventes;

    int pos = 0;

    for ( ; pos < NING; ++pos)
        if (servente_precisa_descansar(bancada->serventes[pos])
            && servente_pode_atender(bancada->serventes[pos]))
        {
            break;
        }

    if (pos < NING)
    {
        manda_embora_servente(bancada, pos);
        bancada_solicita_servente(bancada);
    }

    return bancada->n_serventes;
}


void bancada_recebe_usuario(Bancada *bancada, Usuario *usuario)
{
    enfileirar(&bancada->fila, usuario);
}


Usuario *bancada_atendimento(Bancada *bancada)
{
    Usuario *ret = NULL;

    int pos = bancada->vegetariana? NING - 1 : NING - 2;

    if (bancada->usuarios[pos] &&
        usuario_foi_atendido(bancada->usuarios[pos]))
    {
        ret = usuario_deixar_bancada(bancada->usuarios[pos]);
        bancada->usuarios[pos] = NULL;

        ++bancada->n_usuarios_atendidos;
        bancada->tempo_atendimento += usuario_tempo_atendimento(ret);
    }


    for ( ; pos > 0; --pos)
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

    if (!bancada->usuarios[0] && !filaVazia(&bancada->fila))
    {
        bancada->usuarios[0] = usuario_entrar_bancada(desenfileirar(&bancada->fila));

        if (usuario_tempo_fila(bancada->usuarios[0]) <= QUANDO_CHAMAR_SERVENTE)
            bancada_solicita_servente(bancada);
    }

    if (bancada->usuarios[0] &&
        usuario_esta_aguardando(bancada->usuarios[0]) &&
        servente_pode_atender(bancada->serventes[0]))
    {
        atende_usuario(bancada, 0);
    }

    if (bancada->n_serventes < BANSERMIN)
        bancada_solicita_servente(bancada);

    if (!bancada_tem_usuarios(bancada) && !bancada->acolhendo)
        bancada_desativar(bancada);

    return ret;
}
