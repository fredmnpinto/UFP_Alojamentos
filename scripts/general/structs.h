//
// Created by Frederico on 29/11/2020.
//

#ifndef UFP_ALOJAMENTOS_STRUCTS_H
#define UFP_ALOJAMENTOS_STRUCTS_H

#include "utils.h"

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
    char nome[STR_MAX];
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
 * OUTRAS_AGENDAS_HANDLER:
 * @param agendas               Array dinamico com todas as outras agendas (que nao sao master)
 * @param size                  Tamanho do array de agendas
 * @param find                  Funcao para encontrar uma determinada agenda, dentro do array
 * \attention INICIALIZAR SOMENTE USANDO A RESPETIVA FUNCAO INICIALIZADORA
 */
typedef struct OutrasAgendasHandler {
    AGENDA *agendas;
    int size;
    AGENDA* (*find)(struct OutrasAgendasHandler* self, int index, char* nome_agenda);
    int (*free)(struct OutrasAgendasHandler*);
    void (*print_all)(struct OutrasAgendasHandler*);
    void (*insert_to_end)(struct OutrasAgendasHandler*, AGENDA*);
    int (*check_availability)(struct OutrasAgendasHandler*, DATA, int);
    AGENDA* (*get_agenda)(struct OutrasAgendasHandler*, int);
}AGENDAS_HANDLER;

/**
 * ESTUDIO:
 * @param nome                  Nome do estudio
 * @param id                    Identificador do estudio (Index)
 * @param edificio_id           Identificador do edificio onde o estudio esta alojado
 * @param agenda_master         Apontador para a agenda principal do estudio
 * @param agendas_outras        Array onde estao as agendas a parte baseadas nas outras plataformas
 * @param preco_base            Preco base do estudio
 */
typedef struct Estudio {
    int id;
    int edificio_id;
    char nome[STR_MAX];
    AGENDA* agenda_master;
    AGENDA* agendas_outras;
    float preco_base;
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

/**
 * @param id              Identificador
 * @param regra           Nome da regra
 * @param taxa            Taxa da regra
 */
typedef struct Regras_Preco {
    int id;
    char regra[STR_MAX];
    int taxa;
} RP;

typedef struct Estadia {
    DATA date;
    char nome_cliente[STR_MAX];
}ESTADIA;

typedef struct EdificiosQueue{
    ED * head;
    ED * tail;
    void (*print)(struct EdificiosQueue*);
    void (*append)(struct EdificiosQueue*, ED*);
    void (*remove)(struct EdificiosQueue*, ED*);
    void (*free_all)(struct EdificiosQueue*);
    void (*insert_to_front)(struct EdificiosQueue*, ED*);
}ED_QUEUE;

typedef struct Hospedes{
    int id;
    char nome[STR_MAX];
    char email[STR_MAX];
    struct Hospedes *next;
}HOSP;

typedef struct HospedesStack{
    HOSP * head;
    HOSP * tail;
}HOSP_STACK;

#endif //UFP_ALOJAMENTOS_STRUCTS_H
