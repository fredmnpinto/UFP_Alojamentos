//
// Created by Frederico on 08/12/2020.
//

#ifndef UFP_ALOJAMENTOS_DATA_WRITER_H
#define UFP_ALOJAMENTOS_DATA_WRITER_H

#include "../general/utils.h"
#include "../API/estudios.h"
#include "../API/edificios.h"
#include "../API/agendas.h"
#include "../API/guests_list.h"
#include "./data_reader.h"

/**
 * Funcao para salvar as agendas outras a partir do Handler
 * @param handler   Ponteiro para o handler
 */
void saveDataAgendasOutras(AGENDAS_HANDLER *handler);

/**
 * Funcao para salvar os dados de uma agenda
 * @param master    Ponteiro para a agenda
 */
void saveDataSingleAgenda(AGENDA *agenda);

void saveDataEstudio(EST_HANDLER *handler);

void saveDataEdificios(ED_LIST *list);

void saveDataHospedes(HOSP_STACK* stack);

#endif //UFP_ALOJAMENTOS_DATA_WRITER_H
