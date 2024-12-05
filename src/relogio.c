#define _DEFAULT_SOURCE

#include "config.h"
#include "log.h" 
#include "relogio.h"


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


bool relogio_check_end(Refeicao ref)
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


char *relogio_formatado(void)
{
    static char buffer[HORAFMTLEN];

    int horas = hora_atual / 3600;
    int minutos = (hora_atual % 3600) / 60;
    int segundos = hora_atual % 60;

    snprintf(buffer, HORAFMTLEN, "%02d:%02d:%02d", horas, minutos, segundos);

    return buffer;
}
