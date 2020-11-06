//
// Created by Frederico on 27/10/2020.
//

#ifndef UFP_ALOJAMENTOS_PROJECT_H
#define UFP_ALOJAMENTOS_PROJECT_H

#define ARR_SMALL 10
#define STR_MAX 50
#define AGENDA_MAX 365

#include <stdio.h>
#include <stdlib.h>

//Structs

typedef struct Data {
    int ano, mes, dia;
} DATA;

typedef struct Marcacao{
    DATA data;
    char descricao[STR_MAX];
    int agenda_id;
} MARC;

typedef struct Agenda{
    MARC marcacoes[AGENDA_MAX];
    long id;
    int size;
    char path[STR_MAX];
} AGENDA;

typedef struct Local {
    char endereco[STR_MAX];
    int lat, longi;
} LOCAL;

/**
 * ESTUDIO:
 * @nome             Nome do estudio
 * @id               Identificador do estudio (Index)
 * @edificio_id      Identificador do edificio onde o estudio esta alojado
 * @agenda_master    Agenda principal do estudio
 * @agendas_outras   Array onde estao as agendas a parte baseadas nas outras
 *                   plataformas
 * @a_o_size         Tamanho do array @agendas_outras
 */
typedef struct Estudio {
    int edificio_id;
    long id;
    char nome[STR_MAX];
    AGENDA agenda_master;
    AGENDA agendas_outras[ARR_SMALL];
    int a_o_size;
} EST;

typedef struct Edificio {
    long id;
    LOCAL endereco;
    char nome[STR_MAX];
} ED;

typedef struct Alojamento {
    long id;
    char nome[STR_MAX];
    int estudio_id;
    int tipo;
} ALOJ;

//Functions
void main_menu(int argc, char *argv[]);

/**
 * Função para fazer o parse da string para a struct DATA
 *
 * @param str_date  Data em forma de string
 * @return          Data em forma de DATA
 */
DATA string_to_date(char str_date[]);

/**
 * Função para checar a disponibilidade em uma data de uma agenda
 *
 * @param agenda_id     Id da agenda a checar a disponibilidade
 * @param data          Data a checar
 * @return              retorna 1 se estiver disponivel e 0 se nao
 */
int checar_disponibilidade(int agenda_id, DATA data);

int main_proj(int argc, char* argv[]);

#endif //UFP_ALOJAMENTOS_PROJECT_H
