#include "relogio.h"

int hora_atual = 0;

// horários padrão
enum Horarios {
    CAFE_DA_MANHA = 8 * 60 * 60, 
    ALMOCO = 12 * 60 * 60,       
    JANTA = 18 * 60 * 60         
};

// horário específico
void relogio_set(Horarios horario) {
    hora_atual = horario;
}

// horário atual no formato HH:MM:SS
void relogio_formatado(char *buffer) {
    int horas = hora_atual / 3600;
    int minutos = (hora_atual % 3600) / 60;
    int segundos = hora_atual % 60;
    snprintf(buffer, 9, "%02d:%02d:%02d", horas, minutos, segundos);
}

// incrementar o relógio em segundos
void relogio_incrementar(int segundos) {
    hora_atual += segundos;
    if (hora_atual >= 24 * 60 * 60) { 
        hora_atual %= 24 * 60 * 60;
    }
}

// obter a hora atual em segundos desde a meia-noite
int relogio_obter() {
    return hora_atual;
}
