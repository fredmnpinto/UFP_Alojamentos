//
// Created by Frederico on 06/11/2020.
//

#ifndef UFP_ALOJAMENTOS_DATA_READER_H
#define UFP_ALOJAMENTOS_DATA_READER_H

#include <errno.h>
#include "../general/utils.h"


/**
 * Pega os dados do arquivo .csv e armazena-os em um array dinamico
 * @num_alojs Numero de alojamentos \attention ENTRA VAZIO, SAI PREENCHIDO \attention
 * @return Array dinamico com todos os alojamentos do .csv
 */
ALOJ *get_data_aloj(int *num_alojs);    //DONE

/**
 * Pega os dados do arquivo .csv e armazena-os em um array dinamico
 * @num_rp Numero de regras \attention ENTRA VAZIO, SAI PREENCHIDO \attention
 * @return Array dinamico com todos as regras do .csv
 */
RP *get_data_rp(int *num_rp);    //DONE

/**
 * Funcao para pegar os estudios de um arquivo .csv e armazena-los em uma
 * lista ligada de structs do tipo ED (struct Edificio)
 * @return              Endereco do primeiro elemento da lista (HEAD)
 */
ED_QUEUE* get_data_edfs();                    //DONE

HOSP_STACK* get_data_hosp();

/**
 * Funcao para pegar os dados do arquivo .psv e armazena-los em um
 * array dinamico de structs do tipo EST (struct Estudio)
 * @param size          Tamanho do array
 * @return              Endereco do array
 */
EST* get_data_estudio(int *size);           //ONGOING

/**
 * Funcao para pegar os dados de um arquivo .psv de uma especifica agenda
 * master e armazena-los em uma struct do tipo AGENDA (struct agenda)
 * @param id            Id da agenda a ser buscada (primeira parte do nome do arquivo)
 * @return              Struct do tipo AGENDA com todos os dados lidos do arquivo
 */
AGENDA* get_data_agenda_master(int id);

/**
 * Funcao para buscar o array dinamico de agendas de outras plataformas
 * @return              Objeto da struct AGENDAS_HANDLER com o array dinamico de todas as agendas de outras plataformas
 */
AGENDAS_HANDLER * get_data_agendas_outras();

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
 * Funcao para montar o path do arquivo da agenda do respectivo id
 * @param id    Identificador da agenda a ser trabalhada
 * @return      Nome do arquivo onde esta guardada a agenda
 */
char* get_filepath_agenda_master(int id);

/**
 * Funcao para lidar com o input e administrar o que fazer a partir dele
 * no caso dele ser "read", como visto na funcao main_menu() de projeto.c
 * @param argc          Numero de argumentos
 * @param argv          Quais dados serao lidos (i.e. "aloj")
 */
void get_data_main(int argc, char* argv[]);

#endif //UFP_ALOJAMENTOS_DATA_READER_H
