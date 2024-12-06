#define _DEFAULT_SOURCE

#include "config.h"
#include "log.h" 
#include "relogio.h"

#include <unistd.h>

// Tamanho da string "HH:MM:SS" + \0
// Seria 9 bytes. Mas, colocamos 16 para silenciar um warning do compilador.
#define HORAFMTLEN 16


int hora_atual = 0;


void relogio_set(Refeicao ref)
{
    switch (ref)
    {
        case CAFE_DA_MANHA:
            hora_atual = HORAINICAFE;
            break;
        case ALMOCO:
            hora_atual = HORAINIALMOCO;
            break;
        case JANTA:
            hora_atual = HORAINIJANTA;
            break;
        default:
            log_err(ERR_CRITICAL, ERR_HORA_NAO_DEF);
    }
}


bool relogio_fim(Refeicao ref)
{
    switch (ref)
    {
        case CAFE_DA_MANHA: return hora_atual >= HORAFIMCAFE;
        case ALMOCO:        return hora_atual >= HORAFIMALMOCO;
        case JANTA:         return hora_atual >= HORAFIMJANTA;
        default:
            log_err(ERR_CRITICAL, ERR_HORA_NAO_DEF);
            return true;
    }
}


int relogio_range(Refeicao ref)
{
    switch (ref)
    {
        case CAFE_DA_MANHA: return HORAFIMCAFE - HORAINICAFE;
        case ALMOCO:        return HORAFIMALMOCO - HORAINIALMOCO;
        case JANTA:         return HORAFIMJANTA - HORAINIJANTA;
        default:
            log_err(ERR_CRITICAL, ERR_HORA_NAO_DEF);
            return 1;
    }
}


int relogio_hora_relativa(Refeicao ref)
{
    switch (ref)
    {
        case CAFE_DA_MANHA:     return hora_atual - HORAINICAFE;
        case ALMOCO:            return hora_atual - HORAINIALMOCO;
        case JANTA:             return hora_atual - HORAINIJANTA;
        default:
            log_err(ERR_CRITICAL, ERR_HORA_NAO_DEF);
            return 0;
    }
}


double relogio_hora_fracionada(Refeicao ref)
{
    return (double) relogio_hora_relativa(ref) / relogio_range(ref);
}


void relogio_incrementa(int velocidade)
{
    if (velocidade > 0)
    {
        usleep(1000000 / velocidade);
    }

    ++hora_atual;
}


char *relogio_formatado(int segundos)
{
    static char buffer[HORAFMTLEN];
    int tempo = segundos < 0 ? hora_atual : segundos;

    int horas = tempo / 3600;
    int minutos = (tempo % 3600) / 60;
    int seg = tempo % 60;

    snprintf(buffer, HORAFMTLEN, "%02d:%02d:%02d", horas, minutos, seg);

    return buffer;
}
