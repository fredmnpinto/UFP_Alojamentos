//
// Created by Frederico on 30/11/2020.
//

#ifndef UFP_ALOJAMENTOS_BILLING_H
#define UFP_ALOJAMENTOS_BILLING_H

#include "../general/utils.h"

/**
 * Pega os dados do arquivo .csv e armazena-os em um array dinamico
 * @num_rp Numero de regras \attention ENTRA VAZIO, SAI PREENCHIDO \attention
 * @return Array dinamico com todos as regras do .csv
 */
RP *get_data_rp(int *num_rp);    //DONE

/**
 * Funcao para devolver um array dinamico igual ao estatico recebido
 * @param static_array      Array estatico de regras
 * @param size              Numero de objetos no array
 * @return                  Array dinamico
 */
RP *rp_dyn_arr(RP *static_array, int size);

/**
 * Funcao para printar as regras de preco
 * @param rp_array          Array dinamico das regras
 * @param array_size        Tamanho do array
 */
void print_rp(RP* rp_array, int array_size);

#endif //UFP_ALOJAMENTOS_BILLING_H
