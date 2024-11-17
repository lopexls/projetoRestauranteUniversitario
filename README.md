# simulaRU

Um simulador de restaurante universitário implementado como trabalho final
da disciplina de *Algoritmos e Estruturas de Dados I*.

O foco do simulador é na estrutura de filas. São implementadas filas de
usuários para acesso ao restaurante e uma lógica de serviço que determina a
velocidade de consumo destas filas.

Veja os [requisitos completos](./AED-Requisitos_Trabalho_Final.pdf) do programa
para mais informações.

## Tempos do Simulador e Ciclo

As especificações do trabalho estabelecem que "o tempo de resolução" do
simulador deverá ser de 1 segundo. Ou seja, que os controles devem ter tempo
de resposta de 1 segundo. Por outro lado, também estabelecem que o simulador
deve simular 1 minuto do funcionamento do RU a cada 1 segundo de execução.

Para evitarmos a confusão entres os tempos envolvidos, é melhor fixarmos já
os quatro conceitos utilizados:

1. O *tempo simulado*

   É o tempo vivido no interior da simulação, cuja resolução é de 1 segundo.
   Podemos pensar no tempo simulado como o tempo que seria percebido por
   agentes (usuários, serventes…) dentro daquele universo. No tempo simulado,
   o RU funciona durante 6h diárias.

2. O *tempo de execução*

   É o tempo, real, de funcionamento do programa, medido por um(a)
   observador(a) externo.

3. A *velocidade de simulação*

   É a razão entre o tempo de execução e o tempo simulado. Uma razão de 1:1
   implicaria que o programa demora 1 segundo para simular 1 segundo do RU.
   De acordo com as especificações do trabalho, a velocidade de simulação
   padrão é de 1:60. Ou seja, ao longo de 1 segundo de execução, o programa
   simula a passagem de 60 segundos no universo simulado.

4. Um *ciclo*

   É o conjunto de todas as operações que são realizadas no RU para que seja
   simulado 1 segundo de seu funcionamento. Ou seja, naquele ciclo, usuários
   novos podem chegar ao sistema, um servente pode continuar servindo a
   porção de alimentos, uma vasilha pode ficar sem alimento, etc. O ciclo é
   repetido do início ao fim da simulação.

Para reforçar o que é central: o simulador é implementado como um grande laço
(loop), contendo uma sequência de instruções que mimetizam o que pode ocorrer
naquele instante da simulação. Este é o *ciclo*. Ao final do ciclo, deve-se
incrementar em 1 segundo o *tempo simulado*.

Por meio deste mecanismo é que mantemos registro da passagem do tempo no interior
do RU. As especificações do trabalho indicam os horários em que o restaurante
abre e fecha para cada uma das refeições. Nós só precisamos fazer o registro
do horário ao longo de um dia, i.e. 24 horas. Para isso, mantemos uma única
variável inteira, que conta os segundos transcorridos desde o início do dia.

## Diagramas

Os diagramas que foram utilizados no planejamento deste software utilizam
a sintaxe da ferramenta open-source [PlantUML][1]. A sequência de texto que
define cada um dos diagramas pode ser copiada e colada no website da ferramenta
para a visualização do diagrama. A edição deles também pode ser feita no
website.

[1]: https://www.plantuml.com/

### Diagrama de sequência

A proposta do diagrama de sequencia é prever a sequencia de trocas entre os
princiais objetos do programa ao longo de um ciclo do simulador. Nem todas
as trocas foram representadas no diagrama, apenas o essencial das relações
entre bancada, fila, serventes, etc. O diagrama ajudou a visualizar a
implementação do ciclo e a distinguirmos os principais TADs necessários.

### Diagrama de classes

Utilizado para desenharmos o conjunto de TADs que seriam utilizados, suas
funções, atributos e relações.

### Lógica de bancada

Fluxograma utilizado na implementação da lógica de bancada.

## Sobre o código

Esta seção apresenta algumas *guidelines* utilizadas para o desenvolvimento
do código fonte.

### Diretórios

Arquivos de *header* são salvos em [include](./include). Código fonte é
salvo é [src](./src).

### TADs

- Todo TAD é implementado em um arquivo de código fonte (nome_do_tad.c) e
um arquivo de header (nome_do_tad.h). O header deve conter a definição
da estrutura subjacente ao tipo (`typedef struct ...`) e os protótipos
das funções disponibilizadas pelo TAD.

- Todo TAD deve conter uma função `new()`, que retorna um ponteiro para uma
instância do tipo e uma função `free()`, que libera a memória utilizada
pela instância.

- Funções que funcionam como métodos do TAD devem receber um ponteiro para a
instância do tipo do TAD como primeiro argumento.

### Estilo de código

O que se segue são **sugestões** de estilo para a escrita do código, que
ajudam a manter a consistência e clareza do programa. Embora, pela natureza
deste projeto, não necessáriamente precisam ser seguidas.

- Nomes que identificam tipos utilizam CamelCase, iniciando com letras
maiúsculas. Enquanto nomes que identificam funções e variável utilizam
underscore_case, iniciando com minúsculas.

- Evitar ultrapassar 79 caracteres em uma linha. Eventualmente, esta regra pode
ser ignorada, mas é bom evitar a repetição de linhas longas e favorecer a
quebra de linha para melhorar a leitura do código.

- A identação deve ser realizada com quatro espaços.

- Funções que operam como métodos de TADs devem ser prefixadas com o nome do
TAD, seguido pelo nome da função.

### Documentando o código

Podemos utilizar a ferramenta [doxygen][2] para a geração automática da
documentação do código. A ferramenta é bastante flexível com relação à sintaxe
utilizada. Mas, podemos seguir a seguinte convenção:

- Documentar as funções com um comentário logo antes da **declaração** da mesma.
O comentário segue o estilo:
```
/** Descrição suscinta da função.
 *
 * Descrição detalhada da função,
 * que pode ter várias linhas. E frases. Se necessário.
 *
 * @param nome_do_parâmetro descrição do parâmetro.
 * @return descrição do que é retornado, se tiver algo.
 */
```
É necessário que o comentário inicie com uma barra e dois asteriscos.

Mais informações sobre a sintaxe reconhecida pelo *doxygen* podem ser estudados
na página do projeto.

[2]: https://doxygen.nl/index.html

### O módulo xalloc

O módulo [xalloc](./include/xalloc.h) implementa os macros `xmalloc()` e
`xcalloc()` que, por sua vez, chamam as funções `malloc()` e `calloc()` com
os mesmos argumentos. Adicionalmente, eles verificam se a alocação de memória
foi bem sucedida e encerram o programa caso contrário.

Assim, evitamos ter que escrever a verificação todas as vezes que queremos
alocar memória nova. Também, implementa uma decisão de *design*, na qual um
erro de alocação de memória leva a imediata finalização do programa. Esta
decisão é aceitável, porque tais erros são raros e é muito difícil recuperar o
programa quando eles ocorrem.

### O módulo log

O módulo [log](./include/log.h) tem a função de registrar mensagens de erro
que possam ocorrer durante a execução do programa.

### config

É em [config.h](./include/config.h) que definimos todas as macros de configuração
do programa.
