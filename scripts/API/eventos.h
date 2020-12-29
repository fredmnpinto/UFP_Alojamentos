//
// Created by Gabriel Fernandes on 24/12/2020.
//

#ifndef UFP_ALOJAMENTOS_EVENTOS_H
#define UFP_ALOJAMENTOS_EVENTOS_H

#include "../general/utils.h"

/**
 * Funcao que inicializa uma lista ligada(queue) de eventos diarios
 * @return                  Apontador para a lista ligada criada
 */
EVENT_QUEUE *init_event_queue();

/**
 * Funcao que adiciona um elemento novo a frente do last da queue
 * @param queue             Apontador para a queue
 * @param newEvent          Apontador para o novo elemento a ser adicionado(novo last)
 */
void event_list_enqueue(EVENT_QUEUE *queue, EVENT *newEvent);

/**
 * Funcao que remove o elemento mais antigo a ser adicionado(first)
 * @param queue             Apontador para a queue
 */
void event_list_dequeue(EVENT_QUEUE *queue);

/**
 * Funcao que retorna o tamanho atual da queue
 * @param queue             Apontador para a queue
 * @return                  Tamanho atual da queue
 */
int event_size(EVENT_QUEUE *queue);

/**
 * Funcao que indica se a queue esta vazia ou nao
 * @param queue             Apontador para a queue
 * @return                  0(Falso) se o size nao for igual a 0, e 1(Verdadeiro) se o size for igual a 0
 */
int event_isEmpty(EVENT_QUEUE *queue);

/**
 * Funcao que imprime todos os elementos da queue
 * @param queue             Apontador para a queue
 */
void print_event_queue(EVENT_QUEUE *queue);


#endif //UFP_ALOJAMENTOS_EVENTOS_H
