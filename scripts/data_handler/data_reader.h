//
// Created by Frederico on 06/11/2020.
//

#ifndef UFP_ALOJAMENTOS_DATA_READER_H
#define UFP_ALOJAMENTOS_DATA_READER_H

#include <errno.h>
#include "../general/utils.h"


/**
 * Funcao para pegar os hospedes de um arquivo .csv e armazenalos em uma
 * lista ligada de structs do tipo HOSP (struct Hospede)
 * @return              Endereco do primeiro elemento da lista (HEAD)
 */
HOSP_STACK* get_data_hosp();

HIST_STACK* get_data_hist();

EVENT_QUEUE* get_data_event();

/**
 * Funcao para pegar os estudios de um arquivo .csv e armazena-los em uma
 * lista ligada de structs do tipo ED (struct Edificio)
 * @return              Endereco do primeiro elemento da lista (HEAD)
 */
ED_LIST *get_data_edfs();                    //DONE

/**
 * Funcao para pegar os dados do arquivo .psv e armazena-los em um
 * array dinamico de structs do tipo EST (struct Estudio)
 * @return              Endereco do Handler de estudios
 */
EST_HANDLER *get_data_estudio();           //ONGOING

/**
 * Funcao para pegar os dados de um arquivo .psv de uma especifica agenda
 * master e armazena-los em uma struct do tipo AGENDA (struct agenda)
 * @param id            Id da agenda a ser buscada (primeira parte do nome do arquivo)
 * @return              Struct do tipo AGENDA com todos os dados lidos do arquivo
 */
AGENDA *get_data_agenda_master(int id); // DONE

/**
 * Funcao para buscar o array dinamico de marcacoes de uma agenda
 * @param id            Id da agenda a ser buscada
 * @return              Agenda lida do arquivo ou NULL se ela nao existir
 */
AGENDA * get_data_single_agenda_outra(int id); // DONE

/**
 * Funcao para buscar as agendas de outras plataformas do respectivo estudio
 * a partir do id do handler dessas agendas
 * @param handler_id    Id do handler que cuida das agendas desse estudio
 * @return              Ponteiro para o handler
 */
AGENDAS_HANDLER * get_data_agendas_outras(int handler_id); // DONE

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
 * Funcao para pegar o path para o arquivo .psv da respetiva agenda
 * @param id            Id da agenda
 * @return              Apontador para a string dinamica com o path
 */
char* get_filepath_agenda_outra(int id);

/**
 * Funcao para criar o path para o handler de respetivo id
 * @param handler_id    Id do handler
 * @return              Ponteiro para a string do path
 */
char* get_filepath_agendas_handler(int handler_id);

/**
 * Funcao para lidar com o input e administrar o que fazer a partir dele
 * no caso dele ser "read", como visto na funcao main_menu() de projeto.c
 * @param argc          Numero de argumentos
 * @param argv          Quais dados serao lidos (i.e. "aloj")
 */
void get_data_main(int argc, char* argv[]);

#endif //UFP_ALOJAMENTOS_DATA_READER_H
