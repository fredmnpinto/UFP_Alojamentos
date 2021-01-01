//
// Created by Frederico on 29/11/2020.
//

#ifndef UFP_ALOJAMENTOS_STRUCTS_H
#define UFP_ALOJAMENTOS_STRUCTS_H
#define STR_MAX 80

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
 * @param plataforma      Plataforma em que a reserva foi efetuada
 * @param duracao         Duracao da reserva(em dias)
 * @param preco           Preco diario da reserva
 * @param hospedeID       Id do hospede que efetuou a reserva
 */
typedef struct Marcacao {
    DATA data;
    char *plataforma;
    int duracao;
    int preco;
    int hospedeID;
} MARC;

/**
 * @param data          Data
 * @param marcacao      Apontador para uma marcacao nessa data (NULL se nao houver)
 * @param Eventos       Apontador para uma lista ligada de eventos desse dia (NULL se nao houver)
 */
typedef struct Calendario {
    DATA data;
    MARC *marcacao;
    struct EventosDiariosStack *Eventos;
}CALEND;

/**
 * @param id              Identificador da agenda
 * @param calendario      Apontador para o calendario da agenda
 * @param size            Tamanho do array \marcacoes
 */
typedef struct Agenda {
    int id;
    CALEND *calendario;
    int size;
    char *path;
} AGENDA;

/**
 * @param endereco        Endereco por escrito do local
 * @param lat             Latidude do local
 * @param longi           Longitude do local
 */
typedef struct Local {
    char *endereco;
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
    char *filepath;
    int id;
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
    char *configuracao;
    int precoDiario_base;
    AGENDA *agenda_master;
    AGENDAS_HANDLER *outrasHandler;
} EST;

/** ESTUDIO HANLDER:
 * @member id          Nao deve ser preciso
 * @member estArray    Ponteiro para o array de estudios
 * @member size        Tamanho do array
 * @method free        Funcao para fazer free() a todos
 *                     os elementos do array
 */
typedef struct EstudioHandler {
    int id;
    EST *estArray;
    char *header;
    int size;

    void (*freeSingle)(struct EstudioHandler *handler, int id, char *nome);
} EST_HANDLER;

/**
 * @param id              Identificador
 * @param edereco         O endereco e coordenadas do edificio
 * @param nome            Efetivamente no nome do edificio
 */
typedef struct Edificio {
    int id;
    LOCAL endereco;
    char *nome;
    struct Edificio *next;
} ED;

typedef struct EdificiosList{
    char *fHeader;
    ED *head;
    ED * tail;
    void (*print)(struct EdificiosList*);
    void (*append)(struct EdificiosList*, ED*);
    void (*remove)(struct EdificiosList*, ED*);
    void (*free_all)(struct EdificiosList*);
    void (*insert_to_front)(struct EdificiosList*, ED*);
} ED_LIST;

///Billing
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

/**
 * @param id        ID do hospede
 * @param nome      Nome do hospede
 * @param email     E-mail do hospede
 */
typedef struct Hospedes{
    int id;
    char *nome;
    char *email;
    struct Hospedes *next;
}HOSP;

/**
 * @param head      Apontador para o ultimo elemento a ser adicionado na stack
 * @param tail      Apontador para o primeiro elemento a ser adicionado na stack
 * @param size      Variavel que controla o tamanho da stack
 */
typedef struct HospedesStack{
    HOSP * head;
    HOSP * tail;
    int size;
}HOSP_STACK;

/**
 * @attention Esta struct e apenas um exemplo ainda nao sei bem como vou fazer
 * @param id            ID do historico
 * @param hospede_id    ID de um hospede
 * @param reserva       Reserva
 */
typedef struct Historico{
    int estudio_id;
    MARC* marcacao;
    DATA data;
    struct Historico *next;
}HIST;

/**
 * @param head      Apontador para o ultimo elemento a ser adicionado na stack
 * @param tail      Apontador para o primeiro elemento a ser adicionado na stack
 * @param size      Variavel que controla o tamanho da stack
 */
typedef struct HistoricoStack{
    HIST * head;
    HIST * tail;
    int size;
}HIST_STACK;

/**
 * @param descricao         Descricao do evento
 */
typedef struct EventosDiarios{
    char *descricao;
    struct EventosDiarios *next;
}EVENT;

/**
 * @param head              Apontador para a head da stack
 * @param tail              Apontador para a tail da stack
 * @param size              Tamanho da stack
 */
typedef struct EventosDiariosStack{
    EVENT *head;
    EVENT *tail;
    int size;
}EVENT_STACK;

#endif //UFP_ALOJAMENTOS_STRUCTS_H