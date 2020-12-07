//
// Created by Frederico on 29/11/2020.
//

#ifndef UFP_ALOJAMENTOS_AGENDAS_H
#define UFP_ALOJAMENTOS_AGENDAS_H

#include "../general/utils.h"
#include "../general/structs.h"

/**
 * Funcao para printar uma agenda especifica (Por motivos de debug)
 * @param ag    Agenda a ser printada
 */
void print_agenda(AGENDA ag);

/**
 * Funcao para inicializar o handler de agendas outras.
 * @param agendas               Array de agendas que sera guardado
 * @param size                  Tamanho do array de agendas
 * @return                      Objeto da struct AGENDA_HANDLER inicializado
 */
AGENDAS_HANDLER* init_outras_handler(AGENDA* agendas, int size, int id);

/**
 * Funcao para inicializar uma unica agenda
 * @param marc_array        Array de marcacoes
 * @param size              Tamanho do array
 * @param                   Path para a agenda
 * @return Ponteiro para essa agenda inicializada
 */
AGENDA* init_single_agenda(MARC* marc_array, int size, int id, char* path);

/**
 * Funcao para checar se a agenda foi inicializada de forma correta
 * @param agenda
 * @return
 */
int check_init(AGENDA* agenda);

//region Agendas Methods
/**
 * Funcao para dar free a agendas handler, assim como todas as agendas do seu respetivo array
 * @param handler   O Obj de Handler que sera deletado
 * @returns         Bool [Retorna 1 se for bem sucedido e 0 se ocorrer um erro]
 */
int _agendas_handler_free_all(AGENDAS_HANDLER* self);

/**
 * Funcao para printar todas as agendas de um agendas_handler
 * @param self      O Obj de agendas_handler a ser printado
 */
void _agendas_handler_print_all(AGENDAS_HANDLER* self); //DONE

/**
 * Funcao para checar disponibilidade em todas as agendas outras ou em uma especifica
 * @param self      Ponteiro para o Handler das agendas
 * @param data      Data em que se quer checar a disponibilidade
 * @param agenda_id Id da agenda que se quer checar [INSERIR -1 SE FOR PARA CHECAR TODAS]
 * @return          BOOLEAN [Retorna 1 se estiver disponivel e 0 se nao estiver]
 */
int _agendas_handler_check_availability(AGENDAS_HANDLER* self, DATA data, int agenda_id); //DONE, mas nao foi testado

/**
 * Funcao para buscar uma agenda pelo nome ou index \attention CASO SEJA PELO NOME ESPECIFICAR INDEX = -1
 * @param self                  Objeto da struct AGENDAS_HANDLER
 * @param index                 Index da agenda a ser buscada (SOMENTE SE ESTIVER BUSCANDO PELO INDEX)
 * @param nome_agenda           Nome da agenda a ser buscado (SE NAO SOUBER, ESPECIFICAR "" STRING VAZIA)
 * @return                      Agenda encontrada ou NULL se nao encontrou nenhuma agenda
 */
AGENDA* _agendas_handler_get_agenda(AGENDAS_HANDLER* self, int index, char* nome_agenda); //DONE, mas nao foi testado
//endregion

/**
 * Funcao para juntar duas agendas sem repeticoes
 * e conseguir um array ordenado com todas as marcacoes delas
 * @param a1    Uma das agendas
 * @param a2    A outra agenda
 * @return      Array ordenado das marcacoes
 */
MARC* unifyAgendas(AGENDA a1, AGENDA a2);

/**
 * Funcao para ordenar o array de uma agenda
 * @param agenda    Agenda a ser ordenado
 * @return          Ponteiro para o array de marcacoes ordenado
 */
MARC* sortAgenda(AGENDA* agenda);

/**
 * Funcao para devolver o dia de hoje como struct DATA
 * @return      Data do dia de hoje
 */
DATA get_today();

/**
 * Iniciar uma data de forma mais pratica
 * \attention NAO É USADA MEMORIA DINAMICA
 * @param dia   dia
 * @param mes   mes
 * @param ano   ano
 * @return      Data inserida em forma de DATA
 */
DATA init_data(int dia, int mes, int ano);

/**
 * Funcao para printar uma data
 * @param d         Data a ser printada
 * @param format    Formato a ser printado, por exemplo "DD/MM/YYYY"
 */
void print_data(DATA d, char* format);

/**
 * Funcao para comparar duas datas
 * @param dat1      Primeira data a ser comparada
 * @param dat2      Segunda data a ser comparada
 * @return          Retorna -1 se a primeira for mais cedo,
 *                  1 se a segunda for e 0 se forem iguais
 */
int comp_date(DATA dat1, DATA dat2);


#endif //UFP_ALOJAMENTOS_AGENDAS_H
