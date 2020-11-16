//
// Created by Frederico on 07/11/2020.
//

#ifndef UFP_ALOJAMENTOS_GLOBAL_DEFINES_H
#define UFP_ALOJAMENTOS_GLOBAL_DEFINES_H

#define ARR_SMALL 10
#define STR_MAX 50
#define AGENDA_MAX 365
#define ALOJ_HEADER "id,estudio_id,tipo"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/// STRUCTS TO BE USED IN ALL FILES
/**
 * Auto explicativo
 * @param ano   Ano
 * @param mes   Mes
 * @param dia   Dia
 */
typedef struct Data {
    int ano, mes, dia;
} DATA;

/**
 * @param data            Data de para quando esta marcado
 * @param descricao       Descricao da marcacao (motivo)
 * @param int             Id da agenda onde esta guardada essa marcacao
 */
typedef struct Marcacao {
    DATA data;
    char *descricao;
} MARC;


/**
 * @param marcacoes       Array de atas ja agendadas e ocupadas
 * @param id              Identificador da agenda
 * @param size            Tamanho do array \marcacoes
 */
typedef struct Agenda {
    MARC *marcacoes;
    int id;
    int size;
    char *path;
} AGENDA;

/**
 * @param endereco        Endereco por escrito do local
 * @param lat             Latidude do local
 * @param longi           Longitude do local
 */
typedef struct Local {
    char endereco[STR_MAX];
    double lat, longi;
} LOCAL;

/**
 * ESTUDIO:
 * @param nome                  Nome do estudio
 * @param id                    Identificador do estudio (Index)
 * @param edificio_id           Identificador do edificio onde o estudio esta alojado
 * @param agenda_master         Apontador para a agenda principal do estudio
 * @param agendas_outras        Array onde estao as agendas a parte baseadas nas outras plataformas
 */
typedef struct Estudio {
    int id;
    int edificio_id;
    char nome[STR_MAX];
    AGENDA* agenda_master;
    AGENDA *agendas_outras;
} EST;

/**
 * @param id              Identificador
 * @param edereco         O endereco e coordenadas do edificio
 * @param nome            Efetivamente no nome do edificio
 */
typedef struct Edificio {
    int id;
    LOCAL endereco;
    char nome[STR_MAX];
    struct Edificio* next;
} ED;

/**
 * @param id              Identificador
 * @param estudio_id     Id do estudio correspondente a esse alojamento
 * @param tipo           O tipo de alojamento (T0, T1, T2, T2+1, ...)
 */
typedef struct Alojamento {
    int id;
    unsigned long int estudio_id;
    char tipo[5];
} ALOJ;


//GLOBAL FUNCTIONS [Usadas ou que podem ser usadas por todos os arquivos]

/**
 * Remove o '\ n' no final da string, caso tenha
 * \warning         Altera o valor da string inicial (remove o \ n)
 * @param str       string com ou sem a quebra de linha no fim
 */
void remove_linebreak_on_the_end(char str[]);

/**
 * Remove o '\ n' de qualquer posicao da string
 * \warning NAO FUNCIONAL, NAO UTILIZAR
 * @param str   String sem qualquer quebra de linha
 */
void remove_linebreak(char str[]);

/**
 * Funcao para printar todos os alojs do array
 * @param aloj_array    Array com todos os alojamentos
 * @param array_size    Tamanho do array
 */
void print_alojs(ALOJ *aloj_array, int array_size);

/**
 * Funcao para retornar a versao em lowercase de um determinado caracter
 * @param C     Caracter em uppercase ou nao
 * @return      Caracter em lowercase
 */
char get_lower_c(char C);

/**
 * Funcao para retornar a versao upppercase de um caracter
 * @param c     Caracter lowercase ou nao
 * @return      Caracter uppercase
 */
char get_upper_c(char c);

/**
 * Funcao para retornar a versao lowercase de uma string
 * @param STR       String em uppercase ou nao
 * @return          String em lowercase
 */
char * get_lower_str(char STR[]);

/**
 * Funcao para retornar a versao uppercase de uma string
 * @param str       String em lowercase ou nao
 * @return          String em uppercase
 */
char * get_upper_str(char str[]);

/**
 * Funcao para determinar se um caracter é uppercase ou nao
 * @param c     Caracter em questao
 * @return      1 para sim, 0 para nao
 */
int is_upper_c(char c);



#endif //UFP_ALOJAMENTOS_GLOBAL_DEFINES_H
