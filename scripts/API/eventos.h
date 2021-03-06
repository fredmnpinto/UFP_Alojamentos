//
// Created by Gabriel Fernandes on 24/12/2020.
//

#ifndef UFP_ALOJAMENTOS_EVENTOS_H
#define UFP_ALOJAMENTOS_EVENTOS_H

#include "../general/utils.h"

/**
 * Funcao que inicializa uma lista ligada(stack) de eventos diarios
 * @return                  Apontador para a lista ligada criada
 */
EVENT_STACK *init_event_stack();

/**
 * Funcao que adiciona um elemento novo atras do ultimo adicionado(head)
 * @param stack             Apontador para a stack
 * @param newEvent          Apontador para o novo elemento a ser adicionado(novo last)
 */
void event_list_push(EVENT_STACK *stack, EVENT *newEvent);

/**
 * Funcao que remove o ultimo elemento a ser adicionada
 * @param stack             Apontador para a stack
 */
void event_list_pop(EVENT_STACK *stack);

/**
 * Funcao que retorna o tamanho atual da stack
 * @param stack             Apontador para a stack
 * @return                  Tamanho atual da stack
 */
int event_size(EVENT_STACK *stack);

/**
 * Funcao que indica se a stack esta vazia ou nao
 * @param stack             Apontador para a stack
 * @return                  0(Falso) se o size nao for igual a 0, e 1(Verdadeiro) se o size for igual a 0
 */
int event_isEmpty(EVENT_STACK *stack);

/**
 * Funcao que imprime todos os elementos da queue
 * @param queue             Apontador para a queue
 */
void print_event_stack(EVENT_STACK *stack);

/**
 * Funcao que pega numa lista de eventos e percorre-a ate chegar ao evento que procuramos, ou ate ao final da lista
 * @param stack             Apontador para a lista de eventos
 * @param eventSearchFor    String com a descricao do evento que procuramos
 * @return                  1 se encontramos o evento na lista de eventos           -1 se nao encontrarmos
 */
int check_event(EVENT_STACK* stack, char eventSearchFor[]);

/**
 * Funcao que preenche uma stack de eventos com os evento no array "eventos[]"
 * @param eventos           Array com eventos
 * @param listaEventos      Apontador para a stack a ser preenchida
 * @return                  Apontador para a stack com os eventos adicionados
 */
EVENT_STACK* add_data_event(char eventos[], EVENT_STACK* listaEventos);

/**
 * Funcao que da free em todos os eventos da stack
 * @param stack             Apontador para a stack
 * @return                  Apontador para uma stack sem qualquer elemento
 */
EVENT_STACK* freeAll(EVENT_STACK* stack);

/**
 * Funcao que altera um evento selecionado da lista de eventos
 * @param listaEventos      Apontadar para a lista ligada de eventos
 * @param eventSearchFor    String com o evento a ser alterado
 * @param newChangedEvent   String com o novo evento
 * @return                  Apontador para a lista de eventos alterada
 */
EVENT_STACK* change_event(EVENT_STACK *listaEventos, char eventSearchFor[], char newChangedEvent[]);
#endif //UFP_ALOJAMENTOS_EVENTOS_H
