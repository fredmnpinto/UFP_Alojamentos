//
// Created by Frederico on 29/11/2020.
//

#include "edificios.h"

ED_LIST * initEdList(){
    ED_LIST* queue = (ED_LIST*)malloc(sizeof(ED_LIST));
    queue->print = _edfs_list_print;
    queue->append = _edfs_list_append;
    queue->remove = _edfs_list_remove;
    queue->free_all = _edfs_list_free_all;
    queue->insert_to_front = _edfs_list_insert_to_front;
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    return queue;
}

void _edfs_list_print(ED_LIST *queue){
    ED *tmp = queue->head;
    while(tmp != NULL){
        printEdificio(*tmp);
        tmp = tmp->next;
    }
}

void _edfs_list_append(ED_LIST* queue, ED* edificio){
    if(queue->head == NULL) {
        queue->head = edificio;
        queue->tail = edificio;
    }else{
        queue->tail->next = edificio;
        edificio->next = NULL;
        queue->tail = edificio;
    }
    queue->size++;
}

void edf_list_dequeue(ED_LIST* queue) {
    if(!edList_isEmpty(queue)) {
        ED* elementToRemove = queue->head;
        queue->head = elementToRemove->next;
        queue->size--;
        free(elementToRemove->endereco.endereco);
        free(elementToRemove->nome);
        free(elementToRemove);
    }
}

void _edfs_list_remove(ED_LIST* queue, ED* edificio){
    ED* current = queue->head;
    while(current != NULL){
        if(current->next->id == edificio->id){
            ED* to_be_deleted = current->next;
            current->next = current->next->next;
            free(edificio);
            free(to_be_deleted);
            queue->size--;
            return;
        }
        current = current->next;
    }
    printf("404 - Edificio Not Found withing the list\n");
}

void _edfs_list_free_all(ED_LIST* queue){
    ED* current = queue->head;
    ED* _next;
    while(current != NULL){
        _next = current->next;
        free(current);
        current = _next;
    }
    if (queue->head == NULL && queue->tail == NULL) // Checar se tail faz free() ja ou se precisa fazer manualmente
        printf("List has been freed\n");
    else
        printf("Error freeing the list\n");
    queue->size=0;
}

void _edfs_list_insert_to_front(ED_LIST *list, ED *edificio) {
//    ED* prior_head = list->head;
    edificio->next = list->head;
    list->head = edificio;
    list->size++;
}

void freeEdificioByPtr(ED *ed) {
    if (ed == NULL)
        return;
    free(ed->endereco.endereco);
    free(ed->nome);
    free(ed);
}

ED* getEdificioFromID(ED_LIST* queue, int id) {
    ED* node = queue->head;
    while(node != NULL){
        if (node->id == id)
            return node;
        node = node->next;
    }
//    printf("Edificio with ID=%d was not found", id);
    return NULL;
}

ED* getEdifcioFromName(ED_LIST* list, char* name){
    ED* node = list->head;
    char* nameLo = toLowerStr(name);
    while (node != NULL){
        char* nodeNameLower = toLowerStr(node->nome);
        if (strcmp(nodeNameLower, nameLo) == 0){
            return node;
        }
        free(nodeNameLower);
        node = node->next;
    }
    free(nameLo);
    return NULL;
}

void printEdificio(ED edificio){
    printf("\nId: %d\nNome: %s\nEndereco: %s\t(lat: %f longi: %f)\n", edificio.id, edificio.nome, edificio.endereco.endereco, edificio.endereco.lat, edificio.endereco.longi);
}

int return_edList_size(ED_LIST* queue) {
    return queue->size;
}

int edList_isEmpty(ED_LIST* queue) {
    return queue->size==0;
}