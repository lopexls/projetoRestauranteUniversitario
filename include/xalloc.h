/** @file xalloc.h
 * Fornece as macros `xalloc()` e `xcalloc()`, para alocação dinâmica.
 *
 * As macros são wrappers sobre as funções da biblioteca padrão, incluindo
 * a verificação subsequente do sucesso da operação.
 *
 * A idéia é evitar fazer esta verificação repetidas vezes no código, já que
 * ela está embutida na própria chamada. Se a alocação de memória falhar,
 * uma mensagem de erro é registrada em log e o programa é encerrado.
 * 
 * Assim, tanto `xmalloc()` quanto `xcalloc()` **nunca retornam NULL**.
 *
 * A implementação é feita por meio de macros para evitar o overhead de uma
 * função adicional toda vez que houver requisição de memória.
 */
#pragma once

#include "log.h"

#include <stdlib.h>


/** Wrapper sobre a função de stdlib `malloc()`.
 *
 * Se a `malloc()` retornar NULL, o programa é encerrado.
 *
 * @param size Tamanho, em bytes, da memória requisitada.
 * @return Ponteiro para a região da memória.
 */
#define xmalloc(size) ({ \
    void *_ptr = malloc(size); \
    if (!_ptr) log_err(ERR_FATAL, ERR_MEMORY_ALLOC); \
    _ptr; \
})


/** Wrapper sobre a função de stdlib `calloc()`.
 *
 * Se a `calloc()` retornar NULL, o programa é encerrado.
 *
 * @param nmemb Número de objetos requisitados.
 * @param size Tamanho, em bytes, de cada unidade requisitada.
 * @return Ponteiro para a região da memória.
 */
#define xcalloc(nmemb, size) ({ \
    void *_ptr = calloc(nmemb, size); \
    if (!_ptr) log_err(ERR_FATAL, ERR_MEMORY_ALLOC); \
    _ptr; \
})
