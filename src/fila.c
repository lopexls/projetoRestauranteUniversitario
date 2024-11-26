// fila.c
#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

// Função para inicializar uma fila
void inicializarFila(Fila* fila) {
    fila->frente = NULL;
    fila->traseira = NULL;
    fila->tamanho = 0;
}

// Função para verificar se a fila está vazia
int filaVazia(Fila* fila) {
    return fila->tamanho == 0;
}

// Função para enfileirar um usuário na fila
void enfileirar(Fila* fila, Usuario usuario) {
    Nodo* novoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (novoNodo == NULL) {
        printf("Erro ao alocar memória para o usuário.\n");
        return;
    }
    novoNodo->usuario = usuario;
    novoNodo->proximo = NULL;

    if (filaVazia(fila)) {
        fila->frente = novoNodo;
    } else {
        fila->traseira->proximo = novoNodo;
    }
    fila->traseira = novoNodo;
    fila->tamanho++;
}

// Função para desenfileirar um usuário da fila
Usuario desenfileirar(Fila* fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia, não há usuários para atender.\n");
        Usuario usuarioVazio = {CARNIVORO, 0, 0, 0};  // Retorna um usuário "vazio"
        return usuarioVazio;
    }

    Nodo* temp = fila->frente;
    Usuario usuario = temp->usuario;
    fila->frente = fila->frente->proximo;
    if (fila->frente == NULL) {
        fila->traseira = NULL;
    }
    free(temp);
    fila->tamanho--;

    return usuario;
}

// Função para exibir os usuários da fila (para depuração)
void exibirFila(Fila* fila) {
    Nodo* atual = fila->frente;
    while (atual != NULL) {
        printf("Usuário: Tipo %s, Tempo de Atendimento: %d segundos\n",
               atual->usuario.tipo == VEGETARIANO ? "Vegetariano" : "Carnívoro",
               atual->usuario.tempoAtendimento);
        atual = atual->proximo;
    }
}

