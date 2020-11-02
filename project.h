//
// Created by Frederico on 27/10/2020.
//

#ifndef UFP_ALOJAMENTOS_PROJECT_H
#define UFP_ALOJAMENTOS_PROJECT_H

#define STR_MAX 50
#define AGENDA_MAX 365

#include <stdio.h>
#include <stdlib.h>

//Structs
typedef struct Local {
    char endereco[STR_MAX];
    int lat, longi;
} LOCAL;

typedef struct Estudio {
    int edificio_id;
    long id;
    char nome[STR_MAX];
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
    char tipo[4];
} ALOJ;

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
    char name[STR_MAX];
} AGENDA;

//Functions



int main_proj(int argc, char* argv[]);

#endif //UFP_ALOJAMENTOS_PROJECT_H
