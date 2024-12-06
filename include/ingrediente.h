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
    TipoIngrediente tipo;
    int porcaoMedia;
    double chanceAceitacao;
    int capVasilha;
    int totalConsumido;
} Ingrediente;


void inicializarIngrediente(Ingrediente *i, TipoIngrediente t);


#endif // INGREDIENTE_H
