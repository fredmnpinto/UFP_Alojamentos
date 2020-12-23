//
// Created by Frederico on 08/12/2020.
//

#include "data_writer.h"


void saveDataEstudio(EST_HANDLER *handler) { // Tested
    char *filepath = "../data/estudioTest.psv";
    FILE *fw = fopen(filepath, "w");
    printf("Oppening %s\n...\n", filepath);
    if (fw != NULL) {
        int size = handler->size;
        fprintf(fw, "%s", handler->header);

        for (int i = 0; i < size; ++i) {
            EST *aux = &handler->estArray[i];
            fprintf(fw, "%d|%d|%s|%d|%d\n", aux->id, aux->edificio_id, aux->nome, aux->agenda_master->id,
                    aux->outrasHandler->id);
            freeEstudioByPtr(aux);
        }
        fclose(fw);
    } else {
        perror("ERROR OPPENING FILE");
    }
}

void saveDataEdificios(ED_LIST *list) {
    char *filepath = "../data/edfsTest.psv";
    FILE *fw = fopen(filepath, "w");
    printf("Oppening %s\n...\n", filepath);
    if (fw != NULL) {
        fprintf(fw, "%s", list->fHeader);
        if (list->head == NULL)
            return;
        ED *current = list->head;
        while (current->next != NULL) {
            fprintf(fw, "%d|%s|%f|%f|%s\n", current->id, current->endereco.endereco, current->endereco.lat,
                    current->endereco.longi, current->nome);
            ED *aux = current->next;
            freeEdificioByPtr(current);
            current = aux;
        }
        list->head = NULL;
        list->tail = NULL;
        printf("Saved!\n");
        fclose(fw);
    } else {
        perror("ERROR in saveDataEdificios");
    }
}

void saveDataSingleAgenda(AGENDA *agenda) {
    char *filepath = agenda->path;
    FILE *fw = fopen(filepath, "w");
    printf("Oppening %s\n...\n", filepath);
    if (fw != NULL) {
        fprintf(fw, "%s", "Dia|Mes|Ano|Descricao\n");
        if (agenda == NULL)
            return;
        MARC *a = agenda->marcacoes;
        for (int i = 0, size = agenda->size; i < size; ++i) {
            fprintf(fw, "%d|%d|%d|%s\n", a[i].data.dia, a[i].data.mes, a[i].data.ano, a[i].descricao);
        }
        freeAgendaByPtr(agenda);
        fclose(fw);
    } else {
        perror("ERROR in saveDataSingleAgenda");
    }
}

void saveDataAgendasOutras(AGENDAS_HANDLER *handler) {
    char *filepath = handler->filepath;
    FILE *fw = fopen(filepath, "w");
    printf("Oppening %s\n...\n", filepath);
    if (fw != NULL) {
        fprintf(fw, "outra_id|nome");
        if (handler == NULL) {
            printf("HANDLER cannot be NULL\n");
            return;
        }
        for (int i = 0, size = handler->size; i < size; ++i) {
            fprintf(fw, "%d|%s\n", handler->agendas[i].id, handler->agendas->nome);
            saveDataSingleAgenda(&handler->agendas[i]);
            freeAgendaByPtr(&handler->agendas[i]);
        }
        free(handler->filepath);
        free(handler->agendas);
        printf("Saved!\n");
        fclose(fw);
    } else {
        perror("ERROR in saveDataAgendasOutras");
    }
}