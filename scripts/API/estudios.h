//
// Created by Frederico on 08/12/2020.
//

#ifndef UFP_ALOJAMENTOS_ESTUDIOS_H
#define UFP_ALOJAMENTOS_ESTUDIOS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../general/structs.h"


/**
 * Funcao para inicializar um EstHandler
 * @param array     Ponteiro para o array de Estudios
 * @param size      Tamanho do array
 * @return
 */
EST_HANDLER *initEstHandler(EST *array, int size);

/** Funcao para liberar a memoria dos estudios
 * @param handler   Handler dos estudios
 */
void _freeEstudios(EST_HANDLER *handler);

/**
 * Funcao para liberar a memoria de um unico estudio
 * buscado pelo seu id
 * \attention Ele nao remove o estudio da posicao do array para nao haver problemas na funcoa de Save
 * @param handler   Handler dos estudios
 * @param id        Id do estudio a ser liberado
 */
void _freeSingleEstudio(EST_HANDLER *handler, int id, char *nome);

/**
 * Funcao para liberar um unico estudio pelo seu ponteiro
 * @param ePtr   Ponteiro do estudio a ser liberado
 */
void freeEstudioByPtr(EST *ePtr);

/** Funcao para adicionar um novo estudio ao array
 * @param handler   Handler de Estudios
 * @param estudio   Estudio a ser adicionado
 */
void _addEstudioToArray(EST_HANDLER *handler, EST *estudio);

/** Funcao para remover um estudio do array
 * @param handler   Handler de estudios
 * @param id        Id do estudio a ser removido    [Caso nao saiba, passar -1]
 * @param nome      Nome do estudio a ser removido  [Caso nao saiba, passar NULL]
 */
void _removeEstudioFromArray(EST_HANDLER *handler, int id, char *nome);

/**
 * Funcao para buscar em pesquisa binaria um Estudio dentro do array
 * @param handler   Handler de estudios
 * @param id        Id do estudio   [Caso nao saiba, passar -1]
 * @param nome      Nome do estudio [Caso nao saiba, passar NULL]
 * @return          Ponteiro para o estudio
 */
EST *_findEstudioInArray(EST_HANDLER *handler, int id, char *nome);

/**
 * Funcao para printar todos os estudios do array
 * @param handler   Ponteiro para o handler de estudios
 */
void _printAllEstudios(EST_HANDLER *handler);

/**
 * Funcao para printar um estudio
 * @param e     Estudio a printar
 */
void printEstudio(EST e);

/**
 * Funcao para buscar o index de um estudio do array
 * \attention   NAO BUSCA O MEMBRO {ID} DE ESTUDIO.ID, BUSCA O INDEX
 * @param handler       Handler de estudios
 * @param id            Id do Estudio buscado
 * @return              Index do estudio
 */
int getEstudioArrayIndex(EST_HANDLER *handler, int id, char *nome);

#endif //UFP_ALOJAMENTOS_ESTUDIOS_H
