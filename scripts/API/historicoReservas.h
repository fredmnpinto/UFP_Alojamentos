//
// Created by Gabriel Fernandes on 06/12/2020.
//

#ifndef UFP_ALOJAMENTOS_HISTORICORESERVAS_H
#define UFP_ALOJAMENTOS_HISTORICORESERVAS_H

#include "../general/utils.h"

/**
 * Funcao que incializa uma lista ligada(stack) de historico
 * @return              Apontador para a stack historico
 */
HIST_STACK* init_hist_stack();

/**
 * Funcao que adiciona um elemento novo atras da head da stack
 * @param stack         Apontador para a stack
 * @param newHead       Apontador para o elemento a ser adicionado(nova head)
 */
void hist_list_push(HIST_STACK* stack, HIST* newHead);

/**
 * Funcao que remove o ultimo elemento a ser adicionado(a head)
 * @param stack         Apontador para a stack
 */
void hist_list_pop(HIST_STACK* stack);

/**
 * Funcao que retorna o tamanho atual da stack
 * @param stack         Apontador para a stack
 * @return              Tamanho atual da stack
 */
int hist_list_size(HIST_STACK* stack);

/**
 * Funcao que indica se a stack esta vazia ou nao
 * @param stack         Apontador para a stack
 * @return              0(Falso) se o size nao for igual a 0, e 1(Verdadeiro) se o size for igual a 0
 */
int hist_isEmpty(HIST_STACK* stack);

/**
 * Funcao que imprime todos os elementos da stack
 * @param stack         Apontador para a stack
 */
void print_hist_Stack(HIST_STACK* stack);

#endif //UFP_ALOJAMENTOS_HISTORICORESERVAS_H
