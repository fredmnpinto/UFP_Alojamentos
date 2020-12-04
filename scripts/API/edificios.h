//
// Created by Frederico on 29/11/2020.
//

#ifndef UFP_ALOJAMENTOS_EDIFICIOS_H
#define UFP_ALOJAMENTOS_EDIFICIOS_H

#include "../general/utils.h"
#include "../general/structs.h"

/**
 * Funcao para inicializar uma lista de edificios
 * \attention MUITO IMPORTANTE INICIALIZAR POR AQUI
 * @return Ponteiro para a lista inicializada
 */
ED_QUEUE * init_ed_queue();

/**
 * Funcao para adicionar um edificio a frente da lista de Edificios
 * @param queue     Ponteiro para a lista de Edificios
 * @param edifcio   Ponteiro para o edificio a ser inserido
 */
void _edfs_list_insert_to_front(ED_QUEUE* queue, ED* edifcio);

/**
 * Funcao para fazer free() a todos edificios da lista
 * @param queue     Ponteiro para a lista
 */
void _edfs_list_free_all(ED_QUEUE* queue);

/**
 * Funcao para printar todos os elementos da lista de edificios
 * @param head  Ponteiro para a head da lista de edificios a ser printada
 */
void _edfs_list_print(ED_QUEUE* queue);

/**
 * Funcao para fazer o append ou enqueue de um edificio para a respetiva lista
 * @param queue     Ponteiro para a lista onde sera feito o append
 * @param edificio  Ponteiro para o edificio que sera adicionado
 */
void _edfs_list_append(ED_QUEUE* queue, ED* edificio);

/**
 * Funcao para fazer o remove de um edificio especifico da lista de edificios
 * @param queue     Ponteiro para a lista de edificios
 * @param edificio  Edificio a ser removido
 */
void _edfs_list_remove(ED_QUEUE* queue, ED* edificio);

#endif //UFP_ALOJAMENTOS_EDIFICIOS_H
