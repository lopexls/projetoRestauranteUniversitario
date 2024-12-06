/** @file log.h
 * Funcionalidade de log do programa.
 *
 * Serve para registrar mensagens de erro e debug.
 */
#pragma once

/** Um tipo para a classe de erro. */
typedef enum
{
    ERR_FATAL,      /**< Erro fatal. */
    ERR_CRITICAL,   /**< Erro crítico. */
    ERR_WARNING     /**< Aviso. */
} ErrType;


/** Um tipo para a fonte do erro. */
typedef enum
{
    ERR_MEMORY_ALLOC,    /**< Erro de alocação de memória. */
    ERR_DESCANSO_CHEIO,  /**< Erro de descanso cheio. Indica BUG. */
    ERR_HORA_NAO_DEF     /**< Erro de horário indefinido. */
} ErrSource;


/** Função para registrar um erro em log.
 *
 * Se o erro for fatal, a função chama `exit()` e encerra o programa com
 * um código de erro.
 *
 * @param type O tipo de erro. Ver `ErrType`.
 * @param source A fonte do erro. Ver `ErrSource`.
 */
void log_err(ErrType type, ErrSource source);


/** Imprime uma mensagem se NDEBUG não estiver definido.
 *
 * Caso a macro NDEBUG não estiver definida, esta função não faz nada.
 *
 * @param msg Ponteiro para uma cadeia de caracteres, que será impressa.
 */
void log_debug(const char *msg);
