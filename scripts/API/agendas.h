//
// Created by Frederico on 29/11/2020.
//

#ifndef UFP_ALOJAMENTOS_AGENDAS_H
#define UFP_ALOJAMENTOS_AGENDAS_H

#include "../general/utils.h"
#include "../general/structs.h"
#include "./eventos.h"

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
AGENDA* init_single_agenda(CALEND* calendario, int size, int id, char* path);

/**
 * Funcao para checar se a agenda foi inicializada de forma correta
 * @param agenda
 * @return
 */
int check_init(AGENDA *agenda);

//region Agendas Methods
/**
 * Funcao para dar free a agendas handler, assim como todas as agendas do seu respetivo array
 * @param handler   O Obj de Handler que sera deletado
 * @returns         Bool [Retorna 1 se for bem sucedido e 0 se ocorrer um erro]
 */
int _agendas_handler_free_all(AGENDAS_HANDLER *self);

/**
 * Funcao para liberar o espaco de memoria de uma agenda
 * a partir de seu ponteiro
 * @param a         Ponteiro para a agenda
 */
void freeAgendaByPtr(AGENDA *a);

/**
 * Funcao para printar todas as agendas de um agendas_handler
 * @param self      O Obj de agendas_handler a ser printado
 */
void _agendas_handler_print_all(AGENDAS_HANDLER *self); //DONE

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
AGENDA* _agendas_handler_get_agenda(AGENDAS_HANDLER* self, int index); //DONE, mas nao foi testado
//endregion

/**
 * Funcao para juntar duas agendas sem repeticoes
 * e conseguir um array ordenado com todas as marcacoes delas
 *
 * @param a1    Uma das agendas
 * @param a2    A outra agenda
 * @return      Array ordenado das marcacoes
 */
CALEND* unifyMarcs(CALEND* a1, CALEND* a2, int size1, int size2, int* newSize);

/**
 * Funcao para juntar duas agendas sem repeticoes
 * e conseguir um array ordenado com todas as
 * marcacoes delas
 *
 * @param a1    Uma das agendas
 * @param a2    A outra agenda
 * @return      Agenda contendo o conteudo ordenado
 *              de todas as duas agendas
 */
AGENDA* unifyAgendas(AGENDA a1, AGENDA a2);

/**
 * Funcao para ordenar o array de uma agenda
 * @param marcArray Ponteiro para o array a ser ordenado
 * @return          Ponteiro para o array de marcacoes ordenado
 */
CALEND* sortCalendAsc(CALEND* calendArray, int size);

/**
 * Funcao para fazer o qsort do array de marcacoes
 * de forma descendente (do mais recente para o mais
 * antigo)
 *
 * @param marcArray Array a ser ordenado
 * @param size      Tamanho do array
 * @return          Ponteiro para o array ordenado
 */
CALEND* sortCalendDesc(CALEND* calendArray, int size);

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
 */
void print_data(DATA d);

/**
 * Funcao para converter uma DATA em string
 * @param d     Data a ser convertida
 * @return      Data em forma "DD/MM/AAAA"
 */
char *dataToString(DATA d);

/**
 * Funcao para comparar duas datas
 * \warning NAO USAR
 * @param p1        Ponteiro para a primeira data a ser comparada
 * @param p2        Ponteiro para a segunda data a ser comparada
 * @return          Retorna -1 se a primeira for mais cedo,
 *                  1 se a segunda for e 0 se forem iguais
 */
int __comp_date1(const void *p1, const void *p2);

/**
 * Funcao para comparar duas datas
 * \warning NAO USAR
 * @param p1        Ponteiro para a primeira data a ser comparada
 * @param p2        Ponteiro para a segunda data a ser comparada
 * @return          Retorna 1 se a primeira for mais cedo,
 *                  -1 se a segunda for e 0 se forem iguais
 */
int __comp_date2(const void *p1, const void *p2);

/**
 * Mesma funcao que a de cima, porem para nos usarmos
 * @param dat1      Primeira data a ser comparada
 * @param dat2      Segunda data a ser comparada
 * @return          1 se a primeira for depois,
 *                  -1 se for antes e 0 se forem
 *                  iguais
 */
int compDate(DATA dat1, DATA dat2);

/**
 * Funcao para adicionar uma marcacao a uma respectiva agenda
 * @param agenda
 * @param marc
 */
AGENDA* addMarc(AGENDA *agenda, MARC *marc, DATA data);

/**
 * Funcao para remover uma marcacao da agenda
 * @param agenda
 */
void remMarc(AGENDA *agenda, DATA data);

/**
 * Funcao para fazer o update de uma marcacao de index: {index}
 * na respectiva agenda. No caso de querer manter algum dado antigo,
 * basta passar NULL ao respectivo parametro
 * @param agenda    Agenda
 * @param index     index da marcacao
 * @param newData   Nova data para a marcacao
 * @param newDesc   Nova descricao para a marcacao
 */
void updateMarcFromPos(AGENDA *agenda, int index, DATA *newData, char *newDesc);

/**
 * Funcao para selecionar o index de uma marcacao a partir da sua data
 * @param agenda    Agenda onde ela esta
 * @param data      Data da marcacao
 * @return          Index da marcacao ou -1 se nao for encontrado
 */
int getMarcIndex(AGENDA *agenda, DATA data);

/**
 * Funcao para conseguir uma marcacao a partir da sua data
 * @param agenda    Agenda onde ela esta
 * @param data      Data da marcacao
 * @return          Marcacao desejada
 */
MARC getMarc(AGENDA *agenda, DATA data);

/**
 * Funcao para determinar o quao proximas sao duas datas
 * @param data1     Primeira data
 * @param data2     Segunda data
 * @return          o numero de dias que se diferem
 * \attention       Se a primeira data for antes, retorna um num positivo, se nao negativo
 */
int howCloseToData(DATA data1, DATA data2);

/**
 * Funcao para converter uma data para dias
 * @param data      Data desejada
 * @return          Numero de dias a que ela corresponde
 */
int dataInDays(DATA data);

/**
 * Quantidade de dias que ha em um dado mes
 * Por exemplo: Janeiro = 31, Novembro = 30
 * \attention Nao funciona em fevereiro vai sempre retornar 28
 * @param mes       Mes desejado (de 1 a 12)
 * @return          Numero de dias
 */
int daysInMonth(int mes);

/**
 * Funcao para conseguir o numero de dias que ocorreram ate aquele ano
 * @param ano       Ano desejado
 * @return          Numero de dias
 * \attention       Placeholder, nao muito preciso no numero de dias
 */
int daysInYear(int ano);

/**
 * Funcao para checar se o ano é bissexto
 * @param ano       ano
 * @return          1 ou 0, V ou F
 */
int isLeapYear(int ano);

/**
 * Funcao que retorna a diferenca entre duas datas (data1 e data2)
 * @param data1     DATA data1
 * @param data2     DATA data2
 * @return          struct DATA com a diferenca entre a data1 e a data2
 */
DATA return_data_difference(DATA data1, DATA data2);
#endif //UFP_ALOJAMENTOS_AGENDAS_H
