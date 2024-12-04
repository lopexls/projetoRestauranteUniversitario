#define _DEFAULT_SOURCE

#include "fila.h"
#include "xalloc.h"

#include <stdlib.h>


// Função para inicializar uma fila
void inicializarFila(Fila* fila) {
    fila->frente = NULL;
    fila->traseira = NULL;
    fila->tamanho = 0;
}

// Função para verificar se a fila está vazia
int filaVazia(const Fila* fila) {
    return fila->tamanho == 0;
}

void filaEsvazia(Fila* fila) {
    while(!filaVazia(fila))
        usuario_free(desenfileirar(fila));
}

// Função para enfileirar um usuário na fila
void enfileirar(Fila* fila, Usuario* usuario) {
    Nodo* novoNodo = (Nodo*)xmalloc(sizeof(Nodo));

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
Usuario* desenfileirar(Fila* fila) {
    if (filaVazia(fila))
        return NULL;

    Nodo* temp = fila->frente;
    Usuario* usuario = temp->usuario;
    fila->frente = fila->frente->proximo;
    if (fila->frente == NULL) {
        fila->traseira = NULL;
    }
    free(temp);
    fila->tamanho--;

    return usuario;
}
