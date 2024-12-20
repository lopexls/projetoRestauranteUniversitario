#define _DEFAULT_SOURCE

#include "bancada.h"
#include "config.h"
#include "ingrediente.h"
#include "descanso.h"
#include "relatorio.h"
#include "relogio.h"
#include "servente.h"
#include "usuario.h"

#include <stdio.h>


static const char *nomeDaRef[] = {"Café da Manhã", "Almoço", "Jantar"};

static const char *nomeDoIng[] = {"Arroz", "Feijão", "Proteína animal",
                                  "Legumes Cozidos", "Legumes salada",
                                  "Folhas", "Opção vegetariana"};

//  relatório do expediente
void gerar_relatorio(Restaurante *ru, int total_usuarios,
                     int tempo_total_espera, int tempo_total_atendimento)
{
    printf("\n==== RELATÓRIO DO EXPEDIENTE: %s ====\n",
           nomeDaRef[ru->refeicao]);

    Servente **serventes = ru->descanso->serventes;
    printf("\nServentes:\n");
    for (int i = 0; i < QTDSERMAX + 1; i++) {
        if (serventes[i]) {
            printf(
                "Servente %d:\n"
                "- Atendimentos realizados: %d\n"
                "- Tempo médio de atendimento: %d segundos\n",
                i + 1,
                serventes[i]->n_usuarios_servidos,
                servente_tempo_atendimento_medio(serventes[i]));
        }
    }

    Bancada **bancadas = ru->bancadas;
    printf("\nBancadas:\n");
    for (int i = 0; i < QTDBANCADAMAX; i++) {
        printf(
            "Bancada %d:\n"
            "- Usuários atendidos: %d\n"
            "- Tempo médio de atendimento: %d segundos\n",
            i + 1,
            bancadas[i]->n_usuarios_atendidos,
            bancada_tempo_atendimento(bancadas[i]));
    }

    Ingrediente *ingredientes = ru->cardapio;
    printf("\nIngredientes consumidos:\n");
    for (int i = 0; i < NING; i++) {
        printf(
            "Ingrediente: %s\n"
            "- Total consumido: %d kg\n",
            nomeDoIng[ingredientes[i].tipo],
            ingredientes[i].totalConsumido / 1000);
    }

    // geral
    printf(
        "\nResumo geral:\n"
        "- Usuários atendidos: %d\n"
        "- Tempo médio de espera nas filas: %d segundos\n"
        "- Tempo médio de atendimento dos usuários: %d segundos\n"
        "- Hora de fechamento: %s\n",
        total_usuarios,
        total_usuarios > 0 ? tempo_total_espera / total_usuarios : 0,
        total_usuarios > 0 ? tempo_total_atendimento / total_usuarios : 0,
        relogio_formatado(-1));

    printf("\n==== FIM DO RELATÓRIO ====\n");
}
