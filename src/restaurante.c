#define _DEFAULT_SOURCE

#include "rando.h"
#include "relatorio.h"
#include "restaurante.h"
#include "usuario.h"
#include "xalloc.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


#define QUANDO_ABRIR_BANCADA 500 // Número de usuários no sistema


static bool deve_gerar_usuario(Refeicao ref)
{
    const double u = rando_uniform();

    return u <= rando_chi_squared(relogio_hora_fracionada(ref));
}


static Bancada *encontra_menos_cheia(Restaurante *ru)
{
    Bancada *ret = ru->bancadas[0];

    for (int i = 0; i < ru->n_bancadas_ativas; ++i)
        if (bancada_esta_acolhendo(ru->bancadas[i])
            && bancada_tamanho_fila(ru->bancadas[i]) < bancada_tamanho_fila(ret))
        {
            ret = ru->bancadas[i];
        }

    return ret;
}


static void abre_bancada(Restaurante *ru)
{
    if (ru->n_bancadas_ativas < QTDBANCADAMAX)
    {
        if (!bancada_ativar(ru->bancadas[ru->n_bancadas_ativas]))
            ++ru->n_bancadas_ativas;
    }
}


static void fecha_bancada(Restaurante *ru)
{
    if (ru->n_bancadas_ativas > 1)
        bancada_desativar(ru->bancadas[--ru->n_bancadas_ativas]);
}


Restaurante *restaurante_new(Refeicao ref, int velocidade)
{
    Restaurante *new = xmalloc(sizeof(*new));

    new->descanso = descanso_new();

    for (int i = 0; i < NING; ++i)
        inicializarIngrediente(&new->cardapio[i], i);

    new->bancadas[0] = bancada_new(new->cardapio, new->descanso, true);

    for (int i = 1; i < QTDBANCADAMAX; ++i)
        new->bancadas[i] = bancada_new(new->cardapio, new->descanso, false);

    new->refeicao = ref;
    new->velocidade = velocidade;
    new->n_bancadas_ativas = 0;

    return new;
}


void restaurante_free(Restaurante *ru)
{
    for (int i = 0; i < QTDBANCADAMAX; ++i)
        bancada_free(ru->bancadas[i]);

    descanso_free(ru->descanso);

    free(ru);
}


int restaurante_simula(Restaurante *ru)
{
    int n_usuarios_presentes = 0;
    int n_usuarios_processados = 0;
    int tempo_fila = 0;
    int tempo_atendimento = 0;

    relogio_set(ru->refeicao);

    abre_bancada(ru);

    while (!relogio_fim(ru->refeicao) || n_usuarios_presentes)
    {
        if (n_usuarios_presentes > QUANDO_ABRIR_BANCADA)
            abre_bancada(ru);
        else
            fecha_bancada(ru);

        if (!relogio_fim(ru->refeicao) && deve_gerar_usuario(ru->refeicao))
        {
            Usuario *novo_u = usuario_new();
            if (usuario_vegetariano(novo_u))
                bancada_recebe_usuario(ru->bancadas[0], novo_u);
            else
                bancada_recebe_usuario(encontra_menos_cheia(ru), novo_u);
            ++n_usuarios_presentes;
        }

        for (int i = 0; i < QTDBANCADAMAX; ++i)
        {
            if (!bancada_esta_ativa(ru->bancadas[i]))
                continue;

            bancada_descansos_obrigatorios(ru->bancadas[i]);

            Usuario *processado = bancada_atendimento(ru->bancadas[i]);
            if (processado)
            {
                tempo_fila += usuario_tempo_fila(processado);
                tempo_atendimento += usuario_tempo_atendimento(processado);
                usuario_free(processado);
                --n_usuarios_presentes;
                ++n_usuarios_processados;
            }
        }

        relogio_incrementa(ru->velocidade);
    }

    bancada_desativar(ru->bancadas[0]);

    gerar_relatorio(ru, n_usuarios_processados, tempo_fila, tempo_atendimento);

    return 0;
}
