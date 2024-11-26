#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "usuario.h"

// Função para gerar um número aleatório e determinar o tipo do usuário
TipoUsuario gerarTipoUsuario() {
    int numeroAleatorio = rand() % MAX_NUM + 1; // Gera número entre 1 e MAX_NUM
    if (numeroAleatorio <= 4) {
        return VEGETARIANO;  // 40% chance de ser vegetariano
    } else {
        return CARNIVORO;  // 60% chance de ser carnívoro
    }
}

// Função para alocar o usuário na fila
int escolherFila(TipoUsuario tipo) {
    if (tipo == VEGETARIANO) {
        return 0;  // Fila especial para vegetarianos
    } else {
        return rand() % NFILAS_MAX + 1;  // Fila aleatória para carnívoros
    }
}

// Função para gerar usuários no restaurante
void gerarUsuarios(Restaurante* restaurante, int quantidadeUsuarios) {
    for (int i = 0; i < quantidadeUsuarios; i++) {
        Usuario usuario;
        usuario.tipo = gerarTipoUsuario();
        usuario.filaEscolhida = escolherFila(usuario.tipo);
        usuario.tempoEspera = 0;
        usuario.tempoAtendimento = rand() % 4 + 3; // Tempo entre 3 e 6 segundos
        adicionarUsuario(restaurante, usuario);
    }
}

// Função para adicionar usuário na fila
void adicionarUsuario(Restaurante* restaurante, Usuario usuario) {
    if (usuario.filaEscolhida == 0) {
        // Fila especial para vegetarianos
        if (restaurante->qtdUsuariosVeg < MAX_USUARIOS) {
            restaurante->filaEspecial[restaurante->qtdUsuariosVeg++] = usuario;
        } else {
            printf("Fila especial para vegetarianos cheia.\n");
        }
    } else {
        int filaIndex = usuario.filaEscolhida - 1;
        // Fila normal para carnívoros
        if (restaurante->qtdUsuariosNormais[filaIndex] < MAX_USUARIOS) {
            restaurante->filaNormais[filaIndex][restaurante->qtdUsuariosNormais[filaIndex]++] = usuario;
        } else {
            printf("Fila %d para carnívoros cheia.\n", filaIndex + 1);
        }
    }
}

// Função para atender o próximo usuário da fila
void atenderUsuario(Restaurante* restaurante, int filaIndex) {
    if (filaIndex == 0) {
        // Atende o próximo vegetariano na fila especial
        if (restaurante->qtdUsuariosVeg > 0) {
            Usuario* usuario = &restaurante->filaEspecial[0];
            printf("Atendendo vegetariano, tempo de atendimento: %d segundos\n", usuario->tempoAtendimento + TEMPO_EXTRA_VEG);
            // Shift a fila para remover o usuário
            for (int i = 1; i < restaurante->qtdUsuariosVeg; i++) {
                restaurante->filaEspecial[i - 1] = restaurante->filaEspecial[i];
            }
            restaurante->qtdUsuariosVeg--;
        }
    } else {
        // Atende o próximo carnívoro na fila normal
        if (restaurante->qtdUsuariosNormais[filaIndex] > 0) {
            Usuario* usuario = &restaurante->filaNormais[filaIndex][0];
            printf("Atendendo carnívoro, tempo de atendimento: %d segundos\n", usuario->tempoAtendimento);
            // Shift a fila para remover o usuário
            for (int i = 1; i < restaurante->qtdUsuariosNormais[filaIndex]; i++) {
                restaurante->filaNormais[filaIndex][i - 1] = restaurante->filaNormais[filaIndex][i];
            }
            restaurante->qtdUsuariosNormais[filaIndex]--;
        }
    }
}

// Função para exibir todos os usuários e suas filas
void exibirUsuarios(Restaurante* restaurante) {
    printf("\nLista de usuários:\n");
    // Exibe vegetarianos
    for (int i = 0; i < restaurante->qtdUsuariosVeg; i++) {
        printf("Vegetariano %d: Fila Especial\n", i + 1);
    }
    // Exibe carnívoros
    for (int i = 0; i < NFILAS_MAX; i++) {
        for (int j = 0; j < restaurante->qtdUsuariosNormais[i]; j++) {
            printf("Carnívoro %d: Fila %d\n", j + 1, i + 1);
        }
    }
}

// Função para gerar relatórios de atendimento
void gerarRelatorio(Restaurante* restaurante) {
    printf("\nRelatório Final:\n");
    int totalAtendidos = 0;
    int totalVeg = 0;
    int totalCarn = 0;
    
    // Contagem de atendidos
    for (int i = 0; i < NFILAS_MAX; i++) {
        totalAtendidos += restaurante->qtdUsuariosNormais[i];
    }
    totalAtendidos += restaurante->qtdUsuariosVeg;

    totalVeg = restaurante->qtdUsuariosVeg;
    totalCarn = totalAtendidos - totalVeg;

    printf("Total de usuários atendidos: %d\n", totalAtendidos);
    printf("Total de vegetarianos atendidos: %d\n", totalVeg);
    printf("Total de carnívoros atendidos: %d\n", totalCarn);
}

// Função para simular o atendimento
void simularAtendimento(Restaurante* restaurante) {
    for (int i = 0; i < NFILAS_MAX; i++) {
        while (restaurante->qtdUsuariosNormais[i] > 0) {
            atenderUsuario(restaurante, i);
        }
    }

    // Atendendo vegetarianos
    while (restaurante->qtdUsuariosVeg > 0) {
        atenderUsuario(restaurante, 0);
    }

    gerarRelatorio(restaurante); // Relatório final após o atendimento
}
