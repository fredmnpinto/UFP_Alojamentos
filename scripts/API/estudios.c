//
// Created by Frederico on 08/12/2020.
//

#include "estudios.h"

EST_HANDLER *initEstHandler(EST *array, int size) { // Finished
    EST_HANDLER *nHandler = (EST_HANDLER *) malloc(sizeof(EST_HANDLER));
    nHandler->estArray = array;
    nHandler->size = size;
    nHandler->header = "id|edificio_id|nome|agenda_master_id|outras_agendas_id\n";
    return nHandler;
}

void _freeSingleEstudio(EST_HANDLER *handler, int id) // Finished
{
    int size = handler->size;
    EST *ePtr = _findEstudioInArray(handler, id);
    if (ePtr == NULL) {
        printf("Error in _findEstudioArray(): Returning NULL\nPARAMS{handler of id %d, studio_id = %d}\n",
               handler->id, id);
        return;
    }
    free(ePtr->agenda_master->calendario);
    free(ePtr->agenda_master->path);
    ePtr->outrasHandler->free(ePtr->outrasHandler);
}

void freeEstudioByPtr(EST *ePtr) { //Finished
    free(ePtr->agenda_master->calendario);
    free(ePtr->agenda_master->path);
    ePtr->outrasHandler->free(ePtr->outrasHandler);
}

void freeEstudioArray(EST_HANDLER *handler) { // Finished
    for (int i = 0, size = handler->size; i < size; ++i) {
        freeEstudioByPtr(&handler->estArray[i]);
        handler->size--;
    }
    printf(handler->size == 0 ? NULL : "Error on freeEstudioArray(handler->id = %d)\n", handler->id);
}

EST *_findEstudioInArray(EST_HANDLER *handler, int id) // Finished
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
    }
    perror("Invalid Input\n");
    printf(" on _findEstudioArray(handler.id = %d, id = %d)\n", handler->id, id);
    return NULL;
}

void _removeEstudioFromArray(EST_HANDLER *handler, int id) { // Finished
    if (id < 1) {
        perror("Invalid id");
        printf("in _removeEstudioFromArray(handler.id = %d, id = %d)", handler->id, id);
        return;
    }

    EST *auxArr = (EST *) malloc(sizeof(EST) * (handler->size - 1));
    int index = getEstudioArrayIndex(handler, id);

    freeEstudioByPtr(&handler->estArray[index]);
    for (int i = index; i + 1 < handler->size; ++i) {
        handler->estArray[i] = handler->estArray[i + 1];
    }
}

void printEstudio(EST e) {
    printf("Id: %d\nEdificio id: %d\nAgenda master id: %d\n Agenda Handler id: %d\n Preco Base: %d\tConfiguracao: %s\n",
           e.id,
           e.edificio_id, e.agenda_master->id, e.outrasHandler->id, e.precoDiario_base, e.configuracao);
}

void _printAllEstudios(EST_HANDLER *handler) { //Finished
    for (int i = 0, size = handler->size; i < size; ++i)
        printEstudio(handler->estArray[i]);
}

int getEstudioArrayIndex(EST_HANDLER *handler, int id) { //Finished
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
    }
    perror("Invalid Input\n");
    printf("Error on getEstudioArrayIndex(handler.id = %d, id = %d)\n", handler->id, id);
    return -1;
}

EST *getEstudioAvailableFromConfig(EST_HANDLER handler, char *config) {
    int size = handler.size;
    int estsWithConfigSize = 10;
    int j = 0;
    EST *estsWithConfig = (EST *) malloc(sizeof(EST) * estsWithConfigSize);
    for (int i = 0; i < size; ++i) {
        if (strcmp(handler.estArray[i].configuracao, config) == 0) {
            if (j == estsWithConfigSize) {
                estsWithConfig += 10;
                estsWithConfig = realloc(estsWithConfig, sizeof(EST) * estsWithConfigSize);
            }
            estsWithConfig[j++] = handler.estArray[i];
        }
    }
    if (j <= 0)
        return NULL;
    EST *eClosest = &handler.estArray[0];
    DATA dClosest = getEstudioClosestAvailability(handler.estArray[0]);
    int eWithConfig = 0;
    for (int i = 0; i < size; ++i) {
        DATA dAvailable = getEstudioClosestAvailability(handler.estArray[i]);
        if (compDate(dClosest, dAvailable) > 0) {
            dClosest = dAvailable;
            eClosest = &handler.estArray[i];
            eWithConfig++;
        }
    }
    return eWithConfig > 0 ? eClosest : NULL;
}

DATA getEstudioClosestAvailability(EST estudio) {
    int size = estudio.agenda_master->size;
    AGENDA a = *estudio.agenda_master;
    DATA hoje = get_today();
    DATA closest = a.calendario[0].data;
    int dClosest = 99999;
    for (int i = 0; i < size;) {
        if (a.calendario[i].marcacao != NULL) {
            int d = howCloseToData(hoje, a.calendario[i].data);
            if (d < dClosest && d > 0) {
                dClosest = d;
                closest = a.calendario[i].data;
            }
            i += a.calendario[i].marcacao->duracao;
        } else
            i++;
    }
    return closest;
}

EST *getEstudioFromIndex(EST_HANDLER *handler, int index) {
    int size = handler->size;
    if (index > size || index < 0)
        return NULL;
    return &handler->estArray[index];
}
