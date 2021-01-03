//
// Created by Frederico on 08/12/2020.
//

#include "data_writer.h"


void saveDataEstudio(EST_HANDLER *handler) { // Tested
    char *filepath = "../data/estudio.psv";
    FILE *fw = fopen(filepath, "w");
    printf("Oppening %s\n...\n", filepath);
    if (fw != NULL) {
        int size = handler->size;
        fprintf(fw, "%s", handler->header);

        for (int i = 0; i < size; ++i) {
            EST *aux = &handler->estArray[i];
            fprintf(fw, "%d|%d|%s|%d|%d|%d\n", aux->id, aux->edificio_id, aux->configuracao, aux->precoDiario_base, aux->agenda_master->id,aux->outrasHandler->id);
           // freeEstudioByPtr(aux);    //Desativei porque esta a dar erro no elemento novo criado
        }
        fclose(fw);
    } else {
        perror("ERROR OPPENING FILE");
    }
}

void saveDataEdificios(ED_LIST *list) {
    char *filepath = "../data/edfs.psv";
    FILE *fw = fopen(filepath, "w");
    printf("Oppening %s\n...\n", filepath);
    if (fw != NULL) {
        fprintf(fw, "%s", list->fHeader);
        if (list->head == NULL)
            return;
        ED *current = list->head;
        do{fprintf(fw, "%d|%s|%f|%f|%s\n", current->id, current->endereco.endereco, current->endereco.lat,current->endereco.longi, current->nome);
            edf_list_dequeue(list);
            current = list->head;
            //freeEdificioByPtr(current);
        }while (!edList_isEmpty(list));
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
        fprintf(fw, "%s\n", "dia|mes|ano|plataforma|duracao|preco|hospedeID");
        if (agenda == NULL)
            return;
        CALEND *a = agenda->calendario;
        for (int i = 0, size = agenda->size; i < size; ++i) {
           //NAO PRINTA NAO FUNCIONA
           fprintf(fw, "%d|%d|%d|%s|%d|%d|%d\n", a[i].marcacao->data.dia, a[i].marcacao->data.mes, a[i].marcacao->data.ano, a[i].marcacao->plataforma, a[i].marcacao->duracao, a[i].marcacao->preco, a[i].marcacao->hospedeID);
        }
//        freeAgendaByPtr(agenda);
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
            fprintf(fw, "%d\n", handler->agendas[i].id);
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

void saveDataHospedes(HOSP_STACK* stack) {
    FILE *fw = fopen("../data/hospedes.csv", "w");
    printf("Oppening %s\n...\n", "../data/hospedes.csv");
    if (fw != NULL) {
        fprintf(fw, "id,nome,email\n");
        if (stack == NULL) {
            printf("STACK cannot be NULL\n");
            return;
        }
        while(!hosp_isEmpty(stack)) {
            fprintf(fw, "%d,%s,%s\n", stack->head->id, stack->head->nome, stack->head->email);
            guests_list_pop(stack, stack->head);
        }
        free(stack);
        printf("Saved!\n");
        fclose(fw);
    } else {
        perror("ERROR in saveDataAgendasOutras");
    }
}