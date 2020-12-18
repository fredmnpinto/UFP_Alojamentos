//
// Created by Frederico on 08/12/2020.
//

#include "estudios.h"

EST_HANDLER *initEstHandler(EST *array, int size) { // Finished
    EST_HANDLER *nHandler = (EST_HANDLER *) malloc(sizeof(EST_HANDLER));
    nHandler->estArray = array;
    nHandler->size = size;
    nHandler->header = "id|edificio_id|nome|agenda_master_id|outras_agendas_id\n";
    nHandler->freeSingle = _freeSingleEstudio;
    return nHandler;
}

void _freeSingleEstudio(EST_HANDLER *handler, int id, char *nome) // Finished
{
    int size = handler->size;
    EST *ePtr = _findEstudioInArray(handler, id, nome);
    if (ePtr == NULL) {
        printf("Error in _findEstudioArray(): Returning NULL\nPARAMS{handler of id %d, studio_id = %d, nome = %s}\n",
               handler->id, id, nome);
        return;
    }
    free(ePtr->agenda_master->marcacoes);
    free(ePtr->agenda_master->nome);
    free(ePtr->agenda_master->path);
    free(ePtr->nome);
    ePtr->outrasHandler->free(ePtr->outrasHandler);
}

void freeEstudioByPtr(EST *ePtr) { //Finished
    free(ePtr->agenda_master->marcacoes);
    free(ePtr->agenda_master->nome);
    free(ePtr->agenda_master->path);
    free(ePtr->nome);
    ePtr->outrasHandler->free(ePtr->outrasHandler);
}

void freeEstudioArray(EST_HANDLER *handler) { // Finished
    for (int i = 0, size = handler->size; i < size; ++i) {
        freeEstudioByPtr(&handler->estArray[i]);
        handler->size--;
    }
    printf(handler->size == 0 ? NULL : "Error on freeEstudioArray(handler->id = %d)\n", handler->id);
}

EST *_findEstudioInArray(EST_HANDLER *handler, int id, char *nome) // Finished
{
    if (id > -1) {
        int size = handler->size;
        int hi = size;
        int lo = 0;
        while (1) {
            int mid = (hi + lo) / 2;
            if (handler->estArray[mid].id > id)
                lo = mid;
            else if (handler->estArray[mid].id < id)
                hi = mid;
            else
                return &handler->estArray[mid];
        }
    } else if (nome != NULL) {
        int size = handler->size;
        for (int i = 0; i < size; ++i) {
            if (strcmp(nome, handler->estArray[i].nome) == 0)
                return &handler->estArray[i];
        }
        printf("Estudio Not Found: %s\n", nome);
        return NULL;
    }
    perror("Invalid Input\n");
    printf(" on _findEstudioArray(handler.id = %d, id = %d, nome = %s)\n", handler->id, id, nome);
    return NULL;
}

void _removeEstudioFromArray(EST_HANDLER *handler, int id, char *nome) { // Finished
    if (id < 1) {
        perror("Invalid id");
        printf("in _removeEstudioFromArray(handler.id = %d, id = %d, name = %s)", handler->id, id, nome);
        return;
    }
    EST *auxArr = (EST *) malloc(sizeof(EST) * (handler->size - 1));
    int index = getEstudioArrayIndex(handler, id, nome);
    freeEstudioByPtr(&handler->estArray[index]);
    memcpy(auxArr, handler->estArray, sizeof(EST) * (index + 1));
    memcpy(auxArr + index + 1, handler->estArray + index + 1, sizeof(EST) * (handler->size - index));
    int newSize = handler->size - 1;
    freeEstudioArray(handler);
    handler->estArray = auxArr;
    handler->size = newSize;
}

void printEstudio(EST e) {
    printf("Nome: %s\tId: %d\nEdificio id: %d\nAgenda master id: %d\n Agenda Handler id: %d\n", e.nome, e.id,
           e.edificio_id, e.agenda_master->id, e.outrasHandler->id);
}

void _printAllEstudios(EST_HANDLER *handler) { //Finished
    for (int i = 0, size = handler->size; i < size; ++i)
        printEstudio(handler->estArray[i]);
}

int getEstudioArrayIndex(EST_HANDLER *handler, int id, char *nome) { //Finished
    if (id > -1) {
        int size = handler->size;
        int hi = size;
        int lo = 0;
        while (1) {
            int mid = (hi + lo) / 2;
            if (handler->estArray[mid].id > id)
                lo = mid;
            else if (handler->estArray[mid].id < id)
                hi = mid;
            else
                return mid;
        }
    } else if (nome != NULL && strcmp(nome, "") != 0) {
        int size = handler->size;
        for (int i = 0; i < size; ++i) {
            if (strcmp(nome, handler->estArray[i].nome) == 0)
                return i;
        }
        printf("Estudio Not Found: %s\n", nome);
        return -1;
    }
    perror("Invalid Input\n");
    printf("Error on getEstudioArrayIndex(handler.id = %d, id = %d)\n", handler->id, id);
    return -1;
}
