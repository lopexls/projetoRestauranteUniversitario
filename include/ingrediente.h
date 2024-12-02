#ifndef INGREDIENTE_H
#define INGREDIENTE_H


typedef enum
{
    ARROZ,
    FEIJAO,
    PROTEINA_ANIMAL,
    LEG_COZIDO,
    LEG_SALADA,
    FOLHA,
    OPT_VEG
} TipoIngrediente;


typedef struct
{
    int porcaoMedia;
    double chanceAceitacao;
    int capVasilha;
} Ingrediente;


void inicializarIngrediente(Ingrediente *i, TipoIngrediente t);


#endif // INGREDIENTE_H
