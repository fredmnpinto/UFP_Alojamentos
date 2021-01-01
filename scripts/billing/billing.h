//
// Created by Frederico on 30/11/2020.
//

#ifndef UFP_ALOJAMENTOS_BILLING_H
#define UFP_ALOJAMENTOS_BILLING_H

#include "../general/utils.h"
#include "../data_handler/report_generator.h"
#include "../API/agendas.h"

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

/**
 * Pega os dados do arquivo .csv e armazena-os em um array dinamico
 * @return Array dinamico com todos as regras do .csv
 */
RP *get_data_rp();

/**
 * Funcao que calcula o preco de uma marcacao, num estudio especificado, com base nas regras de preco
 * @param marcacao          Apontador para a marcacao a ser efetuada
 * @param estudio           Apontador para o estudio que esta a ser marcado
 * @param regras            Apontador para o array de regras de preco
 * @param estudioCalend     Apontador para o calendario do estudio
 * @return                  preco que vai ficar a marcacao, caso seja efetuada
 */
int generate_price_est(MARC* marcacao, EST* estudio, RP* regras, CALEND *estudioCalend);

#endif //UFP_ALOJAMENTOS_BILLING_H
