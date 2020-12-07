//
// Created by Gabriel Fernandes on 04/12/2020.
//

#ifndef UFP_ALOJAMENTOS_GUESTS_LIST_H
#define UFP_ALOJAMENTOS_GUESTS_LIST_H

#include "../general/utils.h"

/**
 * Funcao para inicializar a stack da lista de hospedes
 * @return  Ponteiro para a stack
 */
HOSP_STACK* init_guest_stack();

/**
 * Funcao para adicionar um novo hospede a stack(Atras do ultimo hospede adicionado)
 * @param stack     Ponteiro para a stack
 * @param newHead   Ponteiro para o novo hospede que sera a nova head da stack
 */
void guests_lists_push(HOSP_STACK* stack, HOSP* newHead);

/**
 * Funcao para remover o ultimo hospede adicionado da stack
 * @param stack     Ponteiro para a stack
 * @param currHead  Ponteiro para a atual head da stack (O hospede que ira ser removido)
 */
void guests_list_pop(HOSP_STACK* stack, HOSP* currHead);

/**
 * Funcao para saber o tamanho da lista de hospede
 * @return  O tamanho da lista
 */
int guests_list_size();

/**
 * Funcao para saber se a stack esta vazia ou nao
 * @return  0(Falso) se o size nao for igual a 0, e 1(Verdadeiro) se o size for igual a 0
 */
int hosp_isEmpty();

/**
 * Funcao que imprime todos os valores da stack
 * @param stack     Ponteiro para a stack
 */
void print_hosp_Stack(HOSP_STACK* stack);

#endif //UFP_ALOJAMENTOS_GUESTS_LIST_H