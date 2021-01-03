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
ED_LIST * initEdList();

/**
 * Funcao para adicionar um edificio a frente da lista de Edificios
 * @param list     Ponteiro para a lista de Edificios
 * @param edifcio   Ponteiro para o edificio a ser inserido
 */
void _edfs_list_insert_to_front(ED_LIST* list, ED* edifcio);

/**
 * Funcao para fazer free() a todos edificios da lista
 * @param queue     Ponteiro para a lista
 */
void _edfs_list_free_all(ED_LIST* queue);

/**
 * Funcao para printar todos os elementos da lista de edificios
 * @param head  Ponteiro para a head da lista de edificios a ser printada
 */
void _edfs_list_print(ED_LIST* queue);

/**
 * Funcao para fazer o append ou enqueue de um edificio para a respetiva lista
 * @param queue     Ponteiro para a lista onde sera feito o append
 * @param edificio  Ponteiro para o edificio que sera adicionado
 */
void _edfs_list_append(ED_LIST *queue, ED *edificio);

/**
 * Funcao para fazer o remove de um edificio especifico da lista de edificios
 * @param queue     Ponteiro para a lista de edificios
 * @param edificio  Edificio a ser removido
 */
void _edfs_list_remove(ED_LIST *queue, ED *edificio);

/**
 * Funcao para liberar o espaco de um edificio a partir de seu ponteiro
 * @param ed        Ponteiro para o edificio a ser liberado
 */
void freeEdificioByPtr(ED *ed);

/**
 * Funcao que percorre a lista ligada de edificio ate encontrar o edificio com o id que desejamos, e retorna-o
 * @param queue     Ponteiro para a lista ligada de edificios
 * @param id        ID do edificio que procuramos
 * @return          Ponteiro para o edificio procurado, ou NULL caso nao seja encontrado.
 */
ED* getEdificioFromID(ED_LIST* queue, int id);

/**
 * Funcao para buscar um edifcio pelo seu nome
 * @param list      Lista de edificios
 * @param name      Nome do edficio desejado
 * @return          Ponteiro para o edificio com o respetivo nome
 */
ED* getEdifcioFromName(ED_LIST* list, char* name);

/**
 * Funcoa para printar um edificio
 * @param edficio   Edifcio desejado
 */
void printEdificio(ED edificio);

void updateEdificioNome(ED_LIST* list, int id, char* newName);

void updateEdificioEndereco(ED_LIST* list, int id, char* newEndereco, float lat, float longi);

int return_edList_size(ED_LIST* queue);

int edList_isEmpty(ED_LIST* queue);

void edf_list_dequeue(ED_LIST* queue);

#endif //UFP_ALOJAMENTOS_EDIFICIOS_H
