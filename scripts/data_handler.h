//
// Created by Frederico on 06/11/2020.
//

#ifndef UFP_ALOJAMENTOS_DATA_HANDLER_H
#define UFP_ALOJAMENTOS_DATA_HANDLER_H

#include <errno.h>
#include "global_defines.h"

/**
 * Pega os dados do arquivo .csv e armazena-os em um array dinamico
 * @num_alojs Numero de alojamentos \attention ENTRA VAZIO, SAI PREENCHIDO \attention
 * @return Array dinamico com todos os alojamentos do .csv
 */
ALOJ *get_aloj_data(int *num_alojs);


#endif //UFP_ALOJAMENTOS_DATA_HANDLER_H
