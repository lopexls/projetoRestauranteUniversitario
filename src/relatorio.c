#include <stdio.h>
#include "relogio.h"
#include "servente.h"
#include "usuario.h"
#include "vasilha.h"
#include "bancada.h"

//  relatório do expediente
void gerar_relatorio(Bancada *bancadas, int n_bancadas, Servente **serventes, int n_serventes, Ingrediente *ingredientes, int n_ingredientes) {
    int total_usuarios = 0;
    double tempo_total_atendimento = 0;
    double tempo_total_espera = 0;
    int total_consumido[n_ingredientes];

    // Inicializar 
    for (int i = 0; i < n_ingredientes; i++) {
        total_consumido[i] = 0;
    }

    printf("\n==== RELATÓRIO DO EXPEDIENTE ====\n");

    // servente
    printf("\nServentes:\n");
    for (int i = 0; i < n_serventes; i++) {
        if (serventes[i]) {
            printf("Servente %d:\n", i + 1);
            printf("- Usuários atendidos: %d\n", serventes[i]->n_usuarios_servidos);
            printf("- Tempo médio de atendimento: %.2f segundos\n", servente_tempo_atendimento_medio(serventes[i]));
        }
    }

    // bancada
    printf("\nBancadas:\n");
    for (int i = 0; i < n_bancadas; i++) {
        int usuarios_atendidos = 0;
        double tempo_atendimento = 0;

        for (int j = 0; j < NING; j++) {
            if (bancadas[i].usuarios[j]) {
                usuarios_atendidos++;
                tempo_atendimento += usuario_tempo_atendimento(bancadas[i].usuarios[j]);
                tempo_total_espera += usuario_tempo_fila(bancadas[i].usuarios[j]);
            }
        }

        printf("Bancada %d:\n", i + 1);
        printf("- Usuários atendidos: %d\n", usuarios_atendidos);
        printf("- Tempo médio de atendimento: %.2f segundos\n", usuarios_atendidos > 0 ? tempo_atendimento / usuarios_atendidos : 0);

        total_usuarios += usuarios_atendidos;
        tempo_total_atendimento += tempo_atendimento;
    }

    // ingredientes
    printf("\nIngredientes consumidos:\n");
    for (int i = 0; i < n_ingredientes; i++) {
        total_consumido[i] = ingredientes[i].capacidade - ingredientes[i].quantidadeAtual;
        printf("- %s: %d gramas consumidos\n", ingredientes[i].nome, total_consumido[i]);
    }

    // geral
    printf("\nResumo geral:\n");
    printf("- Usuários atendidos: %d\n", total_usuarios);
    printf("- Tempo médio de atendimento dos usuários: %.2f segundos\n", total_usuarios > 0 ? tempo_total_atendimento / total_usuarios : 0);
    printf("- Tempo médio de espera nas filas: %.2f segundos\n", total_usuarios > 0 ? tempo_total_espera / total_usuarios : 0);

    printf("\n==== FIM DO RELATÓRIO ====\n");
}
