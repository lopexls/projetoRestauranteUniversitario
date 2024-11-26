#ifndef USUARIOS_H
#define USUARIOS_H

#include <time.h>

#define NFILAS_MAX 3        // Número de filas normais
#define MAX_USUARIOS 10     // Limite de usuários por fila
#define MAX_NUM 10          // Faixa para o número aleatório (1 a 10)
#define TEMPO_EXTRA_VEG 2   // Tempo extra para atender usuários vegetarianos

typedef enum { CARNIVORO, VEGETARIANO } TipoUsuario;

typedef struct {
    TipoUsuario tipo;          // Tipo de usuário: CARNIVORO ou VEGETARIANO
    int filaEscolhida;         // Fila onde o usuário está (0 para especial, 1 a NFILAS_MAX para filas normais)
    int tempoEspera;           // Tempo de espera do usuário
    int tempoAtendimento;      // Tempo de atendimento do usuário
} Usuario;

typedef struct {
    Usuario filaNormais[NFILAS_MAX][MAX_USUARIOS]; // Filas normais (para carnívoros)
    Usuario filaEspecial[MAX_USUARIOS];            // Fila especial para vegetarianos
    int qtdUsuariosNormais[NFILAS_MAX];            // Quantidade de usuários em cada fila normal
    int qtdUsuariosVeg;                            // Quantidade de vegetarianos na fila especial
    int qtdServentes;                              // Quantidade de serventes
} Restaurante;

// Funções para manipulação de filas e usuários

TipoUsuario gerarTipoUsuario(); // Gerar tipo de usuário (carnívoro ou vegetariano)
int escolherFila(TipoUsuario tipo); // Escolher a fila do usuário
void gerarUsuarios(Restaurante* restaurante, int quantidadeUsuarios); // Gerar usuários para o restaurante
void atenderUsuario(Restaurante* restaurante, int filaIndex); // Atender o próximo usuário da fila
void adicionarUsuario(Restaurante* restaurante, Usuario usuario); // Adicionar usuário à fila
void exibirUsuarios(Restaurante* restaurante); // Exibir usuários nas filas
void gerarRelatorio(Restaurante* restaurante); // Gerar relatório após atendimento
void simularAtendimento(Restaurante* restaurante); // Simulação do atendimento no restaurante

#endif



