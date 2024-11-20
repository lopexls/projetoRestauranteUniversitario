/** @file log.h
 * Funcionalidade de log do programa.
 *
 * Provavelmente ainda vai ser espandida ou totalmente reformulada no futuro.
 * Por enquanto, serve apenas para registrar eventuais erros de alocação de
 * memória.
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
    ERR_MEMORY_ALLOC    /**< Erro de alocação de memória. */
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
