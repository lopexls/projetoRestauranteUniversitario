// fila.h
#ifndef FILA_H
#define FILA_H

#include "usuario.h"

// Definições de estruturas de fila
typedef struct Nodo {
    Usuario* usuario;
    struct Nodo* proximo;
} Nodo;

typedef struct {
    Nodo* frente;
    Nodo* traseira;
    int tamanho;
} Fila;

// Funções de manipulação da fila
void inicializarFila(Fila* fila);
int filaVazia(const Fila* fila);
void filaEsvazia(Fila* fila);
void enfileirar(Fila* fila, Usuario* usuario);
Usuario* desenfileirar(Fila* fila);


#endif // FILA_H
