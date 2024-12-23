#ifndef USUARIO_H
#define USUARIO_H

#include <stdbool.h>

typedef enum { CARNIVORO, VEGETARIANO } TipoUsuario;


typedef struct {
    TipoUsuario tipo;          // Tipo de usuário: CARNIVORO ou VEGETARIANO
    int hora_criacao;
    int hora_chega_bancada;
    int hora_sai_bancada;
    int hora_fim_atendimento;
} Usuario;


void usuario_free(Usuario *u);
Usuario *usuario_new(void);

bool usuario_esta_aguardando(const Usuario *u);
bool usuario_foi_atendido(const Usuario *u) __attribute__((nonnull(1)));
bool usuario_vegetariano(const Usuario *u) __attribute__((nonnull(1)));

int usuario_tempo_fila(const Usuario *u);
int usuario_tempo_atendimento(const Usuario *u);
int usuario_tempo_total(const Usuario *u);

Usuario *usuario_avancar(Usuario *u);
Usuario *usuario_entrar_bancada(Usuario *u);
Usuario *usuario_deixar_bancada(Usuario *u);
Usuario *usuario_inicia_atendimento(Usuario *u, int tempo);


#endif // USUARIO_H
