//
// Created by Frederico on 07/11/2020.
//

#ifndef UFP_ALOJAMENTOS_GLOBAL_DEFINES_H
#define UFP_ALOJAMENTOS_GLOBAL_DEFINES_H

#define ARR_SMALL 10
#define STR_MAX 50
#define AGENDA_MAX 365
#define ALOJ_HEADER 19

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/// STRUCTS TO BE USED IN ALL FILES
/**
 * Auto explicativo
 */
typedef struct Data {
    int ano, mes, dia;
} DATA;

/**
 * @data            Data de para quando esta marcado
 * @descricao       Descricao da marcacao (motivo)
 * @int             Id da agenda onde esta guardada essa marcacao
 */
typedef struct Marcacao {
    DATA data;
    char descricao[STR_MAX];
    int agenda_id;
} MARC;


/**
 * @marcacoes       Array de atas ja agendadas e ocupadas
 * @id              Identificador da agenda
 * @size            Tamanho do array \marcacoes
 */
typedef struct Agenda {
    MARC *marcacoes;
    int id;
    int size;
    char *path;
} AGENDA;

/**
 * @endereco        Endereco por escrito do local
 * @lat             Latidude do local
 * @longi           Longitude do local
 */
typedef struct Local {
    char endereco[STR_MAX];
    int lat, longi;
} LOCAL;

/**
 * ESTUDIO:
<<<<<<< Updated upstream
 * @nome             Nome do estudio
 * @id               Identificador do estudio (Index)
 * @edificio_id      Identificador do edificio onde o estudio esta alojado
 * @agenda_master    Agenda principal do estudio
 * @agendas_outras   Array onde estao as agendas a parte baseadas nas outras
 *                   plataformas
 * @a_o_size         Tamanho do array @agendas_outras
=======
 * @param nome                  Nome do estudio
 * @param id                    Identificador do estudio (Index)
 * @param edificio_id           Identificador do edificio onde o estudio esta alojado
 * @param agenda_master_id      Agenda principal do estudio
 * @param agendas_outras        Array onde estao as agendas a parte baseadas nas outras plataformas
>>>>>>> Stashed changes
 */
typedef struct Estudio {
    int id;
    int edificio_id;
    char nome[STR_MAX];
    AGENDA agenda_master;
    AGENDA *agendas_outras;
} EST;

/**
 * @id              Identificador
 * @edereco         O endereco e coordenadas do edificio
 * @nome            Efetivamente no nome do edificio
 */
typedef struct Edificio {
    long id;
    LOCAL endereco;
    char nome[STR_MAX];
} ED;

/**
 * @id              Identificador
 * @estudio_id      Id do estudio correspondente a esse alojamento
 * @tipo            O tipo de alojamento (T0, T1, T2, T2+1, ...)
 */
typedef struct Alojamento {
    int id;
    unsigned long int estudio_id;
    char tipo[5];
} ALOJ;


///GLOBAL FUNCTIONS [Usadas ou que podem ser usadas por todos os arquivos]

/**
 * Remove o '\n' no final da string, caso tenha
 * @param str
 */
void remove_linebreak_on_the_end(char str[]);

/**
 * Remove o '\n' de qualquer posicao da string
 * @param str
 */
void remove_linebreak(char str[]);

/**
 * Funcao para printar todos os alojs do array
 * @param aloj_array    Array com todos os alojamentos
 * @param array_size    Tamanho do array
 */
void print_alojs(ALOJ *aloj_array, int array_size);




#endif //UFP_ALOJAMENTOS_GLOBAL_DEFINES_H
