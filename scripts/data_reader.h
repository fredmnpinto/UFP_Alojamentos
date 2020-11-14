//
// Created by Frederico on 06/11/2020.
//

#ifndef UFP_ALOJAMENTOS_DATA_READER_H
#define UFP_ALOJAMENTOS_DATA_READER_H

#include <errno.h>
#include "global_defines.h"

/**
 * Pega os dados do arquivo .csv e armazena-os em um array dinamico
 * @num_alojs Numero de alojamentos \attention ENTRA VAZIO, SAI PREENCHIDO \attention
 * @return Array dinamico com todos os alojamentos do .csv
 */
ALOJ *get_aloj_data(int *num_alojs); //DONE

/**
 * Funcao para pegar os estudios de um arquivo .csv e armazena-los em uma
 * lista ligada de structs do tipo ED (struct Edificio)
 * @param num_ests      Numero de Edificios lidos
 * @return              Endereco do primeiro elemento da 
 */
ED get_data_estudio(int *num_eds);

/**
 * Funcao para devolver um array dinamico igual ao estatico recebido
 * @param static_array      Array estatico de alojamentos
 * @param size              Numero de objetos no array
 * @return                  Array dinamico
 */
ALOJ *aloj_dyn_arr(ALOJ *static_array, int size);

/**
 * Funcao para ler o numero de linhas em um arquivo
 * \attention CONTANDO COM O HEADER NO CASO DE UM CSV
 * @param fr                Ponteiro do arquivo (inicializado em READ)
 * @return                  Numero de linhas do arquivo
 */
int get_number_of_lines(FILE *fr);

/**
 * Funcao para lidar com o input e administrar o que fazer a partir dele
 * no caso dele ser "read", como visto na funcao main_menu() de projeto.c
 * @param argc          Numero de argumentos
 * @param argv          Quais dados serao lidos (i.e. "aloj")
 */
void get_data_main(int argc, char* argv[]);


#endif //UFP_ALOJAMENTOS_DATA_READER_H
