//
// Created by Frederico on 29/11/2020.
//

#include "agendas.h"

AGENDA* init_single_agenda(MARC* marc_array, int size, int id, char* path){
    AGENDA* new_agenda = (AGENDA*)malloc(sizeof(AGENDA));
    new_agenda->marcacoes = marc_array;
    new_agenda->size = size;
    new_agenda->id = id;
    new_agenda->path = path;
    return new_agenda;
}

AGENDAS_HANDLER* init_outras_handler(AGENDA* agendas, int size){
    AGENDAS_HANDLER *new_outras = (AGENDAS_HANDLER*)malloc(sizeof(AGENDAS_HANDLER));
    new_outras->agendas = agendas;
    new_outras->size = size;
    new_outras->find = _agendas_handler_get_agenda;
//    new_outras->free = _agendas_handler_free_all;
    new_outras->print_all = _agendas_handler_print_all;
    return new_outras;
}

void _agendas_handler_print_all(AGENDAS_HANDLER* self){
    for (int i = 0; i < self->size; ++i) {
        print_agenda(&self->agendas[i]);
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
        AGENDA* agenda = _agendas_handler_get_agenda(self, agenda_id, NULL);
        for (int i = 0; i < agenda->size; ++i) {
            if(comp_date(agenda->marcacoes[i].data, data))
                return 0;
        }
        return 1;
    }
}

AGENDA* _agendas_handler_get_agenda(AGENDAS_HANDLER* self, int index, char* nome_agenda){
    int n = self->size;
    if (index > -1){
        // TODO Binary search
        for (int hi = self->size, mid = hi/2, lo = 0; hi > lo; mid = (hi + lo)/ 2) {
            if (self->agendas[mid].id < index){
                lo = mid;
            }
            else if (self->agendas[mid].id > index){
                hi = mid;
            }
            else if (self->agendas[mid].id == index) {
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

void print_agenda(AGENDA* ag){
    int n = ag->size;
    for (int i = 0; i < n; ++i) {
        printf("Dia: %d  Mes: %d  Ano: %d\tDesc: %s\n", ag->marcacoes[i].data.dia, ag->marcacoes[i].data.mes, ag->marcacoes[i].data.ano, ag->marcacoes[i].descricao);
    }
}