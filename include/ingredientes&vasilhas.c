#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "config.h"  
#include "fila.h"    
#include "usuarios.h"

typedef struct 
{
    int id; 
    char nome[20];
    int capacidade;
    int quantidadeAtual;
    int qntMinServida;
    int qntMaxServida;
    int probabilidadeUso;
} Ingrediente; 

typedef struct 
{
    Ingrediente ingredientes[NING];
} Vasilha;

void inicializarIngredientes(Vasilha *vasilha) 
{
    for (int i = 0; i < NING; i++) 
    {
        vasilha->ingredientes[i].id = i;
        snprintf(vasilha->ingredientes[i].nome, 20, "Ingrediente %d", i + 1);
        vasilha->ingredientes[i].capacidade = CAPING1;            
        vasilha->ingredientes[i].quantidadeAtual = CAPING1;       
        vasilha->ingredientes[i].qntMinServida = QTDMINING1;      
        vasilha->ingredientes[i].qntMaxServida = QTDMAXING1;      
        vasilha->ingredientes[i].probabilidadeUso = NPROBING1;    
    }
}

int vaiUsarIngrediente(Ingrediente *ingrediente) 
{
    int teste = rand() % 100;  
    return teste < ingrediente->probabilidadeUso; 
}

int servirIngrediente(Ingrediente *ingrediente) 
{
    int quantidadeServida = (rand() % (ingrediente->qntMaxServida - ingrediente->qntMinServida + 1)) + ingrediente->qntMinServida;
    if (ingrediente->quantidadeAtual >= quantidadeServida) 
    {
        ingrediente->quantidadeAtual -= quantidadeServida;
        return quantidadeServida;
    } else 
    {
        printf("Ingrediente %s acabou. Realizando a reposicao...\n", ingrediente->nome);
        ingrediente->quantidadeAtual = ingrediente->capacidade;  /
        return 0; 
    }
}

void atenderUsuario(Vasilha *vasilha, Usuario usuario) {
    printf("Atendendo usuario: Tipo %s\n",
           usuario.tipo == VEGETARIANO ? "Vegetariano" : "Carnivoro");

    for (int i = 0; i < NING; i++) 
    {
        if (usuario.tipo == VEGETARIANO && i == 0) 
        {  
            printf("Ingrediente %s preparado especialmente para vegetarianos.\n", vasilha->ingredientes[i].nome);
        }

        if (vaiUsarIngrediente(&vasilha->ingredientes[i])) 
        {
            int servido = servirIngrediente(&vasilha->ingredientes[i]);
            if (servido > 0) {
                printf("Servido %d gramas do %s\n", servido, vasilha->ingredientes[i].nome);
            }
        }
    }
}

