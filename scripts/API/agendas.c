//
// Created by Frederico on 29/11/2020.
//

#include <time.h>
#include "agendas.h"

AGENDA* init_single_agenda(MARC* marc_array, int size, int id, char* path){
    AGENDA* new_agenda = (AGENDA*)malloc(sizeof(AGENDA));
    new_agenda->marcacoes = marc_array;
    new_agenda->size = size;
    new_agenda->id = id;
    new_agenda->path = path;
    return new_agenda;
}

AGENDAS_HANDLER* init_outras_handler(AGENDA* agendas, int size, int id){
    AGENDAS_HANDLER *newHandler = (AGENDAS_HANDLER*)malloc(sizeof(AGENDAS_HANDLER));
    newHandler->agendas = agendas;
    newHandler->id = id;
    newHandler->size = size;
    newHandler->find = _agendas_handler_get_agenda;
    newHandler->free = _agendas_handler_free_all;
    newHandler->print_all = _agendas_handler_print_all;
    newHandler->check_availability = _agendas_handler_check_availability;
    return newHandler;
}

void _agendas_handler_print_all(AGENDAS_HANDLER* self){
    for (int i = 0; i < self->size; ++i) {
        print_agenda(self->agendas[i]);
    }
}

int _agendas_handler_check_availability(AGENDAS_HANDLER* self, DATA data, int agenda_id){
    if (agenda_id < 0) {
        // Iterates through all agendas
        for (int i = 0; i < self->size; ++i)
            for (int j = 0; j < self->agendas[i].size; ++j)
                if (comp_date(data, self->agendas[i].marcacoes[j].data))
                    return 0;
        return 1;
    }
    else {
        // Searches in a specific agenda
        AGENDA agenda = *_agendas_handler_get_agenda(self, agenda_id, NULL);
        for (int i = 0; i < agenda.size; ++i) {
            if (comp_date(agenda.marcacoes[i].data, data))
                return 0;
        }
        return 1;
    }
}

AGENDA *_agendas_handler_get_agenda(AGENDAS_HANDLER *self, int index, char *nome_agenda) {
    int n = self->size;
    if (index > -1) {
        // TODO Binary search
        for (int hi = self->size, mid = hi / 2, lo = 0; hi > lo; mid = (hi + lo) / 2) {
            if (self->agendas[mid].id < index) {
                lo = mid;
            } else if (self->agendas[mid].id > index) {
                hi = mid;
            } else if (self->agendas[mid].id == index) {
                return &self->agendas[mid];
            }
        }

    }
    else if (strcmp(nome_agenda, "") != 0)
    {
        for (int i = 0; i < n; ++i) {
            if(strcmp(self->agendas[i].nome, nome_agenda) == 0)
                return &self->agendas[i];
        }
    }
    printf("\n\nINVALID INPUT ON AGENDAS_FIND\n\nMUST ENTER EITHER THE INDEX OR THE NAME OF THE AGENDA WANTED\n\n");
    /*AGENDA* agenda_placeholder = (AGENDA*)malloc(sizeof(AGENDA));
    char* nome = "Placeholder Name";

    strcpy(agenda_placeholder->nome, nome);
    agenda_placeholder->size = 0;
    agenda_placeholder->id = -1;
    agenda_placeholder->path = "Path/to/placeholder.txt";*/
    return NULL;
}

void print_agenda(AGENDA ag) {
    int n = ag.size;
    for (int i = 0; i < n; ++i) {
        printf("Dia: %d  Mes: %d  Ano: %d\tDesc: %s\n", ag.marcacoes[i].data.dia, ag.marcacoes[i].data.mes, ag.marcacoes[i].data.ano, ag.marcacoes[i].descricao);
    }
}

int _agendas_handler_free_all(AGENDAS_HANDLER* self) {
    int n = self->size;
    for (int i = 0; i < n; ++i) {
        free(self->agendas[i].path);
        free(self->agendas[i].marcacoes);
        free(&self->agendas[i]);
        self->size--;
    }
    free(self->agendas);
    int working = self->size == 0 ? 1 : 0;
    free(self);
    return working && !self->agendas && !self ? 1 : 0;
}


MARC* sortAgenda(AGENDA* agenda){
    int n = agenda->size;


    return NULL;
}

int comp_date(DATA dat1, DATA dat2){
    if((dat1.dia < dat2.dia && dat1.mes <= dat2.mes) && dat1.ano <= dat2.ano)
        return -1;
    else if ((dat1.dia > dat2.dia && dat1.mes >= dat2.mes) && dat1.ano >= dat2.ano)
        return 1;
    return 0;
}

DATA get_today(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return init_data(tm.tm_mday, tm.tm_mon, tm.tm_year);
}

DATA init_data(int dia, int mes, int ano){
    DATA nData;
    nData.dia = dia;
    nData.mes = mes;
    nData.ano = ano;
    return nData;
}



